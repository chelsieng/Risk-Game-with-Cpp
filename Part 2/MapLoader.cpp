//
// Created by Raffi Alan Bezirjian on 2020-10-01.
//

#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

MapLoader::MapLoader() {                                      // Default Constructor
    this->fileName = NULL;
}

MapLoader::MapLoader(MapLoader &map){                         // Copy Constructor
    fileName = map.fileName;
}

MapLoader& MapLoader:: operator = (const MapLoader &map){    // Assignment Operator
    return *this;
}

MapLoader::~MapLoader(){                                     // Destructor
    delete this;
}

MapLoader::MapLoader(string fileName) {
    this->fileName = new std::string(fileName);
}

Map* MapLoader::GetMap(string filePath) {
    ReadMap(filePath);
    return resultMap;
}

Map map;
void MapLoader::ReadMap(string fileName) {
    try {
        string line = "";
        bool hasContinent = false;
        bool hasCountries = false;
        bool hasBorders = false;

        ifstream readFile;
        readFile.open(fileName);

        if (!readFile) {
            cout << "Error: Cannot Read The Map File" << endl;
        }
        else {
            while (getline(readFile, line))
            {
                if (line.find("[continents]") == 0) {               // Reading Continents
                    getline(readFile, line);

                    int index = 1;
                    while (line.find("[countries]") != 0) {
                        if (line == "")
                            break;

                        vector<string> attributes = SplitWords(line);
                        Continent* newContinent = new Continent(index, attributes[0], stoi(attributes[1])); //stoi converts str to int
                        map.addContinent(newContinent);
                        cout << "New Continent: " << line << endl;
                        index++;
                        getline(readFile, line);
                    }
                    hasContinent = true;
                }

                if (line.find("[countries]") == 0) {
                    getline(readFile, line);
                    while (line.find("[borders]") != 0) {
                        if (line == "")
                            break;

                        vector<string> attributes = SplitWords(line); 
                        Territory* newCountry = new Territory(stoi(attributes[0]), attributes[1]);
                        map.listOfContinents[stoi(attributes[2]) - 1]->addTerritory(newCountry);
                        map.addTerritory(newCountry);
                        cout << "New Country: " << line << endl;
                        getline(readFile, line);
                    }

                    hasCountries = true;
                }

                if (line.find("[borders]") == 0) {
                    getline(readFile, line);
                    while (!line.empty()) {
                        if (line == "")
                            break;

                        vector<string> adjCountries = SplitWords(line);
                        Territory* t0 = map.getTerritory(stoi(adjCountries[0]));
                        for (int i = 1; i < adjCountries.size(); i++)
                        {
                            Territory* t = map.getTerritory(stoi(adjCountries[i]));
                            map.addAdjTerritory(t0, t);
                        }

                        cout << "New Border: " << line << endl;
                        getline(readFile, line);
                    }
                    hasBorders = true;
                }
            }

            if (hasContinent && hasCountries && hasBorders) {
                cout << "Success: Map File is valid" << endl;
                this->resultMap = &map;
                readFile.close();
            }
            else {
                cout << "Error: Map File is invalid" << endl;
                readFile.close();
            }
        }
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
    }
}

vector<string> MapLoader::SplitWords(string s)
{
    istringstream iss(s);
    vector<string> v;
    while (iss >> s)
    {
        v.push_back(s);
    }
    return v;
}
