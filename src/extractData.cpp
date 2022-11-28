#include "../includes/extractData.h"


void Project::readRoutes(string path) {
    string line;
    ifstream ifs;
    //Make it your own absolute path. We'll find a fix later
    // ifs.open("/Users/aryanmalhotra/Desktop/cs225project/OpenFlights-CS225-FinalProject/src/firstRoutes.dat");
    ifs.open(path);
    if (ifs.is_open()) {
        // cout << "ifs is open"<<endl;
        int t = 0;
        while(getline(ifs,line)) {
            //Filter data
            t++;
            int count = 0;
            string temp = "";
            bool missing = false;
            for (int i = 0; i < (int) line.length(); i++) {
                if (line.substr(i,1) == ",") {
                    if (count == 3 && temp != "\\N") from.push_back(stoi(temp));
                    else if (count == 3 && temp == "\\N") missing = true;
                    
                    if (count == 5 && temp != "\\N" && !missing) to.push_back(stoi(temp));
                    else if (count == 5 && temp == "\\N" && !missing) {
                        from.pop_back();
                    }

                    temp = "";
                    count++;
                } else if (count == 3 || count == 5) {
                    temp += line[i];
                }
            }
            // cout << "Err: " << t <<endl;
        }
        ifs.close();
    }
    // cout << "Count From: " << from.size() << endl;
    // cout << "Count To: " << to.size() << endl;
    // print statement
    // for (int i = 0; i < (int) from.size(); i++) {
    //     cout << "From: " << from[i] << "    To: " << to[i] << endl;
    // }
}

void Project::readAirports(string path) {
    string record;
    ifstream airport_csv;
    // replace with absolute path of your own
    airport_csv.open(path);
    if (airport_csv.is_open()) {
        while (getline(airport_csv, record)) {
            int quotes = 0;
            int count = 0;
            string temp = "";
            for (int i = 0; i < (int) record.length(); i++) {
                if (record.substr(i,1) == "\"") quotes++;
                if (record.substr(i,1) == "," && quotes % 2 == 0) {
                    if (count == 0) airports.push_back(stoi(temp));
                    else if (count == 6) latitudes.insert(std::pair<int, double>(airports.back(), stod(temp)));
                    else if (count == 7) longitudes.insert(std::pair<int, double>(airports.back(), stod(temp)));
                    temp = "";
                    count++;
                } else if (count == 0 || count == 6 || count == 7) {
                    temp += record[i];
                }
            }
        }
        airport_csv.close();
    }
    // for (int i = 0; i < (int) airports.size(); i++) {
    //     cout << "Airport: " << airports[i] <<  endl;
    //     cout << "Latitude: " << latitudes[airports[i]] <<  endl;
    //     cout << "Longitude: " << longitudes[airports[i]] <<  endl;
    // }
    // cout << "Size: " << airports.size() << endl;
}

void Project::createAdjacencyList() {
    for (int i = 0; i < (int) airports.size(); i++) {
        if (adjacencyLists.find(airports[i]) == adjacencyLists.end()) {
            vector<int> temp;
            adjacencyLists.insert(pair<int, vector<int> > (airports[i], temp));
        }
    }
    for (int i = 0; i < (int) from.size(); i++) {
        if (adjacencyLists.find(from[i]) != adjacencyLists.end() && adjacencyLists.find(to[i]) != adjacencyLists.end()) {
            adjacencyLists[from[i]].push_back(to[i]); //routes are directional
        }
    }
    // for (int i = 0; i < (int) adjacencyLists[1].size(); i++) {
    //     cout << adjacencyLists[1][i] << "   ";
    // }
}
//DFS for the graph components
void Project::DFS(int v) {
    int cap = 0;
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end() && cap < 100; ++x)  {
        verticesLabel[x->first] = false; 
        cap++;
    }
    DFSHelper(v);
}
void Project::DFSHelper(int v) {
    verticesLabel[v] = true;
    std::cout << to_string(v) << " ";
    for (auto x = adjacencyLists[v].begin(); x != adjacencyLists[v].end(); ++x)  {
        if (!verticesLabel[*x]) {
            DFSHelper(*x);
        }
    }
}

// bool DFS(int from, int to) {
//     // for dfs I'll need a stack,
//     DFSHelper(from, to);
// }
void Project::printMap() {
    int cap = 0;
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end() && cap < 100; ++x) {
        // x shoudl be a pair of int and vector
        cout << x->first << " Neighhbors: ";
        for (unsigned i = 0; i < x->second.size() && i < 100;++i) {
            cout << x->second[i] << " ";
        }
        cout << endl;
        cap++;
    }
}

void Project::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = title + ".dot";
    neatoFile.open(filename.c_str());
    neatoFile<<"digraph {\n";
    int cap = 0;
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end() && cap < 100; ++x) {
        // x shoudl be a pair of int and vector
        
        for (unsigned i = 0; i < x->second.size() && i < 100;++i) {
            neatoFile << (x->first)<<"->";
            neatoFile << x->second[i] << "\n";
        }
        if(x->second.size()==0){
            neatoFile<<(x->first)<<"\n";
        }
        cap++;
    }
    neatoFile<<"}";



    neatoFile.close();
    string command = "dot "+ title +".dot -Tpng -o test.png";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output graph saved as " << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Run `make install_graphviz` first to install dependencies." << endl;
    }
}

double Project::calculateDistance(double latFrom, double longFrom, double latTo, double longTo) {
    return sqrt(((latFrom - latTo) * (latFrom - latTo)) + ((longFrom - longTo) * (longFrom - longTo)));
}

void Project::createEdgeWeights() {
    for (int i = 0; i < (int) from.size(); i++) {
        vector<int> temp;
        temp.push_back(from[i]);
        temp.push_back(to[i]);
        if (latitudes.find(from[i]) != latitudes.end() && latitudes.find(to[i]) != latitudes.end()) {
            if (longitudes.find(from[i]) != longitudes.end() && longitudes.find(to[i]) != longitudes.end()) {
                double weight = calculateDistance(latitudes[from[i]], longitudes[from[i]], latitudes[to[i]], longitudes[to[i]]);
                edgesLabel.insert(pair<vector<int>, double>(temp, weight));
            }
        }
    }
    // for (auto it = edgesLabel.begin(); it != edgesLabel.end(); it++) {
    //     cout << "From: " << it->first[0] << "   To :" << it->first[1] << "    Weight: " << it->second << endl;
    // }
}