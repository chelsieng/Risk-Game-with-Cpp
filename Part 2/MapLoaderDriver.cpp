//
//  MapLoaderDriver.cpp
//  A1
//
//  Created by Raffi Alan Bezirjian on 2020-09-27.
//  Copyright © 2020 Raffi Alan Bezirjian. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "MapLoader.h"

int main() {
    MapLoader* ML = new MapLoader();
    std::string input;
    std::cout <<"Please input name of the map file \n";
    std::cin >> input;
    Map* map = ML->ProduceMap("dotMap/"+input);
    delete ML;
    for(auto a: map->GetContinents()) {
        std::cout << a->GetName() << std::endl;
        for(auto b: *a->GetTerritories()){
            std::cout <<*b->GetName() << std::endl;
            std::cout <<"Neighbors**: ";
            for (auto c : *b->GetNeighbors()) {
                std::cout << *c->GetName() << ", " ;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
    
}
