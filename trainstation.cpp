/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    trainstation.cpp
    Definitions for the TrainStation Class. Manipulates TrainStation-objects.
*/

#include "trainstation.h"


//Add vehicle to vector
void TrainStation::addVehicle(std::shared_ptr<Vehicle> pmVehicle)
{
    vehicleVect.push_back(pmVehicle);
}

//Read TrainStation from file
TrainStation TrainStation::readTrainStationFromFile(std::ifstream &pmTrainStationStream)
{
    pmTrainStationStream >> stationName;
    std::string tmpString;
    getline(pmTrainStationStream, tmpString, '\n');
    std::stringstream ss(tmpString);

    //Read until there are no more vehicles at this station
    while(true)
    {
        std::stringstream ss1;
        getline(ss, tmpString, '(');
        getline(ss, tmpString, ')');
        if(tmpString.size() == 0)
        {
            break;
        }
        ss1 << tmpString;
        int tmpIdNumber=0, tmpVehicleType=0, tmpParam1=0, tmpParam2=0;
        ss1 >> tmpIdNumber >> tmpVehicleType >> tmpParam1;

        //Create the correct Vehicle-object and put in vector
        switch(static_cast<VehicleType> (tmpVehicleType))
        {
            case eSittingCar:           {
                                        ss1 >> tmpParam2;
                                        SittingCar theVehicle(tmpIdNumber, tmpParam1, tmpParam2);
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eSittingCar));
                                        addVehicle(std::make_shared<SittingCar> (theVehicle));
                                        break;
                                        }

            case eSleepingCar:          {
                                        SleepingCar theVehicle(tmpIdNumber, tmpParam1);
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eSleepingCar));
                                        addVehicle(std::make_shared<SleepingCar> (theVehicle));
                                        break;
                                        }

            case eOpenCargoCar:         {
                                        ss1 >> tmpParam2;
                                        OpenCargoCar theVehicle(tmpIdNumber, tmpParam1, tmpParam2);
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eOpenCargoCar));
                                        addVehicle(std::make_shared<OpenCargoCar> (theVehicle));
                                        break;
                                        }

            case eClosedCargoCar:       {
                                        ClosedCargoCar theVehicle(tmpIdNumber, tmpParam1);
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eClosedCargoCar));
                                        addVehicle(std::make_shared<ClosedCargoCar> (theVehicle));
                                        break;
                                        }

            case eElectricLocomotive:   {
                                        ss1 >> tmpParam2;
                                        ElectricLocomotive theVehicle(tmpIdNumber, tmpParam1, tmpParam2);
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eElectricLocomotive));
                                        addVehicle(std::make_shared<ElectricLocomotive> (theVehicle));
                                        break;
                                        }

            case eDieselLocomotive:     {
                                        ss1 >> tmpParam2;
                                        DieselLocomotive theVehicle(tmpIdNumber, tmpParam1, tmpParam2);
                                        theVehicle.setTypeOfVehicle(static_cast<int>(eDieselLocomotive));
                                        addVehicle(std::make_shared<DieselLocomotive> (theVehicle));
                                        break;
                                        }
            default: std::cout << "Error, shouldn't happen.\n\n";
        }
    }
    return *this;
}

//Print TrainStation
void TrainStation::printTrainStation(std::string pmLogLevel) const
{
    std::cout << "Station name: " << stationName <<std::endl;
    if(pmLogLevel == "Normal" || pmLogLevel == "High")
    {
        for(auto &it: vehicleVect)
        {
            it->printVehicle(pmLogLevel);
        }
        HelpFunctions::pressEnter();
    }
}

//Sort vehicles in vehicleVect so we always get the one with lowest IdNumber
void TrainStation::sortVehicles()
{
    std::sort(vehicleVect.begin(), vehicleVect.end(), [] (std::shared_ptr<Vehicle> const& v1, std::shared_ptr<Vehicle> const& v2) -> bool
              {return v1->getIdNumber() < v2->getIdNumber();});
}
