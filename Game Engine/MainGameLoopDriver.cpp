//
// Created by Dominique Cartier on 2020-11-16.
//
//
// Created by Dominique Cartier on 2020-11-10.
//
#include <iostream>
#include "GameEngine.h"
#include <cstdlib>

int main() {
    //making a deck
    BlockadeCard card1;
    DiplomacyCard card2;
    AirliftCard card3;
    BombCard card4;
    ReinforcementCard card5;
    deckNode head(&card4, NULL);
    Deck* theDeck = new Deck(&head);
    theDeck->addToDeck(&card1);
    theDeck->addToDeck(&card3);
    theDeck->addToDeck(&card4);
    theDeck->addToDeck(&card5);


    GameEngine *gameEngine = new GameEngine();

 ///Create a map
    cout << "Making a map to use." << endl;

    string territoryName1 = "Bikini Bottom";
    string territoryName2 = "Goo Lagoon";
    string territoryName3 = "Davie's Locker";
    string territoryName4 = "Texas";
    string territoryName5 = "Perfume Department";

    string continentName1 = "Sea";
    string continentName2 = "Land";


    Territory *territory1 = new Territory(territoryName1);
    Territory *territory2 = new Territory(territoryName2);
    Territory *territory3 = new Territory(territoryName3);
    Territory *territory4 = new Territory(territoryName4);
    Territory *territory5 = new Territory(territoryName5);

    vector<Territory *> *territoriesVector1 = new vector<Territory *>;
    vector<Territory *> *territoriesVector2 = new vector<Territory *>;

    Graph<int> *mapGraph = new Graph<int>;

    territoriesVector1->push_back(territory1);
    territoriesVector1->push_back(territory2);
    territoriesVector2->push_back(territory3);
    territoriesVector2->push_back(territory4);
    territoriesVector2->push_back(territory5);

    mapGraph->add_vertex(territory1->getId());
    mapGraph->add_vertex(territory2->getId());
    mapGraph->add_vertex(territory3->getId());
    mapGraph->add_vertex(territory4->getId());
    mapGraph->add_vertex(territory5->getId());

    mapGraph->add_edge(territory1->getId(), territory2->getId());
    mapGraph->add_edge(territory2->getId(), territory3->getId());
    mapGraph->add_edge(territory3->getId(), territory4->getId());
    mapGraph->add_edge(territory3->getId(), territory5->getId());
    mapGraph->add_edge(territory4->getId(), territory5->getId());
    mapGraph->add_edge(territory1->getId(), territory5->getId());
    mapGraph->add_edge(territory2->getId(), territory5->getId());

    Continent *continent1 = new Continent(continentName1, mapGraph, territoriesVector1);
    Continent *continent2 = new Continent(continentName2, mapGraph, territoriesVector2);

    continent2->setControlValue(6);
    continent1->setControlValue(4);

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
 ///

    //creating everything we need for a new player, including a hand object
    //-> taken directly from player driver
    Hand* player1Hand = new Hand(5, theDeck); // Creating the player's hands
    OrdersList* orderListP1 = new OrdersList(); // Creating the player's list of orders
    vector<Territory*>* territoryListP1 = new vector<Territory*>(); // Creating the player's list of territories

    vector<Territory*>* territoryListP2 = new vector<Territory*>();

    vector<Territory*>* territoryListP3 = new vector<Territory*>();

    vector<Territory*>* territoryListP4 = new vector<Territory*>();
///Make first player:
    Player* p1 = new Player(player1Hand, orderListP1, territoryListP1);
////////Make a second player:
    Hand* player2Hand = new Hand(5, theDeck); // Creating the player's hands
    OrdersList* orderListP2 = new OrdersList(); // Creating the player's list of orders
    Player* p2 = new Player(player2Hand, orderListP2, territoryListP2);
///////Make a third player
    Hand* player3Hand = new Hand(5, theDeck); // Creating the player's hands
    OrdersList* orderListP3 = new OrdersList(); // Creating the player's list of orders
    Player* p3 = new Player(player3Hand, orderListP3, territoryListP3);
//////Make a fourth player
    Hand* player4Hand = new Hand(5, theDeck); // Creating the player's hands
    OrdersList* orderListP4 = new OrdersList(); // Creating the player's list of orders
    Player* p4 = new Player(player4Hand, orderListP4, territoryListP4);

    ///create vector of players
    vector<Player*>* ps1 = new vector<Player*>();
    p1->setPlayerStrategy(new BenevolentPlayerStrategy);
    p1->getHand()->addToHand(theDeck->draw());
    p1->getHand()->addToHand(theDeck->draw());
    p1->getHand()->addToHand(theDeck->draw());
    p1->getHand()->addToHand(theDeck->draw());
    p1->getHand()->addToHand(theDeck->draw());

    ps1->push_back(p1);
    ps1->push_back(p2);
 //   ps1->push_back(p3);
 //   ps1->push_back(p4);

 //We'll start each player off with a card in hand:
 //   p1->getHand()->addToHand(theDeck->draw());
 //   p2->getHand()->addToHand(theDeck->draw());


    cout << "Here is our list of players:" << endl;
    for(int i = 0; i < ps1->size(); i++){
        cout << *ps1->at(i) << endl;
    }
 //   GameEngine* gameEngine = new GameEngine();
    gameEngine->phaseObserver = new PhaseObserver(gameEngine);
    gameEngine->statisticsObserver = new StatisticsObserver(gameEngine);
    cout << "We will now enter the start up phase function:" << endl;
    gameEngine->startupPhase(ps1,map1->getTerritories());


 cout << "Time for the main game loop!" << endl;
    gameEngine->mainGameLoop(ps1, map1->getContinents(), map1);

    //All the deletes that are commented out cause errors when the program terminates, probably cause they result
    //in deleting things that have already been deleted... Though actually I'm not entirely sure.
    //   delete territory1;
    //   delete territory2;
    //   delete territory3;
    //   delete territory4;
    //   delete territory5;
    //   delete territory6;
    //   delete territory7;
    //   delete territory8;
    //   delete player1Hand;
    //   delete player2Hand;
    //   delete player3Hand;
    //   delete player4Hand;
    //   delete p1;
    //   delete p2;
    //   delete p3;
    //   delete p4;
  //  delete orderListP1;
  //  delete orderListP2;
  //  delete orderListP3;
  //  delete orderListP4;
    delete theDeck;
    delete territoryListP1;
    delete territoryListP2;
    delete territoryListP3;
    delete territoryListP4;
 //   delete map1;
    return 0;
}//end of main

