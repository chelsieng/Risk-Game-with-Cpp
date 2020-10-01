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

string Card::getType()
{
	return *type;	//returns the string itself, not the pointer
}

void Card::setDescription(string t)
{	
	*description = t;
}

string Card::getDescription() {
	return *description;		//returns the string itself, not the pointer
}

void Card::printDescription() {
	cout << this->getDescription() << endl;
}

void Card::play()
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

DiplomacyCard::DiplomacyCard()
	: Card("Diplomacy")
{
	setDescription("This is a diplomacy card. More info will be added later");
}

ReinforcementCard::ReinforcementCard()
	: Card("Reinforcement")
{
	setDescription("This is a reinforcement card. More info will be added later");
}

AirliftCard::AirliftCard()
	: Card("Airlift")
{
	setDescription("This is an airlift card. More info will be added later");
}

BlockadeCard::BlockadeCard()
	: Card("Blockade")
{
	setDescription("This is a blockade card. More info will be added later");
}



//Deck and deckNode stuff:

deckNode::deckNode()
{
}

deckNode::deckNode(Card* thedata, deckNode* theLink)
	: data(thedata), link(theLink)
{
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
	: limit(new int(l)), gameDeck(d), cardsInHand()	//again, note to self, DO NOT USE &(parameter) to try
{													//to initialize pointer: DOING SO DOES NOT WORK!!!
											//Also beware, had we taken a Deck as a parameter instead and used new(), it wouldn't be pointing to the right object!
	for (int i = 0; i < *limit; i++) {				//...Maybe. Verify this.
		Card* c = d->draw();
		cardsInHand.push_back(c);
	}
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