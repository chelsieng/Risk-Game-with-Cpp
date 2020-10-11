//#include <iostream>
//#include "Map.h"
//
//int main() {
//    //Creating territories
//    Territory *territory1 = new Territory();
//    Territory *territory2 = new Territory();
//    Territory *territory3 = new Territory();
//    Territory *territory4 = new Territory();
//    Territory *territory5 = new Territory();
//    Territory *territory6 = new Territory();
//
//    //Creating territory vectors and graphs
//    vector<Territory *> *territoriesVector1 = new vector<Territory *>;
//    vector<Territory *> *territoriesVector2 = new vector<Territory *>;
//    Graph<int> *territoriesGraph1 = new Graph<int>;
//    Graph<int> *territoriesGraph2 = new Graph<int>;
//
//    //Assigning territories 1, 2 and 3 to territoriesVector1
//    territoriesVector1->push_back(territory1);
//    territoriesVector1->push_back(territory2);
//    territoriesVector1->push_back(territory3);
//
//    //Assigning territories 4, 5 and 6 to territoriesVector2
//    territoriesVector2->push_back(territory4);
//    territoriesVector2->push_back(territory5);
//    territoriesVector2->push_back(territory6);
//
//    //Adding territories 1, 2 and 3 as vertex to territoriesGraph1
//    territoriesGraph1->add_vertex(territory1->getId());
//    territoriesGraph1->add_vertex(territory2->getId());
//    territoriesGraph1->add_vertex(territory3->getId());
//
//    //Adding territories 4, 5 and 6 as vertex to territoriesGraph2
//    territoriesGraph2->add_vertex(territory4->getId());
//    territoriesGraph2->add_vertex(territory5->getId());
//    territoriesGraph2->add_vertex(territory6->getId());
//
//    // Connect territories 1-2-3 to territoriesGraph1
//    territoriesGraph1->add_edge(territory1->getId(), territory2->getId());
//    territoriesGraph1->add_edge(territory2->getId(), territory3->getId());
//
//    // Connect territories 4-5, but not 6 to territoriesGraph2
//    territoriesGraph2->add_edge(territory4->getId(), territory5->getId());
//
//    // Creating continents
//    // Assigning territories 1, 2 and 3 to continent 1 and territories 4, 5 and 6 to continent 2
//    Continent *continent1 = new Continent(territoriesGraph1, territoriesVector1);
//    Continent *continent2 = new Continent(territoriesGraph2, territoriesVector2);
//
//    // Creating vector of continents in order to pass it to the Map constructor
//    vector<Continent *> *continents1 = new vector<Continent *>;
//    continents1->push_back(continent1);
//    continents1->push_back(continent2);
//
//    // Creating vector of graphs in order to pass it to the Map constructor
//    vector<Graph<int> *> *graphs1 = new vector<Graph<int> *>;
//    graphs1->push_back(territoriesGraph1);
//    graphs1->push_back(territoriesGraph2);
//
//    // Test case 1:
//    // Continent 1: territories 1, 2 and 3 which are connected
//    // Continent 2: territories 4, 5 and 6 where territory 6 isn't connected to 4 or 5
//    // Should print "Invalid: A continent is not a connected subgraph"
//    cout << "Test case 1:" << endl;
//    cout << "Continent 1: territories 1, 2 and 3 which are connected" << endl;
//    cout << "Continent 2: territories 4, 5 and 6 where territory 6 isn't connected to 4 or 5" << endl;
//    cout << "Should print 'Invalid: A continent is not a connected subgraph'" << endl
//         << endl;
//    // Creating Map
//    Map *map = new Map(graphs1, continents1);
//    cout << "Results:" << endl;
//    if (!map->validate()) {
//        cout << "Test case 1 failed." << endl;
//    } else {
//        cout << "Test case 1 passed." << endl;
//    }
//    return 0;
//}
