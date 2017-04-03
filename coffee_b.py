                                                                                                                                                                                               
                                                                                                                                                                                               
import serial                                                                                                                                                                                  
import os                                                                                                                                                                                      
import time                                                                                                                                                                                    
import json, httplib                                                                                                                                                                           
import mraa                                                                                                                                                                                    
                                                                                                                                                                                               
pin = mraa.Gpio(17)                                                                                                                                                                            
pin.dir(mraa.DIR_OUT)                                                                                                                                                                          
pin_boot = mraa.Gpio(16)                                                                                                                                                                       
pin_boot.dir(mraa.DIR_OUT)                                                                                                                                                                     
                                                                                                                                                                                               
#pin_boot.write(1)                                                                                                                                                                             
                                                                                                                                                                                               
def get_serial_data():                                                                                                                                                                         
        serial_data = ser.readline().strip('\r\n')                                                                                                                                             
        return serial_data                                                                                                                                                                     
                                                                                                                                                                                               
flag = False                                                                                                                                                                                   
requestFlag = False                                                                                                                                                                            
                                                                                                                                                                                               
def post_data(val):                                                                                                                                                                            
        global flag                                                                                                                                                                            
        global requestFlag                                                                                                                                                                     
        if val == "1" and flag == False:                                                                                                                                                       
                flag = True                                                                                                                                                                    
                requestFlag = True                                                                                                                                                             
        elif val == "1" and flag == True:                                                                                                                                                      
                requestFlag = False                                                                                                                                                            
        elif val == "0" and flag == True:                                                                                                                                                      
                flag = False                                                                                                                                                                   
                requestFlag = False                                                                                                                                                            
        #elif val == 0 and flag == 0:                                                                                                                                                          
                #coffee is full, delivery complete                                                                                                                                             
        print "Sensor value: " + val                                                                                                                                                           
        #print flag                                                                                                                                                                            
                                                                                                                                                                                               
def command():                                                                                                                                                                                 
        print "Request made"                                                                                                                                                                   
        indicator()                                                                                                                                                                            
        time.sleep(2)                                                                                                                                                                          
                                                                                                                                                                                               
def indicator():                                                                                                                                                                               
        pin.write(1)                                                                                                                                                                           
        time.sleep(1)                                                                                                                                                                          
        pin.write(0)                                                                                                                                                                           
        time.sleep(1)                                                                                                                                                                          
        print "-----ON------"                                                                                                                                                                  
                                                                                                                                                                                               
                                                                                                                                                                                               
def main():                                                                                                                                                                                    
        while True:                                                                                                                                                                            
                sensor_val = get_serial_data()                                                                                                                                                 
                post_data(sensor_val)                                                                                                                                                          
                #print "................"                                                                                                                                                      
                #print flag                                                                                                                                                                    
                global flag                                                                                                                                                                    
                global requestFlag                                                                                                                                                             
                if requestFlag == True:                                                                                                                                                        
                        print "--------------flag raised"                                                                                                                                      
                        command()                                                                                                                                                              
                                                                                                                                                                                               
if __name__ == "__main__":                                                                                                                                                                     
        SERIAL_PORT = "/dev/ttyS0"                                                                                                                                                             
        ser = serial.Serial(SERIAL_PORT, 9600)                                                                                                                                                 
        ser.timeout = None                                                                                                                                                                     
                                                                                                                                                                                               
        main()      
