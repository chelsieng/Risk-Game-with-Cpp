#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>
#include "MapLoader.h"

using namespace std;

// Default constructor
MapLoader::MapLoader() {
    filePath = "";
    resultMap = nullptr;
}

// Parametrized constructor
MapLoader::MapLoader(const string &filePath) {
    this->filePath = filePath;
    resultMap = loadMap(this->filePath);
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
    delete resultMap;
    resultMap = nullptr;
}

ostream &operator<<(ostream &output, const MapLoader &mapLoader) {
    return output;
}

Map *MapLoader::getMap() {
    return this->resultMap;
}

string MapLoader::getMapName() {
    return this->filePath;
}

// Reading the input file and generating a valid map
Map *MapLoader::loadMap(const string &filePath) {
    Map *result;
    std::ifstream input(filePath);
    string line;
    int edge;
    vector<Territory *> countryList; // Vector holding all the countries read from file
    // Vector of vectors
    // Basically the inner vector contains the countries that share border which forms a continent
    // These continents are place in another vector to store all of the continents
    // Will be needed to form a graph
    vector<vector<Territory *> *> continentList;
    vector<string> continentName; // Storing the name of the continents read from the file
    // Pointer to a graph made up of the IDs of the countries
    auto mapGraph = new Graph<int>;
    // Data structure type map to store the the key value pairs of countries and continents
    map<int, string> countryMap{};
    // vector to hold the information regarding borders between countries
    string borderInfo;

    // Error if file cannot be opened
    if (!input) {
        cout << filePath << " cannot be opened." << endl;
        return nullptr;
    }

    // reading map file until [continents] header
    while (line.find("[continents]") != 0) {
        // file does not contain [continent] header
        if (input.eof()) {
            cout << "Error: Could not load map file, " << filePath << " is invalid." << endl;
            return nullptr;
        }
        getline(input, line);
    }

    // Continents info
    while (true) {
        getline(input, line);
        // End of continent info
        if (line == "\n" || line == "\r" || line.empty()) {
            break;
        }
        // Creating a new vector of territories for each continent
        continentList.push_back(new vector<Territory *>());
        string continent_name = parseString(line).at(0);
        continentName.push_back(continent_name); // getting continent name

    }
    // Reading file up to [countries] header
    while (line.find("[countries]") != 0) {
        // file does not contain [countries] header
        if (input.eof()) {
            cout << "Error: Could not load map file, " << filePath << " is invalid." << endl;
            return nullptr;
        }
        getline(input, line);
    }

    // Countries info
    while (true) {
        getline(input, line);
        // end of countries info
        if (line == "\n" || line == "\r" || line.empty()) {
            break;
        }
        // File does not contain countries info
        if (input.eof()) {
            cout << "Error: Could not load map file, " << filePath << " is invalid." << endl;
            return nullptr;
        }
        // New territory for each country read
        string territoryName = parseString(line).at(1);
        auto *t = new Territory(territoryName);
        countryMap.insert(pair<int, string>(t->getId(), parseString(line).at(2)));
        countryList.push_back(t);
//        cout << line << endl;
    }
    // Adding the country lists (continents) to the continent vector
    // Looping same number of times as number of continents
    // Checking if the country's continent ID matches the index of the continent in the vector
    // Adding the country to the right continent
    for (int i = 0; i < continentList.size(); i++) {
        for (auto &j : countryMap) {
            if (stoi(j.second) == i + 1) { // second is the continent ID
                for (auto k : countryList) {
                    if (j.first == k->getId()) {
                        continentList.at(i)->push_back(k); // Accessing vector of territories
                    }
                }
            }
        }
    }
    // Adding all the territory vertices to the graph
    // Looping through continents and their territories
    // adding vertices of all territories from each continent to the mapGraph
    for (auto cont : continentList) {
        for (auto terr : *cont) {
            mapGraph->add_vertex(terr->getId());
        }
    }
    // Reading file up to [borders] header
    while (line.find("[borders]") != 0) {
        // file does not contain [borders] header
        if (input.eof()) {
            cout << "Error: Could not load map file, " << filePath << " is invalid." << endl;
            return nullptr;
        }
        getline(input, line);
    }

    // Borders info
    while (true) {
        if (line == "\n" || line == "\r" || line == "") {
            break;
        }
        getline(input, line);
        string s = line;
        std::string delimiter = " ";

        string ID = s.substr(0, s.find(delimiter)); //getting territory ID
        int terrID = 0;
        if (ID != "") {
            terrID = stoi(ID); // avoid uncaught exception of "no conversion"
        }
        if (s != "") { //avoiding uncaught exception for later
            borderInfo = s.erase(0, s.find(delimiter) + delimiter.length()); //gets border specs of territory ID
        }

        size_t pos = 0;
        std::string token;
        // Token represents each border specs
        while ((pos = borderInfo.find(delimiter)) != std::string::npos) {
            token = borderInfo.substr(0, pos);
            if (token != "") {
                edge = stoi(token); // avoiding uncaught exception of "no conversion"
            }
            // Creating the edges between countries
            // Looping through the graph
            // adding an edge between all the territories that share a border
            for (auto vert : mapGraph->get_vertices()) {
                if (vert == terrID) { // territory vertex and terrID has the same territory ID
                    mapGraph->add_edge(vert, edge); // add edge between 2 countries
                }
            }
            borderInfo.erase(0, pos + delimiter.length()); // removing already used token from line
        }
        // last token
        if (borderInfo != "\r" && borderInfo != "\n" && borderInfo != "") {
            for (auto vert : mapGraph->get_vertices()) {
                if (vert == terrID) { // territory vertex and terrID has the same territory ID
                    mapGraph->add_edge(vert, (stoi(borderInfo))); // add edge between 2 countries
                }
            }
        }
    }
    // Vector to store all of the continents and their territories
    auto *continentVector = new vector<Continent *>();
    for (int i = 0; i < continentList.size(); i++) {
        continentVector->push_back(new Continent(continentName.at(i), mapGraph, continentList.at(i)));
    }
    input.close();
    cout << filePath << " successfully loaded. Map has been created." << endl;
    // Uncomment to get check neighbours of a vertex
//    for (auto i: mapGraph->get_neighbours(79)) {
//        cout << i << endl;
//    }
    result = new Map(mapGraph, continentVector);
    return result;
}

// Helper method to parse input file lines
std::vector<string> MapLoader::parseString(string s) {
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> result(begin, end);
    return result;
}




