#!/usr/bin/env python3

#communication variables ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
import serial
import time
import numpy as np

recieve_tag = 666
recieved_var1=0
recieved_var2=0
recieved_var3=0

send_tag = 555
send_var_1 = 669
send_var_2 = 8899.123
send_var_3 = 100

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.flush()
#communication variables eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee

#communication functions SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
def update_recieved_variables(ser):
    global recieved_var1
    global recieved_var2
    global recieved_var3

    if(ser.in_waiting > 0):
        try:
            input_string = ser.readline().decode("ASCII")
            word = input_string[:-1]
            input_array =(word.split(','))
            x = np.array(input_array)
            float_array=x.astype(np.float)
            tag=int(float_array[0])
            
            if(tag==recieve_tag):
                recieved_var1=float_array[1]
                recieved_var2=float_array[2]
                recieved_var3=float_array[3]
        except:
            pass
#communication functions eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee


def send_send_variables(ser):
        string = str(send_tag ) +"," +str(send_var_1) + "," +str(send_var_2) + "," + str(send_var_3) +"\n"
        # print(string)
        message = bytes(string, 'utf-8')
        ser.write(message)
        time.sleep(.01) #without this the recieved values keeps fluctuating


if __name__ == '__main__':

    while True:

        send_send_variables(ser)
        update_recieved_variables(ser)
        print(recieved_var3)
        




