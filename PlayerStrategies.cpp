//
// Created by Dominique Cartier on 2020-11-23.
//
#include "PlayerStrategies.h"
#include <algorithm>


vector<Territory *> HumanPlayerStrategy::toAttack(Map *theMap, Player *player) {
    cout << "\n Here are the places that you can attack:" << endl;
    vector<Territory*> attackable = player->AttackAble(theMap);
    vector<Territory *> chosen(0);
    if(attackable.size() > 0) {
        vector<int> options = {}; //so that they don't pick the same territory more than once
//        set<int> *options = new set<int>; //so that they don't pick the same territory more than once
        for (int i = 0; i < attackable.size(); i++) {
            options.push_back(i);
            cout << i << ": " << attackable.at(i)->getTerritoryName() << endl;
        }//end of for (show all attackable territories)
        cout
                << "\nType the corresponding numbers in the above list of the territories you would like to attack, in order of priority."
                << "\nENTER A NEGATIVE NUMBER IF YOU ARE FINISHED. Input answers one at a time." << endl;
        bool done = false;
        while (done == false) {
            int ans = -1;
            cout << "What territory will you attack?" << endl;
            cin >> ans;
            if (ans < 0) { done = true; }
            else if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                continue; // Keep prompting user
            }
            else if (find(options.begin(), options.end(), ans) == options.end()) {
                cout << "That is not an option!"
                     << "\nRemember that you cannot chose the same territory more than once, "
                     << "and must chose from the list provided" << endl;
            } else {
                chosen.push_back(attackable.at(ans));
                int counter = 0;
                for (auto el : options) {
                    if (el == ans) {
                        options.erase(options.begin() + counter);
                    }
                    counter++;
                }//end of for
                cout << "Added " << attackable.at(ans)->getTerritoryName() << " to your list." << endl;
            }//end of else (valid option chosen)
        }//end of while
        cout << "Great! You have chosen which territories you would like to attack" << endl;
    }//end of if (player actually had options for attacking).
    else{
        cout << "Oh! There aren't any." << endl;
    }
    // Returning territories to attack
    return chosen;
}///End of human player version of toAttack

vector<Territory *> HumanPlayerStrategy::toDefend(Map *theMap, Player *player) {
    vector<Territory*> listToDefend(0);
    cout << "Here are the territories you can defend:" << endl;
    vector<int> options = {}; //so that they don't pick the same territory more than once
    for(int i = 0; i < player->getPlayerTerritories()->size(); i++){
        options.push_back(i);
        cout << i << ": " << player->getPlayerTerritories()->at(i)->getTerritoryName() << endl;
    }//end of for (print all options)
    cout  << "\nType the corresponding numbers in the above list of the territories you would like to defend, in order of priority."
          << "\nENTER A NEGATIVE NUMBER IF YOU ARE FINISHED. Input answers one at a time." << endl;
    bool done = false;
    while (done == false) {
        int ans = -1;
        cout << "What territory will you defend?" << endl;
        cin >> ans;
        if (ans < 0) { done = true; }
        else if (cin.fail()) {
            cin.clear(); // clears error flag
            cin.ignore(); // skips to the next line
            continue; // Keep prompting user
        }
        else if (find(options.begin(), options.end(), ans) == options.end()) {
            cout << "That is not an option!"
                 << "\nRemember that you cannot chose the same territory more than once, "
                 << "and must chose from the list provided" << endl;
        } else {
            listToDefend.push_back(player->getPlayerTerritories()->at(ans));
            int counter = 0;
            for (auto el : options) {
                if (el == ans) {
                    options.erase(options.begin() + counter);
                }
                counter++;
            }//end of for
            cout << "Added " << player->getPlayerTerritories()->at(ans)->getTerritoryName() << " to your list." << endl;
        }//end of else (valid option chosen)
    }//end of while

    // Returning territories to defend
    return listToDefend;
    ///End of human player version of toDefend
}

