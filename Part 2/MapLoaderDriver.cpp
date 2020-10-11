//
// Created by Raffi Alan Bezirjian on 2020-10-10.
//

#include "MapLoader.h"
#include <iostream>
#include <string>

// testing the .map files

 int main() {
	MapLoader* mapLoader = new MapLoader();
	Map* map = mapLoader->GetMap("arctic.map");  // we can try other .map files
    std::cout << endl;

//  Testing a failed .map file (invalid.map)
   
// 	*MapLoader* mapLoaderInvalid = new MapLoader();
// 	mapLoaderFail->ReadMap("invalid.map");
// 	std::cout << endl;*/


 }
