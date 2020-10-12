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
//    //Creating map graph
//    Graph<int> *mapGraph1 = new Graph<int>;
//    //Adding continent1 and continent2 as vertex to mapGraph
//    mapGraph1->add_vertex(continent1->getId());
//    mapGraph1->add_vertex(continent2->getId());
//
//    //Connecting continent 1-2 to mapGraph
//    mapGraph1->add_edge(continent1->getId(), continent2->getId());
//
//    // Creating vector of continents in order to pass it to the Map constructor
//    vector<Continent *> *continents1 = new vector<Continent *>;
//    continents1->push_back(continent1);
//    continents1->push_back(continent2);
//
//    // Creating vector of mapGraph in order to pass it to the Map constructor
//    vector<Graph<int> *> *graphs1 = new vector<Graph<int> *>;
//    graphs1->push_back(mapGraph1);
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
//    Map *map1 = new Map(graphs1, continents1);
//    cout << *map1;
//    cout << endl << "Results:" << endl << "--------" << endl;
//    if (!map1->validate()) {
//        cout << "Test case 1 failed." << endl << endl;
//    } else {
//        cout << "Test case 1 passed." << endl << endl;
//    }
//
//    // Connecting territories 5 and 6
//    territoriesGraph2->add_edge(territory5->getId(), territory6->getId());
//
//    // Creating continents
//    // Assigning territories 1, 2 and 3 to continent 3 and territories 4, 5 and 6 to continent 4
//    Continent *continent3 = new Continent(territoriesGraph1, territoriesVector1);
//    Continent *continent4 = new Continent(territoriesGraph2, territoriesVector2);
//
//    // Creating vector of continents in order to pass it to the Map constructor
//    vector<Continent *> *continents2 = new vector<Continent *>;
//    continents2->push_back(continent3);
//    continents2->push_back(continent4);
//
//    //Creating map graph
//    Graph<int> *mapGraph2 = new Graph<int>;
//
//    //Adding continent3 and continent4 as vertex to mapGraph
//    mapGraph2->add_vertex(continent3->getId());
//    mapGraph2->add_vertex(continent4->getId());
//
//    //Connecting continent 3-4 to mapGraph
//    mapGraph2->add_edge(continent3->getId(), continent4->getId());
//
//    // Creating vector of graphs in order to pass it to the Map constructor
//    vector<Graph<int> *> *graphs2 = new vector<Graph<int> *>;
//    graphs2->push_back(mapGraph2);
//
//    // Test case 2:
//    // Same setup as in test case 1, but connecting territories 5 and 6
//    // Should pass
//    cout << "Test case 2:" << endl;
//    cout << "Same setup as in test case 1, but connect territories 5 and 6" << endl;
//    cout << "Should pass with no error printed" << endl << endl;
//
//    // Creating Map
//    Map *map2 = new Map(graphs2, continents2);
//    cout << *map2;
//    cout << endl << "Results:" << endl << "--------" << endl;
//    if (!map2->validate()) {
//        cout << "Test case 2 failed." << endl << endl;
//    } else {
//        cout << "Test case 2 passed." << endl << endl;
//    }
//
//    // Creating continents
//    // Assigning territories 1, 2 and 3 to continent 5 and territories 4, 5 and 6 to continent 6
//    Continent *continent5 = new Continent(territoriesGraph1, territoriesVector1);
//    Continent *continent6 = new Continent(territoriesGraph2, territoriesVector2);
//
//    // Creating vector of continents in order to pass it to the Map constructor
//    vector<Continent *> *continents3 = new vector<Continent *>;
//    continents3->push_back(continent5);
//    continents3->push_back(continent6);
//
//    //Creating map graph
//    Graph<int> *mapGraph3 = new Graph<int>;
//    //Adding continent5 and continent6 as vertex to mapGraph
//    mapGraph3->add_vertex(continent5->getId());
//    mapGraph3->add_vertex(continent6->getId());
//
//    // Creating vector of graphs in order to pass it to the Map constructor
//    vector<Graph<int> *> *graphs3 = new vector<Graph<int> *>;
//    graphs3->push_back(mapGraph3);
//
//    // Test case 3:
//    // Same setup as in test case 2, but continent 5 and 6 are not connected
//    // Should print "Invalid: Map is not a connected graph"
//    cout << "Test case 3:" << endl;
//    cout << "Same setup as in test case 2, but continent 5 and 6 are not connected" << endl;
//    cout << "Should print 'Invalid: Map is not a connected graph'" << endl << endl;
//
//    // Creating Map
//    Map *map3 = new Map(graphs3, continents3);
//    cout << *map3;
//    cout << endl << "Results:" << endl << "--------" << endl;
//    if (!map3->validate()) {
//        cout << "Test case 3 failed." << endl << endl;
//    } else {
//        cout << "Test case 3 passed." << endl << endl;
//    }
//
//    // Adding territory 3 to territoriesVector2 (continent 2)
//    territoriesVector2->push_back(territory3);
//
//    // Creating continents
//    // Assigning territories 1, 2 and 3 to continent 5 and territories 3, 4, 5 and 6 to continent 6
//    Continent *continent7 = new Continent(territoriesGraph1, territoriesVector1);
//    Continent *continent8 = new Continent(territoriesGraph2, territoriesVector2);
//
//    // Creating vector of continents in order to pass it to the Map constructor
//    vector<Continent *> *continents4 = new vector<Continent *>;
//    continents4->push_back(continent7);
//    continents4->push_back(continent8);
//
//    //Creating map graph
//    Graph<int> *mapGraph4 = new Graph<int>;
//
//    //Adding continent7 and continent8 as vertex to mapGraph
//    mapGraph4->add_vertex(continent7->getId());
//    mapGraph4->add_vertex(continent8->getId());
//
//    //Connecting continent 7-8 to mapGraph
//    mapGraph4->add_edge(continent7->getId(), continent8->getId());
//
//    // Creating vector of graphs in order to pass it to the Map constructor
//    vector<Graph<int> *> *graphs4 = new vector<Graph<int> *>;
//    graphs4->push_back(mapGraph4);
//
//    // Test case 4:
//    // Now adding territory 3 to continent 2 (territory 3 already belongs to continent 1)
//    // Should print 'Invalid: Duplicate territory in multiple continents'
//    cout << "Test case 4:" << endl;
//    cout << "Now adding territory 3 to continent 2 (territory 3 already belongs to continent 1)" << endl;
//    cout << "Should print 'Invalid: Duplicate territory in multiple continents'" << endl
//         << endl;
//
//    // Creating Map
//    Map *map4 = new Map(graphs4, continents4);
//    cout << *map4;
//    cout << endl << "Results:" << endl << "--------" << endl;
//    if (!map4->validate()) {
//        cout << "Test case 4 failed." << endl << endl;
//    } else {
//        cout << "Test case 4 passed." << endl << endl;
//    }
//
//    // Deleting territory 3 from continent 2
//    territoriesVector2->pop_back();
//
//    // Adding extra territory in territories graph and connecting it, but not declaring it in territories vector
//    Territory *territory7 = new Territory();
//    territoriesGraph1->add_vertex(territory7->getId());
//    territoriesGraph1->add_edge(territory7->getId(), territory1->getId());
//
//    // Creating continents
//    // Assigning territories 1, 2, 3 and 7 (without declaring in territoriesVector1) to continent 7 and territories 4, 5 and 6 to continent 7
//    Continent *continent9 = new Continent(territoriesGraph1, territoriesVector1);
//    Continent *continent10 = new Continent(territoriesGraph2, territoriesVector2);
//
//    // Creating vector of continents in order to pass it to the Map constructor
//    vector<Continent *> *continents5 = new vector<Continent *>;
//    continents5->push_back(continent9);
//    continents5->push_back(continent10);
//
//    //Creating map graph
//    Graph<int> *mapGraph5 = new Graph<int>;
//    //Adding continent9 and continent10 as vertex to mapGraph
//    mapGraph5->add_vertex(continent9->getId());
//    mapGraph5->add_vertex(continent10->getId());
//
//    //Connecting continent 9-10 to mapGraph
//    mapGraph5->add_edge(continent9->getId(), continent10->getId());
//
//    // Creating vector of graphs in order to pass it to the Map constructor
//    vector<Graph<int> *> *graphs5 = new vector<Graph<int> *>;
//    graphs5->push_back(mapGraph5);
//
//    // Test case 5:
//    // Removed territory 3 from continent 2
//    // Now added new territory 7 to continent 1 and connected it to the other territories in the continent
//    // but did not add territory 7 in territoriesVector1 in order to create an inconsistency
//    // Should print 'Invalid: Inconsistent number of territories in graph and in vector'
//    cout << "Test case 5:" << endl;
//    cout << "Removed territory 3 from continent 2" << endl;
//    cout << "Now adding new territory 7 to continent 1 and connected it to the other territories in the continent"
//         << endl;
//    cout << "but did not add territory 7 in continent vector in order to create an inconsistency" << endl;
//    cout
//            << "Should print 'Invalid: Inconsistent number of territories in graph and in vector'"
//            << endl << endl;
//
//    // Creating Map
//    Map *map5 = new Map(graphs5, continents5);
//    cout << *map5;
//    cout << endl << "Results:" << endl << "--------" << endl;
//    if (!map5->validate()) {
//        cout << "Test case 5 failed." << endl << endl;
//    } else {
//        cout << "Test case 5 passed." << endl << endl;
//    }
//    return 0;
//}
