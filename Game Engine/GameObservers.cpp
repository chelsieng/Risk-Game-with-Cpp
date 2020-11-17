
#include <vector>
#include "GameEngine.h"

using namespace std;

PhaseObserver::PhaseObserver(GameEngine *subject) {
    subject->attach(this);
    this->subject = subject;
}

void PhaseObserver::update() {

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
}

StatisticsObserver::~StatisticsObserver() {
    delete this->subject;
    this->subject = nullptr;
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



