#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "MapLoader.h"

using namespace std;

// Default constructor
MapLoader::MapLoader() {
    filePath = "";
}

// Parametrized constructor
MapLoader::MapLoader(const string& filePath) {
    this->filePath = filePath;
    this->resultMap = loadMap(this->filePath);
}

//Copy Constructor
MapLoader::MapLoader(MapLoader &mapLoader) {
    filePath = mapLoader.filePath;
    delete this->resultMap;
    this->resultMap = nullptr;

    this->resultMap = new Map(*mapLoader.resultMap);
}

// Assignment Operator Overload
MapLoader &MapLoader::operator=(const MapLoader &mapLoader) {
    //handling self assignment
    if (this != &mapLoader) {
        this->filePath = mapLoader.filePath;

        delete resultMap;
        resultMap = nullptr;
        resultMap = new Map(*mapLoader.resultMap);
    }
    return *this;
}

// Destructor
MapLoader::~MapLoader() {
    filePath = nullptr;
    delete resultMap;
    resultMap = nullptr;
}

ostream &operator<<(ostream &output, const MapLoader &mapLoader) {
    return output;
}

Map* MapLoader::getMap() {
//    this->resultMap = loadMap(this->filePath);
    return this->resultMap;
}

string MapLoader::getMapName() {
    return this->filePath;
}

// Reading the input file and generating a valid map
Map* MapLoader::loadMap(const string &filePath) {
    std::ifstream input(filePath);
    string line;

    vector<Territory*> countryList; // Vector holding all the countries read from file
    // Vector fo vectors
    // Basically the inner vector contains the countries that share border which forms a continent
    // These continents are place in in another vector to store all of the continents
    // Will be needed to form a graph
    vector<vector<Territory*>*> continentList;
    vector<string*> continentName; // Storing the name of the continents read from the file

    // Pointer to a graph made up of the IDs of the countries
    auto mapGraph = new Graph<int>;
    // Data structure type map to store the the key value pairs of countries and continents
    map<int, string> countryMap{};
    // vector to hold the information regarding borders between countries
    vector<vector<string>> borderSpecs;

    // Looping through all lines of the file
    while (!input.eof()) {
        //reading new line
        getline(input, line, '\n');

        //------------------------CONTINENTS VECTOR---------------------------

        // When reader hits the continents list
        if (line.find("[continents]") == 0) {
            // read new line
            getline(input, line);

            int continentVectorSize = 1;

            // End of continents section
            while(line.find("[countries]") != 0) {
                if (line == "\r") {
                    break;
                }

                // Creating a new vector of territories for each continent
                continentList.push_back(new vector<Territory*>());
                continentName.push_back(&parseString(line).at(1)); // getting continent name

                // read new line
                getline(input, line);
            }
        }

        //------------------------COUNTRIES VECTOR----------------------------

        // When reader hits the continents list
        if (line.find("[countries]") == 0) {

            // read new line
            getline(input, line);

            // End of countries section
            while(line.find("[borders]") != 0) {
                if (line == "\r" || line == "\n" || line.empty()) {
                    break;
                }

                // New territory for each country read
                auto* t = new Territory(&parseString(line).at(1));
                // Key : territory ID, Value : Continent
                countryMap.insert(pair<int, string>(t->getId(), parseString(line).at(2)));
                countryList.push_back(t); // Adding territory to list

                // read new line
                getline(input, line);
            }

            // Adding the country lists (continents) to the continent vector
            // Looping same number of times as number of continents
            // Checking if the country's continent ID matches the index of thr continent in the vector
            // Adding the country to the right continent
            for (int i = 0; i < continentList.size(); i++) {
                for (auto j : countryMap) {
                    if (stoi(j.second) == i + 1) { // second is the continent ID
                        for (auto k : countryList) {
                            if (j.first == k->getId()){
                                continentList.at(i)->push_back(k); // Accessing vector of territories
                            }
                        }
                    }
                }
            }
        }

        //--------------------------BUILDING GRAPH----------------------------

        // Adding all the territory vertices to the graph
        // Looping through continents and their territories
        // adding a vertex for each continent in the mapGraph
        for (auto cont : continentList) {
            for (auto terr : *cont) {
                mapGraph->add_vertex(terr->getId());
            }
        }

        // When reader hits the borders list
        if  (line.find("[borders]") == 0) {
            getline(input, line);

            while (!input.eof()) {
                // getting all borders
                 borderSpecs.push_back(parseString(line));

                // Creating the edges between countries
                // Looping through the graph
                // adding an edge between all the territories that share a border
                for (auto vert : mapGraph->get_vertices()) {
                    for(auto borders : borderSpecs) {
                        if (vert == stoi(borders.at(0))) { // index 0 is the ID of the country
                            for (int i = 1 ; i < borders.size(); i++) { // No self-border
                                mapGraph->add_edge(vert, stoi(borders.at(i))); // add edge between 2 countries
                            }
                        }
                    }
                }
                // read new line
                getline(input, line);
            }
        }
    }

    // Vector to store all of the continents and their territories
    auto* continentVector = new vector<Continent*>();
    for (int i = 0; i < continentList.size(); i++) {
        continentVector->push_back(new Continent(continentName.at(i), mapGraph, continentList.at(i)));
    }

    // closing the input stream
    input.close();

    // returning new Map Object
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




