/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    menu.h
    Declarations for the Menu Class. Can create and print different menus
    depending on where in the program we are.
*/

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "helpfunctions.h"


class Menu
{
private:
    //Members
    std::vector<std::string> menuItemVect;
    std::string menuHeadline;

public:
    //Constructors
    Menu();
    Menu(const std::vector<std::string> pmMenuItemVect, const std::string pmMenuHeadline);

    //Member functions
    int getMenuChoice(const int pmLow, const int pmHigh) const;
    void printMenuItems() const;
    void createStartMenu(int pmSimulationStart, int pmSimulationEnd);
    void createSimulationMenu(int pmCurrentTime, int pmInterval, std::string pmLogLevel);
    void createLogLevelMenu(std::string pmLogLevel);
    void createFinishedMenu(std::string pmLogLevel);
    void createTrainMenu(std::string pmLogLevel);
    void createStationMenu(std::string pmLogLevel);
    void createVehicleMenu(std::string pmLogLevel);
    void printTrainASCII() const;
};


#endif // MENU_H
