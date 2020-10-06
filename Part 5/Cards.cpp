//Author: Dominique Cartier
//A1 Part five: Cpp file

#include "Cards.h"
#include <string>
#include <iostream>
using namespace std;


Card::Card()
	: type(new string("default card")), description(new string("nothing here"))
{
}

Card::Card(string t)
	: type(new string(t)), description(new string("nothing here yet"))	//originally used &t which created many many
{}																//errors, not sure why, think it has to do with improper initialization

Card::Card(const Card& copyMe)
{
	type = new string(*copyMe.type);
	description = new string(*copyMe.description);
}

Card::~Card()
{
	delete description;
	delete type;
}

Card& Card::operator=(const Card& rightSide)
{
	if (this == &rightSide) {
		return *this;
	}
	delete type;	//deleting what was already there (if anything) to avoid memory leaks
	delete description;	//same thing for this
	type = new string(*rightSide.type);
	description = new string(*rightSide.description);
	return *this;
}//end of assignment overload (card)

string Card::getType()
{
	return *type;	//returns the string itself, not the pointer
}

void Card::setDescription(string t)
{
	*description = t;
}

void Card::setType(string t)
{
	*type = t;
}

string Card::getDescription() {
	return *description;		//returns the string itself, not the pointer
}

void Card::printDescription() {
	cout << this->getDescription() << endl;
}

void Card::play() //this won't actually be a void method, awaiting updates on OrdersList
{
	//switch(*type)
	//create different order based on type
	cout << "You played a card of type: " << this->getType() << endl;
	//return pointer to order created
}

BombCard::BombCard()
	: Card("bomb")
{
	setDescription("This is a bomb card. More info will be added later");
}

BombCard::BombCard(const BombCard& copyMe)	//if parameter is const we're not able to access the getters and setters	
{											//Fortunately for us, Card and BombCard are good friends
	type = new string(*copyMe.type);
	description = new string(*copyMe.description);
}

BombCard::~BombCard()
{	// it seems that explicitly deleteing type and description in here results in a double deletion
	//which most likely implies that the Card destructor gets called automatically
}

BombCard& BombCard::operator=(const BombCard& rightSide)
{
	if (this == &rightSide) {
		return *this;
	}
	delete type;	//deleting what was already there (if anything) to avoid memory leaks
	delete description;	//same thing for this
	type = new string(*rightSide.type);
	description = new string(*rightSide.description);
	return *this;
}//end of assignment overload (BombCard)

DiplomacyCard::DiplomacyCard()
	: Card("Diplomacy")
{
	setDescription("This is a diplomacy card. More info will be added later");
}

DiplomacyCard::DiplomacyCard(const DiplomacyCard& copyMe)
{
	type = new string(*copyMe.type);
	description = new string(*copyMe.type);
}

DiplomacyCard& DiplomacyCard::operator=(const DiplomacyCard& rightSide)
{
	if (this == &rightSide) {
		return *this;
	}
	delete type;
	delete description;
	type = new string(*rightSide.type);
	description = new string(*rightSide.description);
	return *this;
}

DiplomacyCard::~DiplomacyCard()
{
}

ReinforcementCard::ReinforcementCard()
	: Card("Reinforcement")
{
	setDescription("This is a reinforcement card. More info will be added later");
}

ReinforcementCard::ReinforcementCard(const ReinforcementCard& copyMe)
{
	type = new string(*copyMe.type);
	description = new string(*copyMe.type);
}

ReinforcementCard& ReinforcementCard::operator=(const ReinforcementCard& rightSide)
{
	if (this == &rightSide) {
		return *this;
	}
	delete type;
	delete description;
	type = new string(*rightSide.type);
	description = new string(*rightSide.description);
	return *this;
}

ReinforcementCard::~ReinforcementCard()
{
}

AirliftCard::AirliftCard()
	: Card("Airlift")
{
	setDescription("This is an airlift card. More info will be added later");
}

AirliftCard::AirliftCard(const AirliftCard& copyMe)
{
	type = new string(*copyMe.type);
	description = new string(*copyMe.type);
}

AirliftCard& AirliftCard::operator=(const AirliftCard& rightSide)
{
	if (this == &rightSide) {
		return *this;
	}
	delete type;
	delete description;
	type = new string(*rightSide.type);
	description = new string(*rightSide.description);
	return *this;
}

AirliftCard::~AirliftCard()
{
}

BlockadeCard::BlockadeCard()
	: Card("Blockade")
{
	setDescription("This is a blockade card. More info will be added later");
}

BlockadeCard::BlockadeCard(const BlockadeCard& copyMe)
{
	type = new string(*copyMe.type);
	description = new string(*copyMe.type);
}

BlockadeCard& BlockadeCard::operator=(const BlockadeCard& rightSide)
{
	if (this == &rightSide) {
		return *this;
	}
	delete type;
	delete description;
	type = new string(*rightSide.type);
	description = new string(*rightSide.description);
	return *this;
}

