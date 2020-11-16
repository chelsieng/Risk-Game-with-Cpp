//
// Created by Dominique Cartier on 2020-11-10.
//
#include <iostream>
#pragma once
#include "GameEngine.h"
#include <cstdlib>

int main() {

    //making a deck
    BombCard bomb1;
    ReinforcementCard reinforcement1;
    deckNode head(&reinforcement1, NULL);
    Deck* theDeck = new Deck(&head);
    theDeck->addToDeck(&bomb1);

    //creating random territories to check some stuff out
    string territoryName1("Dawson");
    Territory *territory1 = new Territory(territoryName1);
    string territoryName2("Abbott");
    Territory *territory2 = new Territory(territoryName2);
    string territoryName3("Vanier");
    Territory *territory3 = new Territory(territoryName3);
    string territoryName4("Champlain");
    Territory *territory4 = new Territory(territoryName4);
    string territoryName5("Concordia");
    Territory *territory5 = new Territory(territoryName5);
    string territoryName6("McGill");
    Territory *territory6 = new Territory(territoryName6);
    string territoryName7("Texas");
    Territory *territory7 = new Territory(territoryName7);
    string territoryName8("Bikini Bottom");
    Territory *territory8 = new Territory(territoryName8);

    //creating everything we need for a new player, including a hand object
    //-> taken directly from player driver
    Hand* player1Hand = new Hand(5, theDeck); // Creating the player's hands
    OrdersList* orderListP1 = new OrdersList(); // Creating the player's list of orders
    vector<Territory*>* territoryListP1 = new vector<Territory*>(); // Creating the player's list of territories
    //     territoryListP1->push_back(territory1);
    vector<Territory*>* territoryListP2 = new vector<Territory*>();
    //     territoryListP2->push_back(territory2);
    vector<Territory*>* territoryListP3 = new vector<Territory*>();
    //   territoryListP3->push_back(territory3);
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
    ps1->push_back(p1);
    ps1->push_back(p2);
    ps1->push_back(p3);
    ps1->push_back(p4);

    ///Create vector of territories
    vector<Territory*>* ts = new vector<Territory*>();
    ts->push_back(territory1);
    ts->push_back(territory2);
    ts->push_back(territory3);
    ts->push_back(territory4);
    ts->push_back(territory5);
    ts->push_back(territory6);
    ts->push_back(territory7);
    ts->push_back(territory8);


    cout << "Here is our list of players:" << endl;
    for(int i = 0; i < ps1->size(); i++){
        cout << *ps1->at(i) << endl;
    }

    cout << "We will now enter the start up phase function:" << endl;
    GameEngine::startupPhase(ps1,ts);

    cout << "\nWe have exited the start up phase function. Now, let's look at our list of players again.\n"
         << "They should now be in their assigned turn order, and have territories assigned to them." << endl;

    cout << "\nHere is our list of players now:\n" << endl;
    for(int i = 0; i < ps1->size(); i++){
        cout << *ps1->at(i) << endl;
    }

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
    delete orderListP1;
    delete orderListP2;
    delete orderListP3;
    delete orderListP4;
    delete theDeck;
    delete territoryListP1;
    delete territoryListP2;
    delete territoryListP3;
    delete territoryListP4;
    return 0;
}//end of main
