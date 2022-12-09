#include "../includes/tests.h"


void ReadRoutesSimple() {
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath(),"testsimple");
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
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath(),"testsimple");
    vector<int> airports_expected = {1,2,3,4,5,6,7,8,9};
    vector<int> airports_actual = init.getAirports();
    assert(airports_expected.size() == airports_actual.size());
    for (int i = 0; i < (int) airports_actual.size(); i++) {
        assert(airports_expected[i] == airports_actual[i]);
    }

    vector<double> latitudes_expected = {-10, 0, 10, -10, 0, 10, -10, 0, 10};
    map<int, double> latitudes_actual = init.getLatitudes();
    assert(latitudes_expected.size() == latitudes_actual.size());
    for (int i = 0 ; i < (int) latitudes_expected.size(); i++) {
        assert(((int) latitudes_expected[i]) == ((int) latitudes_actual[airports_actual[i]]));
    }

    vector<double> longitudes_expected = {20, 20, 20, 10, 10, 10, 0, 0, 0};
    map<int, double> longitudes_actual = init.getLongitudes();
    assert(longitudes_expected.size() == longitudes_actual.size());
    for (int i = 0 ; i < (int) longitudes_expected.size(); i++) {
        assert(((int) longitudes_expected[i]) == ((int) longitudes_actual[airports_actual[i]]));
    }
    cout << "Read Airports Simple: ALL ASSERTIONS PASSED" << endl;
}

void SimplePathExist() {
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath(),"testsimple");

    assert(init.AirportConnection("BGSF", "AYNZ") == 1);
    assert(init.AirportConnection("AYNZ", "BGSF") == 0);

    //one step path
    assert(init.AirportConnection("AYMD", "AYWK") == 1);
    assert(init.AirportConnection("BGSF", "AYGA") == 1);

    //Mulitple step paths
    assert(init.AirportConnection("AYNZ", "BGGH") == 1);
    assert(init.AirportConnection("BGSF", "AYWK") == 1);

    //no connections (no paths)
    assert(init.AirportConnection("BGBW", "BGSF") == 0);

    //strict directional paths (one direction)
    assert(init.AirportConnection("BGGH", "AYMH") == 0);
    assert(init.AirportConnection("AYPY", "AYNZ") == 0);

    cout << "Path Exists: ALL ASSERTIONS PASSED" << endl;
}
void TestsAdjacencyListsSimple() {
    
    Project init(getSimpleRoutesPath(),getSimpleAirportsPath(),"testsimple");
    
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
            assert(adj_l_expected[key_idx][value_idx] == neighbor);
            value_idx++;
        }
        key_idx++;

    }
    cout << "Testing Map: ALL ASSERTIONS PASSED"<<endl;
}

void testSimpleGraphOutput() {
    std::ofstream neatoFile;
    string filename ="suite.dot";
    neatoFile.open(filename.c_str());
    neatoFile<<"digraph {\n";
    neatoFile<<"layout=neato;\n";
    neatoFile<<"scale=0.5;\n";
    neatoFile<<"\"AYGA\" [pos=\"20,-10!\"]\n";
    neatoFile<<"\"AYMD\" [pos=\"20,0!\"]\n";
    neatoFile<<"\"AYMH\" [pos=\"20,10!\"]\n";
    neatoFile<<"\"AYNZ\" [pos=\"10,-10!\"]\n";
    neatoFile<<"\"AYPY\" [pos=\"10,0!\"]\n";
    neatoFile<<"\"AYWK\" [pos=\"10,10!\"]\n";
    neatoFile<<"\"BGBW\" [pos=\"0,-10!\"]\n";
    neatoFile<<"\"BGGH\" [pos=\"0,0!\"]\n";
    neatoFile<<"\"BGSF\" [pos=\"0,10!\"]\n";
    neatoFile<<"\"AYGA\"->\"AYPY\" [label=\"14.142136\"]\n";
    neatoFile<<"\"AYMD\"->\"AYWK\" [label=\"14.142136\"]\n";
    neatoFile<<"\"AYMH\"->\"BGBW\" [label=\"28.284271\"]\n";
    neatoFile<<"\"AYNZ\"->\"BGGH\" [label=\"14.142136\"]\n";
    neatoFile<<"\"BGSF\"->\"AYGA\" [label=\"28.284271\"]\n";
    neatoFile<<"\"BGSF\"->\"AYMD\" [label=\"22.360680\"]\n";
    neatoFile<<"\"BGSF\"->\"AYMH\" [label=\"20.000000\"]\n";
    neatoFile<<"\"BGSF\"->\"AYNZ\" [label=\"22.360680\"]\n";
    neatoFile<<"}";
    neatoFile.close();
    string command = "neato -Tpng suite.dot -o suite.png";
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Output graph saved as suite.png" << endl;
    } else {
        cout << "Unable to generate graph using `neato`. Run `sudo apt install graphviz`." << endl;
    }

    Project init(getSimpleRoutesPath(),getSimpleAirportsPath(),"testsimple");
    init.printFullMap("testsimple");
    int val =system("diff testsimple.dot suite.dot");
    assert(val==0);
    cout<<"Testing Graph: ALL ASSERTIONS PASSED" << endl;
}
void TestShortestPath(){
    Project init(getDijkstrasRoutesPath(),getDijkstrasAirportsPath(),"testdijkstras");
    vector<double> solutions = {12.4,6.3,11.6,3.6,6.7};
    // Note: Due to possible rounding errors, we will round all our values down to the nearest tenth and check if the rounded distance matches
    vector<string> to_airportIDs = {"AYGA","AYMD","AYMH","AYNZ","AYPY"}; //Every airport in our dataset
    string target = "AYWK"; //Our target airport has ID 6, 'Zo_2'
    for (unsigned i = 0; i < to_airportIDs.size(); ++i) {
        double shortest_distance = init.shortestPath(to_airportIDs[i], target);
        
        assert(abs(shortest_distance - solutions[i]) < 0.1);
    }
    cout << "Dijkstras on Simple Paths: ALL ASSERTIONS PASSED" << endl;
    int source = 5;
    vector<int> destinations = {1,2,3};
    vector<int> five_one_expect = {5,6,4,3,1};
    vector<int> five_two_expect = {5,6,4,3,1,2};
    vector<int> five_three_expect = {5,6,4,3};
    vector<vector<int>> expected_vector = {
        five_one_expect,
        five_two_expect,
        five_three_expect
    };
    for (int idx = 0; idx < (int) destinations.size(); ++idx) {
        vector<int> s = init.findPath(source,destinations[idx]);

        assert(s == expected_vector[idx]);
    }
    cout << "TESTING SHORTEST PATH: ALL ASSERTIONS PASSED" << endl;

}


int main() {
    ReadRoutesSimple();
    ReadAirportsSimple();
    SimplePathExist();
    testSimpleGraphOutput();
    TestsAdjacencyListsSimple();
    TestShortestPath();
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "-----ALL TESTS PASSED-------" << endl;
}