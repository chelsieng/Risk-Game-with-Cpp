//Author: Dominique Cartier
//A1 Part five: Cpp file

#include <string>
#include <iostream>
#include "Cards.h"

using namespace std;


Card::Card()
        : type(new string("default card")), description(new string("nothing here")) {
}

Card::Card(string t)
        : type(new string(t)),
          description(new string("nothing here yet"))    //originally used &t which created many many
{}                                                                //errors, not sure why, think it has to do with improper initialization

Card::Card(const Card &copyMe) {
    type = new string(*copyMe.type);
    description = new string(*copyMe.description);
}

Card::~Card() {
    delete description;
    delete type;
    description = nullptr;
    type = nullptr;
}

Card &Card::operator=(const Card &rightSide) {
    if (this == &rightSide) {
        return *this;
    }
    delete type;    //deleting what was already there (if anything) to avoid memory leaks
    delete description;    //same thing for this
    type = new string(*rightSide.type);
    description = new string(*rightSide.description);
    return *this;
}//end of assignment overload (card)


string *Card::getType() const {
    return type;    //returns the pointer
}

void Card::setDescription(string t) const {
    *description = t;
}

void Card::setType(string t) const {
    *type = t;
}

string *Card::getDescription() const {
    return description;        //returns the pointer
}

//Might remove print method now that we have << overload
void Card::printDescription() const {
    cout << this->getDescription() << endl;
}

void Card::play(Player *p) {
    //switch(*type)
    //create different order based on type

    if (type->compare("Bomb") == 0) {
        p->issueOrder(new Bomb());
    } //Note that (type->compare(str)) defaults the equal to false (or 1 rather)
    else if (type->compare("Diplomacy") == 0) { p->issueOrder(new Negotiate()); }
    else if (type->compare("Reinforcement") == 0) { p->issueOrder(new Deploy()); }
    else if (type->compare("Airlift") == 0) { p->issueOrder(new Airlift()); }
    else if (type->compare("Blockade") == 0) { p->issueOrder(new Blockade()); }
    cout << "You played a card of type: " << *this->getType() << endl;
    //return pointer to order created -> hm no I guess not?
}

