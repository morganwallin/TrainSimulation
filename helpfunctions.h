/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    helpfunctions.h
    Declarations for the HelpFunctions Class. Contains static member functions,
    constants and enums.
*/

#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <string>
#include <iostream>
#include <sstream>

//Enums
enum VehicleType {eSittingCar, eSleepingCar, eOpenCargoCar, eClosedCargoCar, eElectricLocomotive, eDieselLocomotive};
enum LogLevel {LogLevelReturn, Low, Normal, High};
enum TrainMenuChoice {TrainMenuReturn, SearchTrainByNumber, SearchTrainByVehicleID, ShowAllTrains, TrainChangeLogLevel};
enum StationMenuChoice {StationMenuReturn, ShowStationNames, ShowStationByName, ShowAllStations, StationChangeLogLevel};
enum VehicleMenuChoice {VehicleMenuReturn, ShowVehicleByID, ShowAllVehicles, VehicleChangeLogLevel};

//Constants
const std::string TRAINSFILE = "Trains.txt";
const std::string TRAINMAPFILE = "TrainMap.txt";
const std::string TRAINSTATIONSFILE = "TrainStations.txt";
const std::string LOGFILE = "Trainsim.log";

class HelpFunctions
{
public:
    //Static Member Functions
    static void clrScreen();
    static void pressEnter();
    static int validateInt(std::string pmString, int pmMin, int pmMax);
    static std::string validateTimeInput(std::string whatToChange);
    static int TimeToInt(std::string pmTimeToConvert);
    static std::string IntToTime(int pmIntTime);
};

#endif // HELPFUNCTIONS_H
