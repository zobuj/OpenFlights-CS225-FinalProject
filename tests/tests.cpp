#include "../includes/tests.h"
#include "../includes/extractData.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

void ReadRoutesSimple() {
    string path = "/Users/alexisserrano/Documents/CS225_FinalProject/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";
    Project init;
    init.readRoutes(path);
    vector<int> from_expected = {9,9,9,9,1,2,4,3};
    vector<int> from_actual = init.getFrom();
    vector<int> to_expected = {1,2,3,4,5,6,9,8};
    vector<int> to_actual = init.getTo();
    assert(from_expected.size() == from_actual.size());
    assert(to_expected.size() == to_actual.size());
    assert(from_actual.size() == to_actual.size());
    for (int i = 0; i < (int) from_actual.size(); i++) {
        assert(from_expected[i] == from_actual[i]);
        assert(to_expected[i] == to_actual[i]);
    }
    cout << "Read Routes Simple: ALL ASSERTIONS PASSED" << endl;
}
void ReadAirportsSimple() {
    string path = "/Users/alexisserrano/Documents/CS225_FinalProject/OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";
    Project init;
    init.readAirports(path);
    vector<int> airports_expected = {1,2,3,4,5,6,7,8,9};
    vector<int> airports_actual = init.getAirports();
    assert(airports_expected.size() == airports_actual.size());
    for (int i = 0; i < (int) airports_actual.size(); i++) {
        assert(airports_expected[i] == airports_actual[i]);
    }

    vector<double> latitudes_expected = {-6.08168983, -5.207, -5.826789, -6.5698, -9.4433803, -3.5838, 61.160499, 64.1909, 67.0122};
    map<int, double> latitudes_actual = init.getLatitudes();
    assert(latitudes_expected.size() == latitudes_actual.size());
    for (int i = 0 ; i < (int) latitudes_expected.size(); i++) {
        // cout << "Expected: " << (int) latitudes_expected[i] << endl;
        // cout << "Actual: " << (int) latitudes_actual[airports_actual[i]] << endl;
        assert(((int) latitudes_expected[i]) == ((int) latitudes_actual[airports_actual[i]]));
    }

    vector<double> longitudes_expected = {145.391998, 145.7890, 144.2960052490, 146.72, 147.220001, 143.669, -45.425998, -51.67810, -50.71160};
    map<int, double> longitudes_actual = init.getLongitudes();
    assert(longitudes_expected.size() == longitudes_actual.size());
    for (int i = 0 ; i < (int) longitudes_expected.size(); i++) {
        assert(((int) longitudes_expected[i]) == ((int) longitudes_actual[airports_actual[i]]));
    }
    cout << "Read Airports Simple: ALL ASSERTIONS PASSED" << endl;
}

void PathExist() {
    Project init;
    string routes_path = "/Users/alexisserrano/Documents/CS225_FinalProject/OpenFlights-CS225-FinalProject/data/sample/sampleroutes.dat";
    string airports_path = "/Users/alexisserrano/Documents/CS225_FinalProject/OpenFlights-CS225-FinalProject/data/sample/sampleairports.dat";
    
    init.readRoutes(routes_path);
    init.readAirports(airports_path);
    init.createAdjacencyList();

    //undirectional paths (both directions)
    assert(init.DFS(9, 4) == 1);
    assert(init.DFS(4, 9) == 1);

    //one step path
    assert(init.DFS(3, 8) == 1);
    assert(init.DFS(2, 6) == 1);
    assert(init.DFS(9, 1) == 1);

    //Mulitple step paths
    assert(init.DFS(4, 8) == 1);
    assert(init.DFS(9, 6) == 1);
    assert(init.DFS(4, 5) == 1);

    //no connections (no paths)
    assert(init.DFS(7, 9) == 0);

    //strict directional paths (one direction)
    assert(init.DFS(8, 3) == 0);
    assert(init.DFS(5, 4) == 0);

    cout << "Path Exists: ALL ASSERTIONS PASSED" << endl;
}


int main() {
    ReadRoutesSimple();
    ReadAirportsSimple();
    PathExist();
}
