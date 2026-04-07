import random

first_names = [
    "adam", "albert", "butch", "barry", "bert",
    "charlie", "donna", "derek", "darren",
    "estelle", "fiona", "gina", "harry",
    "irene", "jill", "james", "peter", "loyd", "sophia", "samuel", "tara", "bethany", "bernadette", "robert", "kevin", "michael", "mary"
]

last_names = [
    "smith", "roy", "whittaker", "dunphy",
    "carrel", "scott", "goodall", "pitt", "white", "carey", "marshal", "osborne", "johnson", "stevenson", "adams", "hill"
]

departments = ["sales", "finance", "engineering"]

used = set()

def generate_unique_name():
    while True:
        first = random.choice(first_names)
        last = random.choice(last_names)
        full = f"{first} {last}"
        if full not in used:
            used.add(full)
            return first, last

for _ in range(50):
    first, last = generate_unique_name()
    
    cn = f"{first.capitalize()} {last.capitalize()}"
    uid = f"{first}.{last}"
    email = f"{uid}@neptune-software.com"
    dept = random.choice(departments)

    print(f"""dn: cn={cn},ou=employees,dc=neptune-software,dc=com
objectClass: inetOrgPerson
cn: {cn}
sn: {last.capitalize()}
uid: {uid}
mail: {email}
userPassword: s3cur3-pa$$-123
description: {dept}

""")
