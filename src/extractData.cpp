#include "../includes/extractData.h"

Project::Project(string routes_path, string airports_path){
    readAirports(airports_path);
    readRoutes(routes_path);
    createAdjacencyList();
}
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
    } else {
        cout << "problem opening path" << endl;
    }
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
bool Project::DFS(int v, int w) {
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end(); ++x)  {
        verticesLabel[x->first] = false; 

    }
    return DFSHelper(v, w);
}
bool Project::DFSHelper(int v, int w) {
    if (w == v) {
        return true;
    }
    verticesLabel[v] = true;
    for (auto x = adjacencyLists[v].begin(); x != adjacencyLists[v].end(); ++x)  {
        if (!verticesLabel[*x]) {
            if (DFSHelper(*x, w)) {
                return true;
            }
        }
    }
    return false;
}

void Project::printConnected(int v,string title) {
    std::ofstream neatoFile;
    string neatoFileStr="";
    string filename = title + ".dot";
    neatoFile.open(filename.c_str());
    neatoFile<<"digraph {\n";
    neatoFile<<"overlap=false;\n"
                <<"fontsize=6;\n"
                <<"normalize=true;\n"
                <<"ranksep=3;\n"
                <<"height=0.1;\n"
                <<to_string(v)+"[color=\"red\"]\n";
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end(); ++x)  {
        verticesLabel[x->first] = false; 
    
    }
    printConnectedHelper(v, neatoFileStr);
    //neatoFileStr.erase(neatoFileStr.size()-2,2);
    neatoFile<<neatoFileStr;
    neatoFile<<"}";

    neatoFile.close();
    string command = "twopi -Tpng "+ title +".dot -o DFS.png";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output graph saved as " << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Run `make install_graphviz` first to install dependencies." << endl;
    }
}
void Project::printConnectedHelper(int v, string & neatoFile) {
    verticesLabel[v] = true;
    //std::cout << v<<" ";

    for (auto x = adjacencyLists[v].begin(); x != adjacencyLists[v].end(); ++x)  {
        neatoFile+=to_string(v) +"->";
        if (!verticesLabel[*x]) {
            neatoFile += to_string(*x) + "[arrowhead=halfopen]\n";
            printConnectedHelper(*x, neatoFile);
        }
    }
}

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
    if (cap >= 100) cout << "limiting output, capped at 100 nodes" << endl;
}

void Project::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = title + ".dot";
    neatoFile.open(filename.c_str());
    neatoFile<<"digraph {\n";
    neatoFile<<"layout=twopi;\n"
                <<"overlap=false;\n"
                <<"fontsize=6;\n"
                <<"normalize=true;\n"
                <<"ranksep=3;\n"
                <<"ratio=auto;\n"
                <<"height=0.1;\n";
    //neatoFile<<"node [shape = circle];\n";
    int localcount=0;
    int maxcount=0;
    int maxNode=0;
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end(); ++x) {
        // x shoudl be a pair of int and vector
        localcount=0;
        for (unsigned i = 0; i < x->second.size();++i) {
            neatoFile << (x->first)<<"->";
            neatoFile << x->second[i] << "[arrowhead=halfopen]\n";
            localcount++;
        }
        if(localcount>maxcount){
            maxcount=localcount;
            maxNode=x->first;
        }
        /*if(x->second.size()==0){
            neatoFile<<(x->first)<<"\n";
        }*/
    }
    cout<<maxNode<<endl;
    //neatoFile<<"root="<<maxNode;
    neatoFile<<"}";



    neatoFile.close();
    string command = "circo -Tpng "+ title +".dot -o test.png";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output graph saved as " << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Run `make install_graphviz` first to install dependencies." << endl;
    }
}

/*
void Project::printTo(){
    
    for(size_t i=0;i<to.size();i++){
        std::cout<<from[i]<<" -> "<<to[i]<<std::endl;
    }
}*/
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

int Project::minDistance(map<int, double> dist, map<int, bool> sptSet) {
    int min = INT_MAX;
    int min_airport = -1;
    for (int i = 0; i < (int) airports.size(); i++) {
        int curr = airports[i];
        if (sptSet[curr] == false && dist[curr] <= min) {
            min = dist[curr];
            min_airport = curr;
        }
    }
    return min_airport;
}

map<int, double> Project::dijkstras(map<int, vector<int>> graph, int source) {
    map<int, double> dist;
    map<int, bool> sptSet;
    for (int i = 0; i < (int) airports.size(); i++) {
        dist.insert(pair<int, double> (airports[i], INT_MAX));
        sptSet.insert(pair<int, bool> (airports[i], false));
    }
    dist[source] = 0;
    for (int count = 0; count < (int) airports.size() - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        vector<int> neighbours = graph[u];
        for (int i = 0; i < (int) neighbours.size(); i++) {
            int v = neighbours[i];
            vector<int> from_to = {u, v};
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + edgesLabel[from_to] < dist[v]) {
                dist[v] = dist[u] + edgesLabel[from_to];
            }
        }
    }
    return dist;
}

double Project::shortestPath(int from, int to) {
    map<int, double> shortest_paths = dijkstras(adjacencyLists, from);
    return shortest_paths[to];
}