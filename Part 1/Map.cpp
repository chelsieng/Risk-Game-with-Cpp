#include <vector>
#include <string>
#include <iostream>

#include "Map.h"

using namespace std;
using namespace graph;
int Army::Army::counter = 0;

//Constructor for armies of player
Army::Army(Player *player) {
    owner = player;
    *id = ++counter;
}

void Army::Army::copy(const Army &army) {
    owner = new Player(*army.owner);
    *id = ++counter;
}

Army::Army(const Army &army) {
    owner = new Player(*army.owner);
    *id = ++counter;
} //End of copy constructor

Army::~Army() {
    delete owner;
    delete id;
    --counter;
} //End of destructor

Army &Army::operator=(const Army &army) {
    //handling self assignment
    if (this != &army) {
        if (owner != nullptr) {
            delete owner; //Handling memory
        }
        copy(army);
    }
    return *this;
} //End of assignment operator

//get ID of army
int Army::Army::getId() const {
    return *id;
}

ostream &operator<<(ostream &output, const Army &army) {
    output << "Army " << *army.id << " is owned by player " << army.owner->getId() << endl;
    return output;
} //End of insertion operator

int Territory::counter = 0;

// Constructor for a territory that is not the initial starting territory
Territory::Territory(string *name) {
    *id = ++counter;
    owner = nullptr;
    territoryName = name;
    armies = new vector<Army *>;
}

// Constructor for the territory that players start on
Territory::Territory(Player *player, string *name) {
    *id = ++counter;
    owner = player;
    territoryName = name;
    armies = new vector<Army *>;

    // Create 5 armies in that territory
    for (int j = 0; j < 5; j++) {
        Army *army = new Army(player);
        armies->push_back(army);
    }
}

void Territory::copy(const Territory &territory) {
    *id = ++counter;
    owner = new Player(*territory.owner);
    territoryName = new string(*territory.territoryName);
    armies = new vector<Army *>;

    //Copying armies in that copy territory
    for (int i = 0; i < territory.armies->size(); i++) {
        Army *army = new Army(territory.owner);
        armies->push_back(army);
    }
}

// Copy Constructor for territory
Territory::Territory(const Territory &territory) {
    *id = ++counter;
    owner = new Player(*territory.owner);
    territoryName = new string(*territoryName);
    armies = new vector<Army *>;

    //Copying armies in that copy territory
    for (int i = 0; i < territory.armies->size(); i++) {
        Army *army = new Army(territory.owner);
        armies->push_back(army);
    }
} //End of copy constructor

Territory::~Territory() {
    delete owner;
    delete armies;
    delete territoryName;
    delete id;
    --counter;
} //End of destructor

Territory &Territory::operator=(const Territory &territory) {
    //handling self assignment
    if (this != &territory) {
        if (owner != nullptr) {
            delete owner; //Handling memory
        }
        if (armies != nullptr) {
            delete armies;
        }
        if (territoryName != nullptr) {
            delete territoryName;
        }
        copy(territory);
    }
    return *this;
} //End of assignment operator

//get ID of territory
int Territory::getId() const {
    return *id;
}

//get name of territory
string Territory::getTerritoryName() const {
    return *territoryName;
}

ostream &operator<<(ostream &output, const Territory &territory) {
    if (!territory.armies->empty()) {
        output << "Territory " << territory.getId() << ", " << territory.getTerritoryName() << ":" << endl;
        output << "Army(ies) on territory " << territory.getId() << " :" << endl;
        for (Army *army : *territory.armies) {
            cout << *army;
        }
        output << "The territory is owned by " << territory.owner->getId() << endl;
    } else {
        output << "Territory " << territory.getId() << " is owned by no one" << endl;
    }
    return output;
} //End of insertion operator

int Continent::Continent::counter = 0;

//Constructor of continent containing a list of territories from connected graph of territories
Continent::Continent(string *name, Graph<int> *graph, vector<Territory *> *territories) {
    *id = ++counter;
    continentName = name;
    territoriesGraph = graph;
    territoriesVector = territories;
}

