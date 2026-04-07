#!/bin/bash

INTERFACE="lo"   # use lo if running locally
PCAP_FILE="ldap_capture.pcap"

echo "Starting tshark capture..."

# Start tshark in background
tshark -i $INTERFACE -f "tcp port 389" -w "$PCAP_FILE" >/dev/null 2>&1 &
TSHARK_PID=$!

# Give tshark a moment to start
sleep 2

echo "Tshark started at $TSHARK_PID"
echo "Running LDAP operations..."

# Run python script
python3 ldap_ops.py

echo "Stopping capture..."

# Stop tshark
kill $TSHARK_PID

sleep 1

echo "Capture saved to $PCAP_FILE"
