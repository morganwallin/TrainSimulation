/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    filehandler.h
    Declarations for the FileHandler Class. Reads the data from the
    three const files specified in helpfunctions.h
*/

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <vector>
#include "train.h"
#include "trainstation.h"
#include "stationdistance.h"
#include "helpfunctions.h"


class FileHandler
{
private:
    //Members
    std::ifstream trainStream;
    std::ifstream trainMapStream;
    std::ifstream trainStationStream;

public:
    //Member Functions
    void openAllFiles();
    void readAllFiles(std::vector<Train> &pmTrainVect, std::vector<TrainStation> &pmTrainStationVect,
                               std::vector <StationDistance> &pmStationDistanceVect);
    void readTrainFile(std::vector<Train> &pmTrainVect);
    void readTrainMapFile(std::vector <StationDistance> &pmStationDistanceVect);
    void readTrainStationFile(std::vector<TrainStation> &pmTrainStationVect);

};

#endif // FILEHANDLER_H
