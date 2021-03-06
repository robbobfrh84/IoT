import serial
ser = serial.Serial('/dev/cu.usbserial-01D23684', 115200)
ser.flushInput()

while True:
    line = ser.readline()
    print(line)
    # decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
    # print(decoded_bytes)
    # try:
    #     ser_bytes = ser.readline()
    #     decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
    #     print(decoded_bytes)
    # except:
    #     print("Keyboard Interrupt")
    #     break
