#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route.h"

#define MAX_LINE_LENGTH 256

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_csv_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input file
    FILE* fileIn = fopen(argv[1], "r");
    if (fileIn == NULL) {
        fprintf(stderr, "Error: Could not open input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Create array of route records
    RouteRecord* records = createRecords(fileIn);

    // Fill in the route records with data from the input file
    int numRecords = fillRecords(records, fileIn);

    // Close input file
    fclose(fileIn);

    // Prompt user for search keys and display results
    char key1[MAX_LINE_LENGTH];
    char key2[MAX_LINE_LENGTH];
    int searchType = -1;
    while (searchType != 0) {
        printMenu();
        printf("Enter search type (0 to exit): ");
        scanf("%d", &searchType);
        if (searchType == 0) {
            break;
        }
        printf("Enter first search key: ");
        scanf("%s", key1);
        if (searchType != ROUTE) {
            printf("Enter second search key: ");
            scanf("%s", key2);
        }
        searchRecords(records, numRecords, key1, key2, searchType);
    }

    // Free memory allocated for route records
        int i;
        for (i = 0; i < numRecords; i++) {
        free(records[i].passengers);///before it was records[i].passengerCounts
    }
    free(records);

    return 0;
}
