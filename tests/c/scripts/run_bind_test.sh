#!/bin/bash

CAPTURE="out/bind.pcap"
JSON_OUTPUT="out/bind.json"
EXECUTABLE="./build/test"

mkdir -p out 

tshark -i lo -f "tcp port 389" -w "$CAPTURE" >/dev/null 2>&1 &
PID=$!

sleep 1

if [ -f "$EXECUTABLE" ]; then
    "$EXECUTABLE"
else
    echo "Error: Executable $EXECUTABLE not found. Did you run make?"
    kill $PID
    exit 1
fi

kill $PID
sleep 0.5

tshark -r "$CAPTURE" -Y ldap -T json > "$JSON_OUTPUT"