void Card::play(Player *p, std::vector<Player *> allPlayers, Map* theMap) {

    if (type->compare("Bomb") == 0) {
        cout << "You are playing a card of type: " << *this->getType() << ".\n";

        cout << "\n Here are the places that you can attack:" << endl;
        vector<Territory*>* attackable = p->AttackAble(theMap);
        for(int i = 0; i < attackable->size(); i++){
            cout << i << ": " << attackable->at(i)->getTerritoryName() << endl;
        }//end of for (show all options)
        cout << "Please input the number from the list above beside the territory you would like to bomb." << endl;
        int ans;
        bool valid;
        while(valid == false){
            cin >> ans;
            if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                valid=false; // Keep prompting user
            }
            else if(ans >= 0 && ans < attackable->size()){
                cout << "Understood!" << endl;
                valid = true;
            }
            else{
                cout << "Invalid input! Please try again." << endl;
            }
        }//end of while
        Territory* destination = attackable->at(ans);
        vector<Territory*>* theNeighbours = theMap->getNeighbours(destination);
        vector<Territory *> *neighboursYouOwn = new vector<Territory *>;
        for (int j = 0; j < theNeighbours->size(); j++) {
            if (theNeighbours->at(j)->isOccupiedBy(p)) {
                neighboursYouOwn->push_back(theNeighbours->at(j));
            }//end of if (valid option)
        }//end of for (get neighbours of territory to be attacked that attacking player owns)
        cout << "\nYou chose to attack " << destination->getTerritoryName() << "." << endl;
        cout << "\nHere are your neighbouring territories that you can advance from." << endl;
        for (int k = 0; k < neighboursYouOwn->size(); k++) {
            cout << k << ": " << neighboursYouOwn->at(k)->getTerritoryName() << endl;
        }//end of for (show neighbors)
        cout
                << "\nPlease type in the number in the above list beside the territory that you would like to bomb from."
                << endl;
        int response;
        bool chosen = false;
        Territory *chosenOne;
        while (chosen == false) {
            cin >> response;
            if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                chosen=false; // Keep prompting user
            }
            else if (response < 0 || response > neighboursYouOwn->size()) {
                cout << "Invalid number! Please try again." << endl;
            }//end of if (invalid choice)
            else {
                chosen = true;
                chosenOne = neighboursYouOwn->at(response);
                cout << "Great! You will bomb from " << neighboursYouOwn->at(response)->getTerritoryName()
                     << endl;
            }
        }//end of while (chose proper number)

        p->issueOrder(new Bomb(p, chosenOne, destination));


    } ///END OF BOMB STUFF
    else if (type->compare("Diplomacy") == 0) {
        cout << "You are playing a card of type: " << *this->getType() << ".\n";
        bool found = false;
        Player *toNegotiate;
        while (found == false) {
            cout
                    << "Please indicate the number of the player you would like to negotiate with (type '2' for player 2, etc.)."
                    << endl;
            int answer;
            cin >> answer;
            if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                found=false; // Keep prompting user
            }
            else if (answer > allPlayers.size() || answer < 1) {
                cout << "That player does not exist! Please try again." << endl;
            }//end of if (not valid player)
            else if (answer == p->getId()) {
                cout << "You can't negotiate with yourself! Please try again." << endl;
            }//end of if (chose themself)
            else {
                found = true;
                for (Player *pl : allPlayers) {
                    if (pl->getId() == answer) { toNegotiate = pl; }
                }//end of for (set the indicated player as the one to negotiate with)
                cout << "Understood!" << endl;
                // Print effect when issue negotiate order
                cout << "\nNegotiate order has been issued. Player " << p->getId() << " and Player " << toNegotiate->getId();
                cout << " cannot attack each other's territories until the end of the turn.\n" << endl;
            }//end of else (valid player)
        }//end of while (find player)
        p->issueOrder(new Negotiate(p, toNegotiate));
    } ///END OF DIPLOMACY STUFF

    else if (type->compare("Reinforcement") == 0) {
        cout << "You are playing a card of type: " << *this->getType() << ".\n";
        ReinforcementCard *reinforce = dynamic_cast<ReinforcementCard *>(this);

        cout << reinforce->getNumberOfTroops() << " additional armies have been added to your reinforcement pool." << endl;

        int usableArmies = reinforce->getNumberOfTroops();
        cout << "You have " << usableArmies << " to deploy." << endl;
        bool deployedAll = false;
        while(deployedAll == false) {
            for (int j = 0; j < p->getPlayerTerritories()->size(); j++) {
                if (usableArmies == 0) {deployedAll = true;}
                else {
                    cout << "How many armies will you deploy to " << p->getPlayerTerritories()->at(j)->getTerritoryName() << "?" << endl;
                    int amount;
                    bool valid = false;
                    while(valid == false){
                        cin >> amount;
                        if (cin.fail()) {
                            cin.clear(); // clears error flag
                            cin.ignore(); // skips to the next line
                            valid=false; // Keep prompting user
                        }
                        else if(amount <= usableArmies && amount >= 0){
                            valid = true;
                            if(amount > 0) {
                                p->getPlayerTerritories()->at(j)->addToMockArmies(amount);
                                p->issueOrder(new Deploy(p, p->getPlayerTerritories()->at(j), amount));
                                usableArmies = usableArmies - amount;
                                cout << amount << " armies will be deployed to" << p->getPlayerTerritories()->at(j)->getTerritoryName()
                                     << "." << endl;
                            }//end of if (is actually deploying armies
                        }//end of if (valid amount entered)
                        else{cout << "Invalid amount! Please try again." << endl;}
                    }//end of while (choose valid amount of armies to deploy)
                }//end of else (still has reinforcement in pool)
                if(usableArmies > 0){cout << "You still have " << usableArmies << " armies left to deploy!" << endl;}
            }//end of for (go through all territories)
        }//end of while (deploy all)

    } ///END OF REINFORCEMENT STUFF

    else if (type->compare("Blockade") == 0) {
        cout << "You are playing a card of type: " << *this->getType() << ".\n";
        bool sourceFound = false;
        bool targetFound = false;
        Territory *sourceTerritory;
        Territory *targetTerritory;
        while (sourceFound == false) {
            cout << "Please type the name of the territory you are blockading." << endl;
            string answer;
            getline(cin, answer); //get their response
            for (Territory *t : *p->getPlayerTerritories()) { //see if they actually own this territory
                if (t->getTerritoryName() == answer) {
                    cout << "Understood!" << endl;
                    sourceTerritory = t;
                    sourceFound = true;
                }
            }//end of for (search player's list of territories)
            if (sourceFound == false)
                cout << "You do not own a territory by that name! Please try again." << endl;
        }//end of while (establish valid sourceTerritory)
        p->issueOrder(new Blockade(p, sourceTerritory));
    } ///END OF BLOCKADE STUFF

    else if (type->compare("Airlift") == 0) {
        cout << "You are playing a card of type: " << *this->getType() << ".\n";
        bool sourceFound = false;
        bool targetFound = false;
        Territory *sourceTerritory;
        Territory *targetTerritory;
        while (sourceFound == false) {
            cout << "Please type the name of the territory you are moving armies from." << endl;
            string answer;
            std::cin >> std::ws; // so we don't read whitespace
            getline(cin, answer); //get their response
            for (Territory *t : *p->getPlayerTerritories()) { //see if they actually own this territory
                if (t->getTerritoryName() == answer) {
                    cout << "Understood!" << endl;
                    sourceTerritory = t;
                    sourceFound = true;
                }
            }//end of for (search player's list of territories)
            if (sourceFound == false)
                cout << "You do not own a territory by that name! Please try again." << endl;
        }//end of while (establish valid sourceTerritory)
        while (targetFound == false) {
            cout << "Please type the name of the territory you are moving armies to." << endl;
            string answer;
            getline(cin, answer); //get their response
            for (Player *p : allPlayers) {
                for (Territory *t : *p->getPlayerTerritories()) { //see if they actually own this territory
                    if (t->getTerritoryName() == answer) {
                        cout << "Understood!" << endl;
                        targetTerritory = t;
                        targetFound = true;
                    }
                }//end of for (search player's list of territories)
                if (targetFound == true) { break; }
            } //end of for (search through all players)
            if (targetFound == false)
                cout << "Nobody owns a territory by that name! Please try again." << endl;
        }//end of while (establish valid targetTerritory)
        //Get number of armies to move:
        bool finished = false;
        int numArmies = 0;
        while (finished == false) {
            cout << "How many armies are you moving?" << endl;
            cin >> numArmies;
            if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                finished = false; // Keep prompting user
            }
            else if (numArmies < 0) {
                cout << "Invalid number of armies. Please try again." << endl;
            }//end of if (invalid)
            else if (numArmies > sourceTerritory->getMockArmies()) {
                cout << "This territory does not have that many armies! Please try again." << endl;
            }//end of if (invalid)
            else {
                finished = true;
                cout << "Understood!" << endl;
            }//end of else (valid)
        }//end of while (get number of territories)
        p->issueOrder(new Airlift(p, sourceTerritory, targetTerritory, numArmies));
    } ///END OF AIRLIFT STUFF

    cout << "You played a card of type: " << *this->getType() << endl;

}//end of play method
///////////////////


