#include <fstream>
#include <regex>
#include <vector>
#include <iterator>
#include "NAS.hpp"


void parseData(NAS&);
bool isValidAirport(string);

int main(){

    NAS system;             //contains the adjacency list, BFS algo, and FordFulkerson algo
    parseData(system);      //parses flights.txt file
    
    //system.printAllRoutes();

    int finalFlow = system.findMaxFlow();           //ford-fulkerson algorithm
    cout <<"\n\n\nMax flow: " << finalFlow << endl;

    return 0;
}

void parseData(NAS& system){

    //parses the flights.txt dataset using regex

    regex reg("\\s+");      //the regex
    string line;

    ifstream inputfile;
    inputfile.open("flights.txt");

    if(inputfile.is_open()){
        while(getline(inputfile,line)){
            //for each line in the file, split using the regex. result of splitting a line => itr
            sregex_token_iterator itr(line.begin(),line.end(),reg,-1);
            sregex_token_iterator end;

            //only adds flight if the airport is part of the list of valid airports           
            if(isValidAirport(*itr) && isValidAirport(*next(itr,1))){

                //see NAS.hpp for flight_t struct
                flight_t* aflight = new flight_t();
                
                (*aflight).source = *itr;
                ++itr;
                (*aflight).dest = *itr;
                ++itr;
                (*aflight).startTime = stoi(*itr);
                ++itr;
                (*aflight).endTime = stoi(*itr);
                ++itr;
                (*aflight).capacity = stoi(*itr);

                //adds flight_t to the NAS
                system.addFlight((*aflight).source, *aflight);

            }            
        }
        inputfile.close();
    }
}
bool isValidAirport(string airport){
    
    for(int i = 0; i < sizeof(airportsUsed)/sizeof(airportsUsed[0]); i++){
       if(airportsUsed[i] == airport) return true;
    }
    return false;
}