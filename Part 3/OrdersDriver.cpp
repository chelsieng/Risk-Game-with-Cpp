#include <iostream>
#include <vector>

#include "Orders.h"

using namespace std;
using std::vector;

int main()
{
    cout << "This is a driver class to show whether validate() and execute() of each order work correctly." << endl;
    // Initialize variables
    int oldOwner, newOwner;         // To store ID of players for comparison
    deckNode *baseOfDeck = new deckNode(new BombCard());
    Deck *theDeck = new Deck(baseOfDeck);
    theDeck->addToDeck(new AirliftCard());
    theDeck->addToDeck(new BlockadeCard());
    theDeck->addToDeck(new DiplomacyCard);
    theDeck->addToDeck(new ReinforcementCard());

    vector<Territory *> *player1Territory = new vector<Territory *>;
    vector<Territory *> *player2Territory = new vector<Territory *>;

    Player *player1 = new Player(new Hand(0, theDeck), new OrdersList(), player1Territory);
    Player *player2 = new Player(new Hand(0, theDeck), new OrdersList(), player2Territory);
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

    // Assigning territories to players
    player1Territory->push_back(canada);
    player1Territory->push_back(america);
    player1Territory->push_back(mexico);
    player2Territory->push_back(china);
    player2Territory->push_back(russia);
    player2Territory->push_back(northKorea);

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
    cout << "Player deploy to territory owned by different player:" << endl;
    deploy = new Deploy(player1, china, 5);
    deploy->execute();

    cout << "\nPlayer advance a territory that is owned by different player:" << endl;
    advance = new Advance(player2, canada, america, 5);
    advance->execute();

    cout << "\nPlayer blockade a territory that is owned by different player:" << endl;
    blockade = new Blockade(player1, china);
    blockade->execute();

    cout << "\nPlayer bomb a territory that they own:" << endl;
    bomb = new Bomb(player2, northKorea, china);
    bomb->execute();

    cout << "\nPlayer airlift from a territory that is owned by different player:" << endl;
    airlift = new Airlift(player1, northKorea, china, 5);
    bomb->execute();

    cout << "\nPlayer negotiate with themselves:" << endl;
    negotiate = new Negotiate(player1, player1);
    negotiate->execute();


    cout << "\n\nExecuting orders correctly:" << endl;
    cout << "Deploy to a territory that the player owns:" << endl;
    cout << "Player 1 enforcement pool before deploy: " << player1->getReinforcementPool() << endl;
    cout << "Number of armies in America before deploy: " << america->getNumberOfArmies() << endl;
    deploy = new Deploy(player1, america, 7);
    deploy->execute();
    cout << "Player 1 enforcement pool after deploy: " << player1->getReinforcementPool() << endl;
    cout << "Number of armies in America after deploy: " << america->getNumberOfArmies() << endl;

    cout << "\nAdvance to a territory that is owned by player that issued the order:" << endl;
    cout << "Number of armies in Russia before advance: " << russia->getNumberOfArmies() << endl;
    cout << "Number of armies in China before advance: " << china->getNumberOfArmies() << endl;
    advance = new Advance(player2, russia, china, 2);
    advance->execute();
    cout << "Number of armies in Russia after advance: " << russia->getNumberOfArmies() << endl;
    cout << "Number of armies in China after advance: " << china->getNumberOfArmies() << endl;

    cout << "\nAdvance to a territory that is owned by a different player:" << endl;
    advance = new Advance(player1, america, russia, 9);
    cout << "Number of armies in America before advance: " << america->getNumberOfArmies() << endl;
    cout << "Number of armies in Russia before advance: " << russia->getNumberOfArmies() << endl;
    oldOwner = russia->getOwner()->getId();
    advance->execute();
    newOwner = russia->getOwner()->getId();
    cout << "Before, Russia is owned by player " << oldOwner;
    cout << ". After, Russia is owned by player " << newOwner << "." << endl;
    cout << "Number of armies in America after advance: " << america->getNumberOfArmies() << endl;
    cout << "Number of armies in Russia after advance: " << russia->getNumberOfArmies() << endl;

    cout << "\nAirlift to a territory that is owned by the player that issued the order:" << endl;
    airlift = new Airlift(player1, mexico, canada, 4);
    cout << "Number of armies in Mexico before airlift: " << mexico->getNumberOfArmies() << endl;
    cout << "Number of armies in Canada before airlift: " << canada->getNumberOfArmies() << endl;
    airlift->execute();
    cout << "Number of armies in Mexico after airlift: " << mexico->getNumberOfArmies() << endl;
    cout << "Number of armies in Canada after airlift: " << canada->getNumberOfArmies() << endl;

    cout << "\nAirlift to a territory that is owned by a different player:" << endl;
    airlift = new Airlift(player2, northKorea, america, 5);
    oldOwner = america->getOwner()->getId();
    cout << "Number of armies in North Korea before airlift: " << northKorea->getNumberOfArmies() << endl;
    cout << "Number of armies in America before airlift: " << america->getNumberOfArmies() << endl;
    airlift->execute();
    newOwner = america->getOwner()->getId();
    cout << "Before, America is owned by player " << oldOwner;
    cout << ". After, America is owned by player " << newOwner << "." << endl;
    cout << "Number of armies in North Korea after airlift: " << northKorea->getNumberOfArmies() << endl;
    cout << "Number of armies in America after airlift: " << america->getNumberOfArmies() << endl;

    cout << "\nBlockade the territory that is owned by the played that issued the order:" << endl;
    cout << "Number of armies in China before airlift: " << china->getNumberOfArmies() << endl;
    blockade = new Blockade(player2, china);
    blockade->execute();
    cout << "Comparing old owner and the current owner of the blockade territory: ";
    cout << (player2->getId() == china->getOwner()->getId()) << endl;

    cout << "\nBomb a territory that is owned by a different player:" << endl;
    bomb = new Bomb(player2, america, canada);
    cout << "Number of armies in Canada before bomb: " << canada->getNumberOfArmies() << endl;
    bomb->execute();
    cout << "Number of armies in Canada after bomb: " << canada->getNumberOfArmies() << endl;

    cout << "\nPerform negotiate order:" << endl;
    negotiate = new Negotiate(player1, player2);
    cout << "Players who negotiated with player 1 before the negotiate order:" << endl;
    if(player1->getDiplomacyPlayers().empty())
        cout << "Player 1 has not negotiate with anyone yet." << endl;
    for(Player* p : player1->getDiplomacyPlayers())
        cout << "Player " << p->getId() << endl;
    cout << "Players who negotiated with player 2 before the negotiate order:" << endl;
    if(player1->getDiplomacyPlayers().empty())
        cout << "Player 2 has not negotiate with anyone yet." << endl;
    for(Player* p : player2->getDiplomacyPlayers())
        cout << "Player " << p->getId() << endl;

    negotiate->execute();

    cout << "Players who negotiated with player 1 after the negotiate order:" << endl;
    if(player1->getDiplomacyPlayers().empty())
        cout << "Player 1 has not negotiate with anyone yet." << endl;
    for(Player* p : player1->getDiplomacyPlayers())
        cout << "Player " << p->getId() << endl;
    cout << "Players who negotiated with player 2 after the negotiate order:" << endl;
    if(player1->getDiplomacyPlayers().empty())
        cout << "Player 2 has not negotiate with anyone yet." << endl;
    for(Player* p : player2->getDiplomacyPlayers())
        cout << "Player " << p->getId() << endl;

    // Delete pointers
    delete theDeck;             theDeck = nullptr;
    delete player1Territory;    player1Territory = nullptr;
    delete player2Territory;    player2Territory = nullptr;
//    delete hand1;               hand1 = nullptr;
//    delete hand2;               hand2 = nullptr;
//    delete player1;             player1 = nullptr;
//    delete player2;             player2 = nullptr;
    delete territoryName2;      territoryName2 = nullptr;
    delete territoryName3;      territoryName3 = nullptr;
    delete territoryName1;      territoryName1 = nullptr;
    delete territoryName4;      territoryName4 = nullptr;
    delete territoryName5;      territoryName5 = nullptr;
    delete territoryName6;      territoryName6 = nullptr;
//    delete canada;              canada = nullptr;
//    delete america;             america = nullptr;
//    delete mexico;              mexico = nullptr;
//    delete china;               china = nullptr;
//    delete russia;              russia = nullptr;
//    delete northKorea;          northKorea = nullptr;
    delete territoriesVector1;  territoriesVector1 = nullptr;
    delete territoriesVector2;  territoriesVector2 = nullptr;
    delete theWorld;            theWorld = nullptr;
//    delete northAmerica;        northAmerica = nullptr;
//    delete asia;                asia = nullptr;
//    delete deploy;              deploy = nullptr;
//    delete advance;             advance = nullptr;
//    delete bomb;                bomb = nullptr;
//    delete blockade;            blockade = nullptr;
//    delete negotiate;           negotiate = nullptr;
//    delete airlift;             airlift = nullptr;

    cout << "\nEnd of OrdersDriver" << endl;
    return 0;
}
