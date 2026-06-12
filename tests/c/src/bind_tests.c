#include <stdio.h>
#include <stdlib.h>
#include <ldap.h>
#include "setup.h"
#include "operations.h"
#include "global_stats.h"
/*
int whoami(LDAP *ld) {
    struct berval *retdata = NULL;
    char *retoid = NULL;

    int rc = ldap_extended_operation_s(
            ld,
            "1.3.6.1.4.1.4203.1.11.3",
            NULL,
            NULL,
            NULL,
            &retoid,
            &retdata
            );

    if( rc != LDAP_SUCCESS) {
        fprintf(stderr, COLOR_RED "whoami failed: %s\n" COLOR_RESET, ldap_err2string(rc));
        return 0;
    }

    if (retdata) {
        if (retdata->bv_len == 0) {
        printf("whoami: anonymous\n");
        } else {
        printf("whoami: %s\n", retdata->bv_val);
        }
    } 

    if (retoid){
        ldap_memfree(retoid);
    }

    if (retdata) {
        ber_bvfree(retdata);
    }

    return 0;
}
*/
/***************************************************
 * test_bind_success
 **************************************************/

int test_bind_success() {
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
        printf(COLOR_GREEN "bind_success: PASS\n" COLOR_RESET);
        printf("  * ");
        whoami(ld);
    } else {
        printf(COLOR_RED "bind_success: FAIL %s\n" COLOR_RESET, ldap_err2string(rc) );
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_SUCCESS;
}

/***************************************************
 * test_bind_invalid_password
 **************************************************/

int test_bind_invalid_password(){
    LDAP *ld = NULL;
    int rc;
    int version = LDAP_VERSION3;

    rc = ldap_initialize(&ld, LDAP_URL);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, COLOR_RED "ldap_initialize failed: %s\n" COLOR_RESET, ldap_err2string(rc) );
        return 0;
    }

    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    struct berval cred;
    cred.bv_val = "wrong";
    cred.bv_len = strlen(cred.bv_val);

    rc = ldap_sasl_bind_s(
            ld,
            BIND_DN,
            LDAP_SASL_SIMPLE,
            &cred,
            NULL,
            NULL,
            NULL
            );

    if (rc == LDAP_INVALID_CREDENTIALS) {
        printf(COLOR_GREEN "bind_invalid_password: PASS\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "bind_invalid_password: FAIL (%s)\n" COLOR_RESET, ldap_err2string(rc) );
    }

    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_INVALID_CREDENTIALS;
}

/***************************************************
 * test_invalid_dn
 **************************************************/

int test_invalid_dn() {
    LDAP *ld = NULL;
    int rc;
    int version = LDAP_VERSION3;

    rc = ldap_initialize(&ld, LDAP_URL);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, COLOR_RED "ldap_initialize failed: %s\n" COLOR_RESET, ldap_err2string(rc) );
        return 0;
    }

    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    struct berval cred;
    cred.bv_val = PASSWORD;
    cred.bv_len = strlen(PASSWORD);

    rc = ldap_sasl_bind_s(
            ld, 
            "cn=ghost,dc=neptune-software,dc=com", 
            LDAP_SASL_SIMPLE, 
            &cred, 
            NULL, 
            NULL, 
            NULL
            );

    if (rc == LDAP_INVALID_CREDENTIALS) {
        printf(COLOR_GREEN "invalid_dn: PASS\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "invalid_dn: FAIL %s\n" COLOR_RESET, ldap_err2string(rc) );
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_INVALID_CREDENTIALS;
}

/***************************************************
 * test_bind_anonymous
 **************************************************/

int test_bind_anonymous() {
    LDAP *ld = NULL;
    int rc;
    int version = LDAP_VERSION3;

    rc = ldap_initialize(&ld, LDAP_URL);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, COLOR_RED "ldap_initialize failed: %s\n" COLOR_RESET, ldap_err2string(rc) );
        return 0;
    }

    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    struct berval cred;
    cred.bv_val = ""; 
    cred.bv_len = strlen(cred.bv_val);

    rc = ldap_sasl_bind_s(
            ld, 
            "", 
            LDAP_SASL_SIMPLE, 
            &cred, 
            NULL, 
            NULL, 
            NULL
            );

    if (rc == LDAP_SUCCESS) {
        printf(COLOR_GREEN "bind_anonymous: PASS\n" COLOR_RESET);
        printf("  * ");
        whoami(ld);
    } else {
        printf( COLOR_RED "bind_anonymous: FAIL %s\n" COLOR_RESET, ldap_err2string(rc));
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_SUCCESS;
}

