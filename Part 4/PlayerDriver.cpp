#include <vector>
#include "Player.h"
#include "Map.h"

using namespace std;

int main() {

    // Creating DECK, CARDS, AND HAND
    BombCard bombCard;
    ReinforcementCard reinforcementCard;
    DiplomacyCard diplomacyCard;
    BlockadeCard blockadeCard;
    AirliftCard airliftCard;

    BombCard bombCard2;
    ReinforcementCard reinforcementCard2;
    DiplomacyCard diplomacyCard2;
    BlockadeCard blockadeCard2;
    AirliftCard airliftCard2;

    // First card in Deck
    deckNode head(&bombCard, nullptr);

    // Adding rest of cards to deck
    Deck* deck = new Deck(&head);
    deck->addToDeck(&reinforcementCard);
    deck->addToDeck(&diplomacyCard);
    deck->addToDeck(&blockadeCard);
    deck->addToDeck(&airliftCard);

    deck->addToDeck(&bombCard2);
    deck->addToDeck(&reinforcementCard2);
    deck->addToDeck(&diplomacyCard2);
    deck->addToDeck(&blockadeCard2);
    deck->addToDeck(&airliftCard2);

    //----------------------------------------------------------------------

    // CREATING PLAYER 1
    Hand* player1Hand = new Hand(5, deck); // Creating the player's hands
    OrdersList* orderListP1 = new OrdersList(); // Creating the player's list of orders
    vector<Territory*>* territoryListP1 = new vector<Territory*>(); // Creating the player's list of territories

    Player* p1 = new Player(player1Hand, orderListP1, territoryListP1);

    // CREATING PLAYER 2
    Hand* playerHandP2 = new Hand(5, deck); // Creating the player's hands
    OrdersList* orderListP2 = new OrdersList(); // Creating the player's list of orders
    vector<Territory*>* territoryListP2 = new vector<Territory*>(); // Creating the player's list of territories

    Player* p2 = new Player(playerHandP2, orderListP2, territoryListP2);

    //----------------------------------------------------------------------

    // CREATING TERRITORIES FOR PLAYERS

    int counter = 1; // territory names;

    // Player 1
    Territory *p1territory1 = new Territory(p1, new string("Territory #" + to_string(counter)));
    counter++;
    Territory *p1territory2 = new Territory(p1, new string("Territory #" + to_string(counter)));
    counter++;
    Territory *p1territory3 = new Territory(p1, new string("Territory #" + to_string(counter)));
    counter++;
    Territory *p1territory4 = new Territory(p1, new string("Territory #" + to_string(counter)));
    counter++;
    Territory *p1territory5 = new Territory(p1, new string("Territory #" + to_string(counter)));
    counter++;

    territoryListP1->push_back(p1territory1);
    territoryListP1->push_back(p1territory2);
    territoryListP1->push_back(p1territory3);
    territoryListP1->push_back(p1territory4);
    territoryListP1->push_back(p1territory5);

    // Player 2
    Territory *p2territory1 = new Territory(p2, new string("Territory #" + to_string(counter)));
    counter++;
    Territory *p2territory2 = new Territory(p2, new string("Territory #" + to_string(counter)));
    counter++;
    Territory *p2territory3 = new Territory(p2, new string("Territory #" + to_string(counter)));
    counter++;
    Territory *p2territory4 = new Territory(p2, new string("Territory #" + to_string(counter)));
    counter++;
    Territory *p2territory5 = new Territory(p2, new string("Territory #" + to_string(counter)));
    counter++;

    territoryListP2->push_back(p2territory1);
    territoryListP2->push_back(p2territory2);
    territoryListP2->push_back(p2territory3);
    territoryListP2->push_back(p2territory4);
    territoryListP2->push_back(p2territory5);

//----------------------------------------------------------------------

    //CREATING ORDERS AND ORDER LIST
    int numOfArmies = 5;

    // Player 1
    Order *p1deployOrder = new Deploy(p1, p1territory1, numOfArmies);
    Order *p1advanceOrder = new Advance(p1, p1territory1, p1territory2, numOfArmies);
    Order *p1bombOrder = new Bomb(p1, p1territory1, p1territory2);
    Order *p1blockadeOrder = new Blockade(p1, p1territory1);
    Order *p1airliftOrder = new Airlift(p1, p1territory1, p1territory2, numOfArmies);
    Order *p1negotiateOrder = new Negotiate(p1, p2);

    orderListP1->addToLast(p1deployOrder);
    orderListP1->addToLast(p1advanceOrder);
    orderListP1->addToLast(p1bombOrder);
    orderListP1->addToLast(p1blockadeOrder);
    orderListP1->addToLast(p1airliftOrder);
    orderListP1->addToLast(p1negotiateOrder);

    // Player 2
    Order *p2deployOrder = new Deploy(p2, p1territory1, numOfArmies);
    Order *p2advanceOrder = new Advance(p2, p1territory1, p1territory2, numOfArmies);
    Order *p2bombOrder = new Bomb(p2, p1territory1, p1territory2);
    Order *p2blockadeOrder = new Blockade(p2, p1territory1);
    Order *p2airliftOrder = new Airlift(p2, p1territory1, p1territory2, numOfArmies);
    Order *p2negotiateOrder = new Negotiate(p2, p1);

    orderListP2->addToLast(p2deployOrder);
    orderListP2->addToLast(p2advanceOrder);
    orderListP2->addToLast(p2bombOrder);
    orderListP2->addToLast(p2blockadeOrder);
    orderListP2->addToLast(p2airliftOrder);
    orderListP2->addToLast(p2negotiateOrder);

    //ISSUING NEW ORDER FOR PLAYER 1

    //----------------------------------------------------------------------

    // OUTPUTTING INFORMATION

    cout << "PLAYER 1 INFORMATION : " << endl;
    cout << "----------------------" << endl;
    cout << endl;
    cout << *p1;

    //ISSUING NEW ORDER FOR PLAYER 1
    cout << "Player 1 list of order BEFORE issuing new order : " << endl;
    cout << *p1->getOrdersList() << endl;

    p1->issueOrder(new Bomb(p1, p1territory1, p2territory2));
    cout << endl;

    cout << "Player 1 list of order AFTER issuing new order : " << endl;
    cout << *p1->getOrdersList() << endl;

    // PLAYER 1 DEFENDING THEIR TERRITORIES
    // Creating two arbitrary territories
    Territory* terrToDefend1 = new Territory(p1, new string("Territory #" + to_string(counter)));
    counter++;
    Territory* terrToDefend2 = new Territory(p1, new string("Territory #" + to_string(counter)));
    counter++;

    // Adding them to a list
    vector<Territory*>* listToDefend = new vector<Territory*>();
    listToDefend->push_back(terrToDefend1);
    listToDefend->push_back(terrToDefend2);

    cout << "Player " << p1->getId() << " is defending : " << endl;
    for (Territory* t : *p1->toDefend(listToDefend)) {
        cout << *t << endl;
    }

// PLAYER 1 ATTACKING TERRITORIES
    // Creating two arbitrary territories
    Territory* terrToAttack1 = new Territory(new Player(), new string("Territory #" + to_string(counter)));
    counter++;
    Territory* terrToAttack2 = new Territory(new Player(), new string("Territory #" + to_string(counter)));
    counter++;

    // Adding them to a list
    vector<Territory*>* listToAttack = new vector<Territory*>();
    listToAttack->push_back(terrToAttack1);
    listToAttack->push_back(terrToAttack2);

    cout << "Player " << p1->getId() << " is attacking : " << endl;
    for (Territory* t : *p1->toAttack(listToAttack)) {
        cout << *t << endl;
    }

    cout << "=======================================================" << endl;
    cout << endl;
    cout << "PLAYER 2 INFORMATION : " << endl;
    cout << "----------------------" << endl;
    cout << endl;
    cout << *p2;

    //ISSUING NEW ORDER FOR PLAYER 2
    cout << "Player 2 list of order BEFORE issuing new order : " << endl;
    cout << *p2->getOrdersList() << endl;

    p2->issueOrder(new Blockade(p2, p2territory4));
    cout << endl;

    cout << "Player 1 list of order AFTER issuing new order : " << endl;
    cout << *p2->getOrdersList() << endl;


}