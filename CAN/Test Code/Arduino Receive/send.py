import can

def send_one():
   bus = can.interface.Bus(bustype = 'socketcan', channel = 'can1', bitrate = 125000)
   msg = can.Message(arbitration_id=0xC0FFEE, data = [0, 25, 0, 1, 3, 1, 4, 1], is_extended_id = True)
   try:
      bus.send(msg)
      print(f"Message sent on {bus.channel}")
   except can.CanError:
      print("Message NOT sent")
         
if __name__ == "__main__":
   send_one()
