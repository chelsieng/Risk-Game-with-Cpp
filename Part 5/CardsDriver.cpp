//Author: Dominique Cartier
//A1 Part five: Driver

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

	deckNode head(&reinforcement1, NULL);


	Deck* theDeck = new Deck(&head);
	theDeck->addToDeck(&diplomacy1);
	theDeck->addToDeck(&bomb1);
	theDeck->addToDeck(&blockade1);
	theDeck->addToDeck(&airlift1);

	BombCard b2 = bomb1;
	b2.setDescription("An altered bomb card created as a deep copy :O");

	theDeck->addToDeck(&b2);
	//Show contents of deck:
	cout << *theDeck << endl;
	cout << "Now we will draw the top 5 cards of the deck into a hand.\n\n" << endl;
	//Let's create a hand object, drawing the top four cards
	Hand takeMyHand(4, theDeck);
	//And then draw an additional card from the deck
	takeMyHand.addToHand(theDeck->draw());
	//show contents of hand
	cout << takeMyHand << endl;
	cout << "\nNow, let's play all of them!\n" << endl;
	int count = 0;
	while (count < 5) {
		takeMyHand.playCardAtIndex(0);
		count++;
	}

	cout << "\nEnd of driver!\n" << endl;

	return 0;
};
