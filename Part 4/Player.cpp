#include <iostream>
#include <vector>

#include "Player.h"

using namespace std;

int Player::counter = -1;

// default constructor
Player::Player() :
        playerHand{nullptr},
        playerOrdersList{nullptr},
        playerTerritories{nullptr},
        pID{++counter}, // increasing player count
        reinforcementPool{0} {}

// parameterized constructor
Player::Player(Hand *hand, OrdersList *OrdersList, vector<Territory *> *territories) {
    pID = ++counter; // increasing player count
    this->playerHand = hand;
    this->playerOrdersList = OrdersList;
    this->playerTerritories = territories;
    this->reinforcementPool = 0;
}

// copy constructor
Player::Player(const Player &playerCopy) {
    pID = ++counter; // increasing player count

    // HAND
    // deallocate
    delete this->playerHand;
    this->playerHand = nullptr;

    // copy using Hand copy constructor
    this->playerHand = new Hand(*playerCopy.playerHand);

    // ORDERS LIST
    // deallocate
    delete this->playerOrdersList;
    this->playerOrdersList = nullptr;

    // copy using Hand copy constructor
    this->playerOrdersList = new OrdersList(*playerCopy.playerOrdersList);

    // TERRITORIES
    // deallocate
    for (Territory *t : *this->playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete this->playerTerritories;
    playerTerritories = nullptr;

    // copy using Territory copy constructor
    for (auto pt : *playerCopy.playerTerritories) {
        this->playerTerritories->push_back(new Territory(*pt));
    }
}

// destructor
Player::~Player() {

    // reducing the count of players created
    --counter;

    // free hand
    delete playerHand;
    playerHand = nullptr;

    // free OrdersList
    delete playerOrdersList;
    playerOrdersList = nullptr;

    // free territories
    for (Territory *t : *playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete this->playerTerritories;
    playerTerritories = nullptr;
}

// Returning the player's ID
int Player::getId() const {
    return pID;
}

// Returning the player's order list
OrdersList *Player::getOrdersList() {
    return this->playerOrdersList;
}

// Returning the player's hand
Hand *Player::getHand() {
    return this->playerHand;
}

vector<Territory *> *Player::getPlayerTerritories() {
    return this->playerTerritories;
}

// Adding an order to the end of the player's order list
// A subclass of Order (order types) will be passed as a parameter.
void Player::issueOrder(Order *orderToIssue) {
    Order *newOrder = orderToIssue;
    this->playerOrdersList->addToLast(newOrder);
}



Player &Player::operator=(const Player &player) {

    // Checking for self assignment
    if (this == &player) {
        return *this;
    }

    pID = ++counter; // increasing player count

    // deleting existing pointers
    delete playerHand;
    playerHand = nullptr;

    delete playerOrdersList;
    playerOrdersList = nullptr;

    for (Territory *t : *playerTerritories) {
        delete t;
        t = nullptr;
    }
    delete playerTerritories;
    playerTerritories = nullptr;

    // creating a deep copy
    playerHand = new Hand(*player.playerHand);
    playerOrdersList = new OrdersList(*player.playerOrdersList);
    playerTerritories = new vector<Territory *>(*player.playerTerritories);

    return *this;
}

std::ostream &operator<<(ostream &out, const Player &player) {
    out << "PLAYER " << player.getId() << " HAND: " << endl;
    out << *player.playerHand << endl;
    out << "PLAYER " << player.getId() << " TERRITORIES: " << endl;
    if (player.playerTerritories->empty()) {
        out << "Territories will be assigned later." << endl <<endl;
    } else {
        for (auto terr : *player.playerTerritories) {
            out << *terr << endl;
        }
    }
    out << "PLAYER " << player.getId() << " ORDERS: " << endl;
    out << *player.playerOrdersList << endl;
    out << "PLAYER " << player.getId() << " AVAILABLE (UNUSED) REINFORCEMENT: " << endl;
    out << player.reinforcementPool << endl;

    return out;
}

int Player::getReinforcementPool() const {
    return reinforcementPool;
}

void Player::setReinforcementPool(int i) {
    this->reinforcementPool = i;
}

///Gives all the territories that a player can attack (and returns a vector of pointers to said territories)
vector<Territory *> *Player::AttackAble(Map *theMap){
    vector<Territory *>* attackable = new vector<Territory*>;
    set<int> *IDs = new set<int>;
    for(int i = 0; i < this->getPlayerTerritories()->size(); i++){
        vector<Territory*>* yourNeighbours = theMap->getNeighbours(this->getPlayerTerritories()->at(i));
        for(int j = 0; j < yourNeighbours->size(); j++) {
            if (IDs->find(yourNeighbours->at(j)->getId()) == IDs->end()) {
                IDs->insert(yourNeighbours->at(j)->getId());
            }//end of if (add neighbours to ID list if they haven't been added)
        }//end of for (go through all neighbours)
    }//end of for (go through all the player's owned territories)

    set<int,less<int>>::iterator itr;
    for(itr = IDs->begin(); itr != IDs->end(); itr++) {
        int theNeighbourID = *itr;
        for(int i = 0; i < theMap->getTerritories()->size(); i++){
            if(theMap->getTerritories()->at(i)->getId() == theNeighbourID && theMap->getTerritories()->at(i)->getOwner() != this){
                attackable->push_back(theMap->getTerritories()->at(i));
            }//end of if (valid to attack)
        }//for each ID, check all territories to see if they have the matching ID and don't belong to the player
    }//end of for (go through all IDs in list)
    return attackable;
}//end of Attackable method

void Player::issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice) {

        if(choice == 0) {///DEPLOY:
            ///Chose what to defend:
            vector<Territory *> *defendList = this->toDefend(theMap);
            while(defendList->size() == 0){
                cout << "You must chose territories to deploy your troop to!" << endl;
                defendList = this->toDefend(theMap);
            }//end of while
            if (defendList != NULL && defendList->size() > 0) {
                cout << "\nGreat! You chose to defend these territories:" << endl;
                for (int i = 0; i < defendList->size(); i++) {
                    cout << defendList->at(i)->getTerritoryName() << endl;
                }//end of for (print the list)

                ///Issue deploy orders:
                cout << "\nNow it is time to deploy armies on the territories you are defending."
                     << "\nYou will get the chance to defend by advancing after this step." << endl;
                int usableArmies = this->getReinforcementPool();
                cout << "You have " << usableArmies << " to deploy." << endl;
                bool deployedAll = false;
                while (deployedAll == false) {
                    for (int j = 0; j < defendList->size(); j++) {
                        if (usableArmies == 0) { deployedAll = true; }
                        else {
                            cout << "\nHow many armies will you deploy to " << defendList->at(j)->getTerritoryName()
                                 << "?" << endl;
                            int amount;
                            bool valid = false;
                            while (valid == false) {
                                cin >> amount;
                                if (cin.fail()) {
                                    cin.clear(); // clears error flag
                                    cin.ignore(); // skips to the next line
                                    valid=false; // Keep prompting user
                                }
                                if (amount <= usableArmies && amount >= 0) {
                                    valid = true;
                                    if (amount > 0) {
                                        defendList->at(j)->addToMockArmies(amount);
                                        this->issueOrder(new Deploy(this, defendList->at(j), amount));
                                        usableArmies = usableArmies - amount;
                                        cout << amount << " armies will be deployed to"
                                             << defendList->at(j)->getTerritoryName()
                                             << "." << endl;
                                    }//end of if (is actually deploying armies
                                }//end of if (valid amount entered)
                                else { cout << "Invalid amount! Please try again." << endl; }
                            }//end of while (choose valid amount of armies to deploy)
                        }//end of else (still has reinforcement in pool)
                        if (usableArmies > 0) {
                            cout << "\nYou still have " << usableArmies << " armies left to deploy!" << endl;
                        }
                    }//end of for (go through all territories)
                }
            }
        }///Finished deploying
           if(choice == 1){
               ///Defend by advancing
               ///Chose what to defend:
               vector<Territory*>* defendList = this->toDefend(theMap);
               if(defendList != NULL && defendList->size() > 0) {
                   cout << "\nYou chose to defend these territories:" << endl;
                   for (int i = 0; i < defendList->size(); i++) {
                       cout << defendList->at(i)->getTerritoryName() << endl;
                   }//end of for (print the list)

                   ///Issue Advance defend orders:
                   cout
                           << "\nNow you can defend from advancing armies! " << endl;
                   cout <<   "For each territory selected earlier, you must chose if you would like to advance troops."
                        << endl;
                   for (int i = 0; i < defendList->size(); i++) {
                       cout << "\nWill you advance troops to " << defendList->at(i)->getTerritoryName() << "? Type 1 if yes, and any other number if no." << endl;
                       int advanceResponse;
                       cin >> advanceResponse;
                       if (cin.fail()) {
                           cin.clear(); // clears error flag
                           cin.ignore(); // skips to the next line
                           --i;
                           continue; // Keep prompting user
                       }
                       if(advanceResponse == 1) {
                           vector<Territory *> *theNeighbours = theMap->getNeighbours(defendList->at(i));
                           vector<Territory *> *neighboursYouOwn = new vector<Territory *>;
                           for (int j = 0; j < theNeighbours->size(); j++) {
                               if (theNeighbours->at(j)->isOccupiedBy(this)) {
                                   neighboursYouOwn->push_back(theNeighbours->at(j));
                               }//end of if (valid option)
                           }//end of for (get neighbours of territory to be defended that defending player owns)
                           if(neighboursYouOwn->size() > 0) {
                               cout << "\nYou chose to defend " << defendList->at(i)->getTerritoryName() << "." << endl;
                               cout << "Here are your neighbouring territories that you can advance armies from." << endl;
                               for (int k = 0; k < neighboursYouOwn->size(); k++) {
                                   cout << k << ": " << neighboursYouOwn->at(k)->getTerritoryName() << endl;
                               }//end of for (show neighbors)
                               cout
                                       << "\nPlease type in the number in the above list beside the territory that you would like to move armies from."
                                       << endl;
                               int ans;
                               bool chosen = false;
                               Territory *chosenOne;
                               while (chosen == false) {
                                   cin >> ans;
                                   if (cin.fail()) {
                                       cin.clear(); // clears error flag
                                       cin.ignore(); // skips to the next line
                                       chosen = false; // Keep prompting user
                                   }
                                   else if (ans < 0 || ans >= neighboursYouOwn->size()) {
                                       cout << "Invalid number! Please try again." << endl;
                                   }//end of if (invalid choice)
                                   else {
                                       chosen = true;
                                       chosenOne = neighboursYouOwn->at(ans);
                                       cout << "\nGreat! You will advance from " << neighboursYouOwn->at(ans)->getTerritoryName()
                                            << endl;
                                   }
                               }//end of while (chose proper number)
                               int availableArmies = chosenOne->getMockArmies();
                               cout << chosenOne->getTerritoryName() << " has " << availableArmies
                                    << " armies available to advance."
                                    << endl;
                               cout << "Please chose how many you would like to advance." << endl;
                               int number;
                               bool done = false;
                               while (done == false) {
                                   cin >> number;
                                   if (cin.fail()) {
                                       cin.clear(); // clears error flag
                                       cin.ignore(); // skips to the next line
                                       done = false; // Keep prompting user
                                   }
                                   else if (number < 0 || number > availableArmies) {
                                       cout << "That is not a valid amount! Please try again." << endl;
                                   }//end of if (invalid input)
                                   else {
                                       done = true;
                                       cout << "Perfect!" << endl;
                                   }
                               }//end of while (chose valid number of territories to move)
                               chosenOne->removeMockArmies(number);
                               this->issueOrder(new Advance(this, chosenOne, defendList->at(i), number));
                               cout << "\nAdvance order issued!" << endl;
                           }//end of if (player actually has neighbours from which to advance)
                           else{cout << "You don't have any territories neighbouring this one! Cannot issue advance order." << endl;}
                       }//end of if (player chose to advance armies)
                   }//end of for (go through all territories in the defend list)
                   cout << "\nfinished making defensive advance orders!" << endl;
               }//end of if (list of things to defend is not empty)
               else{
                   cout << "\nYou chose not to defend any territories!" << endl;
               }
           }//finished defending through advance
    if(choice == 2) {///attack by advancing
        ///Chose what to attack by advancing:
        vector<Territory *> *whatWasChosen = this->toAttack(theMap);
        cout << "\nYou chose to attack these territories:" << endl;
        if (whatWasChosen->size() > 0) {
            for (int i = 0; i < whatWasChosen->size(); i++) {
                cout << whatWasChosen->at(i)->getTerritoryName() << endl;
            }
        }//end of if (not empty)


        ///Issue Advance attack orders:
        if (whatWasChosen != NULL && whatWasChosen->size() > 0) {
            cout
                    << "\nTime to attack! For each territory selected, you must chose which territory you will attack from."
                    << endl;
            for (int i = 0; i < whatWasChosen->size(); i++) {
                vector<Territory *> *theNeighbours = theMap->getNeighbours(whatWasChosen->at(i));
                vector<Territory *> *neighboursYouOwn = new vector<Territory *>;
                for (int j = 0; j < theNeighbours->size(); j++) {
                    if (theNeighbours->at(j)->isOccupiedBy(this)) {
                        neighboursYouOwn->push_back(theNeighbours->at(j));
                    }//end of if (valid option)
                }//end of for (get neighbours of territory to be attacked that attacking player owns)
                cout << "\nYou chose to attack " << whatWasChosen->at(i)->getTerritoryName() << "." << endl;
                cout << "\nHere are your neighbouring territories that you can advance from." << endl;
                for (int k = 0; k < neighboursYouOwn->size(); k++) {
                    cout << k << ": " << neighboursYouOwn->at(k)->getTerritoryName() << endl;
                }//end of for (show neighbors)
                cout
                        << "\nPlease type in the number in the above list beside the territory that you would like to attack from."
                        << endl;
                int ans;
                bool chosen = false;
                Territory *chosenOne;
                while (chosen == false) {
                    cin >> ans;
                    if (cin.fail()) {
                        cin.clear(); // clears error flag
                        cin.ignore(); // skips to the next line
                        chosen=false; // Keep prompting user
                    }
                    else if (ans < 0 || ans >= neighboursYouOwn->size()) {
                        cout << "Invalid number! Please try again." << endl;
                    }//end of if (invalid choice)
                    else {
                        chosen = true;
                        chosenOne = neighboursYouOwn->at(ans);
                        cout << "Great! You will advance from " << neighboursYouOwn->at(ans)->getTerritoryName()
                             << endl;
                    }
                }//end of while (chose proper number)
                int availableArmies = chosenOne->getMockArmies();
                cout << chosenOne->getTerritoryName() << " has " << availableArmies << " armies available to advance."
                     << endl;
                cout << "\nPlease chose how many you would like to advance." << endl;
                int number;
                bool done = false;
                while (done == false) {
                    cin >> number;
                    if (cin.fail()) {
                        cin.clear(); // clears error flag
                        cin.ignore(); // skips to the next line
                        done = false; // Keep prompting user
                    }
                    else if (number < 0 || number > availableArmies) {
                        cout << "That is not a valid amount! Please try again." << endl;
                    }//end of if (invalid input)
                    else {
                        done = true;
                        cout << "Perfect!" << endl;
                    }
                }//end of while (chose valid number of territories to move)
                chosenOne->removeMockArmies(number);
                this->issueOrder(new Advance(this, chosenOne, whatWasChosen->at(i), number));
                cout << "\nAdvance order issued!" << endl;
            }//end of for (go through all territories in the attack list)
        }//end of if (player had territories to attack)
        //ALL ATTACK ADVANCE ORDERS HAVE BEEN ISSUED
    }//end of attack by advancing
    ////Play cards in hand:
    if(choice == 3){
        cout << "\nYou've chosen to play a card from you hand! Here are the cards currently in your hand:" << endl;
        for(int i = 0; i < this->getHand()->getSize(); i++){
            cout << i << ": " << this->getHand()->getCardatIndex(i) << endl;
        }//end of for (show cards)
        cout << "\nPlease type in the number in the list above of the card you would like to play." << endl;
        int ans;
        bool valid = false;
        while(valid == false) {
            cin >> ans;
            cout << endl;
            if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                valid = false; // Keep prompting user
            }
            else if(ans < this->getHand()->getSize() && ans >= 0){valid = true;}
            else{
                cout << "\nInvalid answer! Please try again." << endl;
            }
        }//end of while (get valid answer)
        this->getHand()->playCardAtIndex(ans, this, *thePlayers, theMap);
    }//end of playing card in hand

}///End of issue order method

