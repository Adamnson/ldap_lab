#include <stdio.h>
#include <stdlib.h>
#include <ldap.h>
#include "setup.h"

/***************************************************
 * test_bind_success
 **************************************************/

int test_bind_success() {
    LDAP *ld = NULL;
    int rc;
    int version = LDAP_VERSION3;

    rc = ldap_initialize(&ld, LDAP_URL);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "ldap_initialize failed: %s\n", ldap_err2string(rc));
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
        printf("bind_success: PASS\n");
    } else {
        printf("bind_success: FAIL %s\n", ldap_err2string(rc));
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

    ldap_initialize(&ld, LDAP_URL);
    if (rc != LDAP_SUCCESS) {
        fprintf(stderr, "ldap_initialize failed: %s\n", ldap_err2string(rc));
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
        printf("bind_invalid_password: PASS\n");
    } else {
        printf("bind_invalid_password: FAIL (%s)\n", ldap_err2string(rc));
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
        fprintf(stderr, "ldap_initialize failed: %s\n", ldap_err2string(rc));
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
        printf("invalid_dn: PASS\n");
    } else {
        printf("invalid_dn: FAIL %s\n", ldap_err2string(rc));
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
        fprintf(stderr, "ldap_initialize failed: %s\n", ldap_err2string(rc));
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
        printf("bind_anonymous: PASS\n");
    } else {
        printf("bind_anonymous: FAIL %s\n", ldap_err2string(rc));
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
        fprintf(stderr, "ldap_initialize failed: %s\n", ldap_err2string(rc));
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
        printf("empty_dn_with_password: PASS\n");
    } else {
        printf("empty_dn_with_password: FAIL %s\n", ldap_err2string(rc));
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
        fprintf(stderr, "ldap_initialize failed: %s\n", ldap_err2string(rc));
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
        printf("bind_version2: PASS\n");
    } else {
        printf("bind_version2: FAIL %s\n", ldap_err2string(rc));
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_PROTOCOL_ERROR;
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
        fprintf(stderr, "ldap_initialize failed: %s\n", ldap_err2string(rc));
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
        printf("bind_success: PASS\n"); 
    } else { 
        printf("bind_success: FAIL %s\n", ldap_err2string(rc)); 
    }

    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_SUCCESS;
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
        fprintf(stderr, "ldap_initialize failed: %s\n", ldap_err2string(rc));
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
        printf("sasl_empty_mech: PASS\n");
    } else {
        printf("sasl_empty_mech: FAIL %s\n", ldap_err2string(rc));
    }
    
    ldap_unbind_ext_s(ld, NULL, NULL);

    return rc == LDAP_AUTH_METHOD_NOT_SUPPORTED;
}


/***************************************************
 * main 
 **************************************************/


int main(){
    test_bind_success();
    test_bind_invalid_password();
    test_sasl_empty_mech();
    test_invalid_dn();
    test_bind_anonymous();
    test_empty_dn_with_password();
    test_bind_version2();
    test_bind_invalid_version();
    return 0;
}
