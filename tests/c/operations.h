
/***************************************************
 * whoami
 **************************************************/

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
