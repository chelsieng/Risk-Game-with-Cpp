#include <iostream>
#include <cstdlib> //so that we can create random numbers

#include "GameEngine.h"
#include "Cards.h"
#include "MapLoader.h"

GameEngine::GameEngine() {
    this->phase = "";
    this->playerTurn = -1;
    this->curr_player = nullptr;
    this->issueRound = -1;
    this->issueResponse = -1;
    this->totalPlayers = nullptr;
    this->currMap = nullptr;
    this->isPhase = true;
    this->isStatistics = true;
}

GameEngine::~GameEngine() {
    delete this->curr_player;
    this->curr_player = nullptr;

    delete this->currMap;
    this->currMap = nullptr;

    delete this->totalPlayers;
    this->totalPlayers = nullptr;
}

Map* generateMap(MapLoader* mapLoader) {
    return mapLoader->getMap();
}

Map *GameEngine::getMap() {
    return this->currMap;
}

string GameEngine::getPhase() {
    return this->phase;
}

int GameEngine::getPlayerTurn() {
    return this->playerTurn;
}

string GameEngine::getConqTerr() {
    return this->conqTerr;
}

int GameEngine::getEliminatedPLayer() {
    return this->eliminatedPlayer;
}

vector<Player *> *GameEngine::getTotalPlayers() {
    return this->totalPlayers;
}

void GameEngine::setPlayerTurn(int p) {
    this->playerTurn = p;
}

int GameEngine::getIssueResponse() {
    return this->issueResponse;
}

void GameEngine::setIssueResponse(int r) {
    this->issueResponse = r;
}

Player *GameEngine::getCurrPlayer() {
    return this->curr_player;
}

void GameEngine::gameStart(GameEngine *g) {
    cout << "* ------------------------------ * " << endl;
    cout << "| Welcome to Warzone's Risk Game |" << endl;
    cout << "* ------------------------------ *" << endl;

    string boolPhase = "";
    cout << "Would you like to enable Observers?" << endl;
    cout << "Enter y or n" << endl;

    while (boolPhase.empty() || (boolPhase != "y" && boolPhase != "n")) {
        cin >> boolPhase;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            continue;
        }
        cout << "Enter any key to continue>> "; // Prompt user to press any key to continue
        cout << endl;
    }

    if (boolPhase == "y") {
        this->isPhase = true;
    }
    if (boolPhase == "n") {
        this->isPhase = false;
    }

    if (this->isPhase) {
        this->phaseObserver = new PhaseObserver(this);
        this->statisticsObserver = new StatisticsObserver(this);
    }
    Map *mapGame = nullptr;
    vector<Player *> *players = new vector<Player *>;
    // If user selects valid map file which creates valid map graph, map selection done


    mapGame = g->selectMap();
    // PLAYER AND DECK CREATION PHASE
    players = g->createPlayers(); // Store players in vector of players

    g->startupPhase(players, mapGame->getTerritories());
    g->mainGameLoop(players, mapGame->getContinents(), mapGame);
}

