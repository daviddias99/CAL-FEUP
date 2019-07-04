#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

int randomBetween(int a, int b){

    return rand() %  (b-a) + a;
}

int main() {

    int nPerson;
    vector<string> names;

    ifstream nameFile,nodeFile;
    ofstream output;

    nameFile.open("names.txt");
    nodeFile.open("nodes_fafe.txt");
    output.open("output.txt");

    srand(time(NULL));

    cin >> nPerson;


    while(!nameFile.eof()){

        string line;

        getline(nameFile,line);

        names.push_back(line);
    }

    string nodeCnt;
    getline(nodeFile,nodeCnt);

    vector<unsigned int> nodeIDs;

    while (!nodeFile.eof()) {

        string currentLine;

        getline(nodeFile, currentLine);
        stringstream line(currentLine);

        char tempChar;
        unsigned int ID;

        line >> tempChar >> ID;

        nodeIDs.push_back(ID);
    }

    for(int i = 0; i < nPerson; i++){

        string newLine = "( " + to_string(i) + " , ";

        int hour1 = randomBetween(6,22);
        int minute1 = randomBetween(0,59);
        int delay = randomBetween(30,120);

        int hour2 = hour1 +(minute1 + delay) / 60;
        int minute2 = (minute1 + delay) % 60;

        newLine += names.at(randomBetween(0,names.size()-1)) + " , ";

        if(minute1 < 10)
            newLine += to_string(hour1) + ":" + "0"+to_string(minute1) + " , ";
        else
            newLine += to_string(hour1) + ":" + to_string(minute1) + " , ";
        newLine += to_string(hour2) + ":" + to_string(minute2) + " , ";
        newLine += to_string(nodeIDs.at(randomBetween(0,nodeIDs.size()-1))) + " , " + to_string(nodeIDs.at(randomBetween(0,nodeIDs.size()-1)))  + " )";

        output << newLine << endl;
    }


    return 0;
}