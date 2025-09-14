"""
This module defines a class for vehicles that can be used in a simulation. The class includes attributes for vehicle type, protocol, message types, and other parameters related to the vehicle's behavior in the simulation.
The Vehicles class has the following attributes:
    - vehicle_type: Type of the vehicle (e.g., car, bus, etc.)
    - protocol: Protocol used for communication (e.g., MQTT, REST, etc.)
    - message_types: List of message types used in the simulation
    - pnb_message_type: Type of message for passenger count
    - pnb_interval: Interval for passenger count
    - initial_lat: Initial latitude of the vehicles
    - initial_long: Initial longitude of the vehicles
    - speed_interval: Interval for vehicle speed
    - consumption_interval: Interval for vehicle consumption
    - ids: List of vehicle IDs
    - gearbox_interval: Interval for vehicle gearbox
"""
class Vehicles:
    def __init__(self, ids, pnb_interval, vehicle_type=None, protocol=None, initial_lat=None, initial_long=None, speed_interval=None, consumption_interval=None, message_types=None, pnb_message_type=None, gearbox_interval=None) -> None:
        self.vehicle_type = vehicle_type
        self.protocol = protocol
        self.message_types = message_types
        self.pnb_message_type = pnb_message_type
        self.pnb_interval = pnb_interval
        self.initial_lat = initial_lat
        self.initial_long = initial_long
        self.gearbox_interval = gearbox_interval
        self.speed_interval = speed_interval
        self.consumption_interval = consumption_interval
        self.ids = ids


    def display(self):
        print(f"Vehicle type: {self.vehicle_type}, Protocol: {self.protocol}, PNB Interval: {self.pnb_interval}, Initial Lat: {self.initial_lat}, Initial Long: {self.initial_long}, Speed Interval: {self.speed_interval}, Consumption Interval: {self.consumption_interval}, IDs: {self.ids}")
