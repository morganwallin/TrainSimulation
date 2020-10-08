/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    train.cpp
    Definitions for the Train Class. Manipulates Train-objects.
    Many data members so mainly setters/getters.
*/

#include "train.h"

//Constructor
Train::Train()
{
    delay=0;
    arrivalDelay=0;
    currentVelocity=0;
    state="NOT ASSEMBLED";
}

//Add vehicle to vehicleVect
void Train::addVehicle(std::shared_ptr<Vehicle> pmVehicle)
{
    vehicleVect.push_back(pmVehicle);
    pmVehicle.reset();
}

//Read Train from file
Train Train::readTrainFromFile(std::ifstream &pmTrainStream)
{
    std::string tmpString;
    getline(pmTrainStream, tmpString, '\n');
    std::stringstream ss(tmpString);

    std::string tmpString2;
    ss >> trainNumber >> origin >> destination >> tmpString2;
    departureTime = HelpFunctions::TimeToInt(tmpString2);
    ss >> tmpString2;
    arrivalTime = HelpFunctions::TimeToInt(tmpString2);
    ss >> maxVelocity;

    int typeOfVehicle;

    //Read and add the specified vehicleType to the vector
    while(ss >> typeOfVehicle)
    {
        switch(static_cast<VehicleType> (typeOfVehicle))
        {
            case eSittingCar:           {
                                        SittingCar theVehicle;
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eSittingCar));
                                        addVehicle(std::make_shared<SittingCar> (theVehicle));
                                        break;
                                        }

            case eSleepingCar:          {
                                        SleepingCar theVehicle;
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eSleepingCar));
                                        addVehicle(std::make_shared<SleepingCar> (theVehicle));
                                        break;
                                        }

            case eOpenCargoCar:         {
                                        OpenCargoCar theVehicle;
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eOpenCargoCar));
                                        addVehicle(std::make_shared<OpenCargoCar> (theVehicle));
                                        break;
                                        }

            case eClosedCargoCar:       {
                                        ClosedCargoCar theVehicle;
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eClosedCargoCar));
                                        addVehicle(std::make_shared<ClosedCargoCar> (theVehicle));
                                        break;
                                        }

            case eElectricLocomotive:   {
                                        ElectricLocomotive theVehicle;
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eElectricLocomotive));
                                        addVehicle(std::make_shared<ElectricLocomotive> (theVehicle));
                                        break;
                                        }

            case eDieselLocomotive:     {
                                        DieselLocomotive theVehicle;
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eDieselLocomotive));
                                        addVehicle(std::make_shared<DieselLocomotive> (theVehicle));
                                        break;
                                        }
            default: std::cout << "Error, shouldn't happen.\n\n";
        }
    }
    return *this;
}

//Print a train with different output depending on LogLevel
void Train::printTrain(std::string pmLogLevel) const
{

    std::cout << "Train Number: " << trainNumber << ", State: " << state;
    if(pmLogLevel == "Normal" || pmLogLevel == "High")
    {
        std::cout << ", Top Speed: " << maxVelocity << "km/h  ";
        std::cout << "\nRoute: " << origin << " - " << destination << " |X| Departure time: " << HelpFunctions::IntToTime(departureTime);
        std::cout << ", Arrival Time: " << HelpFunctions::IntToTime(arrivalTime) << " Delay: " << HelpFunctions::IntToTime(delay) << "\n";

    }
    if(pmLogLevel == "High")
    {
        std::cout << "Vehicles: ";
        for(auto &it: vehicleVect)
        {
            std::cout << "Type: " << it->getTypeOfVehicle() << " ";
            if(it->getIdNumber() != -1)
            {
                std::cout << "(ID: " << it->getIdNumber() << ") ";

            };
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


