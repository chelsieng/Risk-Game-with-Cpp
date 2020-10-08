#include "Map.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Map::Army::Army(Player *player) {
    owner = player;
    static int counter = 0;
    *id = ++counter;
}

int Map::Army::getId() const {
    return *id;
}

void Map::Army::print() const {
    cout << "Army " << *id << " is owned by player " << owner << endl;
}

int Map::Territory::counter = 0;

// Constructor for a territory that is not the initial starting territory
Map::Territory::Territory() {
    *id = ++counter;
    owner = nullptr;
    armies = new vector<Army *>;
}

// Constructor for the territory that players start on
Map::Territory::Territory(Player *player) {
    *id = ++counter;
    owner = player;
    armies = new vector<Army *>;

    // Create 5 armies in that territory
    for (int j = 0; j < 5; j++) {
        Army *army = new Army(player);
        armies->push_back(army);
    }
}

int Map::Territory::getId() const {
    return *id;
}

void Map::Territory::print() const {
    if (armies->size() > 0) {
        cout << "Army(ies) on territory " << this->getId() << " :" << endl;
        for (Army *army : *armies) {
            army->print();
        }
        cout << "The territory is owned by ";
        cout << owner;
        cout << endl;
    } else {
        cout << "Territory " << this->getId() << " is owned by no one" << endl;
    }

}


