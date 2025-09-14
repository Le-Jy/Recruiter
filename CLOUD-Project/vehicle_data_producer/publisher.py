import time
import random

from paho.mqtt import client as mqtt_client
from vehicles import Vehicles
from mqtt_protocol import Protocol1, Protocol2, Protocol3
from threading import Thread


"""
The Publisher class is responsible for publishing messages to an MQTT broker.
It uses the paho-mqtt library to connect to the broker and publish messages.
The Publisher class has the following attributes:
    - client_name: Name of the MQTT client
    - topic_name: Name of the MQTT topic
    - broker: Address of the MQTT Broker
    - port: Port of the MQTT Broker
    - login: Login for the MQTT Broker
    - password: Password for the MQTT broker
    - message_rate_second: Rate of messages per second
    - nb_messages: Number of messages to send
    - vehicles: List of vehicles to simulate
"""
class Publisher(Thread):
    def __init__(self, client_name, topic_name, broker, port, login, password, message_rate_second, nb_messages, vehicles):
        super().__init__()
        self.client_name = client_name
        self.topic_name = topic_name
        self.broker = broker
        self.port = port
        self.login = login
        self.password = password
        self.message_rate_second = message_rate_second
        self.nb_messages = nb_messages
        self.vehicles = self.get_vehicles(vehicles)

    def run(self):
        print(f"""clent_name: {self.client_name}
        topic_name: {self.topic_name}
        broker: {self.broker}
        port: {self.port}
        login: {self.login}
        password: {self.password}
        message_rate_second = {self.message_rate_second}
        """)
        # Create and configure MQTT client
        self.client = mqtt_client.Client(self.client_name)
        self.client.username_pw_set(self.login, self.password)
        self.client.on_connect = self.on_connect

        self.client.connect(self.broker, self.port)
        self.client.loop_start()
        print("Connecting to MQTT Broker...")

        # Start publishing automatically
        self.publish_messages()
        time.sleep(1)
        self.client.loop_stop()
        self.client.disconnect()

    def get_vehicles(self, vehicles):
        return [Vehicles(**v) for v in vehicles]

    def on_connect(self, client, userdata, flags, rc):
        if rc == 0:
            print(f"[{self.client_name}] Connected to MQTT Broker!")
        else:
            print(f"[{self.client_name}] Connection failed with code {rc}")

    def simulate_vehicle_payload(self, vehicle: Vehicles, vin: str):
        if (vehicle.protocol != 3):
            lat = vehicle.initial_lat + random.uniform(-0.0005, 0.0005)
            lon = vehicle.initial_long + random.uniform(-0.0005, 0.0005)
        if isinstance(vehicle.speed_interval, list) and len(vehicle.speed_interval) == 2:
            speed = random.uniform(*vehicle.speed_interval)
        else:
            speed = 0.0
        if isinstance(vehicle.consumption_interval, list) and len(vehicle.consumption_interval) == 2:
            consumption = random.uniform(*vehicle.consumption_interval)
        else:
            consumption = 0.0
        passenger_count = random.randint(*vehicle.pnb_interval)
        if (vehicle.protocol != 3):
            gear = random.randint(*vehicle.gearbox_interval) if vehicle.gearbox_interval else 1
        timestamp = int(time.time())

        if vehicle.protocol == 1:
            return {
                "vin": vin,
                "latitude": round(lat, 5),
                "longitude": round(lon, 5),
                "speed": round(speed, 1),
                "timestamp": timestamp,
                "passenger_count": passenger_count,
                "consumption": round(consumption, 1),
                "gear": gear
            }

        elif vehicle.protocol == 2:
            messages = []
            for msg_type in vehicle.message_types:
                base = {
                    "id": vin,
                    "msg": msg_type,
                    "ts": timestamp
                }

                if msg_type == vehicle.pnb_message_type:
                    base["pnb"] = passenger_count
                elif msg_type == 14:
                    base["lat"] = round(lat, 5)
                    base["long"] = round(lon, 5)
                    base["r"] = round(consumption, 1)
                elif msg_type == 56:
                    base["a"] = round(speed, 1)
                    base["v"] = gear
                    base["c"] = round(consumption, 1)

                messages.append(base)

        elif vehicle.protocol == 3:
            return {
                    "vin": vin,
                    "timestamp": timestamp,
                    "speed": round(speed, 1),
                    "passenger_count": passenger_count,
                    "consumption": round(consumption, 1),
                    "vehid": ""
                    }

        return messages


    def publish_messages(self):
        interval = self.message_rate_second
        success_send = 0
        fail_send = 0

        for msg_count in range(self.nb_messages):
            print(f"\n📤 Message batch {msg_count + 1}/{self.nb_messages}")
            for vehicle in self.vehicles:
                for vin in vehicle.ids:
                    payload = self.simulate_vehicle_payload(vehicle, vin)

                    if vehicle.protocol == 1:
                        message = Protocol1(**payload).create_frame()
                        result = self.client.publish(self.topic_name, message)
                        if result.rc == mqtt_client.MQTT_ERR_NO_CONN:
                            print(f"⚠️ Error: {result.rc}")
                            fail_send += 1
                        else:
                            print(f"[{self.client_name}] ➡ Sent: {message}")
                            success_send += 1

                    elif vehicle.protocol == 2:
                        for msg_payload in payload:
                            try:
                                message = Protocol2(**msg_payload).create_frame()
                                result = self.client.publish(self.topic_name, message)
                                if result.rc == mqtt_client.MQTT_ERR_NO_CONN:
                                    print(f"⚠️ Error: {result.rc}")
                                    fail_send += 1
                                else:
                                    print(f"[{self.client_name}] ➡ Sent: {message}")
                                    success_send += 1
                            except ValueError as ve:
                                print(f"⚠️ Error in message: {ve}")
                                fail_send += 1

                    elif vehicle.protocol == 3:
                        message = Protocol3(**payload).create_frame()
                        result = self.client.publish(self.topic_name, message)

                        if result.rc == mqtt_client.MQTT_ERR_NO_CONN:
                            print(f"⚠️ Error: {result.rc}")
                            fail_send += 1
                        else :
                            print(f"[{self.client_name}] ➡ Sent: {message}")
                            success_send += 1
            time.sleep(interval)

        print(f"\n📊 Summary: {success_send} messages sent successfully, {fail_send} failed.")
