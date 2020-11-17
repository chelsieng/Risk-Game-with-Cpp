#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

int main()
{
    cout << "This is a driver class for the Orders and OrdersList class" << endl;
    // Initialize variables
    int oldOwner, newOwner;
    BombCard *startCard = new BombCard();
    deckNode *baseOfDeck = new deckNode(startCard);
    Deck theDeck(baseOfDeck);

    Hand *hand1 ;
    Hand *hand2 ;


    vector<Territory *> *player1Territory = new vector<Territory *>;
    vector<Territory *> *player2Territory = new vector<Territory *>;

    Player *player0;
    Player *player1 = new Player(hand1, new OrdersList(), player1Territory);
    Player *player2 = new Player(hand2, new OrdersList(), player2Territory);
    player1->setReinforcementPool(10);
    player2->setReinforcementPool(10);

    // Creating a mini map
    // Creating territories
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

    // Creating continents
    vector<Territory *> *territoriesVector1 = new vector<Territory *>;
    territoriesVector1->push_back(canada);
    territoriesVector1->push_back(america);
    territoriesVector1->push_back(mexico);

    vector<Territory *> *territoriesVector2 = new vector<Territory *>;
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

    // Testing orders
    Order *deploy;
    Order *advance;
    Order *blockade;
    Order *bomb;
    Order *airlift;
    Order *negotiate;

    // Checking validate() function
    cout << "\nChecking the validity of each order" << endl;
    cout << "Cases where orders are invalid:" << endl;
    cout << "Player deploy to territory owned by different player: deploy->validate() == ";
    deploy = new Deploy(player1, china, 5);
    cout << deploy->validate() << endl;

    cout << "Player advance a territory that is owned by different player: advance->validate() == ";
    advance = new Advance(player2, canada, america, 5);
    cout << advance->validate() << endl;

    cout << "Player blockade a territory that is owned by different player: blockade->validate() == ";
    blockade = new Blockade(player1, china);
    cout << blockade->validate() << endl;

    cout << "Player bomb a territory that they own: bomb->validate() == ";
    bomb = new Bomb(player2, northKorea, china);
    cout << bomb->validate() << endl;

    cout << "Player airlift from a territory that is owned by different player: bomb->validate() == ";
    airlift = new Airlift(player1, northKorea, china, 5);
    cout << bomb->validate() << endl;

    cout << "Player negotiate with themselves: negotiate->validate() == ";
    negotiate = new Negotiate(player1, player1);
    cout << negotiate->validate() << endl;


    cout << "\nExecuting orders correctly:" << endl;
    cout << "Deploy order:" << endl;
    deploy = new Deploy(player1, america, 5);
    deploy->execute();
    cout << *deploy;
    cout << "Player 1 enforcement pool after deploy: " << player1->getReinforcementPool() << endl;
    cout << "Number of armies in America after deploy: " << america->getNumberOfArmies() << endl;

    cout << "\nAdvance to a territory that is owned by player that issued the order:" << endl;
    advance = new Advance(player2, russia, china, 2);
    advance->execute();
    cout << *advance;
    cout << "Number of armies in Russia after advance: " << russia->getNumberOfArmies() << endl;
    cout << "Number of armies in China after advance: " << china->getNumberOfArmies() << endl;

    cout << "\nAdvance to a territory that is owned by a different order:" << endl;
    advance = new Advance(player1, america, russia, 9);
    cout << "Number of armies in Russia before advance: " << russia->getNumberOfArmies() << endl;
    oldOwner = russia->getOwner()->getId();
    advance->execute();
    newOwner = russia->getOwner()->getId();
    cout << *advance;
    cout << "Before, Russia is owned by player " << oldOwner;
    cout << ". After, Russia is owned by player " << newOwner << "." << endl;
    cout << "Number of armies in Russia after advance: " << russia->getNumberOfArmies() << endl;

    cout << "\nAirlift to a territory that is owned by the player that issued the order:" << endl;
    airlift = new Airlift(player1, mexico, canada, 4);
    cout << "Number of armies in Canada before airlift: " << canada->getNumberOfArmies() << endl;
    airlift->execute();
    cout << *airlift;
    cout << "Number of armies in Canada after airlift: " << canada->getNumberOfArmies() << endl;

    cout << "\nAirlift to a territory that is owned by a different player:" << endl;
    airlift = new Airlift(player2, northKorea, america, 5);
    oldOwner = america->getOwner()->getId();
    cout << "Number of armies in America before airlift: " << america->getNumberOfArmies() << endl;
    airlift->execute();
    newOwner = america->getOwner()->getId();
    cout << *airlift;
    cout << "Before, America is owned by player " << oldOwner;
    cout << ". After, America is owned by player " << newOwner << "." << endl;
    cout << "Number of armies in America after airlift: " << america->getNumberOfArmies() << endl;

    cout << "\nBlockade the territory that is owned by the played that isused the order:" << endl;
    blockade = new Blockade(player2, china);
    blockade->execute();
    cout << *blockade;
    cout << "Comparing old owner and the current owner of the blockade territory: ";
    cout << (player2->getId() == china->getOwner()->getId()) << endl;

    cout << "\nBomb a territory that is owned by a different player:" << endl;
    bomb = new Bomb(player2, america, canada);
    cout << "Number of armies in Canada before bomb: " << canada->getNumberOfArmies() << endl;
    bomb->execute();
    cout << *bomb;
    cout << "Number of armies in Canada after bomb: " << canada->getNumberOfArmies() << endl;

    cout << "\nPerform negotiate order:" << endl;
    negotiate = new Negotiate(player1, player2);
    negotiate->execute();
    cout << *negotiate;

    // Delete pointers
//    delete player1;         player1 = nullptr;
//    delete player2;         player2 = nullptr;
    delete territoryName2;  territoryName2 = nullptr;
    delete territoryName3;  territoryName3 = nullptr;
    delete territoryName1;  territoryName1 = nullptr;
    delete territoryName4;  territoryName4 = nullptr;
    delete territoryName5;  territoryName5 = nullptr;
    delete territoryName6;  territoryName6 = nullptr;
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

    cout << "\nEnd of OrdersDriver" << endl;
    return 0;
}
