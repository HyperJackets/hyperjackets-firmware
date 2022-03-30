import can, datetime

def receive():
    # Test different bitrates
    bus = can.interface.Bus(bustype = 'socketcan', channel = 'can1', bitrate = 125000) # initializes a bus instance to read from CAN1
    start_time = datetime.datetime.now()
    count = 0
    for msg in bus: # iterates over messages in bus
        count += 1
        print('Received #:', msg.data[0], ' ', 'Found #:', count, ' ', 'Time taken (ms):', msg.data[1])
        if count == 10000:
            elapsed = datetime.datetime.now() - start_time
            print('Time elapsed for 10000 messages(seconds):', elapsed)
            start_time = datetime.datetime.now()
        
if __name__ == "__main__":
    receive()
