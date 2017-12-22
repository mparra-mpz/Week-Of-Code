#!/usr/bin/python

#
# Author: Manuel Parra Z.
# Date: 10/12/2017
# License: MIT License
# Hardware:
#       - Arduino Uno R3
#       - TMP36GZ Sensor.
# Description: Project to read from the serial port the ambient temperature,
# then publish the temperature in the cloud using gspread.
# Link: https://github.com/mparra-mpz/week-of-code/wiki/Week-3:-Raspberry-Room-Temperatures
#

import subprocess
import re
import gspread
from oauth2client.service_account import ServiceAccountCredentials
import time
import sys
from optparse import OptionParser
import serial

def get_data(command):
    proc = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    (output, err) = proc.communicate()
    data = output.split("\n")[0]
    return data

def menu():
    usage = "usage: %prog -f credential_file"
    parser = OptionParser(usage=usage)
    parser.add_option("-f", "--file", type="string", dest="credential_file",
                      help="Google credential file.")
    (options, args) = parser.parse_args()
    if options.credential_file is None:
        parser.error("The program needs a credintial file.")
    return options.credential_file

def get_temperature(port):
    # Read all the data in the serial port and store in a string.
    data = ""
    rcv = port.readline()
    while rcv != "":
        data = data + rcv
        rcv = port.readline()
    # Calculate the average temperature read from the serial port.
    temperature = 0.0
    sample = 0
    data_list = data.split("\n")
    for element in data_list:
        if element != "":
            sample = sample + 1
            temperature = temperature + float(element)
    temperature = temperature / sample
    # Just a pretty presentation.
    ans = "%.3f" % temperature
    ans = ans.replace(".",",")
    return ans


if __name__ == "__main__":
    credential_file = menu()

    # Open Serial connection.
    port = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=3.0)

    while True:
        try:
            # Get the timestamp.
            timestamp = get_data('date +"%d/%m/%Y %H:%M:%S"')

            # Get the temperature.
            temperature = get_temperature(port)

            # Display the information.
            print "Timestamp: %s -- Temperature: %s." % (timestamp, temperature)

            # Stablish connection with google docs.
            scope = ["https://spreadsheets.google.com/feeds"]
            credentials = ServiceAccountCredentials.from_json_keyfile_name(credential_file, scope)
            connection= gspread.authorize(credentials)
            # Select the spreadsheet and worksheet.
            spreadsheet = connection.open("Raspberry")
            worksheet = spreadsheet.get_worksheet(1)
            # Publish the information in the worksheet.
            worksheet.append_row((timestamp, temperature))

            # Pause during 1 minute.
            print "Information published in the cloud. Pause the program during 1 minute."
            time.sleep(60)
        except KeyboardInterrupt:
            print "Finishing the program execution."
            port.close()
            sys.exit()
        except httplib2.ServerNotFoundError:
            print "Error: ", sys.exc_info()[0]
            print "Connection with google docs fail. Pause the program during 1 minute."
            time.sleep(60)
        except:
            print "Unexpected error:", sys.exc_info()[0]
            port.close()
            raise
