#include "extractData.h"


void Project::readRoutes() {
    string line;
    ifstream ifs;
    //Make it your own absolute path. We'll find a fix later
    // ifs.open("/Users/aryanmalhotra/Desktop/cs225project/OpenFlights-CS225-FinalProject/src/firstRoutes.dat");
    ifs.open("/workspaces/cs225/revised/release-f22/CS225-final/OpenFlights-CS225-FinalProject/src/firstRoutes.dat");
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
            cout << "Err: " << t <<endl;
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

void Project::readAirports() {
    string record;
    ifstream airport_csv;
    airport_csv.open("OpenFlights-CS225-FinalProject/data/airports.dat");
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
        // cout << "Latitude: " << latitudes[i] <<  endl;
        // cout << "Longitude: " << longitudes[i] <<  endl;
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
    for (int i = 0; i < (int) adjacencyLists[1].size(); i++) {
        cout << adjacencyLists[1][i] << "   ";
    }
}