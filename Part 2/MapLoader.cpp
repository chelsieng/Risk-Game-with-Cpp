//
//  MapLoader.cpp
//  A1
//
//  Created by Raffi Alan Bezirjian on 2020-09-26.
//  Copyright © 2020 Raffi Alan Bezirjian. All rights reserved.
//

#include "MapLoader.h"
#include <stdio.h>

std::vector<std::string> MapLoader::Split(std::string line) const{
    //storing strings
    std::vector<std::string> split_Strings;
    size_t preceding{0},position{0};
    do{
        position = line.find('',preceding);
        if (position == std::string::nposition) position = line.length();
            std::string split = line.substr(preceding, position - preceding);
            if(!split.empty()) splitStrings.push_back(split);
                preceding = position + 1;
    }
    while (position< line.length() && preceding <line.length());
    return split_Strings;
}

void MapLoader::num_processContinents(std::string line, DataType* dataType){
    std::vector<std::string> words = Split(line);
    if(words.size()>0){
        numberOfContinents++;
    } else{
        sizeOfContinents = new int[numberOfContinents];
        for (int i=0; i<numberOfContinents;i++)
            sizeOfContinents[i] = 0;
        cont = std::vector<Continent*>();
        cont.reserve(numberOfContinents);
        *dataType = DataType::None;
    }
    
}

void MapLoader::num_processTerritories(std::string line, DataType* datatype){
    std::vector<std::string> words = Split(line);
    if (words.size()>0){
        if(words.size()< 3) Data_True->trueData = false;
        numberOfTerritories ++;
        try{
            int included = std::stoi(words[2])
            sizeOfContinents[included - 1]++;
        } catch (std::invalid_argument){
            std::cout << "Reading Of An Integer Has Failed" << std::endl;
            Data_True->trueData = false;
        }
    }   else {
        *dataType = DataType::None;
        sizeOfNeighbors = new int[numberofTerritories];
    }
}

void MapLoader::num_processBorders(std::string line,DataType* dataType){
    std::vector<std::string> words = Split(line);
    if (words.size()>0){
        if(words.size()<2){
            Data_True->trueData = false;
            std::cout <<"Error encountered: Invalid Map File" << std::endl;
        }
        try{
            sizeOfNeighbors[std::stoi(words[0]-1)] = words.size() - 1;
        }   catch (std::invalid_argument){
            std::cout << "Reading Of An Integer Has Failed" <<std::endl;
            Data_True->trueData = false;
        }
    }   else
        *dataType = DataType::None;
}

void MapLoader::generate_Borders(std::string line, DataType* dataType){
    std::vector<std::string> words = Split(line);
    if (words.size()>0){
        if (words.size() < 2){
            Data_True->trueData = false;;
            std::cout <<"Error encountered: Invalid Map File" <<std::endl;
        }
        try{
            std::vector<Territory*>* t = producedMap->GetTerritories();
            Territory* territory = (*producedMap->GetTerritories())[std::stoi(words[0]-1)];
        } catch (std::invalid_argument){
            std::cout <<"Reading Of An Integer Has Failed" << std::endl;
            Data_True->trueData = false;
        }
    }   else
        *dataType = DataType::None;
    
}

void MapLoader::generate_Continents(std::string line, DataType* dataType){
    std::vector<std::string> words = Split(line);
    if (words.size()>0){
        if(words.size()< 2) Data_True->trueData = false;
        Continent* continent = new Continent(sizeOfContinents[i],words[0]);
        continents.push_back(continent);
        i++;
        try{
        } catch (std::invalid_argument){
            std::cout <<"Reading Of An Integer Has Failed" <<std::endl;
            Data_True->trueData = false;
        }
    }   else {
        *dataType = DataType::None;
        producedMap = new Map(numberOfTerritories,&continents);
    }
}


void MapLoader::generate_Territories(std::string line, DataType* dataType){
    std::vector<std::string> words = Split(line);
    if(words.size()>0){
        if(words.size() < 3) Data_True->trueData = false;
        std::string* name = new Territory(name);
        try{
            producedMap->AddTerritory(territory);
            territory->SetContinent(continents[std::stoi(words[2])-1]);
        } catch (std::invalid_argument){
            std::cout << "Reading Of An Integer Has Failed" << std::endl;
            Data_True->trueData = false;
        }
    } else
        *dataType = DataType::None;
}


void MapLoader::fileReading(std::string path){
    std::string line;
    std::ifstream myfile(path);
    DataType dataType = DataType::None;
    if (myfile.is_open()){
        while(getline(myfile, line)){
            std::regex title("\\[[a-z]+\\]");
            std::smatch x;
            if (regex_search(line,x,title)){
                if (x.str().compare("[files]"== 0){
                    Data_True->fileFound = true;
                } else if (x.str().compare("[continents]")==0){
                    dataType = DataType::Continents;
                    Data_True->continentsFound = true;
                } else if (x.str().compare("[countries]")==0){
                    dataType = DataType::Territories;
                    Data_True->territoriesFound = true;
                } else if (x.str().compare("[borders]")==0){
                    dataType = DataType::Borders;
                    Data_True->bordersFound = true;
                }
                    } else {
                    switch(dataType)
                        case (DataType::Continents):
                        num_processContinents(line,&dataType);
                    break;
                case (DataType::Territories):
                    num_processTerritories(line,&dataType);
                    break;
                case(DataType::Borders):
                    num_processBorders(line,&dataType);
                    break;
                    
                }
                    }
                    }
                    myfile.close();
                    } else
                    std::cout << "Error: Cannot Open The File";
                    dataType = DataType::None;
                    myfile = std::ifstream(path);
                    if(myfile.is_open()){
                    while (getline(myfile,line)){
                        std::regex title("\\[[a-z]+\\]");
                        std::smatch x;
                        if(regex_search(line,x,title)){
                            if(x.str().compare("[files]")==0){
                            } else if (x.str().compare("[continents]")==0){
                                dataType = DataType::Continents;
                            } else if (x.str().compare("[countries]")==0) {
                                dataType = DataType::Territories;
                            } else if (x.str().compare("[borders]")==0){
                                datatype = DataType::Borders;
                            }
                        } else {
                            switch(DataType) {
                                case(DataType::Continents):
                                    generate_Continents(line,&dataType);
                                    break;
                                case(DataType::Territories):
                                    generate_Territories(line,&dataType);
                                    break;
                                case(DataType::Borders):
                                    generate_Borders(line,&dataType);
                                    break;
                            }
                        }
                    }
                    myfile.close();
                }else
                    std::cout << "Error: Cannot Open The File";
                    }
                    
                    
                    
                    
                    Map* MapLoader::ProduceMap(std::string filePath){
                    ReadFile(filePath);
                    if (Data_True-> validTrue());
                    return producedMap;
                    else{
                        std::cout <<"Error: invalid map file" << std::endl;
                        return nullptr;
                    }
                }
                    
                    MapLoader::MapLoader(){
                    Data_True = new DATA_TRUE();
                    i = 0;
                }
                    
                    MapLoader::~MapLoader(){
                    delete Data_True;
                    delete[] sizeOfContinents;
                    delete[] sizeOfNeighbors;
                }