/***************************************************
 * test_empty_dn_with_password
 **************************************************/

int test_empty_dn_with_password() {
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
            "",
            LDAP_SASL_SIMPLE, 
            &cred, 
            NULL, 
            NULL, 
            NULL
            );

    if (rc == LDAP_INVALID_CREDENTIALS) {
        printf(COLOR_GREEN "empty_dn_with_password: PASS\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "empty_dn_with_password: FAIL %s\n" COLOR_RESET, ldap_err2string(rc));
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_INVALID_CREDENTIALS;
}

/***************************************************
 * test_bind_version2
 **************************************************/

int test_bind_version2() {
    LDAP *ld = NULL;
    int rc;
    int version = LDAP_VERSION2;

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
        printf(COLOR_GREEN "bind_version2: PASS*\n" COLOR_RESET);
        special_notifier("Security Warning: Binding to version2 allowed on this server.");
    } else if (rc == LDAP_PROTOCOL_ERROR || 
        rc == LDAP_UNWILLING_TO_PERFORM ){
        printf(COLOR_GREEN "bind_version2: PASS\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "bind_version2: FAIL %s\n" COLOR_RESET, ldap_err2string(rc));
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    return (rc == LDAP_SUCCESS ||
        rc == LDAP_PROTOCOL_ERROR || 
        rc == LDAP_UNWILLING_TO_PERFORM );
}

/***************************************************
 * test_bind_invalid_version
 **************************************************/

int test_bind_invalid_version() {
    LDAP *ld = NULL;
    int rc;
    int version = 999;

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

    
    if (rc == LDAP_PROTOCOL_ERROR) {
        printf(COLOR_GREEN "bind_invalid_version: PASS\n" COLOR_RESET) ; 
    } else { 
        printf(COLOR_RED "bind_invalid_version: FAIL %s\n" COLOR_RESET, ldap_err2string(rc)); 
    }

    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_PROTOCOL_ERROR;
} 

/***************************************************
 * test_sasl_empty_mech
 **************************************************/

int test_sasl_empty_mech() {
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
            "", 
            &cred, 
            NULL, 
            NULL, 
            NULL
            );

    if (rc == LDAP_AUTH_METHOD_NOT_SUPPORTED) {
        printf(COLOR_GREEN "sasl_empty_mech: PASS\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "sasl_empty_mech: FAIL %s\n" COLOR_RESET, ldap_err2string(rc));
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_AUTH_METHOD_NOT_SUPPORTED;
}
/***************************************************
 * run_bind_tests(int *pass_count, int *fail_count) 
 **************************************************/


void run_bind_tests(int *pass_count,int *fail_count){
    test_bind_success() ? (*pass_count)++ : (*fail_count)++ ;
    test_bind_invalid_password() ? (*pass_count)++ : (*fail_count)++ ;
    test_sasl_empty_mech() ? (*pass_count)++ : (*fail_count)++ ;
    test_invalid_dn() ? (*pass_count)++ : (*fail_count)++ ;
    test_bind_anonymous() ? (*pass_count)++ : (*fail_count)++ ;
    test_empty_dn_with_password() ? (*pass_count)++ : (*fail_count)++ ;
    test_bind_version2() ? (*pass_count)++ : (*fail_count)++ ;
    test_bind_invalid_version() ? (*pass_count)++ : (*fail_count)++ ;

    printf("\nTotal / Pass / Fail :");
    printf(" %d /", (*pass_count) + (*fail_count));
    printf(COLOR_GREEN " %d " COLOR_RESET "/", (*pass_count));
    printf(COLOR_RED " %d\n" COLOR_RESET, (*fail_count));
    
}
