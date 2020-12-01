#include "GameStart.h"
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <map>
#include <string>


using namespace std;

// Function returns true if user selected a valid map file with valid map graph
bool GameStart::selectMap(int mapSelection) {
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

vector<Player *> GameStart::createPlayers(int numOfPlayers) {
    Deck *deck = createDeck(); // creating deck of cards for the game
    vector<Player *> pList;
    string key; // "Press any key" feature for later
    for (int i = 0; i < numOfPlayers; i++) {
        Hand *hand = new Hand(0, deck); // creating hand for each player
        vector<Territory *> *territories = nullptr; // creating vector territories for each player
        auto *ordersList = new OrdersList(); // creating orderList for each player
        auto *player = new Player(hand, ordersList, territories); // creating amount of players user initiated
        pList.push_back(player); // storing players in global vector variable players
    }
    cout << endl << numOfPlayers << " players have been successfully created. \nLet's have a look at them: " << endl;
    while (key.empty()) {
        cout << "Press any key >> "; // Prompt user to press any key to continue
        cin >> key;
        cout << endl;
    }
    for (auto p: pList) {
        cout << *p << endl;
    }
    return pList;
}

Deck *GameStart::createDeck() {
    BombCard *startCard = new BombCard();
    deckNode *baseOfDeck = new deckNode(startCard);
    Deck *theDeck = new Deck(baseOfDeck);
    string key; // "Press any key" feature for later
    for (int i = 0; i < 50; i++) {
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

//int main() {
//    int mapSelection; // int where user selects map file to be loaded
//    int numOfPlayers; // int where user selects the number of players in the game
//    // Displaying welcome message
//    cout << "* ------------------------------ * " << endl;
//    cout << "| Welcome to Warzone's Risk Game |" << endl;
//    cout << "* ------------------------------ *" << endl;
//    cout << endl;
//    cout << "- Game start -" << endl;
//    cout << endl;
//    // If user selection loads invalid map files or creates invalid map graph, keep prompting user to select map file
//    while (true) {
//        // Since mapSelection is an int, if user enters otherwise keep prompting
//        if (cin.fail()) {
//            cin.clear(); // clears error flag
//            cin.ignore(); // skips to the next line
//            continue; // Keep prompting user
//        }
//        cout << "I. Choose a map from the list of map files below: " << endl;
//        cout << "\t1. artic.map" << endl;
//        cout << "\t2. berlin.map" << endl;
//        cout << "\t3. brasil.map" << endl;
//        cout << "\t4. mexico.map" << endl;
//        cout << "\t5. northern-europe.map" << endl;
//        cout << "\t6. swiss.map" << endl;
//        cout << "\t7. world.map" << endl;
//        cout << ">> ";
//        cin >> mapSelection; // user enter selection
//        // If user selects valid map file which creates valid map graph, map selection done
//        if (GameStart::selectMap(mapSelection)) {
//            break;
//        }
//    }
//    // uncomment to see map of game which user selected from
////    cout << *mapGame;
//    while (numOfPlayers > 5 || numOfPlayers < 2) {
//        // Since numOfPlayers is an int, if user enters otherwise keep prompting
//        if (cin.fail()) {
//            cin.clear(); // clears error flag
//            cin.ignore(); // skips to the next line
//            continue; // Keep prompting user
//        }
//        cout << "II. Choose the number of players in the game (2-5 players): " << endl;
//        cout << ">> ";
//        cin >> numOfPlayers;
//    }
//    players = GameStart::createPlayers(numOfPlayers); // Store players in vector of players
//    //Uncomment to check if players were created
//
//    return 0;
//}


