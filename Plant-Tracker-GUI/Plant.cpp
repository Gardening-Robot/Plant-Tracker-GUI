/*
  * File:   Plant.cpp
  *
  * handles attributes of the plant
 */
#include "Plant.h"

Plant::Plant(std::string name, std::string plantDate, int year) {
    this->name = name;
    this->year = year;
    startDate = plantDate;
    plantHarvestDates.insert(std::pair<int, std::string>(0, plantDate));
}

Plant::Plant(std::string name, std::string plantDate, std::string harvestDate, int year) {
    this->name = name;
    this->year = year;
    startDate = plantDate;
    plantHarvestDates.insert(std::pair <int, std::string>(0, startDate));
    plantHarvestDates.insert(std::pair <int, std::string>(dateToPos(harvestDate), harvestDate));
}

std::string Plant::getName() {
    return name;
}

std::string Plant::getPlantDate() {
    return plantHarvestDates.at(0);
}

std::string Plant::getHarvestDates() {
    std::string harvestDates = "";
    for (const auto& datePair : plantHarvestDates) {
        std::string temp = posToDate(datePair.first);
        harvestDates.append(temp + ",");
    }
    harvestDates = harvestDates.substr(6);
    return harvestDates;
}

std::string Plant::getWaterDates() {
    std::string waterDateList = "";
    for (const auto& datePair : waterDates) {
        std::string temp = posToDate(datePair.first);
        waterDateList.append(temp + ",");
    }
    return waterDateList;
}

int Plant::getYear() {
    return year;
}

void Plant::addHarvestDate(std::string harvestDate) {
    plantHarvestDates.insert(std::pair<int, std::string>(dateToPos(harvestDate), harvestDate));
}

void Plant::addWaterDate(std::string waterDate) {
    waterDates.insert(std::pair<int, std::string>(dateToPos(waterDate), waterDate));
}

std::string Plant::to_string() {
    std::string dates = "";
    for (const auto& datePair : plantHarvestDates) {
        std::string temp = posToDate(datePair.first);
        dates.append("   " + temp);
    }
    return ("Plant: " + name + "    Dates: " + dates);
}

int Plant::dateToPos(std::string currentDate) {
    int startMonth = std::stoi(startDate.substr(0, 2));
    int startDay = std::stoi(startDate.substr(3));
    int currentMonth = std::stoi(currentDate.substr(0, 2));
    int currentDay = std::stoi(currentDate.substr(3));
    if (currentMonth == startMonth)
        return currentDay - startDay;
    else if (currentMonth > startMonth) {
        int daysInStartMonth = getDaysInMonth(startMonth - 1, year) - startDay;
        int fullMonthDays = 0;
        for (int i = startMonth; i < currentMonth - 1; i++) {
            fullMonthDays += getDaysInMonth(i, year);
        }
        return currentDay + daysInStartMonth + fullMonthDays;
    }
    else
        return -1;
}

std::string Plant::posToDate(int position) {
    int startMonth = std::stoi(startDate.substr(0, 2));
    int startDay = std::stoi(startDate.substr(3));
    int currentMonth = 0;
    int currentDay = 0;
    if (getDaysInMonth(startMonth - 1, year) >= position + startDay) { // if (# of days in start month >= position + start day)
        if (position + startDay < 10) {
            return (startDate.substr(0, 2) + "/0" + std::to_string(position + startDay));
        }
        else
            return (startDate.substr(0, 2) + "/" + std::to_string(position + startDay));
    }
    else {
        currentMonth = startMonth + 1;
        currentDay = position - getDaysInMonth(startMonth - 1, year) + startDay;
        while (getDaysInMonth(currentMonth - 1, year) < currentDay) {
            currentDay -= getDaysInMonth(currentMonth - 1, year);
            currentMonth++;
        }
        if (currentDay < 10 && currentMonth < 10)
            return ("0" + std::to_string(currentMonth) + "/0" + std::to_string(currentDay));
        else if (currentDay < 10)
            return (std::to_string(currentMonth) + "/0" + std::to_string(currentDay));
        else if (currentMonth < 10)
            return ("0" + std::to_string(currentMonth) + "/" + std::to_string(currentDay));
        else
            return (std::to_string(currentMonth) + "/" + std::to_string(currentDay));
    }
}