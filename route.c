#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "route-records.h"

RouteRecord* createRecords(FILE* fileIn){

char t[200];
fgets(t, 200 ,fileIn);//this fgets will read the first line of data from the excel sheet which gets rid of that first line.

if (fileIn == NULL) {
        printf( "ERROR FILE NOT OPEN\n" );
        return NULL;
    }

//this also goes to the comment below for the next comment char readLine[100];
char numLines[ 100 ];
int lines = 0;

while(fgets(numLines, 100, fileIn) != NULL ){
lines++;
}

RouteRecord* r = ( RouteRecord* ) malloc ( lines * sizeof( RouteRecord ) );

if (r == NULL){
printf("ERROR: Failed to allocate memory for r.\n");
return NULL;
}

int i = 0;//this i is for the for loop which will initialize each of the integer values to 0
int j = 0;
for(i = 0; i < 6; i++){
        for(j=0; j < 6; j++){
                r[i].passengers[j] = 0;}

}

rewind(fileIn);

return r;
}
int fillRecords(RouteRecord* r, FILE* fileIn) {
    char buffer[MAX_LINE_LENGTH];
    int numRecords = 0;

    // Read each line from the CSV file
    while (fgets(buffer, MAX_LINE_LENGTH, fileIn)) {
        // Parse the line into tokens separated by commas
        char* origin = strtok(buffer, ",");
        char* destination = strtok(NULL, ",");
        char* airline = strtok(NULL, ",");
        char* monthStr = strtok(NULL, ",");
        char* passengersStr = strtok(NULL, ",");

        // Convert month and passengers strings to integers
        int month = atoi(monthStr);
        int passengers = atoi(passengersStr);

        // Find the index of an existing record with the same origin, destination, and airline
        int idx = findAirlineRoute(r, numRecords, origin, destination, airline, 0);

        if (idx == -1) {
            // Record not found, create a new record at the end of the array
            strcpy(r[numRecords].origin, origin);
            strcpy(r[numRecords].destination, destination);
            strcpy(r[numRecords].airline, airline);
            memset(r[numRecords].passengersByMonth, 0, sizeof(r[numRecords].passengersByMonth));
            r[numRecords].passengersByMonth[month - 1] = passengers;
            r[numRecords].passengers = passengers;
            numRecords++;
        } else {
            // Record found, update the existing record with passenger data for this month
            r[idx].passengersByMonth[month - 1] += passengers;
            r[idx].passengers += passengers;
        }
    }

    return numRecords;
}

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx) {
    if (curIdx >= length) {
        // End of array, record not found
        return -1;
    } else if (strcmp(r[curIdx].origin, origin) == 0 &&
               strcmp(r[curIdx].destination, destination) == 0 &&
               strcmp(r[curIdx].airline, airline) == 0) {
        // Record found
        return curIdx;
    } else {
        // Recursively search the rest of the array
        return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);
    }
}
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st){

int totalPassengers = 0;
int totalPassengersByMonth[6] = {0};
int numMatches = 0;
int i;
        for(i = 0; i < length; i++){

        bool match = false;

                switch(st) {

                        case ROUTE:

                                if ((strcmp(r[i].origin, key1) == 0) && (strcmp(r[i].destination, key2) == 0)){

                                        match = true;
                                }

                                break;

                        case ORIGIN:

                                if (strcmp(r[i].origin, key1) == 0){

                                        match = true;
                                }

                                break;

                        case DESTINATION:

                                if (strcmp(r[i].destination, key1) == 0){

                                        match = true;
                                }

                                break;

                        case AIRLINE:

                                if (strcmp(r[i].airline, key1) == 0){

                                        match = true;
                                }
                               break;

                        default:
                                break;

                }
                if(match){

                        numMatches++;

                        printf("%s, %s, %s\n", r[i].airline, r[i].origin, r[i].destination);

                        totalPassengers += r[i].passengers[0] + r[i].passengers[1] + r[i].passengers[2] + r[i].passengers[3] + r[i].passengers[4] + r[i].passengers[5];

                        int j;
                        for(j = 0; j < 6; j++){

                                totalPassengersByMonth[j] += r[i].passengers[j];
                        }
                }

        }//end outer for loop

        printf("Total passengers: %d\n", totalPassengers);

        printf("Total passengers by month: ");
                int k;
                for(k = 0; k < 6; k++){

                        printf("%d ", totalPassengersByMonth[k]);
                }

        printf("\n");

                if(numMatches == 0){

                        printf("No matches found.\n");

                }

                else{

                printf("Average passengers by month: ");
                        int l;
                        for(l = 0; l < 6; l++){

                                printf("%.2f ",(float)totalPassengersByMonth[l] / numMatches);
                        }

                        printf("\n");
                }
}

void printMenu(){

printf( "\n\n######### Airline Route Records Database MENU #########\n" );
printf( "1. Search by Route\n" );
printf( "2. Search by Origin Airport\n" );
printf( "3. Search by Destination Airport\n" );
printf( "4. Search by Airline\n" );
printf( "5. Quit\n" );
printf( "Enter your Selection: " );

}
