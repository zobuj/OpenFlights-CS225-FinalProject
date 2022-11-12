#include "extractData.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void readData() {
    
    string line;
    vector<string> from;
    vector<string> to;
    ifstream ifs;
    //Make it your own absolute path. We'll find a fix later
    // ifs.open("/Users/aryanmalhotra/Desktop/cs225project/OpenFlights-CS225-FinalProject/src/firstRoutes.dat");
    ifs.open("/Users/aryanmalhotra/Desktop/cs225project/OpenFlights-CS225-FinalProject/data/raw/routes.dat");
    if (ifs.is_open()) {
        while(getline(ifs,line)) {
            //Filter data
            int count = 0;
            string temp = "";
            for (unsigned i = 0; i < line.length(); i++) {
                if (line.substr(i,1) == ",") {
                    if (from.size() == to.size() && count == 2) from.push_back(temp);
                    else if (count == 4) to.push_back(temp);
                    temp = "";
                    count++;
                } else if (count == 2 || count == 4) {
                    temp += line[i];
                }
            }
        }
        ifs.close();
    }
    for (unsigned i = 0; i < from.size(); i++) {
        cout << "From: " << from[i] << "    To: " << to[i] << endl;
    }
}