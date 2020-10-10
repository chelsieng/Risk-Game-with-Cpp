#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

int main()
{
    cout<<"\nThis is a driver class for the Order and OrdersList class\n"<<endl;

    Player *player1 = new Player();
    Player *player2 = new Player();
    Territory territory1 = new Territory();
    Territory territory2 = new Territory();
    int numOfArmies = 5;

    // Testing each order subclass
    Order *deploy = new Deploy(player1, territory1, numOfArmies);
    Order *advance = new Advance(player1, territory1, territory2, numOfArmies);
    Order *bomb = new Bomb(player1,territory1, territory2);
    Order *blockade = new Blockade();
    Order *negotiate = new Negotiate();
    Order *airlift = new Airlift();

    cout<<"\nTesting Deploy methods"<<endl
        <<"validate(): "<<endl;
    deploy->validate();
    cout<<"execute(): "<<endl;
    deploy->execute();

    cout<<"\nTesting Advance methods"<<endl
        <<"validate(): "<<endl;
    advance->validate();
    cout<<"execute(): "<<endl;
    advance->execute();

    cout<<"\nTesting Bomb methods"<<endl
        <<"validate(): "<<endl;
    bomb->validate();
    cout<<"execute(): "<<endl;
    bomb->execute();

    cout<<"\nTesting Blockade methods"<<endl
        <<"validate(): "<<endl;
    blockade->validate();
    cout<<"execute(): "<<endl;
    blockade->execute();

    cout<<"\nTesting Negotiate methods"<<endl
        <<"validate(): "<<endl;
    negotiate->validate();
    cout<<"execute(): "<<endl;
    negotiate->execute();

    cout<<"\nTesting Airlift methods"<<endl
        <<"validate(): "<<endl;
    airlift->validate();
    cout<<"execute(): "<<endl;
    airlift->execute();

    // Testing OrdersList
    OrdersList *ordersList = new OrdersList();
    ordersList->addToLast(deploy);
    ordersList->addToLast(advance);
    ordersList->addToLast(bomb);
    ordersList->addToLast(blockade);
    ordersList->addToLast(negotiate);
    ordersList->addToLast(airlift);
    // List after added: [deploy, advance, bomb, blockade, negotiation, airlift]

    // Move Order in index 1 to index 3
    ordersList->move(1,3);
    // List after moving: [deploy, bomb, blockade, advance, negotiation, airlift]

    // Delete Order at index 4
    ordersList->deleteAt(4);
    // List after deleting: [deploy, bomb, blockade, advance, airlift]

    // Delete pointers
    delete deploy;
    deploy = nullptr;
    delete advance;
    advance = nullptr;
    delete bomb;
    bomb = nullptr;
    delete blockade;
    blockade = nullptr;
    delete negotiate;
    negotiate = nullptr;
    delete airlift;
    airlift = nullptr;

    cout<<"\nEnd of OrdersDriver\n"<<endl;
    return 0;
}