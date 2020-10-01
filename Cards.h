#pragma once
#ifndef A1_CARDS_H
#define A1_CARDS_H
#include "player.h"
#include "Orders.h"
#include <string>
#include <vector>

using namespace std;
//as per the instructions of the assignment, all data members (of user-made classes) must be of the pointer type

class Card {

private:
	string* type; //points to string whose value is either bomb, reinforcement, blockade, airlift, or diplomacy 
	string* description; //points to string that contains description of card
public:
	Card(); //default constructor, do not use.
	Card(string t);
	string getType();
	void setDescription(string t);
	string getDescription();
	void printDescription();
	//unfortunately, we cannot declare or define the full Play() method here, since it requires a Deck object as
	//input, but the Deck class is later in the file (a forward declaration will not work for a Parameter of
	//	an incomplete type, to the best of my knowledge).
	//So play() will simply create the order and add it to the list, NOT add it back to the deck.
	//To do everything required, we will have another method in the Hand class to play() a specific card and then
	// add it back to the game deck
	void play();	//This should actually return an order (or a pointer to one) -> WAITING FOR ORDERS class to be implemented
		//that is to say, won't remain void
};//end of Card class

//The specific types of cards are implemented as a series of subclasses (of the class Card):

class BombCard : public Card {
public:
	BombCard();
};//end of BombCard class

class DiplomacyCard : public Card {
public:
	DiplomacyCard();
};//end of DiplomacyCard class

class ReinforcementCard : public Card {
public:
	ReinforcementCard();
};//end of ReinforcementCard class

class AirliftCard : public Card {
public:
	AirliftCard();
};//end of AirliftCard class

class BlockadeCard : public Card {
public:
	BlockadeCard();
};//end of BlockadeCard class

//Now we must create a deck class which will contain whatever cards we add to it
//-> Let's make the deck a linked (or doubly linked if necessary) list

class deckNode {
public:
	deckNode();
	deckNode(Card* thedata, deckNode* theLink);

	deckNode* const getLink();
	Card* const getData();
	void setData(Card* theData);
	void setLink(deckNode* theLink);

private:
	Card* data;	//all data members must be of pointer type :(
	deckNode* link;

};//END of deckNode class
typedef deckNode* deckNodePtr;

class Deck {
	//since the deck functions like a stack of cards, we don't have to create functions to add or remove cards to/from
	//a specific index (we draw from the head, and put a card back in at the bottom)
private:
	deckNodePtr head;
public:
	//add default constructor even though we won't use it
	Deck(deckNodePtr thehead);
	void addToDeck(Card* theData); //(equivalent to adding to head)
	Card* draw();	//(equivalent to removing from head)
	void placeOnBottom(Card* theData);
};
//END of deck class

//Finally, the hand class. In this case an array *seems* to make sense, but changing hand size may pose an issue...
//No, we will definitely use vectors instead

class Hand {
private:
	Deck* gameDeck;	//the deck the hand will draw from
	int* limit;
	std::vector<Card*> cardsInHand; //will be initialized in constructor
public:
	Hand(int l, Deck* d);
	void showCardsInHand();
	void playCardAtIndex(int i);
	void addToHand(Card* c);
};

#endif //A1_CARDS_H