BombCard::BombCard()
        : Card("Bomb") {
    setDescription("This is a bomb card. Play this card to kill half of the armies on the adjacent territory.");
}

BombCard::BombCard(const BombCard &copyMe)    //if parameter is const we're not able to access the getters and setters
{                                            //Fortunately for us, Card and BombCard are good friends
    this->setType(*copyMe.getType());
    this->setDescription(*copyMe.getDescription());
}

BombCard::~BombCard() {    // it seems that explicitly deleteing type and description in here results in a double deletion
    //which most likely implies that the Card destructor gets called automatically
}

BombCard &BombCard::operator=(const BombCard &rightSide) {
    if (this == &rightSide) {
        return *this;
    }
    delete this->getType();    //deleting what was already there (if anything) to avoid memory leaks
    delete this->getDescription();    //same thing for this
    setType((*rightSide.getType()));
    setDescription(*rightSide.getDescription());
    return *this;
}//end of assignment overload (BombCard)

DiplomacyCard::DiplomacyCard()
        : Card("Diplomacy") {
    setDescription("This is a diplomacy card. Play this card to enforces peace between two players for a turn.");
}

DiplomacyCard::DiplomacyCard(const DiplomacyCard &copyMe) {
    setType((*copyMe.getType()));
    setDescription((*copyMe.getType()));
}

