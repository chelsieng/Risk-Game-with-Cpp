#include <vector>
#include <Map.h>
#include <Orders.h>
#include <Player.h>

using namespace std;

int main() {

    // Creating DECK, CARDS, AND HAND
    BombCard bomb;
    ReinforcementCard reinforcement;
    DiplomacyCard diplomacy;
    BlockadeCard blockade;
    AirliftCard airlift;

    // First card in Deck
    deckNode head(&bomb, nullptr);

    // Adding rest of cards to deck
    Deck* deck = new Deck(&head);
    deck->addToDeck(&bomb);
    deck->addToDeck(&diplomacy);
    deck->addToDeck(&blockade);
    deck->addToDeck(&airlift);

    //-----------------------------------

    // CREATING PLAYER
    Hand* playerHand = new Hand(4, deck);
    OrdersList* orderList = new OrdersList();
    vector<Map::Territory*>* terr;

    Player* p1 = new Player(playerHand, orderList, terr);

    // Creating Territories
    Map::Territory *territory1 = new Map::Territory(p1);
    Map::Territory *territory2 = new Map::Territory(p1);
    Map::Territory *territory3 = new Map::Territory(p1);
    Map::Territory *territory4 = new Map::Territory(p1);
    Map::Territory *territory5 = new Map::Territory(p1);

    territoryList.push_back(territory1);
    territoryList.push_back(territory2);
    territoryList.push_back(territory3);
    territoryList.push_back(territory4);
    territoryList.push_back(territory5);

    //ORDERS AND ORDERLIST



    Order *deploy = new Deploy(player1, territory1, numOfArmies);
    Order *advance = new Advance(player1, territory1, territory2, numOfArmies);
    Order *bomb = new Bomb(player1,territory1, territory2);
    Order *blockade = new Blockade(player1, territory1);
    Order *negotiate = new Negotiate(player1, player2);
    Order *airlift = new Airlift(player1, territory1, territory2, numOfArmies);
    OrdersList* playerOrdersList = new OrdersList();

//    playerOrdersList->addToLast(b1);

    // Creating hand





}