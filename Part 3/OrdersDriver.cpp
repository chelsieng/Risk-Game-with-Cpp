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

    

    // Testing OrdersList


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