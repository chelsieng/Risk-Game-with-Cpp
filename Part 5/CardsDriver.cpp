//Author: Dominique Cartier
//A1 Part five: Driver

#include <iostream>
#include "Cards.h"
using namespace std;

int main() {	//None of this will do anything visible when run if not in main... Not sure if they want this
	//file to have a main function??? Multiple driver files is why I've assume no... Clarification required.
	BombCard daBomb;
	ReinforcementCard rere;
	DiplomacyCard dp;
	BlockadeCard bbb;
	AirliftCard tiab;

	deckNode head(&rere, NULL);

	Deck* theDeck = new Deck(&head);
	theDeck->addToDeck(&dp);
	theDeck->addToDeck(&daBomb);
	theDeck->addToDeck(&bbb);
	theDeck->addToDeck(&tiab);

	BombCard b2 = daBomb;
	b2.setDescription("An altered bomb card created as a deep copy :O");

	theDeck->addToDeck(&b2);
	//Let's create a hand object, drawing the top four cards
	Hand takeMyHand(4, theDeck);
	//And then draw an additional card from the deck
	takeMyHand.addToHand(theDeck->draw());

	cout << "Let's see what cards are in this hand...\n" << endl;

	takeMyHand.showCardsInHand();
	cout << "\nNow, let's play all of them!\n" << endl;
	int count = 0;
	while (count < 5) {
		takeMyHand.playCardAtIndex(0);
		count++;
	}


	return 0;
};
