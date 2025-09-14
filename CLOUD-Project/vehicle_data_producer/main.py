import sys
from ihm import CodeEditorApp
from PySide6 import QtWidgets
from data_producer import JsonReader

"""
The simulation can be run in two mode:
    - Interactive mode: run the HMI to edit the JSON file
    - Command line mode: run the JSON reader to read the JSON file and publish the data
"""
if __name__ == "__main__":
    if  (len(sys.argv) == 1):
        app = QtWidgets.QApplication(sys.argv)

        default_file = "./ssie_vehicles_data.json"
        editor_window = CodeEditorApp(default_file)
        editor_window.show()

        sys.exit(app.exec())

    elif (len(sys.argv) == 2):
        reader = JsonReader(sys.argv[1])
        reader.read()

        reader.publisher.start()
        reader.publisher.join()

        reader.rest.start()
        reader.rest.join()

    else:
        print("Usage: python main.py [path_to_json_file]")
        sys.exit(1)

