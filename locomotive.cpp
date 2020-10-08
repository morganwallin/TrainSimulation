/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    locomotive.cpp
    Definitions for the LocoMotives. Derived from Vehicles.
*/

#include "locomotive.h"

//Constructor
ElectricLocomotive::ElectricLocomotive(int pmIdNumber, int pmTopSpeed, int pmkW)
: Vehicle(pmIdNumber)
{
    topSpeed=pmTopSpeed;
    kW=pmkW;
}

//Constructor
DieselLocomotive::DieselLocomotive(int pmIdNumber, int pmTopSpeed, int pmFuelConsumption)
: Vehicle(pmIdNumber)
{
    topSpeed=pmTopSpeed;
    fuelConsumption=pmFuelConsumption;
}
