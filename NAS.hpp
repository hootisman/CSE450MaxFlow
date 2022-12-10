#ifndef NAS_H
#define NAS_H

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

const string airportsUsed[10] = {"LAX","JFK","SFO","PHX","SEA","DEN","ATL","ORD","BOS","IAD"};

struct flight_t {
    string source;
    string dest;
    int startTime;
    int endTime;
    int capacity;       // capacity of plane
};

class NAS{
    private:
        map< string, list<flight_t> > allFlights; //map with airport name as key and list of all possible flights from that airport as value
        int length;     //length of allFlights
        void printRoute_h(list<flight_t>&);
    public:
        NAS();
        void addFlight(string, flight_t&);  //adds flight to allFlights
        void printRoute(string);
        void printAllRoutes();
        void BFSearch();       //breadth first search
        ~NAS() {};

};

#endif