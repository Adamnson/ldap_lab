#!/bin/bash

CAPTURE=bind.pcap

tshark -i lo -f "tcp port 389" -w $CAPTURE >/dev/null 2>&1 &
PID=$!

sleep 1

./test

kill $PID

tshark -r $CAPTURE -Y ldap -T json > bind.json
