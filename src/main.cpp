#include "../includes/project.h"

#include <fstream>
#include <iostream>
using namespace std;

string getRoutesPath() {return "../OpenFlights-CS225-FinalProject/data/raw/routes.dat";}


string getAirportsPath() {return  "../OpenFlights-CS225-FinalProject/data/raw/airports.dat";}

int main() {
     cout<<"Creating Entire Graph..."<<endl;
     Project init(getRoutesPath(),getAirportsPath(),"graph");
     string source;
     string dest;
     cout<<"Enter Source Airport 4 Letter Code: ";
     cin>>source;
     cout<<"Enter Destination Airport 4 Letter Code: ";
     cin>>dest;
     std::transform(source.begin(), source.end(),source.begin(), ::toupper);
     std::transform(dest.begin(), dest.end(),dest.begin(), ::toupper);
     cout << "Calculating Shortest Distance and Graphing MST..." << endl;
     double shortestdist=init.shortestPath(source, dest);
     cout << "Shortest Distance from "<<source<<" to "<<dest<<": "<<shortestdist<<endl;
    return 0;
}