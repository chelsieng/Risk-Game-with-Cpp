#pragma once

#include <iostream>
#include <cstdlib> //so that we can create random numbers
#include "GameEngine.h"
#include "Cards.h"
#include "MapLoader.h"

// Function returns true if user selected a valid map file with valid map graph
bool GameEngine::selectMap(int mapSelection) {
    string key; // "Press any key" feature for later
    // Map data structure where key = user select int and value = map files from ../Map Files/ directory
    map<int, string> map = {
            {1, "../Map Files/artic.map"},
            {2, "../Map Files/berlin.map"},
            {3, "../Map Files/brasil.map"},
            {4, "../Map Files/mexico.map"},
            {5, "../Map Files/northern-europe.map"},
            {6, "../Map Files/swiss.map"},
            {7, "../Map Files/world.map"}
    };
    // Returns false if user enters integer which is out of bound
    if (map.count(mapSelection) < 1 || map.count(mapSelection) > 7) {
        cout << "Please try again." << endl << endl;
        return false;
    }
    auto *m = new MapLoader(map[mapSelection]); //Loading selected map files
    // Returns false if map file fails to load (ie invalid map file)
    if (m->getMap() == nullptr) {
        cout << "Please try again." << endl << endl;
        delete m; // handling memory
        return false;
    }
    // Map file successfully loaded
    cout << "Great! Now let's have a look at your map: " << endl;
    // returns true if map graph is valid
    if (m->getMap()->validate()) {
        while (key.empty()) {
            cout << "Press any key >> "; // Prompt user to press any key to continue
            cin >> key;
            cout << endl;
        }
        cout << *m->getMap() << endl; // Display info of map
        mapGame = m->getMap(); // Assign valid map to global variable mapGame
        return true;
    } // else return false if map graph is invalid
    else {
        cout << "Please try again." << endl << endl;
        delete m; // handling memory
        return false;
    }

}

