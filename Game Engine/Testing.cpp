//
// Created by Dominique Cartier on 2020-11-16.
//
#include <iostream>
using namespace std;
#include "GameEngine.h"

int main(){

    cout << "Making a map to use." << endl;

    string territoryName1 = "Bikini Bottom";
    string territoryName2 = "Goo Lagoon";
    string territoryName3 = "Davie's Locker";
    string territoryName4 = "Texas";

    string continentName1 = "Sea";
    string continentName2 = "Land";

    Territory *territory1 = new Territory(territoryName1);
    Territory *territory2 = new Territory(territoryName2);
    Territory *territory3 = new Territory(territoryName3);
    Territory *territory4 = new Territory(territoryName4);

    vector<Territory *> *territoriesVector1 = new vector<Territory *>;
    vector<Territory *> *territoriesVector2 = new vector<Territory *>;

    Graph<int> *mapGraph = new Graph<int>;

    territoriesVector1->push_back(territory1);
    territoriesVector1->push_back(territory2);
    territoriesVector2->push_back(territory3);
    territoriesVector2->push_back(territory4);

    mapGraph->add_vertex(territory1->getId());
    mapGraph->add_vertex(territory2->getId());
    mapGraph->add_vertex(territory3->getId());
    mapGraph->add_vertex(territory4->getId());

    mapGraph->add_edge(territory1->getId(), territory2->getId());
    mapGraph->add_edge(territory2->getId(), territory3->getId());
    mapGraph->add_edge(territory3->getId(), territory4->getId());

    Continent *continent1 = new Continent(continentName1, mapGraph, territoriesVector1);
    Continent *continent2 = new Continent(continentName2, mapGraph, territoriesVector2);

    // Creating vector of continents in order to pass it to the Map constructor
    vector<Continent *> *continents1 = new vector<Continent *>;
    continents1->push_back(continent1);
    continents1->push_back(continent2);

    Map *map1 = new Map(mapGraph, continents1);
    cout << *map1;
    cout << endl << "Results:" << endl << "--------" << endl;
    if (!map1->validate()) {
        cout << "The map is not valid." << endl << endl;
    } else {
        cout << "Map created!." << endl << endl;
    }

    cout << "Here are the neighbours of Davie's Locker:" << endl;
    vector<Territory*>* lockerBuddies = map1->getNeighbours(territory3);
    for(int i = 0; i < lockerBuddies->size(); i++){
        if(lockerBuddies->at(i) != NULL){
        cout << lockerBuddies->at(i)->getTerritoryName() << endl;
        }
    }
    cout << "Here are the neighbours of Goo Lagoon:" << endl;
    vector<Territory*>* lockerBuddies2 = map1->getNeighbours(territory2);
    for(int i = 0; i < lockerBuddies->size(); i++){
        if(lockerBuddies->at(i) != NULL){
            cout << lockerBuddies2->at(i)->getTerritoryName() << endl;
        }
    }
    cout << "finished running this" << endl;
    //delete dynamic stuff
    delete territory1;
    delete territory2;
    delete territory3;
    delete territory4;
    delete territoriesVector1;
    delete territoriesVector2;
 //   delete continent1;
 //   delete continent2;
 //   delete continents1;
    delete map1;



    return 0;
};