bool HumanPlayerStrategy::issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player* player) {
    if (choice == 0) {///DEPLOY:
        ///Chose what to defend:
        vector<Territory *> defendList = player->toDefend(theMap, player);
        while (defendList.size() == 0) {
            cout << "You must chose territories to deploy your troops to!" << endl;
            defendList = player->toDefend(theMap, player);
        }//end of while
        if (defendList.size() > 0) {
            cout << "\nGreat! You chose to defend these territories:" << endl;
            for (int i = 0; i < defendList.size(); i++) {
                cout << defendList.at(i)->getTerritoryName() << endl;
            }//end of for (print the list)

            ///Issue deploy orders:
            cout << "\nNow it is time to deploy armies on the territories you are defending."
                 << "\nYou will get the chance to defend by advancing after this step." << endl;
            int usableArmies = player->getReinforcementPool();
            cout << "You have " << usableArmies << " to deploy." << endl;
            bool deployedAll = false;
            while (deployedAll == false) {
                for (int j = 0; j < defendList.size(); j++) {
                    if (usableArmies == 0) { deployedAll = true; }
                    else {
                        cout << "\nHow many armies will you deploy to " << defendList.at(j)->getTerritoryName()
                             << "?" << endl;
                        int amount;
                        bool valid = false;
                        while (valid == false) {
                            cin >> amount;
                            if (cin.fail()) {
                                cin.clear(); // clears error flag
                                cin.ignore(); // skips to the next line
                                valid = false; // Keep prompting user
                            }
                            if (amount <= usableArmies && amount >= 0) {
                                valid = true;
                                if (amount > 0) {
                                    defendList.at(j)->addToMockArmies(amount);
                                    player->issueOrder(new Deploy(player, defendList.at(j), amount));
                                    usableArmies = usableArmies - amount;
                                    cout << amount << " armies will be deployed to"
                                         << defendList.at(j)->getTerritoryName()
                                         << "." << endl;
                                }//end of if (is actually deploying armies
                            }//end of if (valid amount entered)
                            else { cout << "Invalid amount! Please try again." << endl; }
                        }//end of while (choose valid amount of armies to deploy)
                    }//end of else (still has reinforcement in pool)
                    if (usableArmies > 0) {
                        cout << "\nYou still have " << usableArmies << " armies left to deploy!" << endl;
                    }
                }//end of for (go through all territories)
            }
        }
        return true;
    }///Finished deploying
    else {
        bool okay = false;
        int ans;
        while (okay == false) {
            cout << "Would you like to issue another order? Type 1 for yes, and any other number for no." << endl;
            cin >> ans;

            if (cin.fail()) {
                cin.clear(); // clears error flag
                cin.ignore(); // skips to the next line
                continue;
            } else {
                okay = true;
            }
        }//end of while
        if (ans == 1) {
            bool valid = false;
            int response;
            while (valid == false) {
                cout << "Here are your options. Type in the number corresponding to your choice:" << endl;
                cout << "1. Advance armies to defend." << endl;
                cout << "2. Advance armies to attack." << endl;
                cout << "3. Play a card from your hand." << endl;
                cin >> response;
                if (cin.fail()) {
                    cin.clear(); // clears error flag
                    cin.ignore(); // skips to the next line
                    valid = false; // Keep prompting user
                    cout << "Please try again" << endl;
                } else if (response == 1 || response == 2 || (response == 3 && player->getHand()->getSize() > 0)) {
                    valid = true;
                    cout << "Got it!" << endl;
                } else if (response == 3 && player->getHand()->getSize() < 1) {
                    cout << "You don't have any cards in hand! Try something else." << endl;
                } else { cout << "Invalid choice! Please try again." << endl; }
            }//end of while (get valid choice)

        if (response == 1) {
            ///Defend by advancing
            ///Chose what to defend:
            vector<Territory *> defendList = player->toDefend(theMap, player);
            if (defendList.size() > 0) {
                cout << "\nYou chose to defend these territories:" << endl;
                for (int i = 0; i < defendList.size(); i++) {
                    cout << defendList.at(i)->getTerritoryName() << endl;
                }//end of for (print the list)

                ///Issue Advance defend orders:
                cout
                        << "\nNow you can defend from advancing armies! " << endl;
                cout << "For each territory selected earlier, you must chose if you would like to advance troops."
                     << endl;
                for (int i = 0; i < defendList.size(); i++) {
                    cout << "\nWill you advance troops to " << defendList.at(i)->getTerritoryName()
                         << "? Type 1 if yes, and any other number if no." << endl;
                    int advanceResponse;
                    cin >> advanceResponse;
                    if (cin.fail()) {
                        cin.clear(); // clears error flag
                        cin.ignore(); // skips to the next line
                        --i;
                        continue; // Keep prompting user
                    }
                    if (advanceResponse == 1) {
                        vector<Territory *> *theNeighbours = theMap->getNeighbours(defendList.at(i));
                        vector<Territory *> neighboursYouOwn(0);
                        for (int j = 0; j < theNeighbours->size(); j++) {
                            if (theNeighbours->at(j)->isOccupiedBy(player)) {
                                neighboursYouOwn.push_back(theNeighbours->at(j));
                            }//end of if (valid option)
                        }//end of for (get neighbours of territory to be defended that defending player owns)
                        if (neighboursYouOwn.size() > 0) {
                            cout << "\nYou chose to defend " << defendList.at(i)->getTerritoryName() << "." << endl;
                            cout << "Here are your neighbouring territories that you can advance armies from." << endl;
                            for (int k = 0; k < neighboursYouOwn.size(); k++) {
                                cout << k << ": " << neighboursYouOwn.at(k)->getTerritoryName() << endl;
                            }//end of for (show neighbors)
                            cout
                                    << "\nPlease type in the number in the above list beside the territory that you would like to move armies from."
                                    << endl;
                            int ans;
                            bool chosen = false;
                            Territory *chosenOne;
                            while (chosen == false) {
                                cin >> ans;
                                if (cin.fail()) {
                                    cin.clear(); // clears error flag
                                    cin.ignore(); // skips to the next line
                                    chosen = false; // Keep prompting user
                                } else if (ans < 0 || ans >= neighboursYouOwn.size()) {
                                    cout << "Invalid number! Please try again." << endl;
                                }//end of if (invalid choice)
                                else {
                                    chosen = true;
                                    chosenOne = neighboursYouOwn.at(ans);
                                    cout << "\nGreat! You will advance from "
                                         << neighboursYouOwn.at(ans)->getTerritoryName()
                                         << endl;
                                }
                            }//end of while (chose proper number)
                            int availableArmies = chosenOne->getMockArmies();
                            cout << chosenOne->getTerritoryName() << " has " << availableArmies
                                 << " armies available to advance."
                                 << endl;
                            cout << "Please chose how many you would like to advance." << endl;
                            int number;
                            bool done = false;
                            while (done == false) {
                                cin >> number;
                                if (cin.fail()) {
                                    cin.clear(); // clears error flag
                                    cin.ignore(); // skips to the next line
                                    done = false; // Keep prompting user
                                } else if (number < 0 || number > availableArmies) {
                                    cout << "That is not a valid amount! Please try again." << endl;
                                }//end of if (invalid input)
                                else {
                                    done = true;
                                    cout << "Perfect!" << endl;
                                }
                            }//end of while (chose valid number of territories to move)
                            chosenOne->removeMockArmies(number);
                            player->issueOrder(new Advance(player, chosenOne, defendList.at(i), number));
                            cout << "\nAdvance order issued!" << endl;
                        }//end of if (player actually has neighbours from which to advance)
                        else {
                            cout << "You don't have any territories neighbouring this one! Cannot issue advance order."
                                 << endl;
                        }
                    }//end of if (player chose to advance armies)
                }//end of for (go through all territories in the defend list)
                cout << "\nfinished making defensive advance orders!" << endl;
            }//end of if (list of things to defend is not empty)
            else {
                cout << "\nYou chose not to defend any territories!" << endl;
            }
        }//finished defending through advance
        if (response == 2) {///attack by advancing
            ///Chose what to attack by advancing:
            vector<Territory *> whatWasChosen = player->toAttack(theMap, player);
            cout << "\nYou chose to attack these territories:" << endl;
            if (whatWasChosen.size() > 0) {
                for (int i = 0; i < whatWasChosen.size(); i++) {
                    cout << whatWasChosen.at(i)->getTerritoryName() << endl;
                }
            }//end of if (not empty)


            ///Issue Advance attack orders:
            if (whatWasChosen.size() > 0) {
                cout
                        << "\nTime to attack! For each territory selected, you must chose which territory you will attack from."
                        << endl;
                for (int i = 0; i < whatWasChosen.size(); i++) {
                    vector<Territory *> *theNeighbours = theMap->getNeighbours(whatWasChosen.at(i));
                    vector<Territory *> *neighboursYouOwn = new vector<Territory *>;
                    for (int j = 0; j < theNeighbours->size(); j++) {
                        if (theNeighbours->at(j)->isOccupiedBy(player)) {
                            neighboursYouOwn->push_back(theNeighbours->at(j));
                        }//end of if (valid option)
                    }//end of for (get neighbours of territory to be attacked that attacking player owns)
                    cout << "\nYou chose to attack " << whatWasChosen.at(i)->getTerritoryName() << "." << endl;
                    cout << "\nHere are your neighbouring territories that you can advance from." << endl;
                    for (int k = 0; k < neighboursYouOwn->size(); k++) {
                        cout << k << ": " << neighboursYouOwn->at(k)->getTerritoryName() << endl;
                    }//end of for (show neighbors)
                    cout
                            << "\nPlease type in the number in the above list beside the territory that you would like to attack from."
                            << endl;
                    int ans;
                    bool chosen = false;
                    Territory *chosenOne;
                    while (chosen == false) {
                        cin >> ans;
                        if (cin.fail()) {
                            cin.clear(); // clears error flag
                            cin.ignore(); // skips to the next line
                            chosen = false; // Keep prompting user
                        } else if (ans < 0 || ans >= neighboursYouOwn->size()) {
                            cout << "Invalid number! Please try again." << endl;
                        }//end of if (invalid choice)
                        else {
                            chosen = true;
                            chosenOne = neighboursYouOwn->at(ans);
                            cout << "Great! You will advance from " << neighboursYouOwn->at(ans)->getTerritoryName()
                                 << endl;
                        }
                    }//end of while (chose proper number)
                    int availableArmies = chosenOne->getMockArmies();
                    cout << chosenOne->getTerritoryName() << " has " << availableArmies
                         << " armies available to advance."
                         << endl;
                    cout << "\nPlease chose how many you would like to advance." << endl;
                    int number;
                    bool done = false;
                    while (done == false) {
                        cin >> number;
                        if (cin.fail()) {
                            cin.clear(); // clears error flag
                            cin.ignore(); // skips to the next line
                            done = false; // Keep prompting user
                        } else if (number < 0 || number > availableArmies) {
                            cout << "That is not a valid amount! Please try again." << endl;
                        }//end of if (invalid input)
                        else {
                            done = true;
                            cout << "Perfect!" << endl;
                        }
                    }//end of while (chose valid number of territories to move)
                    chosenOne->removeMockArmies(number);
                    player->issueOrder(new Advance(player, chosenOne, whatWasChosen.at(i), number));
                    cout << "\nAdvance order issued!" << endl;
                }//end of for (go through all territories in the attack list)
            }//end of if (player had territories to attack)
            //ALL ATTACK ADVANCE ORDERS HAVE BEEN ISSUED
        }//end of attack by advancing
        ////Play cards in hand:
        if (response == 3) {
            cout << "\nYou've chosen to play a card from you hand! Here are the cards currently in your hand:" << endl;
            for (int i = 0; i < player->getHand()->getSize(); i++) {
                cout << i << ": " << player->getHand()->getCardatIndex(i) << endl;
            }//end of for (show cards)
            cout << "\nPlease type in the number in the list above of the card you would like to play." << endl;
            int ans;
            bool valid = false;
            while (valid == false) {
                cin >> ans;
                cout << endl;
                if (cin.fail()) {
                    cin.clear(); // clears error flag
                    cin.ignore(); // skips to the next line
                    valid = false; // Keep prompting user
                } else if (ans < player->getHand()->getSize() && ans >= 0) { valid = true; }
                else {
                    cout << "\nInvalid answer! Please try again." << endl;
                }
            }//end of while (get valid answer)
            player->getHand()->playCardAtIndex(ans, player, *thePlayers, theMap);
        }//end of playing card in hand
        return true; //player issued an order
    }//end of if (player chose to issue a non-deploy order)
        else{
        cout << "Okay! No order will be issued." << endl;
        return false; //player didn't issue an order
        }
    }//end of else (not deploy phase- choice must be made)

    ///End of human player version of issueOrder
}
////////////////////////////////////////////

