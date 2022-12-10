#include "NAS.hpp"

NAS::NAS(){

    length = 10;
    for(int i = 0; i < length; i++){
        list<flight_t> route;
        allFlights[airportsUsed[i]] = route;
    }
    
}

void NAS::addFlight(string sourceAirport, flight_t& aflight){
    allFlights[sourceAirport].push_front(aflight);
}

//prints all possible flights from a source airport
void NAS::printRoute(string sourceAirport){
    printRoute_h(allFlights[sourceAirport]);
}

//helper method for printRoutes
void NAS::printRoute_h(list<flight_t>& route){  
    for(auto itr = route.begin(); itr != route.end(); ++itr){
        cout << "\t" << (*itr).source << ", "
                    << (*itr).dest << ", "
                    << (*itr).startTime << ", "
                    << (*itr).endTime << ", "
                    << (*itr).capacity << endl;
    }

}
void NAS::printAllRoutes(){
    for(int i = 0; i < length; i++){
        string airportToPrint = airportsUsed[i];
        cout << airportToPrint << ": " << endl;
        printRoute(airportToPrint);
    }
}
//void 