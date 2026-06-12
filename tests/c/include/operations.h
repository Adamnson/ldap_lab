#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <ldap.h>

/***************************************************
 * whoami - Performs an LDAP WhoAmI extended operation
 **************************************************/
int whoami(LDAP *ld);

#endif // OPERATIONS_H

