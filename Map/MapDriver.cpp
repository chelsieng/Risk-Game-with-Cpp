#include <iostream>
#include "Map.h"

using namespace std;

int main() {
    //Name of territories
    string territoryName1 = "Dawson";
    string territoryName2 = "WhiteHorse";
    string territoryName3 = "CambridgeBay";
    string territoryName4 = "FairBanks";
    string territoryName5 = "Valdez";
    string territoryName6 = "Kodiak";
    string territoryName7 = "Iceleand";
    string territoryName8 = "GreatBritain";

    //Name of continents
    string continentName1 = "Canada";
    string continentName2 = "UnitedStates";
    string continentName3 = "Europe";

    //Creating territories
    Territory *territory1 = new Territory(territoryName1);
    Territory *territory2 = new Territory(territoryName2);
    Territory *territory3 = new Territory(territoryName3);
    Territory *territory4 = new Territory(territoryName4);
    Territory *territory5 = new Territory(territoryName5);
    Territory *territory6 = new Territory(territoryName6);
    Territory *territory7 = new Territory(territoryName7);
    Territory *territory8 = new Territory(territoryName8);

    //Creating territory vectors and graphs
    vector<Territory *> *territoriesVector1 = new vector<Territory *>;
    vector<Territory *> *territoriesVector2 = new vector<Territory *>;
    vector<Territory *> *territoriesVector3 = new vector<Territory *>;
    Graph<int> *mapGraph = new Graph<int>;

    //Assigning territories 1, 2 and 3 to territoriesVector1
    territoriesVector1->push_back(territory1);
    territoriesVector1->push_back(territory2);
    territoriesVector1->push_back(territory3);

    //Assigning territories 4, 5 and 6 to territoriesVector2
    territoriesVector2->push_back(territory4);
    territoriesVector2->push_back(territory5);
    territoriesVector2->push_back(territory6);

    //Adding territories 1, 2, 3, 4, 5 and 6 as vertex to territoriesGraph1
    mapGraph->add_vertex(territory1->getId());
    mapGraph->add_vertex(territory2->getId());
    mapGraph->add_vertex(territory3->getId());
    mapGraph->add_vertex(territory4->getId());
    mapGraph->add_vertex(territory5->getId());
    mapGraph->add_vertex(territory6->getId());

    // Connect territories 1-2-3-4 to graph
    mapGraph->add_edge(territory1->getId(), territory2->getId());
    mapGraph->add_edge(territory2->getId(), territory3->getId());
    mapGraph->add_edge(territory3->getId(), territory4->getId());
    // Connect territories 4-5, but not 6 to graph
    mapGraph->add_edge(territory4->getId(), territory5->getId());

    // Creating continents
    // Assigning territories 1, 2 and 3 to continent 1 and territories 4, 5 and 6 to continent 2
    Continent *continent1 = new Continent(continentName1, mapGraph, territoriesVector1);
    Continent *continent2 = new Continent(continentName2, mapGraph, territoriesVector2);

    // Creating vector of continents in order to pass it to the Map constructor
    vector<Continent *> *continents1 = new vector<Continent *>;
    continents1->push_back(continent1);
    continents1->push_back(continent2);

    // Test case 1:
    // Continent 1: territories 1, 2 and 3 which are connected
    // Continent 2: territories 4, 5 and 6 where territory 6 isn't connected to 4 or 5
    // Should print "Invalid: A continent is not a connected subgraph"
    cout << "Test case 1:" << endl;
    cout << "Continent 1: territories 1, 2 and 3 which are connected" << endl;
    cout << "Continent 2: territories 4, 5 and 6 where territory 6 isn't connected to 4 or 5" << endl;
    cout << "Should print 'Invalid: A continent is not a connected subgraph'" << endl
         << endl;
    // Creating Map
    Map *map1 = new Map(mapGraph, continents1);
    cout << *map1;
    cout << endl << "Results:" << endl << "--------" << endl;
    if (!map1->validate()) {
        cout << "Test case 1 failed." << endl << endl;
    } else {
        cout << "Test case 1 passed." << endl << endl;
    }

    // Connecting territories 5 and 6
    mapGraph->add_edge(territory5->getId(), territory6->getId());

    // Creating continents
    // Assigning territories 1, 2 and 3 to continent 3 and territories 4, 5 and 6 to continent 4
    Continent *continent3 = new Continent(continentName1, mapGraph, territoriesVector1);
    Continent *continent4 = new Continent(continentName2, mapGraph, territoriesVector2);

    // Creating vector of continents in order to pass it to the Map constructor
    vector<Continent *> *continents2 = new vector<Continent *>;
    continents2->push_back(continent3);
    continents2->push_back(continent4);

    // Test case 2:
    // Same setup as in test case 1, but connecting territories 5 and 6
    // Should pass
    cout << "Test case 2:" << endl;
    cout << "Same setup as in test case 1, but connect territories 5 and 6" << endl;
    cout << "Should pass with no error printed" << endl << endl;

    // Creating Map
    Map *map2 = new Map(mapGraph, continents2);
    cout << *map2;
    cout << endl << "Results:" << endl << "--------" << endl;
    if (!map2->validate()) {
        cout << "Test case 2 failed." << endl << endl;
    } else {
        cout << "Test case 2 passed." << endl << endl;
    }

    //Assigning territory 7 and 8 to territoriesVector3
    territoriesVector3->push_back(territory7);
    territoriesVector3->push_back(territory8);

    //Adding territory 7 and 8 as vertex to graph
    mapGraph->add_vertex(territory7->getId());
    mapGraph->add_vertex(territory8->getId());

    //Connecting territories 7-8 to graph
    mapGraph->add_edge(territory7->getId(), territory8->getId());

    // Creating continents
    // Assigning territories 1, 2 and 3 to continent 5, territories 4, 5 and 6 to continent 6, territories 7 and 8 to continent 7
    Continent *continent5 = new Continent(continentName1, mapGraph, territoriesVector1);
    Continent *continent6 = new Continent(continentName2, mapGraph, territoriesVector2);
    Continent *continent7 = new Continent(continentName3, mapGraph, territoriesVector3);

    // Creating vector of continents in order to pass it to the Map constructor
    vector<Continent *> *continents3 = new vector<Continent *>;
    continents3->push_back(continent5);
    continents3->push_back(continent6);
    continents3->push_back(continent7);

    // Test case 3:
    // Same setup as in test case 2, plus added a third continent where territory 7 and 8 are connected but, are not connected to other territories
    // Should print "Invalid: Map is not a connected graph"
    cout << "Test case 3:" << endl;
    cout
            << "Same setup as in test case 2, plus added a third continent where territory 7 and 8 are connected but, are not connected to other territories"
            << endl;
    cout << "Should print 'Invalid: Map is not a connected graph'" << endl << endl;

    // Creating Map
    Map *map3 = new Map(mapGraph, continents3);
    cout << *map3;
    cout << endl << "Results:" << endl << "--------" << endl;
    if (!map3->validate()) {
        cout << "Test case 3 failed." << endl << endl;
    } else {
        cout << "Test case 3 passed." << endl << endl;
    }

    // Connecting territory 6-7 to graph
    mapGraph->add_edge(territory6->getId(), territory7->getId());

    // Adding territory 3 to territoriesVector2 (continent 2)
    territoriesVector2->push_back(territory3);

    // Creating continents
    // Assigning territories 1, 2 and 3 to continent 8 and territories 3, 4, 5 and 6 to continent 9, territories 7 and 8 to continent 10
    Continent *continent8 = new Continent(continentName1, mapGraph, territoriesVector1);
    Continent *continent9 = new Continent(continentName2, mapGraph, territoriesVector2);
    Continent *continent10 = new Continent(continentName3, mapGraph, territoriesVector3);

    // Creating vector of continents in order to pass it to the Map constructor
    vector<Continent *> *continents4 = new vector<Continent *>;
    continents4->push_back(continent8);
    continents4->push_back(continent9);
    continents4->push_back(continent10);

    // Test case 4:
    // Now adding territory 3 to continent 2 (territory 3 already belongs to continent 1)
    // Should print 'Invalid: Duplicate territory in multiple continents'
    cout << "Test case 4:" << endl;
    cout << "Now adding territory 3 to continent 2 (territory 3 already belongs to continent 1)" << endl;
    cout << "Should print 'Invalid: Duplicate territory in multiple continents'" << endl
         << endl;

    // Creating Map
    Map *map4 = new Map(mapGraph, continents4);
    cout << *map4;
    cout << endl << "Results:" << endl << "--------" << endl;
    if (!map4->validate()) {
        cout << "Test case 4 failed." << endl << endl;
    } else {
        cout << "Test case 4 passed." << endl << endl;
    }
    return 0;
}