DiplomacyCard &DiplomacyCard::operator=(const DiplomacyCard &rightSide) {
    if (this == &rightSide) {
        return *this;
    }
    delete this->getType();
    delete this->getDescription();
    setType(*rightSide.getType());
    setDescription(*rightSide.getDescription());
    return *this;
}

DiplomacyCard::~DiplomacyCard() {
}

ReinforcementCard::ReinforcementCard()
        : Card("Reinforcement"), numberOfTroops(1) {
    string str("This is a reinforcement card. It yields ");
    str.append(to_string(numberOfTroops));
    str.append(" armies. Play this card to to gain additional armies.");
    setDescription(str);
}

ReinforcementCard::ReinforcementCard(int armies)
        : Card("Reinforcement"), numberOfTroops(armies) {

    string str("This is a reinforcement card. It yields ");
    str.append(to_string(numberOfTroops));
    str.append(" armies. Play this card to to gain additional armies.");
    setDescription(str);
}

int ReinforcementCard::getNumberOfTroops() const {
    return numberOfTroops;
}

void ReinforcementCard::setNumberOfTroops(int armies) {
    numberOfTroops = armies;
}

ReinforcementCard::ReinforcementCard(const ReinforcementCard &copyMe) {
    setNumberOfTroops(copyMe.getNumberOfTroops());
    setType(*copyMe.getType());
    setDescription(*copyMe.getType());
}

ReinforcementCard &ReinforcementCard::operator=(const ReinforcementCard &rightSide) {
    if (this == &rightSide) {
        return *this;
    }
    delete this->getType();
    delete this->getDescription();
    setNumberOfTroops(rightSide.getNumberOfTroops());
    setType(*rightSide.getType());
    setDescription(*rightSide.getDescription());
    return *this;
}

ReinforcementCard::~ReinforcementCard() {
}

AirliftCard::AirliftCard()
        : Card("Airlift") {
    setDescription("This is an airlift card. Play this card to transfer your armies long distances.");
}

AirliftCard::AirliftCard(const AirliftCard &copyMe) {
    setType(*copyMe.getType());
    setDescription(*copyMe.getType());
}

AirliftCard &AirliftCard::operator=(const AirliftCard &rightSide) {
    if (this == &rightSide) {
        return *this;
    }
    delete this->getType();
    delete this->getDescription();
    setType(*rightSide.getType());
    setDescription(*rightSide.getType());
    return *this;
}


AirliftCard::~AirliftCard() {
}

BlockadeCard::BlockadeCard()
        : Card("Blockade") {
    setDescription("This is a blockade card. Play this card to change one of your territories to a neutral and double the number of armies on that territory.");
}

BlockadeCard::BlockadeCard(const BlockadeCard &copyMe) {
    setType(*copyMe.getType());
    setDescription(*copyMe.getType());
}

BlockadeCard &BlockadeCard::operator=(const BlockadeCard &rightSide) {
    if (this == &rightSide) {
        return *this;
    }
    delete this->getType();
    delete this->getDescription();
    setType(*rightSide.getType());
    setDescription(*rightSide.getDescription());
    return *this;
}

BlockadeCard::~BlockadeCard() {
}

