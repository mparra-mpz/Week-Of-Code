#!/bin/bash

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
