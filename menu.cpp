/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    menu.cpp
    Definitions for the Menu Class. Can create and print different menus
    depending on where in the program we are.
*/

#include "menu.h"

// Constructor
Menu::Menu(): menuItemVect{}, menuHeadline("") {}

// Constructor initializer
Menu::Menu(const std::vector<std::string> pmMenuItemVect, const std::string pmMenuHeadline):
menuItemVect(pmMenuItemVect), menuHeadline(pmMenuHeadline) {}

//Print the menu items
void Menu::printMenuItems() const
{
    //Top frame
    std::cout << std::endl;
    std::cout << "+-----------------------------------------------------------+\n";
    std::cout << std::setw(1) << std::left << "| ";
    std::cout << std::setw(58) << menuHeadline << std::setw(1) << "|\n";
    std::cout << "+-----------------------------------------------------------+\n";

    int idx=0;

    //Print the items
    for(auto it = menuItemVect.begin(); it != menuItemVect.end(); it++)
    {
        std::string printMenuText=*it;
        if(std::next(it) == menuItemVect.end())
        {
            std::cout << std::setw(2) << "| " << "0" << ". " << std::left;
        }
        else
        {
        std::cout << std::setw(2) << "| " << idx+1 << ". " << std::left;
        }
        std::cout << std::setw(54) << printMenuText << std::setw(1);
        std::cout << " " << "|\n";
        idx++;
    }

    //Bottom frame
    std::cout << "+-----------------------------------------------------------+\n";
    std::cout << "What do you want to do?: ";
}

//Gets menu choice from user, validates with HelpFunctions::validateInt
int Menu::getMenuChoice(const int pmLow, const int pmHigh) const
{
    std::string menuInput;
    getline(std::cin, menuInput);
    int intMenuInput=HelpFunctions::validateInt(menuInput, pmLow, pmHigh);
    return intMenuInput;
}

//Create StartMenu
void Menu::createStartMenu(int pmSimulationStart, int pmSimulationEnd)
{
    menuItemVect.clear();

    menuHeadline="Start menu";
    menuItemVect=
    {
        std::string ("Change start time [") + HelpFunctions::IntToTime(pmSimulationStart) + "]",
        std::string ("Change end time [") + HelpFunctions::IntToTime(pmSimulationEnd) + "]",
        std::string ("Start simulation"),
        std::string ("Exit")
    };
}

//Create SimulationMenu
void Menu::createSimulationMenu(int pmCurrentTime, int pmInterval, std::string pmLogLevel)
{
    menuItemVect.clear();

    menuHeadline="Simulation Menu (current time: " + HelpFunctions::IntToTime(pmCurrentTime) + ")";
    menuItemVect=
    {
        std::string ("Change interval [" + std::to_string(pmInterval) + "]"),
        std::string ("Run next interval"),
        std::string ("Next event"),
        std::string ("Finish (Complete simulation)"),
        std::string ("Change log level [" + pmLogLevel + "]"),
        std::string ("Train Menu"),
        std::string ("Station Menu"),
        std::string ("Vehicle Menu"),
        std::string ("Return (this will abort and reset the simulation)")
    };
}

//Create LogLevelMenu
void Menu::createLogLevelMenu(std::string pmLogLevel)
{
    menuItemVect.clear();

    menuHeadline="Log Level menu (current: " + pmLogLevel + ")";
    menuItemVect=
    {
        std::string ("Low log level"),
        std::string ("Normal log level"),
        std::string ("High log level"),
        std::string ("Return")
    };
}

//Create FinishedMenu
void Menu::createFinishedMenu(std::string pmLogLevel)
{
    menuItemVect.clear();

    menuHeadline="Simulation menu ( *** FINISHED *** )";
    menuItemVect=
    {
        std::string ("Change log level [" + pmLogLevel + "]"),
        std::string ("Print statistics"),
        std::string ("Train Menu"),
        std::string ("Station Menu"),
        std::string ("Vehicle Menu"),
        std::string ("Return")
    };
}

//Create TrainMenu
void Menu::createTrainMenu(std::string pmLogLevel)
{
    menuItemVect.clear();

    menuHeadline="Train menu";
    menuItemVect=
    {
        std::string ("Search train by number"),
        std::string ("Search train by vehicle ID"),
        std::string ("Show all trains"),
        std::string ("Change log level [" + pmLogLevel + "]"),
        std::string ("Return")
    };
}

//Create StationMenu
void Menu::createStationMenu(std::string pmLogLevel)
{
    menuItemVect.clear();

    menuHeadline="Station menu";
    menuItemVect=
    {
        std::string ("Show station names"),
        std::string ("Show station by name"),
        std::string ("Show all stations"),
        std::string ("Change log level [" + pmLogLevel + "]"),
        std::string ("Return")
    };
}

//Create VehicleMenu
void Menu::createVehicleMenu(std::string pmLogLevel)
{
    menuItemVect.clear();

    menuHeadline="Vehicle menu";
    menuItemVect=
    {
        std::string ("Show vehicle by ID"),
        std::string ("Show all vehicles"),
        std::string ("Change log level [" + pmLogLevel + "]"),
        std::string ("Return")
    };
}

//Print a pretty little train
void Menu::printTrainASCII() const
{
    std::cout << "\n         ( ) )     \n";
    std::cout << "        ()        ____.______._____\n";
    std::cout << "      .--.  ----- |  - cho cho -  |\n";
    std::cout << "     __||___|[_]| |.|#|.[].[].[]..|\n";
    std::cout << "    o)__ |_ | ..|=|_|-|___________|\n";
    std::cout << "    __ <(__(*)_(*)_~_____~(*)____(*)_____\n";
    std::cout << "  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~";
}
