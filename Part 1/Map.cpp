#include "Map.h"
#include "../Part 1/Graph.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace graph;
int Army::Army::counter = 0;

//Constructor for armies of player
Army::Army(Player *player) {
    owner = player;
    static int counter = 0;
    *id = ++counter;
}


Army::Army(const Army &army) {
    owner = army.owner;
    static int counter = 0;
    *id = ++counter;
} //End of copy constructor

Army::~Army() {
    delete owner;
    delete id;
    --counter;
} //End of destructor

Army &Army::operator=(const Army &army) {
    if (this == &army) {
        return *this;
    }
    delete owner;
    owner = army.owner;
    id = army.id;
    return *this;
} //End of assignment operator

//get ID of army
int Army::Army::getId() const {
    return *id;
}

ostream &operator<<(ostream &output, const Army &army) {
    output << "Army " << army.id << " is owned by player " << army.owner << endl;
    return output;
} //End of insertion operator

int Territory::Territory::counter = 0;

// Constructor for a territory that is not the initial starting territory
Territory::Territory::Territory() {
    *id = ++counter;
    owner = nullptr;
    armies = new vector<Army *>;
}

// Constructor for the territory that players start on
Territory::Territory(Player *player) {
    *id = ++counter;
    owner = player;
    armies = new vector<Army *>;

    // Create 5 armies in that territory
    for (int j = 0; j < 5; j++) {
        Army *army = new Army(player);
        armies->push_back(army);
    }
}

Territory::Territory(const Territory &territory) {
    *id = ++counter;
    owner = territory.owner;
    armies = territory.armies;
} //End of copy constructor

Territory::~Territory() {
    delete owner;
    delete armies;
    delete id;
    --counter;
} //End of destructor

Territory &Territory::operator=(const Territory &territory) {
    if (this == &territory) {
        return *this;
    }
    delete owner;
    delete armies;
    owner = territory.owner;
    armies = territory.armies;
    id = territory.id;
    return *this;
} //End of assignment operator

//get ID of territory
int Territory::Territory::getId() const {
    return *id;
}

ostream &operator<<(ostream &output, const Territory &territory) {
    if (!territory.armies->empty()) {
        output << "Army(ies) on territory " << territory.getId() << " :" << endl;
        for (Army *army : *territory.armies) {
            cout << army;
        }
        output << "The territory is owned by " << territory.owner << endl;
    } else {
        output << "Territory " << territory.getId() << " is owned by no one" << endl;
    }
    return output;
} //End of insertion operator

int Continent::Continent::counter = 0;

//Constructor of continent containing a list of territories from connected graph of territories
Continent::Continent(Graph<int> *graph, vector<Territory *> *territories) {
    *id = ++counter;
    territoriesGraph = graph;
    territoriesVector = territories;
}

Continent::Continent(const Continent &continent) {
    *id = ++counter;
    territoriesGraph = continent.territoriesGraph;
    territoriesVector = continent.territoriesVector;

} //End of copy constructor

Continent::~Continent() {
    delete id;
    delete territoriesGraph;
    delete territoriesVector;
    --counter;
} //End of destructor

Continent &Continent::operator=(const Continent &continent) {
    if (this == &continent) {
        return *this;
    }
    delete territoriesVector;
    delete territoriesGraph;
    territoriesGraph = continent.territoriesGraph;
    territoriesVector = continent.territoriesVector;
    id = continent.id;
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

const vector<Territory *> *Continent::Continent::getTerritoriesVector() {
    return territoriesVector;
}

Graph<int> *Continent::Continent::getTerritoriesGraph() const {
    return territoriesGraph;
}

int Continent::Continent::getId() const {
    return *id;
}

ostream &operator<<(ostream &output, Continent &continent) {
    output << "Here is Continent " << continent.getId() << " and its territories: ";
    auto *territories = new vector<Territory *>;
    *territories = *continent.getTerritoriesVector();
    for (Territory *territory: *territories) {
        output << "Territory " << territory->getId() << endl;
    }
    return output;
} //End of insertion operator

Map::Map(vector<Graph<int> *> *graph, vector<Continent *> *continentsVector) {
    territoriesGraph = graph;
    continents = continentsVector;
}

Map::Map(const Map &map) {
    continents = map.continents;
    territoriesGraph = map.territoriesGraph;
} //End of Copy Constructor

Map::~Map() {
    delete continents;
    delete territoriesGraph;
}//End of destructor

Map &Map::operator=(const Map &map) {
    if (this == &map) {
        return *this;
    }
    delete continents;
    delete territoriesGraph;
    continents = map.continents;
    territoriesGraph = map.territoriesGraph;
    return *this;
} //End of assignment operator

// Check if all territories are connected
bool Map::Map::isConnectedGraph() const {
    bool isConnectedGraph = true;
    //Check every graph
    for (Graph<int> *graph: *territoriesGraph) {
        auto *visited = new vector<int>;
        // For every vertex
        for (int vertex : graph->get_vertices()) {

            // Clear visited vector
            visited->clear();

            // Traverse that vertex
            traverse(vertex, graph, visited);

            // If not all vertices were visited
            if (visited->size() != graph->get_vertices().size()) {
                isConnectedGraph = false;
                break;
            }
        }
        delete visited;
    }
    return isConnectedGraph;
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
    if (!(this->isConnectedGraph())) {
        cout << "Invalid: Map is not a connected graph." << endl;
        return false;
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
        cout << "Invalid: Inconsistent number of territories in graph and in vector";
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
           << map.getTerritories()->size() << "." << endl << "Here are all the list of continents and territories: "
           << endl;
    for (Continent *continent : *map.getContinents()) {
        cout << continent;
    }
    return output;
} //End of insertion operator
