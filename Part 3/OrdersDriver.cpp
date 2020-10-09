#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

int main()
{
    // Testing each order subclass
    Order *deploy = new Deploy();
    Order *advance = new Advance();
    Order *bomb = new Bomb();
    Order *blockade = new Blockade();
    Order *negotiate = new Negotiate();
    Order *airlift = new Airlift();

    deploy->validate();
    deploy->execute();

    advance->validate();
    advance->execute();

    bomb->validate();
    bomb->execute();

    blockade->validate();
    blockade->execute();

    negotiate->validate();
    negotiate->execute();

    airlift->validate();
    airlift->execute();

    // Testing OrdersList
    OrdersList *ordersList = new OrdersList();
    ordersList->add(deploy);
    ordersList->add(advance);
    ordersList->add(bomb);
    ordersList->add(blockade);
    ordersList->add(negotiate);
    ordersList->add(airlift);

    ordersList->move(1,3);

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

    return 0;
}