#!/bin/bash

# CPU temperature.
cpu=$(cat /sys/class/thermal/thermal_zone0/temp)

# GPU temperature.
text=$(/opt/vc/bin/vcgencmd measure_temp)
num=${text//[!0-9]}
gpu=$(($num * 100))

echo "$cpu"
echo "$gpu"
