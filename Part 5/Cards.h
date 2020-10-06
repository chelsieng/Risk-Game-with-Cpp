//Author: Dominique Cartier
//A1 Part five: h

#pragma once
#ifndef A1_CARDS_H
#define A1_CARDS_H
//#include "player.h"
//#include "Orders.h"
#include <string>
#include <vector>

using namespace std;
//as per the instructions of the assignment, all data members (of user-made classes) must be of the pointer type
//EDIT: change was made to say that the above is in fact, not the case. Honestly I wrote most of this before
// any clarification was made so as it stands, most data members will remain as pointers.

class Card {

private:
	string* type; //points to string whose value is either bomb, reinforcement, blockade, airlift, or diplomacy 
	string* description; //points to string that contains description of card
public:
	Card(); //default constructor, do not use.
	Card(string t);
	Card(const Card&); //"In Call by value, a copy of the variable is passed whereas in Call by reference, 
						//a variable itself is passed", "for efficiency reasons, constant call by reference is usually
						//used in place of call by value for classes""
	~Card();
	Card& operator =(const Card& rightSide);
	string getType();
	void setType(string t);
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

	friend class BombCard;				//important, so that these subclasses can access the private data members
	friend class DiplomacyCard;				//particularly relevant since we are required to write copy constructors
	friend class ReinforcementCard;			//and destructors for each of these
	friend class BlockadeCard;
	friend class AirliftCard;
};//end of Card class

//The specific types of cards are implemented as a series of subclasses (of the class Card):

class BombCard : public Card {
public:
	BombCard();
	BombCard(const BombCard& copyMe);
	~BombCard();
	BombCard& operator =(const BombCard& rightSide);
};//end of BombCard class

class DiplomacyCard : public Card {
public:
	DiplomacyCard();
	DiplomacyCard(const DiplomacyCard& copyMe);
	DiplomacyCard& operator =(const DiplomacyCard& rightSide);
	~DiplomacyCard();
};//end of DiplomacyCard class

class ReinforcementCard : public Card {
public:
	ReinforcementCard();
	ReinforcementCard(const ReinforcementCard& copyMe);
	ReinforcementCard& operator =(const ReinforcementCard& rightSide);
	~ReinforcementCard();
};//end of ReinforcementCard class

class AirliftCard : public Card {
public:
	AirliftCard();
	AirliftCard(const AirliftCard& copyMe);
	AirliftCard& operator =(const AirliftCard& rightSide);
	~AirliftCard();
};//end of AirliftCard class

class BlockadeCard : public Card {
public:
	BlockadeCard();
	BlockadeCard(const BlockadeCard& copyMe);
	BlockadeCard& operator =(const BlockadeCard& rightSide);
	~BlockadeCard();
};//end of BlockadeCard class

//Now we must create a deck class which will contain whatever cards we add to it
//-> Let's make the deck a linked (or doubly linked if necessary) list

class deckNode {
public:
	deckNode(Card* thedata);
	deckNode(Card* thedata, deckNode* theLink);
	deckNode(const deckNode& copyMe);
	deckNode& operator =(const deckNode& rightSide);
	~deckNode();

	deckNode* const getLink();
	Card* const getData();
	void setData(Card* theData);
	void setLink(deckNode* theLink);

private:
	Card* data;	//all data members must be of pointer type :(
	deckNode* link;

	friend class Deck;
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
	Deck(const Deck& copyMe);
	Deck& operator =(const Deck& rightSide);
	~Deck();
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
	int limit;
	std::vector<Card*> cardsInHand; //will be initialized in constructor
public:
	Hand(int l, Deck* d);
	Hand(const Hand& copyMe);
	Hand& operator =(const Hand& rightSide);
	~Hand();

	void showCardsInHand();
	void playCardAtIndex(int i);
	void addToHand(Card* c);
};

#endif //A1_CARDS_H