/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    stationdistance.cpp
    Definitions for the StationDistance Class. Used to get distances
    so we can calculate velocity/arrivaltime/delay for trains.
*/

#include "stationdistance.h"

//Default constructor
StationDistance::StationDistance()
{
    trainStation1="";
    trainStation2="";
    distance=0;
}

//Constructor with initializing
StationDistance::StationDistance(std::string pmTrainStation1, std::string pmTrainStation2, int pmDistance)
{
    trainStation1=pmTrainStation1;
    trainStation2=pmTrainStation2;
    distance=pmDistance;
}

//Read station distances from file, used in fileReader-class
StationDistance StationDistance::readStationDistanceFile(std::ifstream &pmTrainMapStream)
{
    pmTrainMapStream >> trainStation1 >> trainStation2 >> distance;
    return *this;
}
