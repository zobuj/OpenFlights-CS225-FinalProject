#include "../includes/tests.h"


void ReadRoutesSimple() {
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath());
    vector<int> from_expected = {9,9,9,9,1,2,4,3};
    vector<int> from_actual = init.getFrom();
    vector<int> to_expected =   {1,2,3,4,5,6,8,7};
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
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath());
    vector<int> airports_expected = {1,2,3,4,5,6,7,8,9};
    vector<int> airports_actual = init.getAirports();
    assert(airports_expected.size() == airports_actual.size());
    for (int i = 0; i < (int) airports_actual.size(); i++) {
        assert(airports_expected[i] == airports_actual[i]);
    }

    vector<double> latitudes_expected = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    map<int, double> latitudes_actual = init.getLatitudes();
    assert(latitudes_expected.size() == latitudes_actual.size());
    for (int i = 0 ; i < (int) latitudes_expected.size(); i++) {
        // cout << "Expected: " << (int) latitudes_expected[i] << endl;
        // cout << "Actual: " << (int) latitudes_actual[airports_actual[i]] << endl;
        assert(((int) latitudes_expected[i]) == ((int) latitudes_actual[airports_actual[i]]));
    }

    vector<double> longitudes_expected = {2, 2, 2, 1, 1, 1, 0, 0, 0};
    map<int, double> longitudes_actual = init.getLongitudes();
    assert(longitudes_expected.size() == longitudes_actual.size());
    for (int i = 0 ; i < (int) longitudes_expected.size(); i++) {
        assert(((int) longitudes_expected[i]) == ((int) longitudes_actual[airports_actual[i]]));
    }
    cout << "Read Airports Simple: ALL ASSERTIONS PASSED" << endl;
}

void SimplePathExist() {
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath());

    assert(init.DFS(9, 4) == 1);
    assert(init.DFS(4, 9) == 0);

    //one step path
    assert(init.DFS(2, 6) == 1);
    assert(init.DFS(9, 1) == 1);

    //Mulitple step paths
    assert(init.DFS(4, 8) == 1);
    assert(init.DFS(9, 6) == 1);

    //no connections (no paths)
    assert(init.DFS(7, 9) == 0);

    //strict directional paths (one direction)
    assert(init.DFS(8, 3) == 0);
    assert(init.DFS(5, 4) == 0);

    cout << "Path Exists: ALL ASSERTIONS PASSED" << endl;
}
/*
void TestsAdjacencyListsSimple() {
    
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath());
    
    map<int, vector<int>> map_actual = init.getGraph();
    vector<int> adj_keys_expected = {1,2,3,4,5,6,7,8,9};
    vector<vector<int>> adj_l_expected
    {
        {5},
        {6},
        {7},
        {8},
        {},
        {},
        {},
        {},
        {1,2,3,4}
    };
    unsigned key_idx = 0;
    for (auto x = map_actual.begin(); x != map_actual.end(); ++x) {
        assert(x->first == adj_keys_expected[key_idx]);
        unsigned value_idx = 0;
        // check if the neighbors are the same
        for (int neighbor:x->second) {
            // cout <<adj_l_expected[key_idx][value_idx] << " " << neighbor << endl; 
            assert(adj_l_expected[key_idx][value_idx] == neighbor);
            value_idx++;
        }
        key_idx++;

    }
    cout << "Testing Map: ALL ASSERTIONS PASSED"<<endl;
}
*/

void testSimpleGraphOutput() {
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath());
    init.savePNG("suite");
    int val =system("diff suite.dot sample.dot");
    assert(val==0);
    cout<<"Testing Graph-Passed All Simple Graph Assertions" <<endl;
}
void TestD(){
    Project init(getDijkstrasRoutesPath(),getDijkstrasAirportsPath());
    vector<double> solutions = {12.4,6.3,11.6,3.6,6.7,0.0};
    // Note: Due to possible rounding errors, we will round all our values down to the nearest tenth and check if the rounded distance matches
    vector<int> to_airportIDs = {1,2,3,4,5,6}; //Every airport in our dataset
    int target = 6; //Our target airport has ID 6, 'Zo_2'
    for (unsigned i = 0; i < to_airportIDs.size(); ++i) {
        double shortest_distance = init.shortestPath(to_airportIDs[i], target);
        assert(abs(shortest_distance - solutions[i]) < 0.1);
    } 
    cout << "Dijkstras on Simple Paths: ALL TEST CASES PASSED" << endl;
}
int main() {
    ReadRoutesSimple();
    ReadAirportsSimple();
    SimplePathExist();
    //TestsAdjacencyListsSimple();
    TestD();
    // for aamir this won't work bc of graphviz package installment issues
    
}