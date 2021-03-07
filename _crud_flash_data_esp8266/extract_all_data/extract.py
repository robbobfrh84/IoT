import serial, os, shutil
ser = serial.Serial('/dev/cu.usbserial-01D23684', 115200)
ser.flushInput()

goForIt = "y"
try:
    os.mkdir("extracted_data")
except:
    print("extracted_data folder already exits.")
    goForIt = raw_input("Would you like to remove the old data for the new? (y/n)")

file = False
if (goForIt == "y"):
    shutil.rmtree("extracted_data")
    os.mkdir("extracted_data")
    while True:
        line = ser.readline()
        flagValue = line.split(":")
        print(line)
        if (flagValue[0] == "<!end!>"):
            if (file):
                file.close()
            break
        if (flagValue[0] == "<!filename!>"):
            if (file):
                file.close()
            file = open("extracted_data"+flagValue[1].rstrip(), 'w')
        elif (file):
            file.write(line)
else:
    print("\nprogram canceled.\n")
