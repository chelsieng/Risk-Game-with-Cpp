#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

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
    owner = nullptr;
    *id = --counter;
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
Territory::Territory(string name) {
    *id = ++counter;
    owner = nullptr;
    territoryName = name;
    armies = new vector<Army *>;
}

// Constructor for the territory that players start on
Territory::Territory(Player *player, string name) {
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
    territoryName = territory.territoryName;
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
    territoryName = territory.territoryName;
    armies = new vector<Army *>;

    //Copying armies in that copy territory
    for (int i = 0; i < territory.armies->size(); i++) {
        Army *army = new Army(territory.owner);
        armies->push_back(army);
    }
} //End of copy constructor

Territory::~Territory() {
    delete owner;
    owner = nullptr;
    delete armies;
    armies = nullptr;
    *id = --counter;
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
    return territoryName;
}

ostream &operator<<(ostream &output, const Territory &territory) {
    if (!territory.armies->empty()) {
        output << "Territory " << territory.getId() << ", " << territory.getTerritoryName() << ":" << endl;
        output << "Army(ies) on territory " << territory.getId() << " :" << endl;
        for (Army *army : *territory.armies) {
            cout << *army;
        }
        output << "The territory is owned by " << territory.owner->getId() << endl;
    } else if (territory.owner != nullptr) {
        output << "The territory " << territory.getTerritoryName() << " is owned by P" << territory.owner->getId()
               << endl;
    } else {
        output << "The Territory " << territory.getTerritoryName() << " is owned by no one" << endl;
    }
    return output;
}

bool Territory::isOccupiedBy(Player *p) const {
    return this->owner->getId() == p->getId();
}

void Territory::setOwner(Player *p) {
    this->owner = p;
}

int Territory::getNumberOfArmies() const {
    return armies->size();
}

void Territory::addArmy() {
        armies->push_back(new Army(this->owner));
}

void Territory::removeArmy() {
    armies->erase(this->armies->begin());      // delete one element
}
//End of insertion operator

int Continent::Continent::counter = 0;

//Constructor of continent containing a list of territories from connected graph of territories
Continent::Continent(string name, Graph<int> *graph, vector<Territory *> *territories) {
    *id = ++counter;
    continentName = name;
    territoriesGraph = graph;
    territoriesVector = territories;
}

void Continent::Continent::copy(const Continent &continent) {
    *id = ++counter;
    continentName = continent.continentName;
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
    continentName = continent.continentName;
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
    *id = --counter;
    delete territoriesGraph;
    territoriesGraph = nullptr;
    territoriesVector->clear();
    delete territoriesVector;
    territoriesVector = nullptr;
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
        copy(continent);
    }
    return *this;
} //End of assignment operator

//Check if all territories are connected
bool Continent::Continent::isConnected() const {
    auto *visited = new vector<int>;
    bool isConnected = true;
    auto *terrID = new vector<int>;
    for (auto terr: *territoriesVector) {
        terrID->push_back(terr->getId());
    }
    // For every vertex
    for (int vertex : territoriesGraph->get_vertices()) {
        // Clear visited vector
        visited->clear();
        if ((std::find(terrID->begin(), terrID->end(), vertex) != terrID->end())) {
            traverse(vertex, territoriesGraph, visited);
        }

        // If not all vertices were visited
        if (visited->size() != terrID->size() && (std::find(terrID->begin(), terrID->end(), vertex) != terrID->end())) {
            isConnected = false;
        }
    }
    delete visited;

    return isConnected;
}

//Visiting each vertex
void Continent::Continent::traverse(const int node, const Graph<int> *graph, vector<int> *visited) const {
    auto *terrID = new vector<int>;
    for (auto terr: *territoriesVector) {
        terrID->push_back(terr->getId());
    }
    // Mark node as visited
    visited->push_back(node);

    // For every neighbour of node
    for (int neighbour : graph->get_neighbours(node)) {
        if (std::find(terrID->begin(), terrID->end(), neighbour) != terrID->end()) {
            // If neighbour of node isn't visited
            if (!(std::find(visited->begin(), visited->end(), neighbour) != visited->end())) {
                // Traverse into neighbour
                traverse(neighbour, graph, visited);
            }
        } else {
            continue;
        }
    }
}

bool Continent::isOccupiedBy(Player *p) const {
    bool occupied = false;
    for (auto terr: *this->territoriesVector) {
        if (terr->isOccupiedBy(p)) {
            occupied = true;
        }
        occupied = false;
    }
    return occupied;
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
    return continentName;
}

int Continent::getControlValue() const {
    return controlValue;
}

void Continent::setControlValue(int controlValue) {
    Continent::controlValue = controlValue;
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

Map::Map(Graph<int> *graph, vector<Continent *> *continentsVector) {
    mapGraph = graph;
    continents = continentsVector;
}

void Map::Map::copy(const Map &map) {
    continents = new vector<Continent *>;
    for (Continent *continent: *map.continents) {
        continents->push_back(continent);
    }
    mapGraph = new Graph<int>;
    for (Territory *territory : *map.getTerritories()) {
        int territoryId = territory->getId();
        mapGraph->add_vertex(territoryId);
        for (int neighbourId : map.mapGraph->get_neighbours(territoryId)) {
            mapGraph->add_edge(territoryId, neighbourId);
        }
    }
}

Map::Map(const Map &map) {
    continents = new vector<Continent *>;
    for (Continent *continent: *map.continents) {
        continents->push_back(continent);
    }
    mapGraph = new Graph<int>;
    for (Territory *territory : *map.getTerritories()) {
        int territoryId = territory->getId();
        mapGraph->add_vertex(territoryId);
        for (int neighbourId : map.mapGraph->get_neighbours(territoryId)) {
            mapGraph->add_edge(territoryId, neighbourId);
        }
    }
} //End of Copy Constructor

Map::~Map() {
    delete continents;
    continents = nullptr;
    delete mapGraph;
    mapGraph = nullptr;
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

bool Map::Map::isConnected() const {
    auto *visited = new vector<int>;
    bool isConnected = true;

    // For every vertex
    for (int vertex : mapGraph->get_vertices()) {
        // Clear visited vector
        visited->clear();

        // Traverse that vertex
        traverse(vertex, mapGraph, visited);

        // If not all vertices were visited
        if (visited->size() != mapGraph->get_vertices().size()) {
            isConnected = false;
            break;
        }
    }

    delete visited;

    return isConnected;
}

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
    // Check if every territory in a continent is connected by choosing a starting vertex and
    // visiting recursively every connected vertex and when it is done, verify all vertex are
    // visited otherwise print "Unconnected continent" error
    for (Continent *continent : *continentsVector) {
        if (!(continent->isConnected())) {
            cout << "Invalid: A continent is not a connected subgraph." << endl;
            return false;
        }
    }
    // Check if map is a connected graph
    //    Check every graph
    if (!(isConnected())) {
        cout << "Invalid: Map is not a connected graph." << endl;
        return false;
    }
    // Cleanup
    territoryIds->clear();
    delete territoryIds;
    return true; //Map is validated
}

bool Map::areNeighbours(Territory *t1, Territory *t2) const {
    bool isNeighbour = false;
    for (int neighbourID : this->mapGraph->get_neighbours(t1->getId())) {
        if (neighbourID == t2->getId()) {
            isNeighbour = true;
        } else {
            isNeighbour = false;
        }
    }
    return isNeighbour;
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


