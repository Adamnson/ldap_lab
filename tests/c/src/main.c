#include <stdio.h>
#include "setup.h"
#include "global_stats.h"

int main() {
    int total_pass = 0;
    int total_fail = 0;

    printf("========================================\n");
    printf("     STARTING GLOBAL LDAP TEST SUITE    \n");
    printf("========================================\n");

    // Execute individual test suites
    run_bind_tests(&total_pass, &total_fail);
    //run_unbind_tests(&total_pass, &total_fail);

    // Print global performance metrics
    printf("\n========================================\n");
    printf("GLOBAL METRICS:\n");
    printf("Total Executed: %d\n", total_pass + total_fail);
    printf("Passed        : %d\n", total_pass);
    printf("Failed        : %d\n", total_fail);

    // Print unique network/behavior insights logged during the run
    display_special_observations();

    return (total_fail > 0) ? 1 : 0; 
}