//Deck and deckNode stuff:

deckNode::deckNode(Card *thedata)
        : data(thedata), link(nullptr) {
}

deckNode::deckNode(Card *thedata, deckNode *theLink)
        : data(thedata), link(theLink) {
}

deckNode::deckNode(const deckNode &copyMe) {
    data = new Card(*copyMe.data);
    link = new deckNode(*copyMe.link);
}

deckNode &deckNode::operator=(const deckNode &rightSide) {
    if (this == &rightSide) {
        return *this; //(recall that "this" is a pointer, so we return what it points to with *)
    }
    delete data;
    delete link;
    data = new Card(*rightSide.data); //(recall that "data" is also a pointer, thus the use of *)
    link = new deckNode(*rightSide.link);
    return *this;
}

deckNode::~deckNode() {    //filling this in with delete data and delete head caused major issues... Probably deletes things more than once?
    data = nullptr;
    link = nullptr;
}

deckNode *deckNode::getLink() const {
    return link;
}

Card *deckNode::getData() const {
    return data;
}

void deckNode::setData(Card *theData) {
    data = theData;
}

void deckNode::setLink(deckNode *theLink) {
    link = theLink;
}

Deck::Deck(deckNodePtr thehead)
        : head(thehead) {
}

Deck::Deck(const Deck &copyMe) {
    if (copyMe.head == NULL) {
        head = NULL;
    } else {
        head = new deckNode(copyMe.head->data, nullptr);
        deckNode *position = head;
        deckNode *objHead = copyMe.head;
        deckNode *current = objHead;

        while (current->link != NULL) {
            position->link = new deckNode(current->link->data);
            position = position->link;
            current = current->link;
        }
    }
}


Deck &Deck::operator=(const Deck &rightSide) {
    if (this == &rightSide) {
        return *this;
    } else {
        delete head; //(avoiding memory leaks)
        head = new deckNode(rightSide.head->data, nullptr);
        deckNode *position = head;
        deckNode *objHead = rightSide.head;
        deckNode *current = objHead;

        while (current->link != NULL) {
            delete position->link; //(again avoiding memory leaks)
            position->link = new deckNode(current->link->data);
            position = position->link;
            current = current->link;
        }
    }
    return *this;
}

deckNode *Deck::getHead() const {
    return head;
}

Deck::~Deck() //(Note that destructors get called automatically when an object goes out of scope)
{
    deckNode *position = head;
    deckNode *next = head->link;
    while (next != NULL) {
        delete position;
        position = next;
        next = next->link;
    }
    head = nullptr;
    position = nullptr;
    next = nullptr;
}

void Deck::addToDeck(Card *theData) {
    head = new deckNode(theData, head);
}

Card *Deck::draw() {
    if (head == NULL) {
        cout << "The deck is empty! Cannot draw a card." << endl;
        return NULL;
    } else {
        Card *topOfStack = head->getData();
        head = head->getLink();
        return topOfStack;
    }
}

