
#pragma once
#include <iostream>
#include <cstdlib> //so that we can create random numbers
#include "Cards.h"
int main() {
    std::cout << "We're gonna create a deck of cards- but not hardcoded!\n" << std::endl;


    //Oh except this first card, that is indeed hardcoded
    BombCard* startCard = new BombCard();
    deckNode* baseOfDeck = new deckNode(startCard);
    Deck theDeck(baseOfDeck);

    for(int i = 0; i < 50; i++){
        int randomNumber = rand();
        if(randomNumber%5 == 0)
              theDeck.addToDeck(new BombCard());
        else if(randomNumber%5 == 1)
            theDeck.addToDeck(new DiplomacyCard());
        else if(randomNumber%5 == 2) {
            //we have to decide how many armies this card gives
            int numOfArmies = rand()%3;
            if(numOfArmies == 0){numOfArmies = 3;} //avoiding cards that give no armies
            theDeck.addToDeck(new ReinforcementCard(numOfArmies));
        }
        else if(randomNumber%5 == 3)
            theDeck.addToDeck(new AirliftCard());
        else if(randomNumber%5 == 4)
            theDeck.addToDeck(new BlockadeCard());
    }//end of for (putting random cards in Deck)

    cout << theDeck << endl;
    cout << "You see that shit? Now that's fucking sexy." << endl;

    return 0;
}
