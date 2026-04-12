from ldap3 import Server, Connection, ALL

LDAP_HOST = "localhost"
LDAP_PORT = 389

BIND_DN = "cn=admin,dc=neptune-software,dc=com"
PASSWORD = "123"

def test_bind_success():
    server = Server(LDAP_HOST, port=LDAP_PORT, get_info=ALL)

    conn = Connection( server, user=BIND_DN, password=PASSWORD, auto_bind=False)
    success = conn.bind()
    print("Bind returned:", success)
    print("Result:", conn.result)

    if success:
        print("Test PASS")
    else:
        print("Test FAIL")

def test_bind_invalid_password():
    server = Server(LDAP_HOST, port=LDAP_PORT, get_info=ALL)

    conn = Connection( server, user=BIND_DN, password="wrong password", auto_bind=False)
    success = conn.bind()

    print("Result:", conn.result)
    
    if conn.result["result"] == 49:
        print("Test PASS")
    else:
        print("Test FAIL")


if __name__ == "__main__":
    test_bind_success()
    test_bind_invalid_password()
