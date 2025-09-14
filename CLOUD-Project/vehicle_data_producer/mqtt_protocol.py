import re

"""
The Protocol1 class is used to create a message frame for a specific protocol, while the Protocol2 class is used to create a message frame for another protocol. The Message class is a base class for creating message frames, and the Message125, Message14, and Message56 classes are subclasses of the Message class that define specific message types.
The Protocol1 class has the following attributes:
    - vin: Vehicle Identification Number
    - latitude: Latitude of the vehicle
    - longitude: Longitude of the vehicle
    - speed: Speed of the vehicle
    - timestamp: Timestamp of the message
    - passenger_count: Number of passengers in the vehicle
    - consumption: Fuel consumption of the vehicle
    - gear: Gear of the vehicle
"""
class Protocol1:
    def __init__(self, vin, latitude, longitude, speed, timestamp, passenger_count, consumption, gear):
        self.separator = "|"
        self.acceptance_regex = r"^[A-Z0-9.]*$"
        self.vin = vin
        self.latitude = latitude
        self.longitude = longitude
        self.speed = speed
        self.timestamp = timestamp
        self.passenger_count = passenger_count
        self.consumption = consumption
        self.gear = gear


    def check_acceptance(self):
        foreach = [self.vin, self.latitude, self.longitude, self.speed, self.timestamp, self.passenger_count, self.consumption, self.gear]
        for item in foreach:
            if not re.match(self.acceptance_regex, str(item)):
                raise ValueError(f"Invalid value for {item}. Expected format: {self.acceptance_regex}")

    def create_frame(self):
        self.check_acceptance()
        frame = f"{self.vin}{self.separator}{self.latitude}{self.separator}{self.longitude}{self.separator}{self.speed}{self.separator}{self.timestamp}{self.separator}{self.passenger_count}{self.separator}{self.consumption}{self.separator}{self.gear}"

        return frame


"""
The Protocol2 class is used to create a message frame for a specific protocol, while the Message class is a base class for creating message frames, and the Message125, Message14, and Message56 classes are subclasses of the Message class that define specific message types.
The Protocol2 class has the following attributes:
    - id: ID of the message
    - msg: Message type
    - ts: Timestamp of the message
    - pnb: Passenger count
    - lat: Latitude of the vehicle
    - long: Longitude of the vehicle
    - r: Speed of the vehicle
    - a: Acceleration of the vehicle
    - v: Vehicle status
    - c: Consumption of the vehicle
"""
class Protocol2:
    def __init__(self, id, msg, ts, pnb=None, lat=None, long=None, r=None, a=None, v=None, c=None):
        if (msg == 125):
            self.message = Message125(id, msg, ts, pnb)
        elif (msg == 14):
            self.message = Message14(id, msg, ts, lat, long, r)
        elif (msg == 56):
            self.message = Message56(id, msg, ts, a, v, c)
        else:
            raise ValueError(f"Message not supported: {msg}. Expected one of: 125, 14, 56")

    def create_frame(self):
            return self.message.create_frame()

class Message:
    def __init__(self, id, msg, ts):
        self.separator = ";"
        self.acceptance_regex = r"^[A-Za-z0-9.]*$"
        self.id = id
        self.msg = msg
        self.ts = ts

    def check_acceptance(self):
        for item in [self.id, self.msg, self.ts]:
            if not re.match(self.acceptance_regex, str(item)):
                raise ValueError(f"Invalid value for {item}. Expected format: {self.acceptance_regex}")


    def create_frame(self):
        self.check_acceptance()
        frame = f"id={self.id}{self.separator}msg={self.msg}{self.separator}ts={self.ts}"

        return frame

class Message125(Message):
    def __init__(self, id, msg, ts, pnb):
        super().__init__(id, msg, ts)
        self.pnb = pnb

    def create_frame(self):
        frame = f"{super().create_frame()}{self.separator}pnb={self.pnb}{self.separator}"

        return frame

class Message14(Message):
    def __init__(self, id, msg, ts, lat, long, r):
        super().__init__(id, msg, ts)
        self.lat = lat
        self.long = long
        self.r = r

    def create_frame(self):
        frame = f"{super().create_frame()}{self.separator}lat={self.lat}{self.separator}long={self.long}{self.separator}r={self.r}{self.separator}"

        return frame

class Message56(Message):
    def __init__(self, id, msg, ts, a, v, c):
        super().__init__(id, msg, ts)
        self.a = a
        self.v = v
        self.c = c

    def create_frame(self):
        frame = f"{super().create_frame()}{self.separator}a={self.a}{self.separator}v={self.v}{self.separator}c={self.c}{self.separator}"

        return frame

"""
The Protocol1 class is used to create a message frame for a specific protocol, while the Protocol2 class is used to create a message frame for another protocol. The Message class is a base class for creating message frames, and the Message125, Message14, and Message56 classes are subclasses of the Message class that define specific message types.
The Protocol1 class has the following attributes:
    - vin: Vehicle Identification Number
    - latitude: Latitude of the vehicle
    - longitude: Longitude of the vehicle
    - speed: Speed of the vehicle
    - timestamp: Timestamp of the message
    - passenger_count: Number of passengers in the vehicle
    - consumption: Fuel consumption of the vehicle
    - gear: Gear of the vehicle
"""
class Protocol3:
    def __init__(self, vin, timestamp, speed, passenger_count, consumption, vehid):
        self.separator = "%"
        self.acceptance_regex = r"^[A-Z0-9.]*$"
        self.vin = vin
        self.timestamp = timestamp
        self.speed = speed
        self.passenger_count = passenger_count
        self.consumption = consumption
        self.vehid = vehid

    def check_acceptance(self):
        vehid_regex = r"VF7VSIETLS[0-9]{7}"
        if not re.match(vehid_regex, str(self.vin)):
            raise ValueError(f"Invalid VIN")
        self.vehid = self.vin[(len(self.vin) - 6):len(self.vin)];
        foreach = [self.vin, self.speed, self.timestamp, self.passenger_count, self.consumption]
        for item in foreach:
            if not re.match(self.acceptance_regex, str(item)):
                raise ValueError(f"Invalid value for {item}. Expected format: {self.acceptance_regex}")

    def create_frame(self):
        self.check_acceptance()
        frame = f"{self.separator}{self.vehid}{self.separator}{self.timestamp}{self.separator}{self.speed}{self.separator}{self.passenger_count}{self.separator}{self.consumption}{self.separator}"
        return frame
