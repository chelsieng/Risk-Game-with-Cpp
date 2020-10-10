#include <vector>
#include <Orders.h>
#include <Player.h>

using namespace std;

int main() {


    Order* bombOrder = new Bomb();




    // DECK, CARDS, AND HAND
    BombCard bomb;
    ReinforcementCard reinforcement;
    DiplomacyCard diplomacy;
    BlockadeCard blockade;
    AirliftCard airlift;

    // First card in Deck
    deckNode head(&bomb, NULL);

    // Adding rest of cards to deck
    Deck* deck = new Deck(&head);
    deck->addToDeck(&bomb);
    deck->addToDeck(&diplomacy);
    deck->addToDeck(&blockade);
    deck->addToDeck(&airlift);

    //-----------------------------------

    //ORDERS AND ORDERLIST

    Order *deploy = new Bomb();
//    OrdersList* playerOrdersList = new OrdersList();

//    playerOrdersList->addToLast(b1);

    // Creating hand
    Hand* playerHand = new Hand(4, deck);
    Player* p1 = new Player();





}