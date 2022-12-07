#include "../includes/project.h"

Project::Project(string routes_path, string airports_path,string title){
    readAirports(airports_path);
    readRoutes(routes_path);
    createAdjacencyList();
    createEdgeWeights();
    printFullMap(title);
    
}
void Project::readRoutes(string path) {
    string line;
    ifstream ifs;
    ifs.open(path);
    if (ifs.is_open()) {

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

        }
        ifs.close();
    } else {
        cout << "problem opening path" << endl;
    }
}

void Project::readAirports(string path) {
    string record;
    ifstream airport_csv;

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
                    else if (count == 5) {
                        airportCode.push_back(temp.substr(1, temp.size() - 2));
                        airportMap.insert(std::pair<string, int>(temp.substr(1, temp.size() - 2), airports.back()));
                    }
                    else if (count == 6) latitudes.insert(std::pair<int, double>(airports.back(), stod(temp)));
                    else if (count == 7) longitudes.insert(std::pair<int, double>(airports.back(), stod(temp)));
                    temp = "";
                    count++;
                } else if (count == 0 || count == 6 || count == 7 || count == 5) {
                    temp += record[i];
                }
            }
            
        }
        airport_csv.close();
    }

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
            bool found = false;
            vector<int> temp2=adjacencyLists[from[i]];
            for(size_t j=0;j<temp2.size();j++){
                if(temp2[j]==to[i]){
                    found=true;
                    break;
                }
            }
            if(!found){
                adjacencyLists[from[i]].push_back(to[i]); //routes are directional
            }
        }
    }

}
//DFS for the graph components
bool Project::AirportConnection(string source, string destination) {
    if(latitudes.find(airportMap[source])==latitudes.end() ||latitudes.find(airportMap[destination])==latitudes.end()){
        return false;
    }
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end(); ++x)  {
        verticesLabel[x->first] = false; 

    }
    return DFSHelper(airportMap[source], airportMap[destination]);
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





void Project::printFullMap(string title) const
{
    std::ofstream neatoFile;
    string filename = title + ".dot";
    neatoFile.open(filename.c_str());
    neatoFile<<"digraph {\n";
    neatoFile<<"layout=neato;\n";
    neatoFile<<"scale=0.5;\n";
    
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end(); ++x) {
        int x_first = (*x).first;
        neatoFile<< "\""<<getCode(x_first)<<"\" [pos=\""<<longitudes.at(x_first)<<","<<latitudes.at(x_first)<<"!\"]\n";
    }
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end(); ++x) {
        for (unsigned i = 0; i < x->second.size();++i) {
            int x_first =(*x).first;
            int x_second =(*x).second[i];
            vector<int>v;
            v.push_back(x_first);
            v.push_back(x_second);
            neatoFile << "\""<<getCode(x_first)<<"\"->";
            neatoFile << "\""<<getCode(x_second)<<"\" [label=\""<<to_string(edgesLabel.at(v))<<"\"]\n";
        }

        /*if(x->second.size()==0){//prints islands
            neatoFile<<(x->first)<<"\n";
        }*/
        
    }
    neatoFile<<"}";

    neatoFile.close();
    string command = "neato -Tpng "+ title +".dot -o "+title+".png";
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
    adjacencyListDijkstras.clear();
    for (int i = 0; i < (int) airports.size(); i++) {
        dist.insert(pair<int, double> (airports[i], INT_MAX));
        sptSet.insert(pair<int, bool> (airports[i], false));
    }
    dist[source] = 0;
    map<int, vector<int>> track;
    for (int count = 0; count < (int) airports.size() - 1; count++) {
        int u = minDistance(dist, sptSet);
        if (adjacencyListDijkstras.find(u) == adjacencyListDijkstras.end()) {
            adjacencyListDijkstras.insert(pair<int, vector<int> > (u, vector<int>()));
        }
        sptSet[u] = true;
        vector<int> neighbours = graph[u];
        for (int i = 0; i < (int) neighbours.size(); i++) {
            int v = neighbours[i];
            vector<int> from_to = {u, v};
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + edgesLabel[from_to] < dist[v]) {
                adjacencyListDijkstras[u].push_back(v);
                if (track.find(v) != track.end()) {
                    std::vector<int>::iterator it = std::find (adjacencyListDijkstras[track[v].back()].begin(), adjacencyListDijkstras[track[v].back()].end(), v);
                    adjacencyListDijkstras[track[v].back()].erase(it);
                    track[v].push_back(u);
                } else {
                    track.insert(pair<int, vector<int>> (v, vector<int>({u})));
                }
                dist[v] = dist[u] + edgesLabel[from_to];
            }
        }
    }
    return dist;
}

