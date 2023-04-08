#ifndef ROUTE_H
#define ROUTE_H

typedef enum SearchType {
    ROUTE,
    ORIGIN,
    DESTINATION,
    AIRLINE
} SearchType;

// Struct for holding information about a route
typedef struct RouteRecord {
    char origin[4];
    char destination[4];
    char airline[3];
    int passengers[6];
} RouteRecord;

// Function prototypes
RouteRecord* createRecords(FILE* fileIn);
int fillRecords(RouteRecord* r, FILE* fileIn);
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);
void printMenu();

#endif