BlockadeCard::~BlockadeCard()
{
}

//Deck and deckNode stuff:

deckNode::deckNode(Card* thedata)
	: data(thedata), link(nullptr)
{
}

deckNode::deckNode(Card* thedata, deckNode* theLink)
	: data(thedata), link(theLink)
{
}

deckNode::deckNode(const deckNode& copyMe)
{
	data = new Card(*copyMe.data);
	link = new deckNode(*copyMe.link);
}

deckNode& deckNode::operator=(const deckNode& rightSide)
{
	if (this == &rightSide) {
		return *this; //(recall that "this" is a pointer, so we return what it points to with *)
	}
	delete data;
	delete link;
	data = new Card(*rightSide.data); //(recall that "data" is also a pointer, thus the use of *)
	link = new deckNode(*rightSide.link);
	return *this;
}

deckNode::~deckNode()
{	//filling this in with delete data and delete head caused major issues... Probably deletes things more than once?
}

deckNode* const deckNode::getLink()
{
	return link;
}

Card* const deckNode::getData()
{
	return data;
}

void deckNode::setData(Card* theData)
{
	data = theData;
}

void deckNode::setLink(deckNode* theLink)
{
	link = theLink;
}

Deck::Deck(deckNodePtr thehead)
	: head(thehead)
{
}

Deck::Deck(const Deck& copyMe)
{
	if (copyMe.head == NULL) {
		head == NULL;
	}
	else {
		head = new deckNode(copyMe.head->data, nullptr);
		deckNode* position = head;
		deckNode* objHead = copyMe.head;
		deckNode* current = objHead;

		while (current->link != NULL) {
			position->link = new deckNode(current->link->data);
			position = position->link;
			current = current->link;
		}
	}
}


Deck& Deck::operator=(const Deck& rightSide)
{
	if (this == &rightSide) {
		return *this;
	}
	else {
		delete head; //(avoiding memory leaks)
		head = new deckNode(rightSide.head->data, nullptr);
		deckNode* position = head;
		deckNode* objHead = rightSide.head;
		deckNode* current = objHead;

		while (current->link != NULL) {
			delete position->link; //(again avoiding memory leaks)
			position->link = new deckNode(current->link->data);
			position = position->link;
			current = current->link;
		}
	}
	return *this;
}

Deck::~Deck()
{
	delete head;
}

void Deck::addToDeck(Card* theData)
{
	head = new deckNode(theData, head);
}

Card* Deck::draw()
{
	if (head == NULL) {
		cout << "The deck is empty! Cannot draw a card." << endl;
		return NULL;
	}
	else {
		Card* topOfStack = head->getData();
		head = head->getLink();
		return topOfStack;
	}
}

void Deck::placeOnBottom(Card* theData)
{
	if (head == NULL) {
		addToDeck(theData);
	}//end of if (deck empty)
	else {
		deckNodePtr position = head;
		while (position->getLink() != NULL) {
			position = position->getLink();
		}
		position->setLink(new deckNode(theData, NULL));
	}//end of else (deck not empty)
}



Hand::Hand(int l, Deck* d)
	: limit(l), gameDeck(d), cardsInHand()	//again, note to self, DO NOT USE &(parameter) to try
{													//to initialize pointer: DOING SO DOES NOT WORK!!!

	for (int i = 0; i < limit; i++) {
		Card* c = d->draw();
		cardsInHand.push_back(c);
	}
}

Hand::Hand(const Hand& copyMe)
	: cardsInHand()
{
	int size = copyMe.cardsInHand.size();
	gameDeck = new Deck(*copyMe.gameDeck);
	limit = copyMe.limit;
	for (int i = 0; i < size; i++) {
		cardsInHand.push_back(new Card(*copyMe.cardsInHand.at(i)));
	}
}

Hand& Hand::operator=(const Hand& rightSide)
{
	if (this == &rightSide) {
		return *this;
	}
	else {
		cardsInHand.clear();
		delete gameDeck;
		limit = rightSide.limit;

		gameDeck = new Deck(*rightSide.gameDeck); //creates a new Deck (I think), which is not useful, but required for true deep copy
		int rightSize = rightSide.cardsInHand.size();
		for (int i = 0; i < rightSize; i++) {
			cardsInHand.push_back(rightSide.cardsInHand.at(i));
		}//end of for
	}//end of else

}

Hand::~Hand()
{
}

void Hand::showCardsInHand()
{
	int size = cardsInHand.size();
	for (int i = 0; i < size; i++) {
		cout << i << ": " << cardsInHand.at(i)->getDescription() << endl;
	}
}



void Hand::playCardAtIndex(int i)
{
	Card cardToPlay = *cardsInHand.at(i);
	cardsInHand.at(i)->play();
	gameDeck->placeOnBottom(cardsInHand.at(i));
	cardsInHand.erase(cardsInHand.begin() + i); //the begin() part is necessary, it seems (can't just use index)

}

void Hand::addToHand(Card* c)
{
	cardsInHand.push_back(c);
}