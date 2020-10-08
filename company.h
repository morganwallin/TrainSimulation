/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    company.h
    Definitions for the Company Class. This is where most of program will run from.
    3 vectors are defined here, Train, TrainStation and TrainStationDistance,
    and we use the functions in here to manipulate all the other classes.
*/

#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "menu.h"
#include "train.h"
#include "trainstation.h"
#include "stationdistance.h"
#include "event.h"
#include "filehandler.h"
#include "simulation.h"


class Company {
private:
    //Data members
    std::vector<Train> trainVect;
    std::vector<TrainStation> trainStationVect;
    std::vector<StationDistance> stationDistanceVect;
    std::vector<TrainStation> backupTrainStationVect;
    std::string logLevel;
    Simulation *theSim;
    bool printOrNot;
    int simulationStart;
    int simulationEnd;
    int interval;
    int totalDelay;

public:
    //Constructor
    Company();

    //Member Functions used in Event Class
    int running(const int pmTrainNumber);
    bool assembly(const int pmTrainNumber);
    void changeToReady(const int pmTrainNumber);
    void disassemble(const int pmTrainNumber);
    void arrived(const int pmTrainNumber);

    //Printing functions
    void printEvent(const int pmTrainNumber, std::string specialMessage);
    void printTrainByVehicleID();
    void printTrainByNumber();
    void printAllVehicles();
    void printVehicleByID();
    void printStatistics();
    void printAllStations() const;
    void printAllStationNames() const;
    void printStationByName() const;
    void printAllTrains() const;

    //Create and run menus
    void run();
    void startSimulation();
    void finishSimulation();
    void runTrainMenu();
    void runStationMenu();
    void runVehicleMenu();

    //Calculating functions
    void initialImport();
    void resetCompany();
    int calculateNewArrivalTime(int pmTrainNumber, int &pmVelocity);

    //Change data members
    void changeSimulationStart();
    void changeSimulationEnd();
    void changeInterval();
    void changeLogLevel();

    //Getters
    int getSimulationStart(){return simulationStart;}
    int getSimulationEnd(){return simulationEnd;}

    //Get pointers
    ptrdiff_t getTrainPos(int pmTrainNumber) {return distance(trainVect.begin(), find_if(trainVect.begin(), trainVect.end(), [&](Train const& t){return pmTrainNumber == t.getTrainNumber();}));}
    ptrdiff_t getTrainStationPos(int pmTrainNumber) {return distance(trainStationVect.begin(), find_if(trainStationVect.begin(), trainStationVect.end(),
                                                                                                       [&](TrainStation const& ts){return trainVect[getTrainPos(pmTrainNumber)].getOrigin() == ts.getStationName();}));}

};

#endif