// Function returns true if user selected a valid map file with valid map graph
Map *GameEngine::selectMap() {
    this->phase = "Map Selection";
    this->notify();

    int mapSelection = -1;
    string key; // "Press any key" feature for later

    // Map data structure where key = user select int and value = map files from ../Map Files/ directory
    map<int, string> map = {
            // Domination
            {1, "../Map Files/Domination/artic.map"},
            {2, "../Map Files/Domination/berlin.map"},
            {3, "../Map Files/Domination/brasil2.map"},
            {4, "../Map Files/Domination/mexico.map"},
            {5, "../Map Files/Domination/northern-europe.map"},
            {6, "../Map Files/Domination/swiss.map"},

            // Conquest
            {7, "../Map Files/Conquest/Africa.map"},
            {8, "../Map Files/Conquest/Asia.map"},
            {9, "../Map Files/Conquest/Earthsea.map"},
            {10, "../Map Files/Conquest/Eurasia - WWII 1939.map"},
            {11, "../Map Files/Conquest/Medieval Europe.map"},
            {12, "../Map Files/Conquest/Mediterranean.map"},
    };

    // If user selection loads invalid map files or creates invalid map graph, keep prompting user to select map file
    while (true) {
        // Since mapSelection is an int, if user enters otherwise keep prompting
        if (cin.fail()) {
            cin.clear(); // clears error flag
            cin.ignore(); // skips to the next line
            continue; // Keep prompting user
        }
        cout << "I. Choose a map from the list of map files below: " << endl;
        cout << endl;
        cout << "Domination Maps" << endl;
        cout << "===============" << endl;
        cout << "\t1. Artic.map" << endl;
        cout << "\t2. Berlin.map" << endl;
        cout << "\t3. Brasil.map" << endl;
        cout << "\t4. Mexico.map" << endl;
        cout << "\t5. Northern-Europe.map" << endl;
        cout << "\t6. Swiss.map" << endl;
        cout << endl;
        cout << "Conquest Maps" << endl;
        cout << "=============" << endl;
        cout << "\t7. Africa.map" << endl;
        cout << "\t8. Asia.map" << endl;
        cout << "\t9. Earthsea.map" << endl;
        cout << "\t10. Eurasia - WWII 1939.map" << endl;
        cout << "\t11. Medival Europe.map" << endl;
        cout << "\t12. Mediterranean.map" << endl;
        cout << endl;
        cout << ">> ";
        cin >> mapSelection; // user enter selection
        // Returns false if user enters integer which is out of bound
        if (map.count(mapSelection) < 1 || map.count(mapSelection) > 12) {
            cout << "Please try again." << endl << endl;
            mapSelection = -1;
            continue;
        }

        MapLoader *mapLoader = nullptr;
        ConquestFileReader *reader = nullptr;
        if (mapSelection >= 7) {
            reader = new ConquestFileReader(map[mapSelection]);
            mapLoader = new ConquestFileReaderAdapter(reader);
        } else {
            mapLoader = new MapLoader(map[mapSelection]); //Loading selected map files
        }

        // Returns false if map file fails to load (ie invalid map file)
        if (generateMap(mapLoader) == nullptr) {
            cout << "Please try again." << endl << endl;
            delete mapLoader; // handling memory
            delete reader;
            continue;
        }

        // Map file successfully loaded
        cout << endl;
        cout << "Great! Now let's have a look at your map: " << endl;

        // returns true if map graph is valid
        if (generateMap(mapLoader)->validate()) {
            while (key.empty()) {
                cout << "Enter any key to continue>> "; // Prompt user to press any key to continue
                cin >> key;
                cout << endl;
                // uncomment to see map of game which user selected from
                cout << *generateMap(mapLoader);
            }
            //     *mapGame = *m->getMap(); // Assign valid map to global variable mapGame
            return generateMap(mapLoader);
        } // else return false if map graph is invalid
        else {
            cout << "Please try again." << endl << endl;
            delete mapLoader; // handling memory
            delete reader;
            continue;
        }
    }

}

