#include <stdio.h>
#include <stdlib.h>
#include <ldap.h>
#include "setup.h"
#include "operations.h"
/***************************************************
 * test_unbind_success
 **************************************************/

int test_unbind_success() {
    LDAP *ld = NULL;
    int rc;
    int version = LDAP_VERSION3;

    rc = ldap_initialize(&ld, LDAP_URL);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, COLOR_RED "ldap_initialize failed: %s\n" COLOR_RESET, ldap_err2string(rc));
        return 0;
    }

    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    struct berval cred;
    cred.bv_val = PASSWORD;
    cred.bv_len = strlen(PASSWORD);

    rc = ldap_sasl_bind_s(
            ld, 
            BIND_DN,
            LDAP_SASL_SIMPLE, 
            &cred, 
            NULL, 
            NULL, 
            NULL
            );

    if (rc == LDAP_SUCCESS) {
        printf(COLOR_GREEN "bind success:\n" COLOR_RESET);
        printf("  * ");
        whoami(ld);
    } else {
        printf(COLOR_RED "bind not successful %s\n" COLOR_RESET, ldap_err2string(rc) );
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    rc = whoami(ld);

    printf("rc : %d", rc);

    return rc == LDAP_SUCCESS;
}

/***************************************************
 * run_unbind_tests(int *pass_count, int *fail_count)
 **************************************************/

void run_unbind_tests(int *pass_count, int *fail_count){
    test_unbind_success() ? (*pass_count)++ : (*fail_count)++ ;
    /*
    test_bind_invalid_password() ? (*pass_count)++ : (*fail_count)++ ;
    test_sasl_empty_mech() ? (*pass_count)++ : (*fail_count)++ ;
    test_invalid_dn() ? (*pass_count)++ : (*fail_count)++ ;
    test_bind_anonymous() ? (*pass_count)++ : (*fail_count)++ ;
    test_empty_dn_with_password() ? (*pass_count)++ : (*fail_count)++ ;
    test_bind_version2() ? (*pass_count)++ : (*fail_count)++ ;
    test_bind_invalid_version() ? (*pass_count)++ : (*fail_count)++ ;
*/
    printf("\nTotal / Pass / Fail :");
    printf(" %d /", (*pass_count) + (*fail_count));
    printf(COLOR_GREEN " %d " COLOR_RESET "/", (*pass_count));
    printf(COLOR_RED " %d\n" COLOR_RESET, (*fail_count));
}
