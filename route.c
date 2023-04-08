//The following is route.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

#define MAX_LINE_LENGTH 256
#define MAX_RECORDS 7000

RouteRecord* createRecords(FILE* fileIn) {
    char line[MAX_LINE_LENGTH];
    int numRecords = 0;
    RouteRecord* records;

    // Count number of records in file
    while (fgets(line, MAX_LINE_LENGTH, fileIn)) {
        numRecords++;
    }

    // Allocate memory for array of records
    records = malloc(numRecords * sizeof(RouteRecord));
    if (records == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize each record
    for (int i = 0; i < numRecords; i++) {
        records[i].passengerCounts = malloc(6 * sizeof(int));
        if (records[i].passengerCounts == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        memset(records[i].passengerCounts, 0, 6 * sizeof(int));
    }

    // Reset file pointer to beginning
    rewind(fileIn);

    // Skip header line
    fgets(line, MAX_LINE_LENGTH, fileIn);

    return records;
}

int fillRecords(RouteRecord* r, FILE* fileIn) {
    char line[MAX_LINE_LENGTH];
    char* token;
    int numRecords = 0;

    // Read each line of the CSV file
    while (fgets(line, MAX_LINE_LENGTH, fileIn)) {
        // Parse the line into fields
        token = strtok(line, ",");
        int month = atoi(token);

        token = strtok(NULL, ",");
        const char* origin = token;

        token = strtok(NULL, ",");
        const char* destination = token;

        token = strtok(NULL, ",");
        const char* airline = token;

        token = strtok(NULL, ",");
        const char* category = token;

        token = strtok(NULL, ",");
        int passengers = atoi(token);

        // Find the route in the array
        int idx = findAirlineRoute(r, numRecords, origin, destination, airline, 0);

        if (idx != -1) {
            // Update existing record
            r[idx].passengerCounts[month-1] = passengers;
        } else {
            // Add new record
            RouteRecord newRecord = {
                .origin = origin,
                .destination = destination,
                .airline = airline,
                .passengerCounts = {0, 0, 0, 0, 0, 0}
            };
            newRecord.passengerCounts[month-1] = passengers;
            r[numRecords] = newRecord;
            numRecords++;
        }
    }

    return numRecords;
}

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx) {
    if (curIdx >= length) {
        // Reached end of array without finding match
        return -1;
    } else if (strcmp(r[curIdx].origin, origin) == 0 &&
               strcmp(r[curIdx].destination, destination) == 0 &&
               strcmp(r[curIdx].airline, airline) == 0) {
        // Found match
        return curIdx;
    } else {
        // Continue searching recursively
        return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);
    }
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st) {
    int totalPassengers = 0;
    int totalPassengersByMonth[6] = {0};
    int numMatches = 0;

    for (int i = 0; i < length; i++) {
        if (st == ORIGIN && strcmp(r[i].origin, key1) == 0) {
            printf("Airline: %s, Route: %s to %s\n", r[i].airline, r[i].origin, r[i].destination);
            for (int j = 0; j < 6; j++) {
                totalPassengers += r[i].passengers[j];
                totalPassengersByMonth[j] += r[i].passengers[j];
            }
            numMatches++;
        } else if (st == DESTINATION && strcmp(r[i].destination, key1) == 0) {
            printf("Airline: %s, Route: %s to %s\n", r[i].airline, r[i].origin, r[i].destination);
            for (int j = 0; j < 6; j++) {
                totalPassengers += r[i].passengers[j];
                totalPassengersByMonth[j] += r[i].passengers[j];
            }
            numMatches++;
        } else if (st == AIRLINE && strcmp(r[i].airline, key1) == 0) {
            printf("Airline: %s, Route: %s to %s\n", r[i].airline, r[i].origin, r[i].destination);
            for (int j = 0; j < 6; j++) {
                totalPassengers += r[i].passengers[j];
                totalPassengersByMonth[j] += r[i].passengers[j];
            }
            numMatches++;
        } else if (st == ROUTE && strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0) {
            printf("Airline: %s, Route: %s to %s\n", r[i].airline, r[i].origin, r[i].destination);
            for (int j = 0; j < 6; j++) {
                totalPassengers += r[i].passengers[j];
                totalPassengersByMonth[j] += r[i].passengers[j];
            }
            numMatches++;
        }
    }

    if (numMatches == 0) {
        printf("No matches found.\n");
    } else {
        printf("Total passengers: %d\n", totalPassengers);
        printf("Total passengers by month:\n");
        for (int i = 0; i < 6; i++) {
            printf("Month %d: %d\n", i + 1, totalPassengersByMonth[i]);
        }
        printf("Average passengers per month: %d\n", totalPassengers / numMatches / 6);
    }
}

void printMenu()
{

printf( "\n\n######### Airline Route Records Database MENU #########\n" );

printf( "1. Search by Route\n" );

printf( "2. Search by Origin Airport\n" );

printf( "3. Search by Destination Airport\n" );

printf( "4. Search by Airline\n" );

printf( "5. Quit\n" );

printf( "Enter your selection: " );

}
