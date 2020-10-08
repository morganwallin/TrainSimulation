/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    locomotive.h
    Declarations for the LocoMotives. Derived from Vehicles.
*/

#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "vehicle.h"

class ElectricLocomotive : public Vehicle
{
private:
    //Data members
    int topSpeed;
    int kW;

public:
    //Constructors
    ElectricLocomotive(){};
    ElectricLocomotive(int pmIdNumber, int pmTopSpeed, int pmkW);

    //Getters
    int getParam0() const override {return topSpeed;}
    int getParam1() const override {return kW;}
};



class DieselLocomotive : public Vehicle
{
private:
    //Data members
    int topSpeed;
    int fuelConsumption;

public:
    //Constructors
    DieselLocomotive(){};
    DieselLocomotive(int pmIdNumber, int pmTopSpeed, int pmFuelConsumption);

    //Getters
    int getParam0() const override {return topSpeed;}
    int getParam1() const override {return fuelConsumption;}
};


#endif // LOCOMOTIVE_H
