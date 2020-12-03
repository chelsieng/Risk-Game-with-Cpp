
#pragma once

#include "Player.h"

//create the abstract class PlayerStrategy
class PlayerStrategy{
public:
    PlayerStrategy();
    PlayerStrategy(PlayerStrategy& strategy);
    virtual ~PlayerStrategy();
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player) = 0;
    virtual vector<Territory*> toAttack(Map* theMap, Player *player) = 0;
    virtual vector<Territory*> toDefend(Map* theMap, Player *player) = 0;

};//end of PlayerStrategy class

class HumanPlayerStrategy : public PlayerStrategy{
public:
    HumanPlayerStrategy();
    HumanPlayerStrategy(HumanPlayerStrategy& strategy);
    ~HumanPlayerStrategy();
    HumanPlayerStrategy& operator = (const HumanPlayerStrategy &strategy);
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player);
    virtual vector<Territory*> toAttack(Map* theMap, Player *player);
    virtual vector<Territory*> toDefend(Map* theMap, Player *player);
};//end of human player strategy class (will take user input)

class AggressivePlayerStrategy : public PlayerStrategy{
public:
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(AggressivePlayerStrategy& strategy);
    ~AggressivePlayerStrategy();
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player);
    virtual vector<Territory*> toAttack(Map* theMap, Player *player);
    virtual vector<Territory*> toDefend(Map* theMap, Player *player);
};

class BenevolentPlayerStrategy : public PlayerStrategy{
public:
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(BenevolentPlayerStrategy& strategy);
    ~BenevolentPlayerStrategy();
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player);
    virtual vector<Territory*> toAttack(Map* theMap, Player *player);
    virtual vector<Territory*> toDefend(Map* theMap, Player *player);
};
class NeutralPlayerStrategy : public PlayerStrategy{
public:
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(NeutralPlayerStrategy& strategy);
    ~NeutralPlayerStrategy();
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player);
    virtual vector<Territory*> toAttack(Map* theMap, Player *player);
    virtual vector<Territory*> toDefend(Map* theMap, Player *player);
};
