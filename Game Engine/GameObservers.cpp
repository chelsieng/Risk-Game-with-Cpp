
#include <vector>
#include "GameEngine.h"

using namespace std;

PhaseObserver::PhaseObserver(GameEngine *subject) {
    subject->attach(this);
    this->subject = subject;
}

void PhaseObserver::update() {
    showInfo();
}

void PhaseObserver::showInfo() {
    string currentPhase = subject->getPhase();
//    int currentPlayer = GameEngine::playerTurn;

    if (currentPhase == "Map Selection") {
        // Displaying welcome message
        cout << "* ------------------------------ * " << endl;
        cout << "| Welcome to Warzone's Risk Game |" << endl;
        cout << "* ------------------------------ *" << endl;
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>MAP SELECTION PHASE<<<<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }
    if (currentPhase == "Player and Deck Creation") {
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>PLAYER AND DECK CREATION PHASE<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }
    if (currentPhase == "Startup Phase") {
        cout << endl;
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>>STARTUP PHASE<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
    }
    if (currentPhase == "Reinforcement Phase") {
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>REINFORCEMENT PHASE<<<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }
    if (currentPhase == "Order Issuing Phase") {
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>Player " << subject->getPlayerTurn() << ": ORDER ISSUING PHASE<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }
    if (currentPhase == "Order Execution Phase") {
        cout << endl;
        cout << "==========================================================" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>ORDER EXECUTION PHASE<<<<<<<<<<<<<<<<" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }
    if (currentPhase == "Game Over") {
        cout << endl;
        cout << endl;
        cout << "==========================================================" << endl;
        cout << "\t \t \t \t \t \t Game Over" << endl;
        cout << "Congratulations Player " << subject->getPlayerTurn() << ", you've won the game!" << endl;
        cout << "==========================================================" << endl;
        cout << endl;
    }

}

PhaseObserver::~PhaseObserver() {
    delete this->subject;
    this->subject = nullptr;
}

StatisticsObserver::StatisticsObserver(GameEngine *subject) {
    subject->attach(this);
    this->subject = subject;
}

void StatisticsObserver::update() {
    showInfo();
}

void StatisticsObserver::showInfo() {

}

StatisticsObserver::~StatisticsObserver() {
    delete this->subject;
    this->subject = nullptr;
}
Subject::Subject() {

}

Subject::~Subject() {

}

void Subject::attach(Observer *o) {
    this->observers.push_back(o);
}

void Subject::detach(Observer *o) {
    int counter = 0;
    for (int i = 0; i < this->observers.size(); i++) {
        if (o == this->observers[i]){
            break;
        }
        counter++;
    }
    this->observers.erase(this->observers.begin() + counter);
}

void Subject::notify() {
    for (Observer* o : this->observers) {
        o->update();
    }
}