vector<Territory*>* Player::toDefend(Map* theMap) {
    vector<Territory*>* listToDefend = new vector<Territory*>;
    cout << "Here are the territories you can defend:" << endl;
    vector<int> options = {}; //so that they don't pick the same territory more than once
    for(int i = 0; i < this->getPlayerTerritories()->size(); i++){
        options.push_back(i);
        cout << i << ": " << this->getPlayerTerritories()->at(i)->getTerritoryName() << endl;
    }//end of for (print all options)
    cout  << "\nType the corresponding numbers in the above list of the territories you would like to defend, in order of priority."
          << "\nENTER A NEGATIVE NUMBER IF YOU ARE FINISHED. Input answers one at a time." << endl;
    bool done = false;
    while (done == false) {
        int ans = -1;
        cout << "What territory will you defend?" << endl;
        cin >> ans;
        if (ans < 0) { done = true; }
        else if (cin.fail()) {
            cin.clear(); // clears error flag
            cin.ignore(); // skips to the next line
            continue; // Keep prompting user
        }
        else if (find(options.begin(), options.end(), ans) == options.end()) {
            cout << "That is not an option!"
                 << "\nRemember that you cannot chose the same territory more than once, "
                 << "and must chose from the list provided" << endl;
        } else {
            listToDefend->push_back(this->getPlayerTerritories()->at(ans));
            counter = 0;
            for (auto el : options) {
                if (el == ans) {
                    options.erase(options.begin() + counter);
                }
                counter++;
            }//end of for
            cout << "Added " << this->getPlayerTerritories()->at(ans)->getTerritoryName() << " to your list." << endl;
        }//end of else (valid option chosen)
    }//end of while

    // Returning territories to defend
    return listToDefend;
} ///end of toDefend() method

