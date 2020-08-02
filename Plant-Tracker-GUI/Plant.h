/*
  * File:   Plant.h
  *
  * handles attributes of the plant
  */
#pragma once
#include <map>
#include <string>
#include "Plant.h"
#include "Year.h"

using std::map;

class Plant
{
protected:
    std::string name;
    int year;
    map <int, std::string> plantHarvestDates;
    map <int, std::string> waterDates;
    std::string startDate;
    int dateToPos(std::string date);
    std::string posToDate(int position);

public:
    Plant(std::string name, std::string plantDate, int year);
    Plant(std::string name, std::string plantDate, std::string harvestDate, int year);
    void addHarvestDate(std::string harvestDate);
    void addWaterDate(std::string waterDate);
    std::string getName();
    std::string getPlantDate();
    std::string getHarvestDates();
    std::string getWaterDates();
    int getYear();
    std::string to_string();
}; 