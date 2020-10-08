/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    trainstation.h
    Declarations for the TrainStation Class. Manipulates TrainStation-objects.
*/

#ifndef TRAINSTATION_H
#define TRAINSTATION_H

#include "vehicle.h"
#include "helpfunctions.h"
#include "locomotive.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <algorithm>


class TrainStation
{
private:
    //Data Members
    std::string stationName;
    std::vector<std::shared_ptr<Vehicle>> vehicleVect;

public:
    //Member Functions
    TrainStation readTrainStationFromFile(std::ifstream &pmTrainStationStream);
    void printTrainStation(std::string pmLogLevel) const;
    void addVehicle(std::shared_ptr<Vehicle> pmVehicle);
    void sortVehicles();

    //Getters
    std::string getStationName() const {return stationName;}
    std::vector<std::shared_ptr<Vehicle>> getVehicleVect() const {return vehicleVect;}

    //Setters
    void setVehicleVect(std::vector<std::shared_ptr<Vehicle>> pmVehicleVect) {vehicleVect=pmVehicleVect;}
};


#endif // TRAINSTATION_H
