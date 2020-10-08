/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    vehicle.h
    Declarations for the Vehicle Class. Manipulates vehicles.
    "Vehicle" is a base class for 4 other "vehicles" and 2 "locomotives".
*/

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>


class Vehicle
{
private:
    //Data Members
    int idNumber;
    int typeOfVehicle;

public:
    //Constructor
    Vehicle();
    Vehicle(int pmIdNumber);
    virtual ~Vehicle() {};

    //Member Functions
    virtual void printVehicle(std::string pmLogLevel) const;

    //Getters
    virtual int getIdNumber() const {return idNumber;}
    virtual int getTypeOfVehicle() const {return typeOfVehicle;}
    virtual int getParam0() const {return 0;}
    virtual int getParam1() const {return 0;}

    //Setters
    virtual void setIdNumber(int pmIdNumber) {idNumber=pmIdNumber;}
    virtual void setTypeOfVehicle(int pmTypeOfVehicle) {typeOfVehicle=pmTypeOfVehicle;}
};



class SittingCar : public Vehicle
{
private:
    //Data Members
    int nrOfSeats;
    int internet;

public:
    //Constructor
    SittingCar(){};
    SittingCar(int pmIdNumber, int pmNrOfSeats, int pmInternet);

    //Getters
    int getParam0() const override {return nrOfSeats;}
    int getParam1() const override {return internet;}
};



class SleepingCar : public Vehicle
{
private:
    //Data Members
    int nrOfBeds;

public:
    //Constructors
    SleepingCar(){};
    SleepingCar(int pmIdNumber, int pmNrOfBeds);

    //Getters
    int getParam0() const override {return nrOfBeds;}
};



class OpenCargoCar : public Vehicle
{
private:
    //Data Members
    int capacity;
    int squareMeter;

public:
    //Constructors
    OpenCargoCar(){};
    OpenCargoCar(int pmIdNumber, int pmCapacity, int pmSquareMeter);

    //Getters
    int getParam0() const override {return capacity;}
    int getParam1() const override {return squareMeter;}
};



class ClosedCargoCar : public Vehicle
{
private:
    //Data members
    int cubicMeter;

public:
    //Constructors
    ClosedCargoCar(){};
    ClosedCargoCar(int pmIdNumber, int pmCubicMeter);

    //Getters
    int getParam0() const override {return cubicMeter;}
};

#endif // VEHICLE_H
