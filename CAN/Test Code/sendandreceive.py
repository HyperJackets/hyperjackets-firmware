import can

def send():
    message = can.Message(arbitration_id = 123, is_extended_id = True, data = [1, 2, 3])
    bus.send(message)
    
def receive():
    for msg in bus:
        # print("Waiting on message")
        print(f"{msg.arbitration_id}: {msg.data}")
        # need_msg = can.Message(arbitration_id = 123)
        # if msg.arbitration_id == need_msg.arbitration_id:
        #     print(f"{msg.arbitration_id}: {msg.data}")
        #     break
    
if __name__ == "__main__":
    bus = can.Bus(bustype = 'socketcan', channel = 'can1', receive_own_messages = True)
    # send()
    receive()
