#include <climits>

#ifndef COMP_345_GAMESTART_H
#define COMP_345_GAMESTART_H

#include "Map.h"

Map *mapGame; // map graph to share among other compilation unit
class GameStart {
public:
    static bool selectMap(int); // Function to load selected map file
};


#endif //COMP_345_GAMESTART_H
