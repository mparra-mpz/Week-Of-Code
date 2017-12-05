#!/usr/bin/python

import subprocess
import re
import gspread
from oauth2client.service_account import ServiceAccountCredentials
import time

if __name__ == "__main__":
    while True:
        # Get the timestamp.
        proc = subprocess.Popen('date +"%d/%m/%Y %H:%M:%S"', stdout=subprocess.PIPE, shell=True)
        (output, err) = proc.communicate()
        timestamp = output.split('\n')[0]

        # Get the CPU temperature.
        proc = subprocess.Popen('cat /sys/class/thermal/thermal_zone0/temp', stdout=subprocess.PIPE, shell=True)
        (output, err) = proc.communicate()
        num = output.split('\n')[0]
        cpu = re.sub(r'\D', '', num)
        cpu = float(cpu) / 1000

        # Get the GPU temperature.
        proc = subprocess.Popen('/opt/vc/bin/vcgencmd measure_temp', stdout=subprocess.PIPE, shell=True)
        (output, err) = proc.communicate()
        num = output.split('\n')[0]
        gpu = re.sub(r'\D', '', num)
        gpu = float(gpu) / 10

        print "%s %.2f %.2f" % (timestamp, cpu, gpu)

        # Send information to google docs.
        scope = ['https://spreadsheets.google.com/feeds']
        credentials = ServiceAccountCredentials.from_json_keyfile_name('../raspberry-pi-cd4c80393fcc.json', scope)
        connection= gspread.authorize(credentials)
        spreadsheet = connection.open('Raspberry Temperature')
        worksheet = spreadsheet.get_worksheet(0)
        worksheet.append_row((timestamp, cpu, gpu))

        # Pause during 1 minute.
        print "Information published in the cloud. Pause the program during 1 minute"
        time.sleep(60)
