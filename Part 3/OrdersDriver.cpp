#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

int main()
{
    cout << "\nThis is a driver class for the Orders and OrdersList class" << endl;

    // Initialize variables
    Player *player1 = new Player();
    Player *player2 = new Player();
    Player *player3 = new Player();
    Player *player4 = new Player();
    Player *player5 = new Player();
    Player *player6 = new Player();

    string *name1 = new string("North Korea");
    string *name2 = new string("USA");
    string *name3 = new string("China");
    string *name4 = new string("Canada");
    string *name5 = new string("Russia");
    string *name6 = new string("Britain");

    Territory *territory1 = new Territory(player1, *name1);
    Territory *territory2 = new Territory(player2, *name2);
    Territory *territory3 = new Territory(player3, *name3);
    Territory *territory4 = new Territory(player4, *name4);
    Territory *territory5 = new Territory(player5, *name5);
    Territory *territory6 = new Territory(player6, *name6);

    int numOfArmies = 5;

    // Testing each order subclass
    // Create an object of each type of Order
    Order *deploy = new Deploy(player1, territory1, numOfArmies);
    Order *advance = new Advance(player1, territory1, territory2, numOfArmies);
    Order *blockade = new Blockade(player4, territory4);
    Order *bomb = new Bomb(player3, territory3, territory4);
    Order *airlift = new Airlift(player5, territory5, territory6, numOfArmies);
    Order *negotiate = new Negotiate(player5, player6);

    cout << "\nTesting Deploy methods execute(): " << endl;
    deploy->execute();
    deploy->printEffect(cout);

    cout << "\nTesting Advance methods execute(): " << endl;
    advance->execute();
    advance->printEffect(cout);

    cout << "\nTesting Bomb methods execute(): " << endl;
    bomb->execute();
    bomb->printEffect(cout);

    cout << "\nTesting Blockade methods execute(): " << endl;
    blockade->execute();
    blockade->printEffect(cout);

    cout << "\nTesting Negotiate methods execute(): " << endl;
    negotiate->execute();
    deploy->printEffect(cout);

    cout << "\nTesting Airlift methods execute(): " << endl;
    airlift->execute();
    deploy->printEffect(cout);

    // Testing OrdersList
    cout << "\nAdding all types of Order into an OrdersList" << endl;
    OrdersList *ordersList = new OrdersList();
    ordersList->addToLast(deploy);
    ordersList->addToLast(advance);
    ordersList->addToLast(bomb);
    ordersList->addToLast(blockade);
    ordersList->addToLast(negotiate);
    ordersList->addToLast(airlift);

    // List after added: [deploy, advance, bomb, blockade, negotiation, airlift]
    cout << "Expected list: [deploy, advance, bomb, blockade, negotiation, airlift]" << endl;
    cout << "OrdersList after everything is added:"<< endl
        << *ordersList << endl;

    // Move Order in index 1 to index 3
    ordersList->move(1,3);
    // List after moving: [deploy, bomb, blockade, advance, negotiation, airlift]
    cout << "Expected list: [deploy, bomb, blockade, advance, negotiation, airlift]" << endl;
    cout << "OrdersList after Order is moved:" << endl
        << *ordersList  << endl;

    // Delete Order at index 4
    ordersList->deleteAt(4);
    // List after deleting: [deploy, bomb, blockade, advance, airlift]
    cout << "Expected list: [deploy, bomb, blockade, advance, airlift]" << endl;
    cout << "OrdersList after Order is deleted:" << endl
        << *ordersList  << endl;

    // Delete pointers
//    delete player1;         player1 = nullptr;
//    delete player2;         player2 = nullptr;
//    delete player3;         player3 = nullptr;
//    delete player4;         player4 = nullptr;
//    delete player5;         player5 = nullptr;
//    delete player6;         player6 = nullptr;
    delete name1;           name1 = nullptr;
    delete name2;           name2 = nullptr;
    delete name3;           name3 = nullptr;
    delete name4;           name4 = nullptr;
    delete name5;           name5 = nullptr;
    delete name6;           name6 = nullptr;
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

    cout << "End of OrdersDriver";
    return 0;
}
