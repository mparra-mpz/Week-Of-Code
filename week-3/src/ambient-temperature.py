#!/usr/bin/python

#
# Author: Manuel Parra Z.
# Date: 10/12/2016
# License: MIT License
# Hardware:
# Description:
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
    data = ""
    rcv = port.readline()
    while rcv != "":
        data = data + rcv
        rcv = port.readline()
    temperature = 0.0
    sample = 0
    data_list = data.split("\n")
    for element in data_list:
        if element != "":
            sample = sample + 1
            temperature = temperature + float(element)
    temperature = temperature / sample
    ans = "%.3f" % temperature
    ans = ans.replace(".",",")
    return ans


if __name__ == "__main__":
    credential_file = menu()
    port = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=3.0)
    while True:
        try:
            # Get the timestamp.
            timestamp = get_data('date +"%d/%m/%Y %H:%M:%S"')

            # Get the temperature.
            temperature = get_temperature(port)

            # Display the information.
            print "Timestamp: %s -- Temperature: %s" % (timestamp, temperature)

            # Send information to google docs.
            scope = ["https://spreadsheets.google.com/feeds"]
            credentials = ServiceAccountCredentials.from_json_keyfile_name(credential_file, scope)
            connection= gspread.authorize(credentials)
            spreadsheet = connection.open("Raspberry")
            worksheet = spreadsheet.get_worksheet(1)
            worksheet.append_row((timestamp, temperature))

            # Pause during 1 minute.
            print "Information published in the cloud. Pause the program during 1 minute"
            time.sleep(60)
        except KeyboardInterrupt:
            print "Finishing the program execution."
            port.close()
            sys.exit()
        except:
            print "Unexpected error:", sys.exc_info()[0]
            port.close()
            raise

