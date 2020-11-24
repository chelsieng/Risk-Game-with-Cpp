//
// Created by Dominique Cartier on 2020-11-23.
//

#ifndef COMP_345_PLAYERSTRATEGIES_H
#define COMP_345_PLAYERSTRATEGIES_H
#include "Player.h"

//create the abstract class PlayerStrategy
class PlayerStrategy{
public:
    virtual void issueOrder() = 0;
    virtual vector<Territory*>* toAttack(Map* theMap) = 0;
    virtual vector<Territory*>* toDefend(Map* theMap) = 0;

};//end of PlayerStrategy class

class HumanPlayerStrategy : public PlayerStrategy{
    virtual void issueOrder();
    virtual vector<Territory*>* toAttack(Map* theMap);
    virtual vector<Territory*>* toDefend(Map* theMap);
};//end of human player strategy class (will take user input)




#endif //COMP_345_PLAYERSTRATEGIES_H
