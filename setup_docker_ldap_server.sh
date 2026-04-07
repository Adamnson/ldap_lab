#!/bin/bash

read -s -p "Enter LDAP admin password: " password
echo
read -s -p "Confirm password: " password2
echo

if [ "$password" != "$password2" ]; then
    echo "Passwords do not match"
    exit 1
fi

sudo systemctl stop slapd
sudo docker rm -f ldap-server >/dev/null

sudo docker run -d \
    --name ldap-server \
    -p 389:389 \
    -e LDAP_ORGANIZATION="Neptune Software" \
    -e LDAP_DOMAIN="neptune-software.com" \
    -e LDAP_ADMIN_PASSWORD="$password" \
    osixia/openldap >/dev/null || exit 1

spinner='|/-\'
i=0

until ldapwhoami -xH ldap://localhost \
    -D "cn=admin,dc=neptune-software,dc=com" \
    -w "$password" >/dev/null 2>&1
do
    i=$(( (i+1) %4 ))
    printf "\rWaiting for LDAP server %c" "${spinner:$i:1}"
    sleep 1
done

echo " LDAP server is ready!"

ldapadd -xH ldap://localhost \
    -D "cn=admin,dc=neptune-software,dc=com" \
    -w $password \
    -f dir_schema/base.ldif >/dev/null || exit 1

echo " + Base setup done."

ldapadd -xH ldap://localhost \
    -D "cn=admin,dc=neptune-software,dc=com" \
    -w $password \
    -f dir_schema/managers.ldif >/dev/null || exit 1

echo " + Managers added."

ldapadd -xH ldap://localhost \
    -D "cn=admin,dc=neptune-software,dc=com" \
    -w $password \
    -f dir_schema/roles.ldif >/dev/null || exit 1

echo " + Roles configured."

ldapadd -xH ldap://localhost \
    -D "cn=admin,dc=neptune-software,dc=com" \
    -w $password \
    -f dir_schema/employees.ldif >/dev/null || exit 1

echo " + Employees added."

