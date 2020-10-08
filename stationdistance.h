/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    stationdistance.h
    Declarations for the StationDistance Class. Used to get distances
    so we can calculate velocity/arrivaltime/delay for trains.
*/

#ifndef STATIONDISTANCE_H
#define STATIONDISTANCE_H

#include <string>
#include <fstream>
#include <iostream>

class StationDistance
{
private:
    //Data Members
    std::string trainStation1, trainStation2;
    int distance;

public:
    //Constructors
    StationDistance();
    StationDistance(std::string pmTrainStation1, std::string pmTrainStation2, int pmDistance);

    //Member functions
    StationDistance readStationDistanceFile(std::ifstream &pmTrainMapStream);

    //Getters
    std::string getStation1() {return trainStation1;}
    std::string getStation2() {return trainStation2;}
    int getDistance() {return distance;}
};


#endif // STATIONDISTANCE_H
