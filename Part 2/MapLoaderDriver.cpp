//
// Created by Raffi Alan Bezirjian on 2020-10-16.
//

#include <string>
#include "MapLoader.h"
#include "Map.h"

using namespace std;

int main() {

    /* Checking Valid Maps */

    MapLoader *m = new MapLoader("../swiss.map");
    // MapLoader* m = new MapLoader("../mexico.map");
    // MapLoader* m = new MapLoader("../northern-europe.map");
    // MapLoader* m = new MapLoader("../canada.map");
    // MapLoader* m = new MapLoader("../artic.map");

    /* Check for invalid maps */

    // MapLoader* m = new MapLoader("../abc.map");
    // MapLoader* m = new MapLoader("../invalid.map");
    // MapLoader* m = new MapLoader("../any.map");

    cout << *m << *(m->load());

    return 0;
}
