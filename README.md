The docker container is setup using the `setup_docker_ldap_server.sh` script. The script picks up `.ldif` files defined in the `dir_schema` folder.

The capture.sh script is run to execute the tests. It first starts tshark and then calls `ldap_ops.py` and saves the output to `ldap_capture.pcap`
