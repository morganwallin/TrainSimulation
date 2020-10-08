/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    filehandler.h
    Definitions for the FileHandler Class. Reads the data from the
    three const files specified in helpfunctions.h
*/

#include "filehandler.h"

//Opens the datafiles, throws runtime_error if something goes wrong
void FileHandler::openAllFiles()
{
    trainStream.open(TRAINSFILE);
    if(!trainStream)
    {
        throw std::runtime_error("Failed to open file " + TRAINSFILE + ".");
    }

    trainMapStream.open(TRAINMAPFILE);
    if(!trainMapStream)
    {
        throw std::runtime_error("Failed to open file " + TRAINMAPFILE + ".");
    }

    trainStationStream.open(TRAINSTATIONSFILE);
    if(!trainStationStream)
    {
        throw std::runtime_error("Failed to open file " + TRAINSTATIONSFILE + ".");
    }
}

//Read all data from the files into the vectors send as parameters
void FileHandler::readAllFiles(std::vector<Train> &pmTrainVect, std::vector<TrainStation> &pmTrainStationVect,
                               std::vector <StationDistance> &pmStationDistanceVect)
{
    try
    {
        openAllFiles();
    }
    catch(std::ios_base::failure &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Exiting...";
        exit(1);
    }

    readTrainFile(pmTrainVect);
    readTrainMapFile(pmStationDistanceVect);
    readTrainStationFile(pmTrainStationVect);
}

//Get all train info from file
void FileHandler::readTrainFile(std::vector<Train> &pmTrainVect)
{
    while(!trainStream.eof())
    {
        Train tmpTrain;
        pmTrainVect.push_back(tmpTrain.readTrainFromFile(trainStream));
    }
}

//Get all train map info from file
void FileHandler::readTrainMapFile(std::vector <StationDistance> &pmStationDistanceVect)
{
    while(!trainMapStream.eof())
    {
        StationDistance tmpStationDistance;
        pmStationDistanceVect.push_back(tmpStationDistance.readStationDistanceFile(trainMapStream));
    }
}

//Get all train station info from file
void FileHandler::readTrainStationFile(std::vector<TrainStation> &pmTrainStationVect)
{
    while(!trainStationStream.eof())
    {
        TrainStation tmpTrainStation;
        pmTrainStationVect.push_back(tmpTrainStation.readTrainStationFromFile(trainStationStream));
    }
}
