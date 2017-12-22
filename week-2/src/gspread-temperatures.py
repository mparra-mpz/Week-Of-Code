#!/usr/bin/python

#
# Author: Manuel Parra Z.
# Date: 10/12/2017
# License: MIT License
# Hardware:
#       - Raspberry Pi B+
# Description: Project to measure the CPU and GPU temperatures in the
# Raspberry, then publish in the data in the cloud using gspread.
# Link: https://github.com/mparra-mpz/week-of-code/wiki/Week-2:-Rasberry-Temperatures
#

import subprocess
import re
import gspread
from oauth2client.service_account import ServiceAccountCredentials
import time
import sys
from optparse import OptionParser

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

if __name__ == "__main__":
    credential_file = menu()
    while True:
        try:
            # Get the timestamp.
            timestamp = get_data('date +"%d/%m/%Y %H:%M:%S"')

            # Get the CPU temperature.
            num = get_data("cat /sys/class/thermal/thermal_zone0/temp")
            aux = re.sub(r"\D", "", num)
            aux = float(aux) / 1000
            cpu = "%.2f" % aux
            cpu = cpu.replace(".",",")

            # Get the GPU temperature.
            num = get_data("/opt/vc/bin/vcgencmd measure_temp")
            aux = re.sub(r"\D", "", num)
            aux = float(aux) / 10
            gpu = "%.2f" % aux
            gpu = gpu.replace(".",",")

            print "%s %s %s." % (timestamp, cpu, gpu)

            # Stablish connection with google docs.
            scope = ["https://spreadsheets.google.com/feeds"]
            credentials = ServiceAccountCredentials.from_json_keyfile_name(credential_file, scope)
            connection= gspread.authorize(credentials)
            # Select the spreadsheet and worksheet.
            spreadsheet = connection.open("Raspberry")
            worksheet = spreadsheet.get_worksheet(0)
            # Publish the information in the worksheet.
            worksheet.append_row((timestamp, cpu, gpu))

            # Pause during 1 minute.
            print "Information published in the cloud. Pause the program during 1 minute."
            time.sleep(60)
        except KeyboardInterrupt:
            print "Finishing the program execution."
            sys.exit()
        except httplib2.ServerNotFoundError:
            print "Connection with google docs fail. Pause the program during 1 minute."
            time.sleep(60)
        except:
            print "Unexpected error:", sys.exc_info()[0]
            raise
