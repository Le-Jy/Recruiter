import sys
from PySide6 import QtCore, QtWidgets, QtGui
from data_producer import JsonReader


class EmittingStream(QtCore.QObject):
    text_written = QtCore.Signal(str)

    def write(self, text):
        self.text_written.emit(str(text))

    def flush(self):
        pass

"""
HMI class to edit the JSON file, save it and start the simulation
"""
class CodeEditorApp(QtWidgets.QWidget):
    def __init__(self, file_path):
        super().__init__()
        self.file_path = file_path
        self.setWindowTitle("Telematic Frame Simulator")

        self.editor = QtWidgets.QTextEdit()
        self.log_output = QtWidgets.QTextEdit()
        self.log_output.setReadOnly(True)

        self.load_file(self.file_path)
        self.reader = None

        self.fetch_MQTT_button = QtWidgets.QPushButton("Generate MQTT Frames")
        self.fetch_MQTT_button.clicked.connect(self.fetch_MQTT_code)

        self.fetch_REST_button = QtWidgets.QPushButton("Generate REST POST Requests")
        self.fetch_REST_button.clicked.connect(self.fetch_REST_code)

        self.save_button = QtWidgets.QPushButton("Save configuration")
        self.save_button.clicked.connect(self.save_code)

        # Layouts
        main_layout = QtWidgets.QHBoxLayout()
        editor_layout = QtWidgets.QVBoxLayout()
        editor_layout.addWidget(self.editor)
        editor_layout.addWidget(self.save_button)
        editor_layout.addWidget(self.fetch_MQTT_button)
        editor_layout.addWidget(self.fetch_REST_button)

        main_layout.addLayout(editor_layout)
        main_layout.addWidget(self.log_output)

        self.setLayout(main_layout)
        self.resize(1000, 600)

        # Redirect stdout
        sys.stdout = EmittingStream(text_written=self.append_log)
        sys.stderr = EmittingStream(text_written=self.append_log)

    """
    Append text to the log output widget
    """
    def append_log(self, text):
        self.log_output.moveCursor(QtGui.QTextCursor.End)
        self.log_output.insertPlainText(text)

    """
    Load the JSON file in the editor
    """
    def load_file(self, path):
        try:
            with open(path, 'r') as f:
                content = f.read()
                self.editor.setText(content)
        except Exception as e:
            QtWidgets.QMessageBox.critical(self, "Error", f"Failed to load file:\n{e}")

    """
    Fetch the code from the editor and start the simulation
    """
    def fetch_MQTT_code(self):
        code = self.editor.toPlainText()
        try:
            self.reader = JsonReader()
            self.reader.read_from_string(code)
            print("[INFO] Code content fetched successfully!")

            self.reader.publisher.start()

        except Exception as e:
            print(f"[ERROR] {e}")
            QtWidgets.QMessageBox.critical(self, "Error", f"Failed to write file:\n{e}")
    
    """
    Fetch the code from the editor and start the simulation
    """
    def fetch_REST_code(self):
        code = self.editor.toPlainText()
        try:
            self.reader = JsonReader()
            self.reader.read_from_string(code)
            print("[INFO] Code content fetched successfully!")

            self.reader.rest.start()

        except Exception as e:
            print(f"[ERROR] {e}")
            QtWidgets.QMessageBox.critical(self, "Error", f"Failed to write file:\n{e}")


    """
    Save the code from the editor to the file
    """
    def save_code(self):
        code = self.editor.toPlainText()
        try:
            with open(self.file_path, 'w') as f:
                f.write(code)
            print("[INFO] Code content saved successfully!")
        except Exception as e:
            print(f"[ERROR] {e}")
            QtWidgets.QMessageBox.critical(self, "Error", f"Failed to write file:\n{e}")

    """
    Close the application and stop the simulation
    Wait for the publisher thread to finish
    """
    def destroy(self):
        if (self.reader.publisher and self.reader.publisher.is_alive()):
            self.reader.publisher.join()

        super().destroy()

