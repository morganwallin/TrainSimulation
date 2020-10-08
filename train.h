/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    train.h
    Declarations for the Train Class. Manipulates Train-objects.
    Many data members so mainly setters/getters.
*/

#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "vehicle.h"
#include "helpfunctions.h"
#include "locomotive.h"

class Train
{
private:
    //Data Members
    int trainNumber;
    int departureTime;
    int arrivalTime;
    int delay;
    int arrivalDelay;
    int maxVelocity;
    int currentVelocity;
    std::string origin;
    std::string destination;
    std::string state;
    std::vector<std::shared_ptr<Vehicle>> vehicleVect;

public:
    //Constructor
    Train();

    //Member Functions
    Train readTrainFromFile(std::ifstream &pmTrainStream);
    void printTrain(std::string pmLogLevel) const;
    void addVehicle(std::shared_ptr<Vehicle> pmVehicle);

    //Setters
    void setState(std::string pmState) {state=pmState;}
    void setVehicleVect(std::vector<std::shared_ptr<Vehicle>> pmVehicleVect) {vehicleVect=pmVehicleVect;}
    void setDepartureTime(int pmDepartureTime) {departureTime=pmDepartureTime;}
    void setArrivalTime(int pmArrivalTime) {arrivalTime=pmArrivalTime;}
    void setArrivalDelay(int pmArrivalDelay) {arrivalDelay=pmArrivalDelay;}
    void setDelay(int pmDelay) {delay=pmDelay;}
    void setCurrentVelocity(int pmCurrentVelocity) {currentVelocity=pmCurrentVelocity;}

    //Getters
    int getCurrentVelocity() const {return currentVelocity;}
    int getMaxVelocity() const {return maxVelocity;}
    int getDepartureTime() const {return departureTime;}
    int getArrivalTime() const {return arrivalTime;}
    int getDelay() const {return delay;}
    int getArrivalDelay() const {return arrivalDelay;}
    int getTrainNumber() const {return trainNumber;}
    std::string getState() const {return state;}
    std::string getOrigin() const {return origin;}
    std::string getDestination() const {return destination;}
    std::vector<std::shared_ptr<Vehicle>> getVehicleVect() {return vehicleVect;}
};


#endif // TRAIN_H
