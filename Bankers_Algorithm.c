#include <stdio.h>

// Define the maximum number of processes and resource types.
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Define the available, maximum, and allocated matrices.
int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocated[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to check if the requested resources are safe to allocate.
int isSafe(int process, int request[]) {
    // Step 1: Check if the request is less than or equal to the need.
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process][i]) {
            return 0;  // Request exceeds need.
        }
    }

    // Step 2: Temporarily allocate resources.
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocated[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Step 3: Check if the system is still in a safe state.
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    // Initialize the work array with available resources.
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    int safeSequence[MAX_PROCESSES];
    int count = 0;

    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == MAX_RESOURCES) {
                    // Resource request can be granted.
                    for (int k = 0; k < MAX_RESOURCES; k++) {
                        work[k] += allocated[i][k];
                    }
                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        // If no process could be allocated, the system is not in a safe state.
        if (!found) {
            break;
        }
    }

    // Step 4: Restore the resource allocation.
    if (count == MAX_PROCESSES) {
        return 1;  // Request is safe and can be allocated.
    } else {
        // Request is not safe, so restore the previous state.
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocated[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return 0;  // Request is not safe.
    }
}

int main() {
    // Initialize the available, maximum, and allocated matrices.
    // You should modify these values according to your needs.
    
    // ...

    // Example request for a process (modify as needed).
    int process = 0;
    int request[MAX_RESOURCES] = {2, 1, 0};

    // Check if the request is safe and allocate if possible.
    if (isSafe(process, request)) {
        printf("Request granted. Resources allocated.\n");

        // Print the safe sequence.
        printf("Safe Sequence: ");
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (i > 0) {
                printf(" -> ");
            }
            printf("P%d", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("Request denied. Resources not allocated. System is in an unsafe state.\n");
        printf("Problem arises with Process P%d\n", process);
    }

    return 0;
}
