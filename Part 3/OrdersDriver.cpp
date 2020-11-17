#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

int main()
{
    cout << "This is a driver class for the Orders and OrdersList class" << endl;

    // Initialize variables
    ReinforcementCard reinforcement;
    deckNode head(&reinforcement, NULL);
    Deck* theDeck = new Deck(&head);

    typedef deckNode* deckNodePtr;
    Hand *hand1 = new Hand(5, theDeck);
    Hand *hand2 = new Hand(5, theDeck);
    vector<Territory *> *territoriesVector1 = new vector<Territory *>;
    vector<Territory *> *territoriesVector2 = new vector<Territory *>;
    Player *player0;
    Player *player1 = new Player(hand1, new OrdersList(), territoriesVector1);
    Player *player2 = new Player(hand2, new OrdersList(), territoriesVector2);

    // Creating a mini map
    string *territoryName1 = new string("Canada");
    string *territoryName2 = new string("America");
    string *territoryName3 = new string("Mexico");
    string *territoryName4 = new string("China");
    string *territoryName5 = new string("Russia");
    string *territoryName6 = new string("North Korea");

    Territory *canada = new Territory(player1, *territoryName1);
    Territory *america = new Territory(player1, *territoryName2);
    Territory *mexico = new Territory(player1, *territoryName3);
    Territory *china = new Territory(player2, *territoryName4);
    Territory *russia = new Territory(player2, *territoryName5);
    Territory *northKorea = new Territory(player2, *territoryName6);

    Graph<int> *theWorld = new Graph<int>;

    territoriesVector1->push_back(canada);
    territoriesVector1->push_back(america);
    territoriesVector1->push_back(mexico);
    territoriesVector2->push_back(china);
    territoriesVector2->push_back(russia);
    territoriesVector2->push_back(northKorea);

    Continent *northAmerica = new Continent("North America", theWorld, territoriesVector1);
    Continent *asia = new Continent("Asia", theWorld, territoriesVector2);

    theWorld->add_vertex(canada->getId());
    theWorld->add_vertex(america->getId());
    theWorld->add_vertex(mexico->getId());
    theWorld->add_vertex(china->getId());
    theWorld->add_vertex(russia->getId());
    theWorld->add_vertex(northKorea->getId());

    // In North America, America is connected to Canada and Mexico
    theWorld->add_edge(america->getId(), canada->getId());
    theWorld->add_edge(america->getId(), mexico->getId());
    // In Asia, China is connected to Russia and North Korea
    theWorld->add_edge(russia->getId(), china->getId());
    theWorld->add_edge(china->getId(), northKorea->getId());
    // America and Russia are connected
    theWorld->add_edge(america->getId(), russia->getId());

    // Testing each order

    Order *deploy = new Deploy(player1, canada, 5);
    Order *advance = new Advance(player1, canada, america, 8);
    Order *blockade = new Blockade(player2, china);
    Order *bomb = new Bomb(player2, northKorea, america);
    Order *airlift = new Airlift(player1, america, china, 5);
    Order *negotiate = new Negotiate(player1, player2);

    cout << "\nTesting Deploy methods execute(): " << endl;
    deploy->execute();
    cout << *deploy;

    cout << "\nTesting Advance methods execute(): " << endl;
    advance->execute();
    cout << *advance;

    cout << "\nTesting Bomb methods execute(): " << endl;
    bomb->execute();
    cout << *bomb;

    cout << "\nTesting Blockade methods execute(): " << endl;
    blockade->execute();
    cout << *blockade;

    cout << "\nTesting Negotiate methods execute(): " << endl;
    negotiate->execute();
    cout << *negotiate;

    cout << "Testing Airlift methods execute(): " << endl;
    airlift->execute();
    cout << *airlift;

//    // Testing OrdersList
//    cout << "\nAdding all types of Order into an OrdersList" << endl;
//    OrdersList *ordersList = new OrdersList();
//    ordersList->addToLast(deploy);
//    ordersList->addToLast(advance);
//    ordersList->addToLast(bomb);
//    ordersList->addToLast(blockade);
//    ordersList->addToLast(negotiate);
//    ordersList->addToLast(airlift);
//
//    // List after added: [deploy, advance, bomb, blockade, negotiation, airlift]
//    cout << "Expected list: [deploy, advance, bomb, blockade, negotiation, airlift]" << endl;
//    cout << "OrdersList after everything is added:"<< endl
//        << *ordersList << endl;
//
//    // Move Order in index 1 to index 3
//    ordersList->move(1,3);
//    // List after moving: [deploy, bomb, blockade, advance, negotiation, airlift]
//    cout << "Expected list: [deploy, bomb, blockade, advance, negotiation, airlift]" << endl;
//    cout << "OrdersList after Order is moved:" << endl
//        << *ordersList  << endl;
//
//    // Delete Order at index 4
//    ordersList->deleteAt(4);
//    // List after deleting: [deploy, bomb, blockade, advance, airlift]
//    cout << "Expected list: [deploy, bomb, blockade, advance, airlift]" << endl;
//    cout << "OrdersList after Order is deleted:" << endl
//        << *ordersList  << endl;


    // Delete pointers
//    delete player1;         player1 = nullptr;
//    delete player2;         player2 = nullptr;
    delete territoryName1;    territoryName1 = nullptr;
    delete territoryName2;    territoryName2 = nullptr;
    delete territoryName3;    territoryName3 = nullptr;
    delete territoryName4;    territoryName4 = nullptr;
    delete territoryName5;    territoryName5 = nullptr;
    delete territoryName6;    territoryName6 = nullptr;
//    delete territory1;      territory1 = nullptr;
//    delete territory2;      territory2 = nullptr;
//    delete territory3;      territory3 = nullptr;
//    delete territory4;      territory4 = nullptr;
//    delete territory5;      territory5 = nullptr;
//    delete territory6;      territory6 = nullptr;
//    delete deploy;          deploy = nullptr;
//    delete advance;         advance = nullptr;
//    delete bomb;            bomb = nullptr;
//    delete blockade;        blockade = nullptr;
//    delete negotiate;       negotiate = nullptr;
//    delete airlift;         airlift = nullptr;
//    delete ordersList;      ordersList = nullptr;

    cout << "\nEnd of OrdersDriver" << endl;
    return 0;
}