void Continent::Continent::copy(const Continent &continent) {
    *id = ++counter;
    continentName = new string(*continent.continentName);
    territoriesGraph = new Graph<int>;
    for (Territory *territory : *continent.territoriesVector) {
        int territoryId = territory->getId();
        territoriesGraph->add_vertex(territoryId);
        for (int neighbourId : continent.territoriesGraph->get_neighbours(territoryId)) {
            territoriesGraph->add_edge(territoryId, neighbourId);
        }
    }
    territoriesVector = new vector<Territory *>;
    for (Territory *territory: *continent.territoriesVector) {
        territoriesVector->push_back(territory);
    }
}

Continent::Continent(const Continent &continent) {
    *id = ++counter;
    continentName = new string(*continent.continentName);
    territoriesGraph = new Graph<int>;
    for (Territory *territory : *continent.territoriesVector) {
        int territoryId = territory->getId();
        territoriesGraph->add_vertex(territoryId);
        for (int neighbourId : continent.territoriesGraph->get_neighbours(territoryId)) {
            territoriesGraph->add_edge(territoryId, neighbourId);
        }
    }
    territoriesVector = new vector<Territory *>;
    for (Territory *territory: *continent.territoriesVector) {
        territoriesVector->push_back(territory);
    }
} //End of copy constructor

Continent::~Continent() {
    delete id;
    delete territoriesGraph;
    delete territoriesVector;
    delete continentName;
    --counter;
} //End of destructor

Continent &Continent::operator=(const Continent &continent) {
    //handling self assignment
    if (this != &continent) {
        if (territoriesGraph != nullptr) {
            delete territoriesGraph; //Handling memory
        }
        if (territoriesVector != nullptr) {
            delete territoriesVector;
        }
        if (continentName != nullptr) {
            delete continentName;
        }
        copy(continent);
    }
    return *this;
} //End of assignment operator

//Check if all territories are connected
bool Continent::Continent::isConnected() const {
    auto *visited = new vector<int>;
    bool isConnected = true;

    // For every vertex
    for (int vertex : territoriesGraph->get_vertices()) {

        // Clear visited vector
        visited->clear();

        // Traverse that vertex
        traverse(vertex, territoriesGraph, visited);

        // If not all vertices were visited
        if (visited->size() != territoriesGraph->get_vertices().size()) {
            isConnected = false;
            break;
        }
    }
    delete visited;

    return isConnected;
}

//Visiting each vertex
void Continent::Continent::traverse(const int node, const Graph<int> *graph, vector<int> *visited) const {
    // Mark node as visited
    visited->push_back(node);

    // For every neighbour of node
    for (int neighbour : graph->get_neighbours(node)) {
        // If neighbour of node isn't visited
        if (!(std::find(visited->begin(), visited->end(), neighbour) != visited->end())) {
            // Traverse into neighbour
            traverse(neighbour, graph, visited);
        }
    }
}

vector<Territory *> *Continent::Continent::getTerritoriesVector() const {
    return territoriesVector;
}

Graph<int> *Continent::Continent::getTerritoriesGraph() const {
    return territoriesGraph;
}

int Continent::Continent::getId() const {
    return *id;
}

string Continent::Continent::getContinentName() const {
    return *continentName;
}

ostream &operator<<(ostream &output, const Continent &continent) {
    auto *territories = new vector<Territory *>;
    *territories = *continent.getTerritoriesVector();
    output << "Here is Continent " << continent.getId() << ", " << continent.getContinentName()
           << " and its territories: " << endl;
    for (Territory *territory: *territories) {
        output << "Territory " << territory->getId() << ", " << territory->getTerritoryName() << endl;
    }
    return output;
} //End of insertion operator

Map::Map(vector<Graph<int> *> *graph, vector<Continent *> *continentsVector) {
    mapGraph = graph;
    continents = continentsVector;
}

void Map::Map::copy(const Map &map) {
    continents = new vector<Continent *>;
    for (Continent *continent: *map.continents) {
        continents->push_back(continent);
    }
    mapGraph = new vector<Graph<int> *>;
    for (Graph<int> *graph:*map.mapGraph) {
        mapGraph->push_back(graph);
    }
}

