#include "extractData.h"

void readData() {
    string line;
    ifstream ifs("../data/sample/firstRoutes.dat");
    if (ifs.is_open()) {
        while(getline(ifs,line)) {
            cout << line << endl;
        }
        ifs.close();
    }
}
void C::help() {
    cout << "helped"<<endl;
}