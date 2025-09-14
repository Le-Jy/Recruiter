from vehicles import Vehicles
from threading import Thread
import requests
import time
import random

"""
This module is responsible for the REST API configuration.
It uses the requests library to send HTTP requests to the REST API.
The Rest class has the following attributes:
    - url: URL of the REST API
    - message_rate_second: Rate of messages per second
    - nb_messages: Number of messages to send
    - vehicles: List of vehicles to simulate

It is not used yet.
"""
class Rest(Thread):
    def __init__(self, url, message_rate_second, nb_messages, vehicles):
        super().__init__()
        self.url = url
        self.message_rate_second = message_rate_second
        self.nb_messages = nb_messages

        self.vehicles = self.get_vehicles(vehicles)

    def run(self):
        # Start publishing automatically
        self.publish_messages()

    def get_vehicles(self, vehicles):
        v = []
        for vehicle in vehicles:
            v.append(Vehicles(**vehicle))

        return v

    def publish_messages(self):
        message_num = 0
        delay = 1 / self.message_rate_second if self.message_rate_second > 0 else 0
        for v in self.vehicles:
            pnb_interval = v.pnb_interval;
            for ids in v.ids:
                try:
                    response = requests.post(
                            self.url,
                            json={'vehicleId': ids, 'localTime': int(time.time()), 'passengerNumber': int(random.uniform(*pnb_interval))},
                            headers={'Content-Type':'application/json'}
                            )
                    if response.status_code == 200:
                        print(f"✓ Message {message_num + 1} sent for vehicle {ids} - Status: {response.status_code}")
                    else:
                        print(f"✗ Message {message_num + 1} failed for vehicle {ids} - Status: {response.status_code}")

                except requests.exceptions.RequestException as e:
                    print(f"✗ Error sending message {message_num + 1} for vehicle {ids}: {e}")

            # Wait between messages to respect the rate limit
            if delay > 0:
                time.sleep(delay)


    def display(self):
        for vehicle in self.vehicles:
            print(f"URL: {self.url}, Message Rate Second: {self.message_rate_second}, Number of Messages: {self.nb_messages}, Vehicles: {vehicle.display()}")
