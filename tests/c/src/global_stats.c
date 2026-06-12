#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_stats.h"

// Encapsulated state: invisible to other files
static char **observations = NULL;
static int observation_count = 0;
static int observation_capacity = 0;

void special_notifier(const char *message) {
    if (message == NULL) return;

    // Initialize or expand capacity if full (doubling strategy)
    if (observation_count >= observation_capacity) {
        observation_capacity = (observation_capacity == 0) ? 4 : observation_capacity * 2;
        char **temp = realloc(observations, observation_capacity * sizeof(char *));
        if (temp == NULL) {
            fprintf(stderr, "Memory allocation failed in special_notifier\n");
            return;
        }
        observations = temp;
    }

    // Allocate memory for the string string copy and store it
    observations[observation_count] = strdup(message);
    if (observations[observation_count] != NULL) {
        observation_count++;
    }
}

void display_special_observations(void) {
    printf("\n========================================\n");
    printf("         SPECIAL OBSERVATIONS           \n");
    printf("========================================\n");

    if (observation_count == 0) {
        printf("No unusual behaviors or observations noted.\n");
    } else {
        for (int i = 0; i < observation_count; i++) {
            printf("[%d] %s\n", i + 1, observations[i]);
            free(observations[i]); // Clean up string memory as we go
        }
    }
    printf("========================================\n");

    // Clean up the main array container
    free(observations);
    observations = NULL;
    observation_count = 0;
    observation_capacity = 0;
}