vector<Player *> *GameEngine::createPlayers(int numOfPlayers) {
    Deck *deck = createDeck(); // creating deck of cards for the game
    auto *pList = new vector<Player *>;
    string key; // "Press any key" feature for later
    for (int i = 0; i < numOfPlayers; i++) {
        Hand *hand = new Hand(0, deck); // creating hand for each player
        auto *territories = new vector<Territory *>; // creating vector territories for each player
        auto *ordersList = new OrdersList(); // creating orderList for each player
        auto *player = new Player(hand, ordersList, territories); // creating amount of players user initiated
        pList->push_back(player); // storing players in global vector variable players
    }
    cout << endl << numOfPlayers << " players have been successfully created. \nLet's have a look at them: " << endl;
    while (key.empty()) {
        cout << "Press any key >> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }
    for (auto p: *pList) {
        cout << *p << endl;
    }
    return pList;
}

Deck *GameEngine::createDeck() {
    auto *startCard = new BombCard();
    auto *baseOfDeck = new deckNode(startCard);
    Deck *theDeck = new Deck(baseOfDeck);
    string key; // "Press any key" feature for later
    for (int i = 0; i < 49; i++) {
        int randomNumber = rand();
        if (randomNumber % 5 == 0)
            theDeck->addToDeck(new BombCard());
        else if (randomNumber % 5 == 1)
            theDeck->addToDeck(new DiplomacyCard());
        else if (randomNumber % 5 == 2) {
            //we have to decide how many armies this card gives
            int numOfArmies = rand() % 3;
            if (numOfArmies == 0) { numOfArmies = 3; } //avoiding cards that give no armies
            theDeck->addToDeck(new ReinforcementCard(numOfArmies));
        } else if (randomNumber % 5 == 3)
            theDeck->addToDeck(new AirliftCard());
        else if (randomNumber % 5 == 4)
            theDeck->addToDeck(new BlockadeCard());
    }//end of for (putting random cards in Deck)
    cout << endl << "First let's have a look at your deck" << endl;
    while (key.empty()) {
        cout << "Press any key >> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }
    cout << *theDeck;
    return theDeck;
}

void GameEngine::startupPhase(vector<Player *> *ps1, vector<Territory *> *ts) {
    //create shallow copy of players vector that will be assigned back to the original later.
    vector<Player *> psv(*ps1);
    vector<Player *> *ps = new vector<Player *>(psv);
    //Assign random order to players
    srand(time(NULL)); //So that we get a new random number each time this
    int shuffleCounter = rand() % 10; //specific value of this doesn't actually matter, but should be random
    for (int i = 0; i < shuffleCounter; i++) {
        int randomNumber = rand() % (ps->size() - 1);
        Player *playerBeingShuffled = ps->at(randomNumber);
        ps->push_back(playerBeingShuffled);
        ps->erase(ps->begin() + randomNumber);
    }//end of for (shuffling players)

    cout << "The turn order has been decided!" << endl;
    cout << "Here is the turn order:" << endl;

    for (int i = 0; i < ps->size(); i++) {
        cout << "P" << ps->at(i)->getId() << endl;
    }

    ///Great, we've assigned a random turn order
    ///Now, we will assign all the territories in the passed vector, randomly

    //to do, we'll first create a copy of the vector of territories
    //it is a shallow copy, which is exactly what we need actually, cause we don't want to change
    //the initial territory vector

    vector<Territory *> tsCopyValue(*ts);
    vector<Territory *> *tsCopy = &tsCopyValue;

    cout << "\nHere are the territories that need to be assigned: " << endl;

    for (int i = 0; i < ts->size(); i++) {
        cout << *ts->at(i) << endl;
    }

    //we will randomize the *copy* of our territories vector in a similar fashion as we did
    //to determine player order, so as to randomize who gets which territories
    //Naturally, this randomized order of territories will be shown to the player

    srand(time(NULL)); //So that we get a new random number each time this
    int shuffleCounter2 = rand() % 10; //specific value of this doesn't actually matter, but should be random
    for (int i = 0; i < shuffleCounter2; i++) {
        int randomNumber = rand() % (tsCopy->size() - 1);
        Territory *territoryBeingShuffled = tsCopy->at(randomNumber);
        tsCopy->push_back(territoryBeingShuffled);
        tsCopy->erase(tsCopy->begin() + randomNumber);
    }//end of for (shuffling players)

    Player *next = ps1->at(0);
    for (int i = 0; i < tsCopy->size(); i++) {
        next = ps1->at(i % (ps1->size()));
        next->getPlayerTerritories()->push_back(tsCopy->at(i));
        cout << "Assigning " << tsCopy->at(i)->getTerritoryName() << " to P" << ps1->at(i % (ps1->size()))->getId()
             << endl;
        tsCopy->at(i)->setOwner(ps1->at(i % (ps1->size())));
    }//end of for (assign all territories)
    //  delete tsCopy;
    tsCopy = nullptr;

    cout << "\nAll territories have been assigned!" << endl;

    cout << "\nLets see the list of territories once again:\n" << endl;

    for (auto p: *players) {
        cout << "P" << p->getId() << " owns the following territories: " << endl;
        for (auto terr : *p->getPlayerTerritories()) {
            cout << *terr;
        }
        cout << endl;
    }
////All territories have been assigned randomly. We will now give everyone armies based on the number of players
    // Assign armies

    cout << "\nAll players have had armies added to their reinforcement pool." << endl;
    for (int i = 0; i < ps1->size(); i++) {

        if (ps1->size() == 2)
            ps1->at(i)->setReinforcementPool(40);
        else if (ps1->size() == 3)
            ps1->at(i)->setReinforcementPool(35);
        else if (ps1->size() == 4)
            ps1->at(i)->setReinforcementPool(30);
        else if (ps1->size() == 5)
            ps1->at(i)->setReinforcementPool(25);
    }//end of for

////Almost done!
//original players vector is assigned version with randomized turn order
    *ps1 = *ps;
    ps = NULL;
}

//end of startup phase function implementation

////END OF STARTUPPHASE FUNCTION

void GameEngine::reinforcementPhase(vector<Player *> *ps1, vector<Continent *> *theContinents) {

    //Give each player a number of armies based on the number of territories they own
    //(number owned / 3, rounded down)

    for (int i = 0; i < ps1->size(); i++) {
        //Give each player a number of armies based on the number of territories they own
        //(number owned / 3, rounded down)
        int toAdd = 0;
        Player *player = ps1->at(i);
        int numOfTerritories = player->getPlayerTerritories()->size();
        toAdd = numOfTerritories / 3;
        player->setReinforcementPool(player->getReinforcementPool() + toAdd);
        cout << "Since P" << player->getId() << " owns " << numOfTerritories << " territories, they get "
             << toAdd << " armies added to their reinforcement pool" << endl;


        //Assign bonus if player owns entire continent
        //for each player
        //for each continent
        //for each territory
        ///So yeah we'll implement that once the control bonus has been added to the map class

        //Make sure each player gets a minimum of 3 armies this turn to deploy

        if (toAdd < 3) {
            int minimum = 3 - toAdd;
            player->setReinforcementPool(player->getReinforcementPool() + minimum);
            cout << "P" << player->getId() << " didn't get many armies, so they have been given "
                 << minimum << " more." << endl;
        }//end of if (they had been given less than 3 until now)

    }//end of for loop (go through process for each player)
}///end of reinforcementPhase function



int main() {
    int mapSelection; // int where user selects map file to be loaded
    int numOfPlayers; // int where user selects the number of players in the game
    string key; // Press any key feature for later
    // Displaying welcome message
    cout << "* ------------------------------ * " << endl;
    cout << "| Welcome to Warzone's Risk Game |" << endl;
    cout << "* ------------------------------ *" << endl;
    cout << endl;
    cout << "- Game start -" << endl;
    cout << endl;
    // If user selection loads invalid map files or creates invalid map graph, keep prompting user to select map file
    while (true) {
        // Since mapSelection is an int, if user enters otherwise keep prompting
        if (cin.fail()) {
            cin.clear(); // clears error flag
            cin.ignore(); // skips to the next line
            continue; // Keep prompting user
        }
        cout << "I. Choose a map from the list of map files below: " << endl;
        cout << "\t1. artic.map" << endl;
        cout << "\t2. berlin.map" << endl;
        cout << "\t3. brasil.map" << endl;
        cout << "\t4. mexico.map" << endl;
        cout << "\t5. northern-europe.map" << endl;
        cout << "\t6. swiss.map" << endl;
        cout << "\t7. world.map" << endl;
        cout << ">> ";
        cin >> mapSelection; // user enter selection
        // If user selects valid map file which creates valid map graph, map selection done
        if (GameEngine::selectMap(mapSelection)) {
            break;
        }
    }
    // uncomment to see map of game which user selected from
//    cout << *mapGame;
    while (numOfPlayers > 5 || numOfPlayers < 2) {
        // Since numOfPlayers is an int, if user enters otherwise keep prompting
        if (cin.fail()) {
            cin.clear(); // clears error flag
            cin.ignore(); // skips to the next line
            continue; // Keep prompting user
        }
        cout << "II. Choose the number of players in the game (2-5 players): " << endl;
        cout << ">> ";
        cin >> numOfPlayers;
    }
    players = GameEngine::createPlayers(numOfPlayers); // Store players in vector of players
    cout << "- You are now entering the Start Up Phase -" << endl;
    while (key.empty()) {
        cout << "Press any key >> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }
    GameEngine::startupPhase(players, mapGame->getTerritories());
    return 0;
}