#include "extractData.h"


void Project::readRoutes(string path) {
    string line;
    ifstream ifs;
    //Make it your own absolute path. We'll find a fix later
    // ifs.open("/Users/aryanmalhotra/Desktop/cs225project/OpenFlights-CS225-FinalProject/src/firstRoutes.dat");
    ifs.open(path);
    if (ifs.is_open()) {
        cout << "ifs is open"<<endl;
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
    cout << "Count From: " << from.size() << endl;
    cout << "Count To: " << to.size() << endl;
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
                    else if (count == 6) latitudes.push_back(stod(temp));
                    else if (count == 7) longitudes.push_back(stod(temp));
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
    //     cout << "Latitude: " << latitudes[i] <<  endl;
    //     cout << "Longitude: " << longitudes[i] <<  endl;
    // }
    // cout << "Size: " << airports.size() << endl;
}

void Project::createAdjacencyList() {
    for (int i = 0; i < (int) airports.size(); i++) {
        if (adjacencyLists.find(airports[i]) == adjacencyLists.end()) {
            vector<int> temp;
            adjacencyLists.insert(pair<int, vector<int>>(airports[i], temp));
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
    neatoFile<<"layout=twopi\n"
                <<"normalize=true\n"
                <<"ranksep=3;\n"
                <<"ratio=auto;\n";
    //neatoFile<<"node [shape = circle];\n";
    int cap = 0;
    int localcount=0;
    int maxcount=0;
    int maxNode=0;
    for (auto x = adjacencyLists.begin(); x != adjacencyLists.end() && cap < 100; ++x) {
        // x shoudl be a pair of int and vector
        localcount=0;
        for (unsigned i = 0; i < x->second.size() && i < 100;++i) {
            neatoFile << (x->first)<<"->";
            neatoFile << x->second[i] << "\n";
            localcount++;
        }
        if(localcount>maxcount){
            maxcount=localcount;
            maxNode=x->first;
        }
        if(x->second.size()==0){
            neatoFile<<(x->first)<<"\n";
        }
        cap++;
    }
    cout<<maxNode<<endl;
    neatoFile<<"root=49;";
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