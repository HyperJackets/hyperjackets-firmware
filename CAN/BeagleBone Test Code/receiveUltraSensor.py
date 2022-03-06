import can

def receive():
    bus = can.interface.Bus(bustype = 'socketcan', channel = 'can1', bitrate = 125000) # initializes a bus instance to read from CAN1
    for msg in bus: # iterates over messages in bus
        print(msg.data[0]) # prints out messages 
if __name__ == "__main__":
    receive()
