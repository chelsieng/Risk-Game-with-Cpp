#pragma once

#include <iostream>
#include <cstdlib> //so that we can create random numbers
#include "GameEngine.h"
#include "Cards.h"

void GameEngine::startupPhase(vector<Player *>* ps1, vector<Territory*>* ts) {
    //create shallow copy of players vector that will be assigned back to the original later.
    vector<Player*> psv(*ps1);
    vector<Player*>* ps = new vector<Player*>(psv);
    //Assign random order to players
    srand(time(NULL)); //So that we get a new random number each time this
    int shuffleCounter = rand() % 10; //specific value of this doesn't actually matter, but should be random
    for(int i = 0; i < shuffleCounter; i++){
        int randomNumber = rand() % (ps->size()-1);
        Player* playerBeingShuffled = ps->at(randomNumber);
        ps->push_back(playerBeingShuffled);
        ps->erase(ps->begin() + randomNumber);
    }//end of for (shuffling players)

    cout << "The turn order has been decided!" << endl;
    cout << "Here is the turn order:" << endl;

    for(int i = 0; i < ps->size(); i++){
        cout << "P" << ps->at(i)->getId() << endl;
    }

    ///Great, we've assigned a random turn order
    ///Now, we will assign all the territories in the passed vector, randomly

    //to do, we'll first create a copy of the vector of territories
    //it is a shallow copy, which is exactly what we need actually, cause we don't want to change
    //the initial territory vector

    vector<Territory*> tsCopyValue(*ts);
    vector<Territory*>* tsCopy = &tsCopyValue;

    cout << "\nHere are the territories that need to be assigned" << endl;

    for(int i = 0; i < ts->size(); i++){
        cout << *ts->at(i) << endl;
    }

    //we will randomize the *copy* of our territories vector in a similar fashion as we did
    //to determine player order, so as to randomize who gets which territories
    //Naturally, this randomized order of territories will be shown to the player

    srand(time(NULL)); //So that we get a new random number each time this
    int shuffleCounter2 = rand() % 10; //specific value of this doesn't actually matter, but should be random
    for(int i = 0; i < shuffleCounter2; i++){
        int randomNumber = rand() % (tsCopy->size()-1);
        Territory* territoryBeingShuffled = tsCopy->at(randomNumber);
        tsCopy->push_back(territoryBeingShuffled);
        tsCopy->erase(tsCopy->begin() + randomNumber);
    }//end of for (shuffling players)

    Player* next = ps1->at(0);
    for(int i = 0; i < tsCopy->size(); i++){
        next = ps1->at(i% (ps1->size()));
        next->getPlayerTerritories()->push_back(tsCopy->at(i));
        cout << "Assigning " << tsCopy->at(i)->getTerritoryName() << " to P" << ps1->at(i% (ps1->size()))->getId() << endl;
        tsCopy->at(i)->setOwner(ps1->at(i% (ps1->size())));
    }//end of for (assign all territories)
    //  delete tsCopy;
    tsCopy = nullptr;

    cout << "\nAll territories have been assigned!" << endl;

    cout << "\nLets see the list of territories once again:\n" << endl;

    for(int i = 0; i < ts->size(); i++){
        cout << *ts->at(i) << endl;
    }
////All territories have been assigned randomly. We will now give everyone armies based on the number of players
    // Assign armies

    cout << "\nAll players have had armies added to their reinforcement pool." << endl;
    for (int i=0; i < ps1->size(); i++) {

        if(ps1->size() == 2)
            ps1->at(i)->setReinforcementPool(40);
        else if(ps1->size() == 3)
            ps1->at(i)->setReinforcementPool(35);
        else if(ps1->size() == 4)
            ps1->at(i)->setReinforcementPool(30);
        else if(ps1->size() == 5)
            ps1->at(i)->setReinforcementPool(25);
    }//end of for

////Almost done!
//original players vector is assigned version with randomized turn order
    *ps1 = *ps;
    ps = NULL;
}//end of startup phase function implementation

////END OF STARTUPPHASE FUNCTION


//int main() {
//    std::cout << "We're gonna create a deck of cards- but not hardcoded!\n" << std::endl;
//
//
//    //Oh except this first card, that is indeed hardcoded
//    BombCard *startCard = new BombCard();
//    deckNode *baseOfDeck = new deckNode(startCard);
//    Deck theDeck(baseOfDeck);
//
//    for (int i = 0; i < 50; i++) {
//        int randomNumber = rand();
//        if (randomNumber % 5 == 0)
//            theDeck.addToDeck(new BombCard());
//        else if (randomNumber % 5 == 1)
//            theDeck.addToDeck(new DiplomacyCard());
//        else if (randomNumber % 5 == 2) {
//            //we have to decide how many armies this card gives
//            int numOfArmies = rand() % 3;
//            if (numOfArmies == 0) { numOfArmies = 3; } //avoiding cards that give no armies
//            theDeck.addToDeck(new ReinforcementCard(numOfArmies));
//        } else if (randomNumber % 5 == 3)
//            theDeck.addToDeck(new AirliftCard());
//        else if (randomNumber % 5 == 4)
//            theDeck.addToDeck(new BlockadeCard());
//    }//end of for (putting random cards in Deck)

//    cout << theDeck << endl;
//    cout << "You see that shit? Now that's fucking sexy." << endl;

//    return 0;
//}