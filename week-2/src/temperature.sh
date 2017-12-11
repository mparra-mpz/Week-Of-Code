#!/bin/bash

#
# Author: Manuel Parra Z.
# Date: 10/12/2017
# License: MIT License
# Hardware:
#       - Raspberry Pi B+
# Description: Project to measure the CPU and GPU temperatures in the Raspberry.
# Link: https://github.com/mparra-mpz/week-of-code/wiki/Week-2:-Rasberry-Temperatures
#

# Timestamp.
timestamp=$(date +"%d/%m/%Y %H:%M:%S")

# CPU temperature.
num=$(cat /sys/class/thermal/thermal_zone0/temp)
cpu=$(($num / 1000))

# GPU temperature.
text=$(/opt/vc/bin/vcgencmd measure_temp)
num=${text//[!0-9]}
gpu=$(($num / 10))

echo "$timestamp CPU:$cpu°C GPU:$gpu°C"
