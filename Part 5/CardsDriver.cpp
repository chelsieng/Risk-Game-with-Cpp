//Author: Dominique Cartier

///A1 Part five: Driver

#pragma once
#include <iostream>
#include "Cards.h"
using namespace std;

int main() {	//None of this will do anything visible when run if not in main... Not sure if they want this
	//file to have a main function??? Multiple driver files is why I've assume no... Clarification required.
	BombCard bomb1;
	ReinforcementCard reinforcement1;
	DiplomacyCard diplomacy1;
	BlockadeCard blockade1;
	AirliftCard airlift1;
	ReinforcementCard reinforcement2(5);

	deckNode head(&reinforcement1, NULL);

	Deck* theDeck = new Deck(&head);

	theDeck->addToDeck(&bomb1);
	theDeck->addToDeck(&diplomacy1);
	theDeck->addToDeck(&blockade1);
	theDeck->addToDeck(&airlift1);
	theDeck->addToDeck(&reinforcement2);

	BombCard b2 = bomb1;
	b2.setDescription("An altered bomb card created as a deep copy :O");

	theDeck->addToDeck(&b2);
	//Show contents of deck:
	cout << *theDeck << endl;
	cout << "Now we will draw the top 5 cards of the deck into a hand.\n\n" << endl;

	//creating a random territory to check some stuff out
    string *territoryName1 = new string("Dawson");
    Territory *territory1 = new Territory(territoryName1);

	//creating everything we need for a new player, including a hand object
	//-> taken directly from player driver
	Hand* player1Hand = new Hand(5, theDeck); // Creating the player's hands
	OrdersList* orderListP1 = new OrdersList(); // Creating the player's list of orders
	vector<Territory*>* territoryListP1 = new vector<Territory*>(); // Creating the player's list of territories

	territoryListP1->push_back(territory1);

	Player* p1 = new Player(player1Hand, orderListP1, territoryListP1);
<<<<<<< HEAD
////////Make a second player:
    Hand* player2Hand = new Hand(5, theDeck); // Creating the player's hands
    OrdersList* orderListP2 = new OrdersList(); // Creating the player's list of orders
    vector<Territory*>* territoryListP2 = new vector<Territory*>(); // Creating the player's list of territories

    Player* p2 = new Player(player1Hand, orderListP1, territoryListP1);
 ///////Make a vector of players:
 std::vector<Player*> thePlayers;
 thePlayers.push_back(p1);
 thePlayers.push_back(p2);

    player1Hand->addToHand(theDeck->draw());
    player1Hand->addToHand(theDeck->draw());
    player1Hand->addToHand(theDeck->draw());
    player1Hand->addToHand(theDeck->draw());
    player1Hand->addToHand(theDeck->draw());
=======
>>>>>>> 3b8d639c7e7c701a6e3f24f8fde9726e8adaf1c1

	//show contents of hand
	cout << *player1Hand << endl;

	cout << "\nNow, let's play all of them!\n" << endl;

	int count = 0;
	while (count < 5) {
		player1Hand->playCardAtIndex(0, p1, thePlayers);
		count++;
	}

	cout << "\nJust to be sure, let's have a look at your list of orders:\n" << endl;
	cout << *orderListP1 << endl;
	cout << "\nEnd of driver!\n" << endl;

	return 0;
};