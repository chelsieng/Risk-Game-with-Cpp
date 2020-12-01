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

    void copy(const Army &); //Copying value of army

public:
    explicit Army(Player *); //Army constructor for player
    Army(const Army &); //Copy constructor
    ~Army(); //Destructor
    Army &operator=(const Army &); //Assignment Operator

    int getId() const;
    void setOwner(Player *p);

    friend ostream &operator<<(ostream &, const Army &);
}; //end of Army class

class Territory {
private:
    static int counter;
    int *id = new int(0);
    Player *owner;
    string territoryName;
    vector<Army *> *armies;
    int mockArmies;
    void copy(const Territory &); //Copying value of territory

public:
    Territory(string name); // Default Territory constructor with no armies present
    explicit Territory(Player *player, string name); // Constructor for 1 player starting with 5 armies
    Territory(const Territory &); //Copy Constructor
    ~Territory(); //Destructor
    Territory &operator=(const Territory &); //Assignment Operator
    int getId() const;
    void resetMockArmies();
    int getMockArmies();
    void addToMockArmies(int temp);
    void removeMockArmies(int temp);

    string getTerritoryName() const;

    int getNumberOfArmies() const;

    void addArmy();                         // add given number of armies into the territory
    void removeArmy();                      // remove given number of armies into the territory
    Player* getOwner() const { return (this->owner); };
    void setOwner(Player *p);
   

    bool isOccupiedBy(Player *p) const; //return true if territory is occupied by player p

    friend ostream &operator<<(ostream &, const Territory &); //insertion operator
}; //end of Territory Class

class Continent {
private:
    static int counter;
    int *id = new int(0);
    string continentName;
    int controlValue; // this value represents the number of bonus armies that a player gets when he controls the whole continent
    vector<Territory *> *territoriesVector;
    Graph<int> *territoriesGraph;

    void copy(const Continent &); //Copying value of continent
    void traverse(int, const Graph<int> *, vector<int> *) const; //visiting each vertex of graph

public:
    Continent(string, Graph<int> *, vector<Territory *> *); //Constructor with graph and list of territories
    Continent(const Continent &); //Copy Constructor
    ~Continent(); //Destructor
    Continent &operator=(const Continent &); //Assignment Operator

    bool isConnected() const; //return true if all territories are connected in continent
    bool isOccupiedBy(Player *p) const; //return true if continent is controlled by player p

    vector<Territory *> *getTerritoriesVector() const;

    Graph<int> *getTerritoriesGraph() const;

    int getId() const;

    string getContinentName() const;

    int getControlValue() const;

    void setControlValue(int controlValue);

    friend ostream &operator<<(ostream &, const Continent &);//insertion operator

}; //End of Continent Class

class Map {
private:
    vector<Continent *> *continents;
    Graph<int> *mapGraph;

    void copy(const Map &); //Copying value of map
    void traverse(int, const Graph<int> *, vector<int> *) const; //Visiting each vertex of graph

public:
    Map(Graph<int> *, vector<Continent *> *);

    Map(const Map &); //Copy constructor
    ~Map(); //Destructor
    Map &operator=(const Map &); //Assignment Operator
    bool isConnected() const;

    bool validate() const; //checking if map is a connected graph, continent is a subgraph
    // and if each territory belongs to one and only one continent

    bool areNeighbours(Territory *t1, Territory *t2) const; //return true if t2 is a neighbour of t1

    vector<Continent *> *getContinents() const;

    vector<Territory *> *getTerritories() const;
    vector<Territory *> *getNeighbours(Territory *theTerritory);

    friend ostream &operator<<(ostream &, const Map &);
}; //End of Map Class
