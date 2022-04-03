import can, datetime

def receive():
    # Test different bitrates
    bus = can.interface.Bus(bustype = 'socketcan', channel = 'can1', bitrate = 125000) # initializes a bus instance to read from CAN1
    start_time = datetime.datetime.now()
    count = 0
    errors = 0
    prev = 255
    for msg in bus: # iterates over messages in bus
        count += 1
        payload = msg.data[0]
        # Out of order only applies for numbers that aren't wrapping back to 0
        if (prev != (payload - 1)%256): # if the next data is not equal to the previous one, we know the data arrived out of order
            # Make an array of out of order packets
            print('Out of order packets', prev, 'and', payload)
            errors += 1
        prev = payload
        # print('Received #:', msg.data[0], ' ', 'Found #:', count, ' ', 'Time taken (ms):', msg.data[1])
        if count == 10000:
            elapsed = datetime.datetime.now() - start_time
            print('Time elapsed for 10000 messages(seconds):', elapsed)
            print('Number of out of order packets:', errors)
            start_time = datetime.datetime.now()
            count = 0
            errors = 0
        
if __name__ == "__main__":
    receive()
