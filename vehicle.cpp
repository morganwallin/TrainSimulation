/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    vehicle.cpp
    Definitions for the Vehicle Class. Manipulates vehicles.
    "Vehicle" is a base class for 4 other "vehicles" and 2 "locomotives".
*/

#include "vehicle.h"

//Constructor
Vehicle::Vehicle()
{
    idNumber=-1;
}

//Constructor with initializing
Vehicle::Vehicle(int pmIdNumber)
{
    idNumber=pmIdNumber;
}

//Prints a vehicle, how much to print depends on the user Log Level
void Vehicle::printVehicle(std::string pmLogLevel) const
{
    //Lowest LogLevel
    std::cout << "ID-Number: " << idNumber << "\t Type of Vehicle: ";
    switch(typeOfVehicle)
        {
            case 0: std::cout << "Sitting Car\t\t";
                    break;
            case 1: std::cout << "Sleeping Car\t\t";
                    break;
            case 2: std::cout << "Open Cargo\t\t";
                    break;
            case 3: std::cout << "Closed Cargo\t\t";
                    break;
            case 4: std::cout << "Electric Locomotive\t";
                    break;
            case 5: std::cout << "Diesel Locomotive\t";
                    break;
            default:break;
        }

    //For normal LogLevel
    if(pmLogLevel == "Normal" || pmLogLevel == "High")
    {
        switch(typeOfVehicle)
        {
            case 0: std::cout << " Number of Seats: " << getParam0();
                    break;
            case 1: std::cout << " Number of Beds: " << getParam0();
                    break;
            case 2: std::cout << " Capacity (tonne): " << getParam0() << "t";
                    break;
            case 3: std::cout << " Capacity (m^3): " << getParam0() << "m^3";
                    break;
            case 4: std::cout << " Max km/h: " << getParam0() << "km/h";
                    break;
            case 5: std::cout << " Max km/h: " << getParam0() << "km/h";
                    break;
            default:break;
        }
    }

    //For High LogLevel
    if(pmLogLevel == "High")
    {
        switch(typeOfVehicle)
        {
            case 0: std::cout << "\t Internet: ";
                    if(getParam1() == 1)
                    {
                        std::cout << "Yes";
                    }
                    else
                    {
                        std::cout << "No";
                    }
                    break;
            case 2: std::cout << "\t Load area(m^2): " << getParam1() << "m^2";
                    break;
            case 4: std::cout << "\t Max kW: " << getParam1() << "kW";
                    break;
            case 5: std::cout << "\t Litre/h: " << getParam1() << " l/h";
                    break;
            default:break;
        }
    }
    std::cout << std::endl;
}

//Constructor
SittingCar::SittingCar(int pmIdNumber, int pmNrOfSeats, int pmInternet)
: Vehicle(pmIdNumber)
{
    nrOfSeats=pmNrOfSeats;
    internet=pmInternet;
}

//Constructor
SleepingCar::SleepingCar(int pmIdNumber, int pmNrOfBeds)
: Vehicle(pmIdNumber)
{
    nrOfBeds=pmNrOfBeds;
}

//Constructor
OpenCargoCar::OpenCargoCar(int pmIdNumber, int pmCapacity, int pmSquareMeter)
: Vehicle(pmIdNumber)
{
    capacity=pmCapacity;
    squareMeter=pmSquareMeter;
}

//Constructor
ClosedCargoCar::ClosedCargoCar(int pmIdNumber, int pmCubicMeter)
: Vehicle(pmIdNumber)
{
    cubicMeter=pmCubicMeter;
}