vector<Territory *> AggressivePlayerStrategy::toDefend(Map *theMap, Player *player) {
    //this version should get the player's strongest country
    Territory* toReturn;
    toReturn = player->getPlayerTerritories()->at(0);
    for(int i = 0; i < player->getPlayerTerritories()->size(); i++){
        if(player->getPlayerTerritories()->at(i)->getNumberOfArmies() > toReturn->getNumberOfArmies()){
            toReturn = player->getPlayerTerritories()->at(i);
        }
    }//end of for
    vector<Territory*> vectorWithStrongest(0); //only using a vector to keep return type consistent across versions
    vectorWithStrongest.push_back(toReturn);
    return vectorWithStrongest;
    ///End of Aggressive version of toDefend
}

bool AggressivePlayerStrategy::issueOrder(Map *theMap, vector<Player *> *thePlayers, int choice, Player *player) {
    if(choice == 0){
        Territory* deployHere = player->toDefend(theMap, player).at(0);
        int amount = player->getReinforcementPool();
        deployHere->addToMockArmies(amount);
        player->issueOrder(new Deploy(player, deployHere, amount));
        cout << "\n" << amount << " armies will be deployed to"
             << deployHere->getTerritoryName()
             << "." << endl;
        return true;
    }//end of if (deploy phase)
    else if(choice == 1){
        //Aggressive player will attack until they can't anymore
        vector<Territory*> couldAttack = player->toAttack(theMap, player);
        bool attacked = false;
        for (int i = 0; i < couldAttack.size(); i++) {
            vector<Territory *> *theNeighbours = theMap->getNeighbours(couldAttack.at(i));
            vector<Territory *> neighboursYouOwn;
            for (int j = 0; j < theNeighbours->size(); j++) {
                if (theNeighbours->at(j)->isOccupiedBy(player)) {
                    neighboursYouOwn.push_back(theNeighbours->at(j));
                }//end of if (valid option)
            }//end of for (get neighbours of territory to be attacked that attacking player owns)
            Territory *chosenOne = nullptr; //attack from here
            for (int k = 0; k < neighboursYouOwn.size(); k++) {
                if(neighboursYouOwn.at(k)->getMockArmies() > 0){
                    chosenOne = neighboursYouOwn.at(k);
                }
            }//end of for (get neighbour we are attacking from)
            if(chosenOne != nullptr) {
                int number = chosenOne->getMockArmies(); //they will attack with all the (mock) armies on this territory
                chosenOne->removeMockArmies(chosenOne->getMockArmies());
                cout << "\nP" << player->getId() << " is advancing " << number << " armies from " << chosenOne->getTerritoryName()
                    << " into " << couldAttack.at(i)->getTerritoryName() << " to attack." << endl;
                player->issueOrder(new Advance(player, chosenOne, couldAttack.at(i), number));
                cout << "\nAdvance order issued!" << endl;
                attacked = true;
            }//end of if (player had a neighbour that actually had armies to attack from)
        }//end of for (go through all territories in the attack list)
        if(attacked == false){
            cout << "\nP" << player->getId() << " could not attack anymore! No new advance orders will be placed." << endl;
        }
        return attacked;
    }//end of else if (not deploy phase- some other action must be taken)
    ///End of Aggressive version of issue order
    cout << "\nNo order was issued!" << endl;
    return false;
}

vector<Territory *> AggressivePlayerStrategy::toAttack(Map *theMap, Player *player) {
    vector<Territory*> attackable = player->AttackAble(theMap);
    return attackable;

    ///End of Aggressive version of toAttack
}