Map::Map(const Map &map) {
    continents = new vector<Continent *>;
    for (Continent *continent: *map.continents) {
        continents->push_back(continent);
    }
    mapGraph = new vector<Graph<int> *>;
    for (Graph<int> *graph:*map.mapGraph) {
        mapGraph->push_back(graph);
    }
} //End of Copy Constructor

Map::~Map() {
    delete continents;
    delete mapGraph;
}//End of destructor

Map &Map::operator=(const Map &map) {
    //handling self assignment
    if (this != &map) {
        if (mapGraph != nullptr) {
            delete mapGraph; //Handling memory
        }
        if (continents != nullptr) {
            delete continents;
        }
        copy(map);
    }
    return *this;
} //End of assignment operator

//Visiting each vertex
void Map::Map::traverse(const int node, const Graph<int> *graph, vector<int> *visited) const {
    // Mark node as visited
    visited->push_back(node);

    // For every neighbour of node
    for (int neighbour : graph->get_neighbours(node)) {
        // If neighbour of node isn't visited
        if (!(std::find(visited->begin(), visited->end(), neighbour) != visited->end())) {
            // Traverse into neighbour
            traverse(neighbour, graph, visited);
        }
    }
}

bool Map::Map::validate() const {
    vector<Continent *> *continentsVector = this->continents;
    // Check if map is a connected graph
    //Check every graph
    for (Graph<int> *graph: *mapGraph) {
        auto *visited = new vector<int>;
        // For every vertex
        for (int vertex : graph->get_vertices()) {

            // Clear visited vector
            visited->clear();

            // Traverse that vertex
            traverse(vertex, graph, visited);

            // If not all vertices were visited
            if (visited->size() != graph->get_vertices().size()) {
                cout << "Invalid: Map is not a connected graph." << endl;
                return false;
            }
        }
        delete visited;
    }
    // Check if every territory in a continent is connected by choosing a starting vertex and
    // visiting recursively every connected vertex and when it is done, verify all vertex are
    // visited otherwise print "Unconnected continent" error
    for (Continent *continent : *continentsVector) {
        if (!(continent->isConnected())) {
            cout << "Invalid: A continent is not a connected subgraph." << endl;
            return false;
        }
    }
    // Check if every territory belong to a single continent by making sure there are no duplicates
    // when going through every single territory of every single continent
    // Also check if there are territories that are in the territories graph, but not in the
    // territories vector by comparing the size of the accumulated territories in both containers
    // otherwise print "Duplicate territory in multiple continents" error
    auto *territoryIds = new vector<int>;
    int numOfTerritoriesGraph = 0;
    int numOfTerritoriesVector = 0;
    for (Continent *continent : *continentsVector) {
        numOfTerritoriesVector += continent->getTerritoriesVector()->size();
        numOfTerritoriesGraph += continent->getTerritoriesGraph()->get_n_vertices();
        for (Territory *territory : *(continent->getTerritoriesVector())) {
            int id = territory->getId();
            if (std::find(territoryIds->begin(), territoryIds->end(), id) != territoryIds->end()) {
                cout << "Invalid: Duplicate territory in multiple continents." << endl;
                return false;
            } else {
                territoryIds->push_back(id);
            }
        }
    }
    //Check if number of territories in graph == number of territories in vector
    //Otherwise print "Inconsistent number" error
    if (numOfTerritoriesGraph != numOfTerritoriesVector) {
        cout << "Invalid: Inconsistent number of territories in graph and in vector" << endl;
        return false;
    }
    // Cleanup
    territoryIds->clear();
    delete territoryIds;
    return true; //Map is validated
}

vector<Continent *> *Map::Map::getContinents() const {
    return continents;
}

vector<Territory *> *Map::Map::getTerritories() const {
    auto *territories = new vector<Territory *>;
    for (Continent *continent : *continents) {
        for (Territory *territory : *(continent->getTerritoriesVector())) {
            territories->push_back(territory);
        }
    }
    return territories;
}

ostream &operator<<(ostream &output, const Map &map) {
    output << "The map is composed of " << map.getContinents()->size() << " continents and "
           << map.getTerritories()->size() << " territories." << endl
           << "Here are all the list of continents and territories: "
           << endl;
    for (Continent *continent : *map.getContinents()) {
        cout << *continent;
    }
    return output;
} //End of insertion operator
