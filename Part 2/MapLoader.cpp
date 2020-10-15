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
Map* MapLoader::loadMap(string fileName) {
    std::ifstream input(fileName);
    string line;

    vector<vector<Territory*>*> continentList;
    vector<string*> continentName;
//    vector<Graph<int>*> graphList;
    auto mapGraph = new Graph<int>;
    vector<Territory*> countryList;
    map<int, string> countryMap{};
    vector<vector<string>> borderSpecs;

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

                continentList.push_back(new vector<Territory*>());
                continentName.push_back(&parseString(line).at(1));
//                graphList.push_back(new Graph<int>());
                getline(input, line);
            }
        }
//        else {
//            cout << "This file is INVALID." << endl;
//            return nullptr;
//        }

        //------------------------COUNTRIES VECTOR----------------------------
        if (line.find("[countries]") == 0) {
            getline(input, line);
            int counter = 1;

            while(line.find("[borders]") != 0) {
                // End of countries section
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
            }
        }

        //--------------------------BUILDING GRAPH----------------------------

        // Adding all the territory vertices to the graph
        int clCounter = 0;
        for (auto cl : continentList) {
            for (auto cont : *cl) {
                int glCounter = 0;
//                for (auto gl : graphList) {
                    if (clCounter == glCounter) {
                        mapGraph->add_vertex(cont->getId());
                    }
                    glCounter++;
//                }
            }
            clCounter++;
        }

        // End of borders section
        if  (line.find("[borders]") == 0) {
            getline(input, line);

            while (!input.eof()) {
                // getting all borders
                 borderSpecs.push_back(parseString(line));

                // Creating the edges between countries
//                for (auto gl : graphList) {
                    for (auto vert : mapGraph->get_vertices()) {
                        for(auto borders : borderSpecs) {
                            if (vert == stoi(borders.at(0))) {
                                for (int i = 1 ; i < borders.size(); i++) {
                                    mapGraph->add_edge(vert, stoi(borders.at(i)));
                                }
                            }
                        }
                    }
//                }
                getline(input, line);
            }
        }
    }


    vector<Continent*>* continentVector = new vector<Continent*>();
    for (int i = 0; i < continentList.size(); i++) {
        continentVector->push_back(new Continent(continentName.at(i), mapGraph, continentList.at(i)));
    }



    input.close();

    return new Map(mapGraph, continentVector);
}

// Helper method to parse input file lines
std::vector<string> MapLoader::parseString(string s) {
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> result(begin, end);

    return result;
}




