#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

int main()
{
    cout << "\nThis is a driver class for the Order and OrdersList class" << endl;

    // Initialize variables
    Player *player1 = new Player();
    Player *player2 = new Player();

    string *name1 = new string("name1");
    string *name2 = new string("name2");
    Territory *territory1 = new Territory(player1, name1);
    Territory *territory2 = new Territory(player2, name2);

    int numOfArmies = 5;

    // Testing each order subclass
    // Create an object of each type of Order
    Order *deploy = new Deploy(player1, territory1, numOfArmies);
    Order *advance = new Advance(player1, territory1, territory2, numOfArmies);
    Order *bomb = new Bomb(player1,territory1, territory2);
    Order *blockade = new Blockade(player1, territory1);
    Order *negotiate = new Negotiate(player1, player2);
    Order *airlift = new Airlift(player1, territory1, territory2, numOfArmies);

    cout << "\nTesting Deploy methods execute(): " << endl;
    deploy->execute();

    cout << "\nTesting Advance methods execute(): " << endl;
    advance->execute();

    cout << "\nTesting Bomb methods execute(): " << endl;
    bomb->execute();

    cout << "\nTesting Blockade methods execute(): " << endl;
    blockade->execute();

    cout << "\nTesting Negotiate methods execute(): " << endl;
    negotiate->execute();

    cout << "\nTesting Airlift methods execute(): " << endl;
    airlift->execute();

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
    player1 = nullptr;
    player2 = nullptr;
    name1 = nullptr;
    name2 = nullptr;
    territory1 = nullptr;
    territory2 = nullptr;
    deploy = nullptr;
    advance = nullptr;
    bomb = nullptr;
    blockade = nullptr;
    negotiate = nullptr;
    airlift = nullptr;
    ordersList = nullptr;

    cout << "End of OrdersDriver" << endl;
    return 0;
}
