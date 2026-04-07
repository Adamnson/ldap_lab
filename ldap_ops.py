import subprocess
import time

BASE_DN = "dc=neptune-software,dc=com"
ADMIN_DN = "cn=admin," + BASE_DN
PASSWORD = "password"   # change if needed

def run(cmd):
    print(f"\n[+] Running: {cmd}")
    subprocess.run(cmd, shell=True)

# 1. Bind (whoami)
run(f"ldapwhoami -x -D '{ADMIN_DN}' -w {PASSWORD}")
time.sleep(1)

# 2. Search
run(f"ldapsearch -x -D '{ADMIN_DN}' -w {PASSWORD} -b '{BASE_DN}' '(objectClass=inetOrgPerson)'")
time.sleep(1)

# 3. Add (new employee)
add_ldif = """
dn: cn=Temp User,ou=employees,dc=neptune-software,dc=com
objectClass: inetOrgPerson
cn: Temp User
sn: User
uid: temp.user
mail: temp.user@neptune-software.com
userPassword: s3cur3-pa$$-123
"""

with open("temp_add.ldif", "w") as f:
    f.write(add_ldif)

run(f"ldapadd -x -D '{ADMIN_DN}' -w {PASSWORD} -f temp_add.ldif")
time.sleep(1)

# 4. Modify (assign manager)
modify_ldif = """
dn: cn=Temp User,ou=employees,dc=neptune-software,dc=com
changetype: modify
add: manager
manager: cn=Alice Johnson,ou=employees,dc=neptune-software,dc=com
"""

with open("temp_modify.ldif", "w") as f:
    f.write(modify_ldif)

run(f"ldapmodify -x -D '{ADMIN_DN}' -w {PASSWORD} -f temp_modify.ldif")
time.sleep(1)

# 5. Delete
run(f"ldapdelete -x -D '{ADMIN_DN}' -w {PASSWORD} 'cn=Temp User,ou=employees,{BASE_DN}'")
time.sleep(1)

print("\n[+] LDAP operations complete")
