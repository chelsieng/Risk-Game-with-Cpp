#include <string>
#include "MapLoader.h"

using namespace std;

int main() {
    // Change path name to any files in Map Files directory
    auto *a = new MapLoader("../Part 2/Map Files/test.txt");
    cout << *a->getMap() << endl;
    if (a->getMap()->validate()) {
        cout << "Pass: Map is valid" << endl;
    } else
        cout << "Fail: Invalid Map!" << endl;
}