
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
        cout << "==========================================================" << endl;
        cout << "STARTUP PHASE" << endl;
        cout << "==========================================================" << endl;
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



