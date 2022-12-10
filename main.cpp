#include <fstream>
#include <regex>
#include <vector>
#include <iterator>
#include "NAS.hpp"


void parseData(NAS&);
bool isValidAirport(string);

int main(){

    NAS system;


    parseData(system);
    system.printAllRoutes();
    //system.printRoute("BOS");



    return 0;
}

void parseData(NAS& system){

    regex reg("\\s+");
    string line;

    ifstream inputfile;
    inputfile.open("flights.txt");

    if(inputfile.is_open()){
        while(getline(inputfile,line)){
            sregex_token_iterator itr(line.begin(),line.end(),reg,-1);
            sregex_token_iterator end;

            //only adds flight if the airport is part of the list of valid airports           
            if(isValidAirport(*itr) && isValidAirport(*next(itr,1))){
                flight_t aflight;
                // cout << "\"" << *itr << "\", "; 
                aflight.source = *itr;
                ++itr;
                aflight.dest = *itr;
                ++itr;
                aflight.startTime = stoi(*itr);
                ++itr;
                aflight.endTime = stoi(*itr);
                ++itr;
                aflight.capacity = stoi(*itr);

                system.addFlight(aflight.source, aflight);

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