double Project::shortestPath(string from, string to) {
     if (!AirportConnection(from, to)) {                      // Checks if two nodes have a path, true = nodes have path -- false = nodes have NO connection
         cout<<"No Path Exists from "<<from<<" to "<<to<<endl;
         return 0;
     }
    map<int, double> shortest_paths = dijkstras(adjacencyLists, airportMap[from]);
    string t= from+"_"+to;
    printMST(t,from,to);
    cout << "Calculating Shortest Path from MST..."<<endl;
    printSinglePath(t,from,to);


    adjacencyListDijkstras.clear();
    return shortest_paths[airportMap[to]];
}
    

 void Project::printMST(string title,string source,string destination)const{  
    std::ofstream neatoFile;
    string filename = title + ".dot";
    neatoFile.open(filename.c_str());
    neatoFile<<"digraph {\n";
    neatoFile<<"layout=neato;\n";
    neatoFile<<"scale=0.5;\n";

    neatoFile<<"\""<<source<<"\" [color=\"red\",style=\"filled\"]\n";
    neatoFile<<"\""<<destination<<"\" [color=\"green\",style=\"filled\"]\n";
    for (auto x = adjacencyListDijkstras.begin(); x != adjacencyListDijkstras.end(); ++x) {
        int x_first = (*x).first;
        neatoFile<< "\""<<getCode(x_first)<<"\" [pos=\""<<longitudes.at(x_first)<<","<<latitudes.at(x_first)<<"!\"]\n";
    }

    for (auto x = adjacencyListDijkstras.begin(); x != adjacencyListDijkstras.end(); ++x) {
        for (unsigned i = 0; i < x->second.size();++i) {
            int x_first =(*x).first;
            int x_second =(*x).second[i];
            vector<int>v;
            v.push_back(x_first);
            v.push_back(x_second);
            neatoFile << "\""<<getCode(x_first)<<"\"->";
            neatoFile << "\""<<getCode(x_second)<<"\" [label=\""<<to_string(edgesLabel.at(v))<<"\"]\n";
        }
        /*if(x->second.size()==0){//prints islands
            neatoFile<<(x->first)<<"\n";
        }*/
    }
    
    neatoFile<<"}";



    neatoFile.close();
    string command = "neato -Tpng "+ title +".dot -o "+title+".png";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output spanning tree for "<< source <<" saved as " << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Run `make install_graphviz` first to install dependencies." << endl;
    }
 }

 string Project::getCode(const int id)const{
    for(size_t i=0;i<airports.size();i++){
        if(airports[i]==id){
            return airportCode[i];
        }
    }
    return " ";
 }

void Project::printSinglePath(string name,string source,string dest){
     std::ofstream neatoFile;
     string title=name+"_singlepath";
     string filename =title+".dot";
     neatoFile.open(filename.c_str());
     neatoFile<<"digraph {\n";
     neatoFile<<"layout=neato;\n";
    
    neatoFile<<"\""<<source<<"\" [color=\"red\",style=\"filled\"]\n";
    neatoFile<<"\""<<dest<<"\" [color=\"green\",style=\"filled\"]\n";
    vector<int> v=findPath(airportMap[source], airportMap[dest]);

    for (auto x = adjacencyListDijkstras.begin(); x != adjacencyListDijkstras.end(); ++x) {
        int x_first = (*x).first;
        if(getCode(x_first)!=source && getCode(x_first)!=dest && std::find(v.begin(), v.end(), x_first) != v.end()){
            neatoFile<< "\""<<getCode(x_first)<<"\" [color=\"yellow\",style=\"filled\" , pos=\""<<longitudes.at(x_first)<<","<<latitudes.at(x_first)<<"!\"]\n";
        }
        neatoFile<< "\""<<getCode(x_first)<<"\" [pos=\""<<longitudes.at(x_first)<<","<<latitudes.at(x_first)<<"!\"]\n";
    }
    for(size_t i=0;i<v.size();i++){
        if(i+1<v.size()){
            vector<int>vect;
            vect.push_back(v[i]);
            vect.push_back(v[i+1]);
            neatoFile<<"\""<<getCode(v[i])<<"\"->"<<"\""<<getCode(v[i+1])<<"\" [penwidth=10, color=\"blue\""<<" , label=\""<<to_string(edgesLabel.at(vect))<<"\""<<"]\n";
        }

    }
     neatoFile<<"}";
     neatoFile.close();
     string command = "neato -Tpng " + title+".dot -o "+ title +".png";
     int result = system(command.c_str());


     if (result == 0) {
         cout << "Output saved as "+ title +".png" << endl;
     } else {
         cout << "Failed to generate visual output graph using `neato`. Run `make install_graphviz` first to install dependencies." << endl;
     }
}
vector<int> Project::findPath(int source, int dest){
    queue<int> q;
    set<int>visited;
    unordered_map<int,int> parent;
    q.push(source);
    while(!q.empty()){
        int node=q.front();

        q.pop();
        if(node==dest){
            vector<int>path;
            int current=dest;
            while(current!=source){
                path.push_back(current);
                
                current=parent[current];
                
            }
            path.push_back(source);
            std::reverse(path.begin(),path.end());
            return path;
        }
        visited.insert(node);
        for(const auto & neighbor:adjacencyListDijkstras[node]){
            if(visited.count(neighbor)==0){
                q.push(neighbor);
                
                parent[neighbor]=node;
                

            }
        }
    }
    return {};
}

