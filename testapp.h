#ifndef TESTAPP_H
#define TESTAPP_H

#include "menu.h"
#include "train.h"
#include "trainstation.h"
#include "stationdistance.h"
#include "event.h"
#include "filehandler.h"
#include "simulation.h"
#include "company.h"
#include <fstream>
#include <queue>
#include <vector>

class TestApp
{
private:
    int simulationStart;
    int simulationEnd;
    int interval;
    std::string logLevel;

public:
    TestApp ();

    void run();
    void changeSimulationStart();
    void changeSimulationEnd();
    void startSimulation();
    void changeInterval();
    void changeLogLevel();
    void finishSimulation();
    void runTrainMenu();
    void runStationMenu();
    void runVehicleMenu();

    int getSimulationStart(){return simulationStart;}
    int getSimulationEnd(){return simulationEnd;}
};

#endif