void Deck::placeOnBottom(Card *theData) {
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


Hand::Hand()        //again you shouldn't use the default constructor
        : limit(5), gameDeck(nullptr), cardsInHand() {
}


Hand::Hand(int l, Deck *d)
        : limit(l), gameDeck(d), cardsInHand()    //again, note to self, DO NOT USE &(parameter) to try
{                                                    //to initialize pointer: DOING SO DOES NOT WORK!!!
    //No longer draws cards automatically
}

Hand::Hand(const Hand &copyMe)
        : cardsInHand() {
    int size = copyMe.cardsInHand.size();
    gameDeck = new Deck(*copyMe.gameDeck);
    limit = copyMe.limit;
    for (int i = 0; i < size; i++) {
        cardsInHand.push_back(new Card(*copyMe.cardsInHand.at(i)));
    }
}

Hand &Hand::operator=(const Hand &rightSide) {
    if (this == &rightSide) {
        return *this;
    } else {
        cardsInHand.clear();
        delete gameDeck;
        limit = rightSide.limit;

        gameDeck = new Deck(
                *rightSide.gameDeck); //creates a new Deck (I think), which is not useful, but required for true deep copy
        int rightSize = rightSide.cardsInHand.size();
        for (int i = 0; i < rightSize; i++) {
            cardsInHand.push_back(rightSide.cardsInHand.at(i));
        }//end of for
    }//end of else
    return *this;
}

Hand::~Hand() {
    delete gameDeck; //careful, this can cause deleting the same thing more than once (error) if we also call delete on the game deck
    gameDeck = nullptr;
}

void Hand::showCardsInHand() {
    int size = cardsInHand.size();
    for (int i = 0; i < size; i++) {
        cout << i << ": " << *cardsInHand.at(i)->getDescription() << endl;
    }
}


void Hand::playCardAtIndex(int i, Player *p) //"default" version, don't use in game engine
{
    Card cardToPlay = *cardsInHand.at(i);
    cardsInHand.at(i)->play(p);
    gameDeck->placeOnBottom(cardsInHand.at(i));
    cardsInHand.erase(cardsInHand.begin() + i); //the begin() part is necessary, it seems (can't just use index)

}

void Hand::playCardAtIndex(int i, Player *p, const std::vector<Player *> &allPlayers, Map* theMap) {
    Card cardToPlay = *cardsInHand.at(i);
    cardsInHand.at(i)->play(p, allPlayers, theMap);                         //uses new version of play() method
    gameDeck->placeOnBottom(cardsInHand.at(i));
    cardsInHand.erase(cardsInHand.begin() + i); //the begin() part is necessary, it seems (can't just use index)

}


void Hand::addToHand(Card *c) {
    cardsInHand.push_back(c);
}

Card Hand::getCardatIndex(int i) const {
    return *cardsInHand.at(i);
}

int Hand::getSize() const {
    return cardsInHand.size();
}

//STREAM OPERATOR OVERLOADS
ostream &operator<<(ostream &outs, const Card &printMe) {
    outs << *printMe.getDescription() << endl;
    return outs;
}


//Since we have the above, overloading the << operator for the specific card types is a bit useless, but the assignment demands it :b

ostream &operator<<(ostream &outs, const BombCard &printMe) {
    outs << *printMe.getDescription() << endl;
    return outs;
}

ostream &operator<<(ostream &outs, const DiplomacyCard &printMe) {
    outs << *printMe.getDescription() << endl;
    return outs;
}

ostream &operator<<(ostream &outs, const ReinforcementCard &printMe) {
    outs << *printMe.getDescription() << endl;
    return outs;
}

ostream &operator<<(ostream &outs, const BlockadeCard &printMe) {
    outs << *printMe.getDescription() << endl;
    return outs;
}

ostream &operator<<(ostream &outs, const AirliftCard &printMe) {
    outs << *printMe.getDescription() << endl;
    return outs;
}

ostream &operator<<(ostream &outs, const deckNode &printMe) {
    outs << "\nA deck node that contains the following card: \n" << *printMe.getData() << endl;
    return outs;
}

ostream &operator<<(ostream &outs, const Deck &printMe) {
    outs << "Here are all the cards currently in this deck:\n" << endl;
    if (printMe.getHead() == NULL) {
        outs << "The deck is empty!" << endl;
    } else {
        deckNode *objHead = printMe.getHead();
        deckNode *current = objHead;
        int i =1;
        while (current != NULL) {
            outs << i <<". " << *current->getData();
            current = current->getLink(); //removed the endl that was here before cause there was no need for all the spaces
            i++;
        }
    }
    return outs;

}

ostream &operator<<(ostream &outs, const Hand &printMe) {

    int size = printMe.getSize();
    if (size == 0) {
        outs << "You have an empty hand." << endl;
    } else {
        outs << "These are the cards currently in your hand:\n" << endl;
        for (int i = 0; i < size; i++) {
            outs << printMe.getCardatIndex(i); //removed "endl" to have less unnecessary spacing
        }
    }
    return outs;
}


