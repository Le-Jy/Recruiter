import json
from publisher import Publisher
from rest import Rest
from io import StringIO

"""
This module is responsible for reading the JSON file and initializing the Publisher and Rest classes.
It uses the json module to parse the JSON file and extract the relevant data.
The JsonReader class has two methods:
    - read: reads the JSON file and initializes the Publisher and Rest classes
    - read_from_string: reads a JSON string and initializes the Publisher and Rest classes
"""
class JsonReader:
    
    def __init__(self, file_path="ssie_vehicles_data.json"):
        self.file_path = file_path
        self.publisher = None
        self.rest = None

    def read(self):
        f = open(self.file_path)
        data = json.load(f)

        self.publisher = Publisher(**data['mqtt'])
        self.rest = Rest(**data['rest'])

    def read_from_string(self, code):
        json_file_like = StringIO(code)
        data = json.load(json_file_like)

        self.publisher = Publisher(**data['mqtt'])
        self.rest = Rest(**data['rest'])
