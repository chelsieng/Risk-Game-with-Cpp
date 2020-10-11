#pragma once

#include <vector>
#include <string>
#include <map>

#include "Graph.h"
#include "Player.h"

using namespace std;
using namespace graph;

// Forward declaration due to circular dependency
class Player;


class Army {
private:
    static int counter;
    int *id = new int(0);
    Player *owner;

    void copy(const Army&); //Copying value of army

public:
    explicit Army(Player *); //Army constructor for player
    Army(const Army &); //Copy constructor
    ~Army(); //Destructor
    Army &operator=(const Army &); //Assignment Operator

    int getId() const;

    friend ostream &operator<<(ostream &, const Army &);
}; //end of Army class

class Territory {
private:
    static int counter;
    int *id = new int(0);
    Player *owner;
    vector<Army *> *armies;
    void copy(const Territory&); //Copying value of territory

public:
    Territory(); // Default Territory constructor with no armies present
    explicit Territory(Player* player); // Constructor for 1 player starting with 5 armies
    Territory(const Territory &); //Copy Constructor
    ~Territory(); //Destructor
    Territory &operator=(const Territory &); //Assignment Operator
    int getId() const;

    friend ostream &operator<<(ostream &, const Territory &); //insertion operator
}; //end of Territory Class

class Continent {
private:
    static int counter;
    int *id = new int(0);
    vector<Territory *> *territoriesVector;
    Graph<int> *territoriesGraph;
    void copy(const Continent&); //Copying value of continent
    void traverse(int, const Graph<int> *, vector<int> *) const; //visiting each vertex of graph

public:
    Continent(Graph<int> *, vector<Territory *> *); //Constructor with graph and list of territories
    Continent(const Continent &); //Copy Constructor
    ~Continent(); //Destructor
    Continent &operator=(const Continent &); //Assignment Operator

    bool isConnected() const; //return true if all territories are connected in continent

    vector<Territory *> *getTerritoriesVector()const;

    Graph<int> *getTerritoriesGraph() const;

    int getId() const;

    friend ostream &operator<<(ostream &, const Continent &); //insertion operator
}; //End of Continent Class

class Map {
private:
    vector<Continent *> *continents;
    vector<Graph<int> *> *territoriesGraph;
    void copy(const Map&); //Copying value of map
    void traverse(int, const Graph<int> *, vector<int> *) const; //Visiting each vertex of graph

public:
    Map(vector<Graph<int> *> *, vector<Continent *> *);

    Map(const Map &); //Copy constructor
    ~Map(); //Destructor
    Map &operator=(const Map &); //Assignment Operator
    bool isConnectedGraph() const;

    bool validate() const; //checking if map is a connected graph, continent is a subgraph
    // and if each territory belongs to one and only one continent

    vector<Continent *> *getContinents() const;

    vector<Territory *> *getTerritories() const;

    friend ostream &operator<<(ostream &, const Map &);
}; //End of Map Class
