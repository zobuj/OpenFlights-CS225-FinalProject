#include "../includes/project.h"

#include <fstream>
#include <iostream>
using namespace std;

string getRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/raw/routes.dat";}


string getAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/raw/airports.dat";}

int main() {
     cout << "Program is starting..."<<endl;
     cout << endl;
     cout << endl;
     Project init(getRoutesPath(),getAirportsPath(),"graph");
     string numAirports;
     cout<<"Would you like to visit 2 or 3 airports?"<<endl;
     cin>>numAirports;
     if(numAirports=="2"){
        string source;
        string dest;
        cout<<"Enter Source Airport 4 Letter Code: ";
        cin>>source;
        cout<<"Enter Destination Airport 4 Letter Code: ";
        cin>>dest;
        std::transform(source.begin(), source.end(),source.begin(), ::toupper);
        std::transform(dest.begin(), dest.end(),dest.begin(), ::toupper);
        cout << "Calculating Shortest Distance and Graphing MST..." << endl;
        double shortestdist = init.shortestPath(source, dest);
        cout << "Shortest Distance from "<<source<<" to "<<dest<<" has a score of: "<<shortestdist<<endl;
     }
     else if(numAirports=="3"){
        string source;
        string stop;
        string dest;
        cout<<"Enter Source Airport 4 Letter Code: ";
        cin>>source;
        cout<<"Enter Stop Airport 4 Letter Code: ";
        cin>>stop;
        cout<<"Enter Destination Airport 4 Letter Code: ";
        cin>>dest;
        std::transform(source.begin(), source.end(),source.begin(), ::toupper);
        std::transform(stop.begin(), stop.end(),stop.begin(), ::toupper);
        std::transform(dest.begin(), dest.end(),dest.begin(), ::toupper);
        cout << "Calculating Shortest Distance and Graphing MST..." << endl;
        double shortestdist_source_stop = init.shortestPath(source, stop);
        cout << "Shortest Distance from "<<source<<" to "<<stop<<" has a score of: "<<shortestdist_source_stop<<endl;
        double shortestdist_stop_dest = init.shortestPath(stop, dest);
        cout << "Shortest Distance from "<<stop<<" to "<<dest<<" has a score of: "<<shortestdist_stop_dest<<endl;
        cout<< "Total distance between "<<source<<" and "<<dest<<": "<<(shortestdist_source_stop+shortestdist_stop_dest)<<endl;
     }
     
    return 0;
}