//
// Created by Dominique Cartier on 2020-11-23.
//

#ifndef COMP_345_PLAYERSTRATEGIES_H
#define COMP_345_PLAYERSTRATEGIES_H
#include "Player.h"

//create the abstract class PlayerStrategy
class PlayerStrategy{
public:
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player) = 0;
    virtual vector<Territory*> toAttack(Map* theMap, Player *player) = 0;
    virtual vector<Territory*> toDefend(Map* theMap, Player *player) = 0;

};//end of PlayerStrategy class

class HumanPlayerStrategy : public PlayerStrategy{
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player);
    virtual vector<Territory*> toAttack(Map* theMap, Player *player);
    virtual vector<Territory*> toDefend(Map* theMap, Player *player);
};//end of human player strategy class (will take user input)

class AggressivePlayerStrategy : public PlayerStrategy{
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player);
    virtual vector<Territory*> toAttack(Map* theMap, Player *player);
    virtual vector<Territory*> toDefend(Map* theMap, Player *player);
};

class BenevolentPlayerStrategy : public PlayerStrategy{
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player);
    virtual vector<Territory*> toAttack(Map* theMap, Player *player);
    virtual vector<Territory*> toDefend(Map* theMap, Player *player);
};
class NeutralPlayerStrategy : public PlayerStrategy{
    virtual bool issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player);
    virtual vector<Territory*> toAttack(Map* theMap, Player *player);
    virtual vector<Territory*> toDefend(Map* theMap, Player *player);
};




#endif //COMP_345_PLAYERSTRATEGIES_H
