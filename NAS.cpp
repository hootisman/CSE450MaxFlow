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
void NAS::printFlight_t(flight_t& flight){
    cout << flight.source << ", "
                    << flight.dest << ", "
                    << flight.startTime << ", "
                    << flight.endTime << ", "
                    << flight.capacity << endl;
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
bool NAS::getFirstFlightTo(string source, string dest, list<flight_t>& aFlightPath, int& currentTime){
    //returns true if we found a flight going from source --> dest that meets our conditions; add flight to flight path
    //otherwise return false if our conditions not met and added flight to flight path
    

    list<flight_t>& sourceFlights = allFlights[source];
    bool wasFlightAdded = false;

    //for each flight_t in allFlights
    for(auto itr = sourceFlights.begin(); itr != sourceFlights.end(); ++itr){
        //found flight from source --> dest
        if((*itr).dest == dest ){
            
            //flight_t& foundFlight = *itr;

            //if the found flight meets the conditions, set the result (wasFlightAdded) to success (true) and add flight to flight path
            if(wasFlightAdded = (*itr).source != "NULL" && (*itr).capacity > 0 && (*itr).startTime >= currentTime){
                
                aFlightPath.push_back(*itr);     //adds flight to flight path
                break;
            }
            
        }
    }
    
    return wasFlightAdded;  //true i
}
bool NAS::BFSearch(list<flight_t>& aFlightPath){

    //clear aFlightPath so we begin a new route, starting at LAX
    aFlightPath.clear();

    //ex: wasAirportVisited["JFK"] => true; returns true if visited, false if not
    map<string, bool> wasAirportVisited;    

    //airports not yet visited
    list<string> notVisited;
    notVisited.push_back("LAX");      //LAX is in front, will be first one visited in while loop below

    //initalize wasAirportVisited
    for(int i = 0; i < length; i++){
        
        wasAirportVisited[airportsUsed[i]] = false;
    }

    wasAirportVisited["LAX"] = true;    //LAX is source, starts as visited

    int currentTime = 0;        //range [0,24], represents time in hours

    while(!notVisited.empty()){
        //start visiting nodes
        string source = notVisited.front();
        notVisited.pop_front();

        //for each airport
        for(int i = 0; i < length; i++){

            string dest = airportsUsed[i];

            if(!wasAirportVisited[dest] && getFirstFlightTo(source,dest,aFlightPath,currentTime))
            {
                
                wasAirportVisited[dest] = true;
                
                if(dest == "JFK"){ break; }             //found a path that ends on JFK, break loop;

                notVisited.push_front(dest);
            }

        }
    }


    return wasAirportVisited["JFK"];        //returns if JFK was visited
}
int NAS::findMaxFlow(){
    int maxFlow = 0;
    list<flight_t> aFlightPath;     //one augmenting path
    
    // for(int k = 0; k < 2; k++){
    //     BFSearch(aFlightPath);
    while(BFSearch(aFlightPath)){
        int minCap = 999999999;     //minimum capacity of path, begins as really big number to start comparing edge capacities

        //finds the minimum capacity for the flight path
        for(auto itr = aFlightPath.begin(); itr != aFlightPath.end(); ++itr){
            minCap = min(minCap, (*itr).capacity);
            
        }

        //adjusts all path edge capacities and adds minCap to maxFlow
        for(auto itr = aFlightPath.begin(); itr != aFlightPath.end(); ++itr){
            cout << minCap << endl;
            (*itr).capacity = (*itr).capacity - minCap;
            
        }

        maxFlow += minCap;
        
    }
    
    return maxFlow;
}