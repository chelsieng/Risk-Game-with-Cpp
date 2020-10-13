#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "MapLoader.h"

using namespace std;

// Default constructor
MapLoader::MapLoader() : fileName{""}
{}

// Parametrized constructor
MapLoader::MapLoader(string fileName) {
    this->fileName = fileName;
}

//void MapLoader::copy(const MapLoader &mapLoader) {
//    fileName = mapLoader.fileName;
//}

//Copy Constructor
MapLoader::MapLoader(MapLoader &mapLoader) {
    fileName = mapLoader.fileName;
}

// Assignment Operator Overload
MapLoader &MapLoader::operator=(const MapLoader &mapLoader) {
    //handling self assignment
    if (this != &mapLoader) {
        this->fileName = mapLoader.fileName;
    }
    return *this;
}

// Destructor
MapLoader::~MapLoader() {
    fileName = nullptr;
}

ostream &operator<<(ostream &output, const MapLoader &mapLoader) {
    return output;
}

// Reading the input file and generating a valid map
void MapLoader::loadMap(string fileName) {
    std::ifstream input(fileName);
    string line;

    vector<vector<Territory*>*> continentList;
    vector<Territory*> countryList;
    map<int, string> countryMap{}; //= new map<int, int>();

    while (!input.eof()) {
        getline(input, line, '\n');

        //------------------------CONTINENTS VECTOR---------------------------
        if (line.find("[continents]") == 0) {
            getline(input, line);

            int continentVectorSize = 1;

            // End of continents section
            while(line.find("[countries]") != 0) {
                if (line == "\r") {
                    break;
                }

                cout << line << endl;
                continentList.push_back(new vector<Territory*>());
                getline(input, line);
            }
        }

        //------------------------COUNTRIES VECTOR----------------------------
        if (line.find("[countries]") == 0) {
            getline(input, line);
            int counter = 1;

            while(line.find("[borders]") != 0) {
                // End of continents section
                if (line == "\r" || line == "\n" || line.empty()) {
                    counter--;
                    break;
                }

                Territory* t = new Territory(&parseString(line).at(1));
                countryMap.insert(pair<int, string>(t->getId(), parseString(line).at(2)));
                countryList.push_back(t);

                getline(input, line);
            }

            for (int i = 0; i < continentList.size(); i++) {
                for (auto j : countryMap) {
                    if (stoi(j.second) == i + 1) {
                        for (auto k : countryList) {
                            if (j.first == k->getId()){
                                continentList.at(i)->push_back(k);
                            }
                        }
                    }
                }
                if (i == 5) {
                    cout << "hello";
                }
            }
        }

        //--------------------------BORDERS VECTOR----------------------------
    }







    input.close();
}

std::vector<string> MapLoader::parseString(string s) {
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> result(begin, end);

    return result;
}