std::vector<Territory*>* Player::toAttack(Map* theMap) {
    cout << "\n Here are the places that you can attack:" << endl;
    vector<Territory*>* attackable = this->AttackAble(theMap);
    vector<Territory *> *chosen = new vector<Territory *>;
    if(attackable->size() > 0) {
        vector<int> options = {}; //so that they don't pick the same territory more than once
//        set<int> *options = new set<int>; //so that they don't pick the same territory more than once
        for (int i = 0; i < attackable->size(); i++) {
            options.push_back(i);
            cout << i << ": " << attackable->at(i)->getTerritoryName() << endl;
        }//end of for (show all attackable territories)
        cout
                << "\nType the corresponding numbers in the above list of the territories you would like to attack, in order of priority."
                << "\nENTER A NEGATIVE NUMBER IF YOU ARE FINISHED. Input answers one at a time." << endl;
        bool done = false;
        while (done == false) {
            int ans = -1;
            cout << "What territory will you attack?" << endl;
            cin >> ans;
            if (ans < 0) { done = true; }
            else if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                continue; // Keep prompting user
            }
            else if (find(options.begin(), options.end(), ans) == options.end()) {
                cout << "That is not an option!"
                     << "\nRemember that you cannot chose the same territory more than once, "
                     << "and must chose from the list provided" << endl;
            } else {
                chosen->push_back(attackable->at(ans));
                counter = 0;
                for (auto el : options) {
                    if (el == ans) {
                        options.erase(options.begin() + counter);
                    }
                    counter++;
                }//end of for
                cout << "Added " << attackable->at(ans)->getTerritoryName() << " to your list." << endl;
            }//end of else (valid option chosen)
        }//end of while
        cout << "Great! You have chosen which territories you would like to attack" << endl;
    }//end of if (player actually had options for attacking).
    else{
        cout << "Oh! There aren't any." << endl;
    }
    // Returning territories to attack
    return chosen;
}
///end of toAttack method

void Player::removeTerritory(Territory *t) {
    // Remove territory from player's list of Territory
    int i = 0;
    for(Territory *c : *this->getPlayerTerritories()) {
        if (t->getId() == c->getId())
            this->getPlayerTerritories()->erase(this->getPlayerTerritories()->begin()+i);
        i++;
    }
}
///end of removeTerritory
