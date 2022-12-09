#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

struct flight_t {
    string source;
    string dest;
    int startTime;
    int endTime;
    int capacity;
};

void parseData(vector<flight_t> &);
void printFlight(flight_t &);
void printFlights(vector<flight_t> &);

int main(){
    vector<flight_t> flights;

    parseData(flights);
    printFlights(flights);

    

    return 0;
}

void parseData(vector<flight_t>& flights){

    regex reg("\\s+");
    string line;
    int linecount = 0;


    ifstream inputfile;
    inputfile.open("flights.txt");

    if(inputfile.is_open()){
        while(getline(inputfile,line)){
            sregex_token_iterator itr(line.begin(),line.end(),reg,-1);
            sregex_token_iterator end;
            
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

            //printFlight(aflight);
            flights.push_back(aflight);
        }
        inputfile.close();
    }
}
void printFlight(flight_t& aflight){
    cout << aflight.source << ", "
            << aflight.dest << ", "
            << aflight.startTime << ", "
            << aflight.endTime << ", "
            << aflight.capacity << endl;
}
void printFlights(vector<flight_t>& theflights){
    for(vector<flight_t>::iterator itr = theflights.begin(); itr != theflights.end(); ++itr ){
        printFlight(*itr);
    }
}