vector<Player *> *GameEngine::createPlayers() {
    this->phase = "Player and Deck Creation";
    this->notify();

    int numOfPlayers = 0;

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

    Deck *deck = createDeck(); // creating deck of cards for the game
    auto *pList = new vector<Player *>;
    this->totalPlayers = pList;
    string key; // "Press any key" feature for later
    for (int i = 0; i < numOfPlayers; i++) {
        Hand *hand = new Hand(0, deck); // creating hand for each player
        auto *territories = new vector<Territory *>; // creating vector territories for each player
        auto *ordersList = new OrdersList(); // creating orderList for each player
        auto *player = new Player(hand, ordersList, territories); // creating amount of players user initiated
        ///Get strategy type
        cout << "\nWhat type of player is P" << player->getId() << "? Type in the corresponding number from the list below." << endl;
        cout << "1. Human player" << endl;
        cout << "2. Aggressive CPU" << endl;
        cout << "3. Benevolent CPU" << endl;
        cout << "4. Neutral CPU" << endl;
        int ans;
        bool valid = false;
        while (valid == false) {
            cin >> ans;
            cout << endl;
            if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                valid = false; // Keep prompting user
            } else if (ans < 5 && ans > 0) { valid = true; } //(switch 3 to 5 later)
            else {
                cout << "\nInvalid answer! Please try again." << endl;
            }
        }//end of while (get valid answer)
        if (ans == 1) { player->setPlayerStrategy(new HumanPlayerStrategy()); }
        if (ans == 2) { player->setPlayerStrategy(new AggressivePlayerStrategy()); }
        if (ans == 3) { player->setPlayerStrategy(new BenevolentPlayerStrategy()); }
        if (ans == 4) { player->setPlayerStrategy(new NeutralPlayerStrategy()); }
        ///
        pList->push_back(player); // storing players in global vector variable players
    }
    cout << endl << numOfPlayers << " players have been successfully created. \nLet's have a look at them: " << endl;
    while (key.empty()) {
        cout << "Enter any key to continue>> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }
    for (auto p: *pList) {
        cout << *p << endl;
    }

    key = "";
    while (key.empty()) {
        cout << "Enter any key to continue>> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
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
        cout << "Enter any key to continue>> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }
    cout << *theDeck;
    return theDeck;
}

void GameEngine::startupPhase(vector<Player *> *ps1, vector<Territory *> *ts) {
//    this->currMap =
    this->phase = "Startup Phase";
    this->notify();
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

    for (auto p: *ps1) {
        cout << "P" << p->getId() << " owns the following territories: " << endl;
        for (auto terr : *p->getPlayerTerritories()) {
            cout << *terr;
        }
        cout << endl;
    }
////All territories have been assigned randomly. We will now give everyone armies based on the number of players
    // Assign armies

    cout << "\nAll players have had armies added to their reinforcement pool." << endl << endl;
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
    cout << "Number of armies in reinforcement pool: " << endl;
    for (auto p: *ps1) {
        cout << "P" << p->getId() << ": " << p->getReinforcementPool() << endl;
    }

    string key;
    while (key.empty()) {
        cout << "Enter any key to continue>> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }

////Almost done!
//original players vector is assigned version with randomized turn order
    *ps1 = *ps;
    ps = NULL;
}

//end of startup phase function implementation

////END OF STARTUPPHASE FUNCTION

void GameEngine::reinforcementPhase(vector<Player *> *ps1, vector<Continent *> *theContinents) {
    this->phase = "Reinforcement Phase";
    this->notify();
    //Give each player a number of armies based on the number of territories they own
    //(number owned / 3, rounded down)

    for (int i = 0; i < ps1->size(); i++) {
        Player *player = ps1->at(i);
        this->setPlayerTurn(player->getId());
        int numOfTerritories = player->getPlayerTerritories()->size();
        this->phase = "Player Reinforcement";
        this->notify();
        //Give each player a number of armies based on the number of territories they own
        //(number owned / 3, rounded down)
        int toAdd = 0;
        toAdd = numOfTerritories / 3;
        player->setReinforcementPool(player->getReinforcementPool() + toAdd);
        cout << "Since P" << player->getId() << " owns " << numOfTerritories << " territories, they get "
             << toAdd << " armies added to their reinforcement pool" << endl;


        int toAdd2 = 0;
        for (int j = 0; j < theContinents->size(); j++) {
            if (theContinents->at(j)->isOccupiedBy(player)) {
                int bonus = theContinents->at(j)->getControlValue();
                toAdd2 = toAdd2 + bonus;
                cout << "Since P" << player->getId() << " owns the continent "
                     << theContinents->at(j)->getContinentName()
                     << ", they get a bonus of " << bonus << " armies" << endl;
                player->setReinforcementPool(player->getReinforcementPool() + bonus);
            }//end of if (they get a bonus)
        }//end of for (go through all continents)
        if (toAdd2 == 0) {
            cout << "P" << player->getId() << " doesn't own any continents, so they won't receive any bonus for that."
                 << endl;
        }

        //Make sure each player gets a minimum of 3 armies this turn to deploy
        int totalAdded = toAdd + toAdd2;
        if (totalAdded < 3) {
            int minimum = 3 - totalAdded;
            player->setReinforcementPool(player->getReinforcementPool() + minimum);
            cout << "P" << player->getId() << " didn't get many armies, so they have been given "
                 << minimum << " more." << endl;
        }//end of if (they had been given less than 3 until now)


    }//end of for loop (go through process for each player)
    cout << endl;
    string key;
    while (key.empty()) {
        cout << "Enter any key to continue>> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }
}///end of reinforcementPhase function

void GameEngine::orderIssuingPhase(vector<Player *> *thePlayers, Map *theMap) {
    this->phase = "Order Issuing Phase";
    this->notify();
    //Reset mock armies for everyone's territories: (moved this to the start of the turn -> bug fix)
    for (int i = 0; i < thePlayers->size(); i++) {
        Player *p = thePlayers->at(i);
        for (int j = 0; j < p->getPlayerTerritories()->size(); j++) {
            p->getPlayerTerritories()->at(j)->resetMockArmies();
        }//end of for (all owned territories)
    }//end of for (all players)
    this->issueRound = 0;
    bool notDone = true;
    while (notDone == true) {
        if (this->issueRound != 0) {
            notDone = false;
        }
        for (int i = 0; i < thePlayers->size(); i++) {
            Player *p = thePlayers->at(i);
            this->curr_player = nullptr;
            this->curr_player = p;
            this->setPlayerTurn(thePlayers->at(i)->getId());
            cout << "\n***Alright Player " << p->getId() << ", it's your turn to issue an order!***" << endl;
            if (issueRound == 0) {
                cout << "\nYou must issue any deploy orders before you can do anything else!\n" << endl;
                p->issueOrder(theMap, thePlayers, 0, p);
            }//end of if (deploy round)
            else {
            bool didTheyIssue = false;
                   didTheyIssue = p->issueOrder(theMap, thePlayers, 1, p);
                   if(didTheyIssue == true){
                       notDone = true;
                   }//(someone issued an order this round, so there will be another round after this)

            }//end of else (not first issue round)
        } //end of for (round robing order issuing for all players)
        issueRound = issueRound + 1;
    }//end of while
    cout << "\nIt seems that everyone is finished issuing orders!" << endl;
    string key;
    while (key.empty()) {
        cout << "\nEnter any key to continue>> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }//end of while

}///end of order issuing phase function

void GameEngine::orderExecutionPhase(vector<Player *> *thePlayers) {
    this->phase = "Order Execution Phase";
    this->notify();
    cout << "Time to execute everyone's orders!" << endl;
    bool notDone = true;
    bool someoneIssued = false;
    while (notDone == true) {
        someoneIssued = false;
        for (int i = 0; i < thePlayers->size(); i++) {
            playerTurn = thePlayers->at(i)->getId();
            if (thePlayers->at(i)->getOrdersList()->getSize() == 0) {
            }//end of if (player has no more orders)
            else {
                this->phase = "Player Execution";
                this->notify();
                int owner = -1;
                someoneIssued = true;
                cout << "Executing P" << thePlayers->at(i)->getId() << "'s next order." << endl;
                int indexOfHighest = thePlayers->at(i)->getOrdersList()->highestPriority();
                Order *toExecute = thePlayers->at(i)->getOrdersList()->getAt(indexOfHighest);

                if (toExecute->getTargetTerritory() != nullptr) {
                    owner = toExecute->getTargetTerritory()->getOwner()->getId();
                }
                toExecute->execute();
                if (toExecute->getTargetTerritory() != nullptr) {
                    if (toExecute->getTargetTerritory()->getOwner()->getId() != owner) {
                        this->conqTerr = toExecute->getTargetTerritory()->getTerritoryName();
                        this->phase = "Conquered";
                        this->notify();

                    }
                }
                thePlayers->at(i)->getOrdersList()->deleteAt(indexOfHighest);
            }//end of else (player still has orders)
        }//end of for (go through all players)
        if (someoneIssued == true) {
            notDone = true;
        } else {
            notDone = false;
        }
    }//end of while

    cout << endl;
    string key;
    while (key.empty()) {
        cout << "Enter any key to continue>> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }
}///end of order execution phase

void GameEngine::mainGameLoop(vector<Player *> *thePlayers, vector<Continent *> *theContinents, Map *theMap) {
    bool won = false;
    vector<Player *> *theFallenOnes = new vector<Player *>; //will contain players to remove, if any
    while (won == false) {
        for (int i = 0; i < thePlayers->size(); i++) {
            thePlayers->at(i)->setConquered(false);
        }//end of for (set hasConquered to false for each player at start of round)
        GameEngine::reinforcementPhase(thePlayers, theContinents);

        GameEngine::orderIssuingPhase(thePlayers, theMap);

        GameEngine::orderExecutionPhase(thePlayers);

        //check if somebody has won:
        bool all = true;
        Player *winner;
        for (int i = 0; i < thePlayers->size(); i++) {
            all = true;
            Player *current = thePlayers->at(i);
            this->playerTurn = current->getId();
            for (int j = 0; j < theContinents->size(); j++) {
                if (!(theContinents->at(j)->isOccupiedBy(current))) {
                    all = false;
                }
            }//end of for (check all continents)
            if (all == true) {
                winner = current;
                won = true;
                this->phase = "Game Over";
                this->notify();

                if (!this->isPhase)
                    cout << "Congratulations Player " << current->getId() << ", you've won the game! **" << endl;
            }//end of if(current player has won)
        }//end of for (check for all players)
        if (won == false) {
            //Remove players with no more territories from the game
            for (int k = 0; k < thePlayers->size(); k++) {
                if (thePlayers->at(k)->getPlayerTerritories()->empty()) {
                    theFallenOnes->push_back(thePlayers->at(k));
                }//end of if (player no longer owns any territories)
            }//end of for (see who has to be removed from the game)
            if (theFallenOnes != nullptr && !theFallenOnes->empty()) {
                for (int i = 0; i < theFallenOnes->size(); i++) {
                    int IDofPlayer = theFallenOnes->at(i)->getId();
                    for (int j = 0; j < thePlayers->size(); j++) {
                        if (thePlayers->at(j)->getId() == IDofPlayer) {
                            thePlayers->erase(thePlayers->begin() + j);
                            this->eliminatedPlayer = IDofPlayer;
                            this->phase = "Player Eliminated";
                            this->notify();
                            if (!this->isPhase)
                                cout << "Player " << IDofPlayer << " owns no territories - they have been removed from the game!";
                        }//end of if (player to be removed found)
                    }//end of for (go and remove that player from the players list)
                }//end of for (go through all players that have to be removed)
            }//end of if (there are players who must be removed from the game)
            theFallenOnes->clear();
            this->totalPlayers = thePlayers;
            this->currMap = theMap;
            this->phase = "Statistics";
            this->notify();
            if (!this->isPhase)
                cout << "\nLet's see everyone's current standings:" << endl;
            for (int m = 0; m < thePlayers->size(); m++) {
                cout << *thePlayers->at(m) << endl;
            }//end of for (print all player statuses)
            ///Option to change strategy during play
            cout << "\nWould you like to change any of the players' strategies? Type 'y' for yes, and anything else for no." << endl;
            string ans = "";
            cin >> ans;
            if(ans == "y") {
                for (Player *player : *thePlayers) {
                    cout << "\nWould you like to change P" << player->getId()<<"'s strategy? Type 'y' for yes, and anything else for no." << endl;
                    string ans = "";
                    cin >> ans;
                    if(ans == "y") {
                        ///Get strategy type
                        cout << "\nWhat type of player is P" << player->getId()
                             << "? Type in the corresponding number from the list below." << endl;
                        cout << "1. Human player" << endl;
                        cout << "2. Aggressive CPU" << endl;
                        cout << "3. Benevolent CPU" << endl;
                        cout << "4. Neutral CPU" << endl;
                        int ans;
                        bool valid = false;
                        while (valid == false) {
                            cin >> ans;
                            cout << endl;
                            if (cin.fail()) {
                                cin.clear(); // clears error flag
                                cin.ignore(); // skips to the next line
                                valid = false; // Keep prompting user
                            } else if (ans < 5 && ans > 0) { valid = true; } //(switch 3 to 5 later)
                            else {
                                cout << "\nInvalid answer! Please try again." << endl;
                            }
                        }//end of while (get valid answer)
                        if (ans == 1) { player->setPlayerStrategy(new HumanPlayerStrategy()); }
                        if (ans == 2) { player->setPlayerStrategy(new AggressivePlayerStrategy()); }
                        if (ans == 3) { player->setPlayerStrategy(new BenevolentPlayerStrategy()); }
                        if (ans == 4) { player->setPlayerStrategy(new NeutralPlayerStrategy()); }
                    }//end of if (they chose to change this specific player's strategy)
                }//end of for (go through all players)
            }//end of if (they chose yes to change some strategies)
            ///
            ///
        }//end of if (nobody has won so far)
    }//end of while

}///END OF MAIN GAME LOOP

int main() {
    GameEngine *gameEngine = new GameEngine();
    gameEngine->gameStart(gameEngine);

    delete gameEngine;
    return 0;
}


