/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    company.h
    Definitions for the Company Class. This is where most of program will run from.
    3 vectors are defined here, Train, TrainStation and TrainStationDistance,
    and we use the functions in here to manipulate all the other classes.
*/

#include "company.h"

//Constructor
Company::Company()
{
    simulationEnd=1439;
    simulationStart=0;
    interval=10;
    logLevel="Low";
    FileHandler fileHandler;
    fileHandler.readAllFiles(trainVect, trainStationVect, stationDistanceVect);
    backupTrainStationVect=trainStationVect;
    printOrNot=false;
    totalDelay=0;
}

//Queue up all the initial AssemblyEvents we got from the data files
void Company::initialImport()
{
    for(auto &v: trainVect)
    {
        if(theSim->getEndTime() > v.getDepartureTime()-30)
        {
            theSim->scheduleEvent(new AssemblyEvent(theSim, this, v.getDepartureTime()-30, v.getTrainNumber()));
        }
    }

    //Reset logfile content at the start of the program, since the program normally appends to file
    std::ofstream os(LOGFILE);
    if(!os)
    {
        throw std::runtime_error("Failed to open file " + LOGFILE + ".");
    }
    os.close();
}

//Attach vehicles to Train and remove the vehicles from train station
bool Company::assembly(const int pmTrainNumber)
{
    //Train to assemble
    ptrdiff_t trainPos = getTrainPos(pmTrainNumber);

    //Trainstation where the train is at
    ptrdiff_t trainStationPos = getTrainStationPos(pmTrainNumber);

    //Set default options, if everything goes allright
    bool success=true;
    trainVect[trainPos].setState("ASSEMBLED");

    //Create temporary vectors
    std::vector<std::shared_ptr<Vehicle>> tmpStationVehicleVect = trainStationVect[trainStationPos].getVehicleVect();
    std::vector<std::shared_ptr<Vehicle>> tmpTrainVehicleVect = trainVect[trainPos].getVehicleVect();

    int counter=0;

    //Attempt to assemble all vehicles
    for(auto &it: trainVect[trainPos].getVehicleVect())
    {
        //If the idNumber of the vehicle is not -1 we know we already assembled that vehicle
        if(it->getIdNumber() != -1)
        {
            counter++;
            continue;
        }

        //Check if there are vehicles of that type at the station
        auto pos = std::find_if(tmpStationVehicleVect.begin(), tmpStationVehicleVect.end(),
                           [&it](std::shared_ptr<Vehicle> const &v){return it->getTypeOfVehicle() == v->getTypeOfVehicle();});

        //If there are no correct vehicles we set error flags and start from the top
        if(pos == tmpStationVehicleVect.end())
        {
            counter++;
            success=false;
            continue;
        }
        //Else we interchange the abstract vehicle with the one at the station, and remove the one at the station
        else
        {
            ptrdiff_t vehiclePos = distance(tmpStationVehicleVect.begin(), pos);
            std::shared_ptr<Vehicle> tmpVehicle = tmpStationVehicleVect[vehiclePos];
            tmpTrainVehicleVect.insert(tmpTrainVehicleVect.begin()+counter, tmpVehicle);
            tmpTrainVehicleVect.erase(tmpTrainVehicleVect.begin()+(++counter));
            tmpStationVehicleVect.erase(pos);
        }

    }

    //Assign the temporary vehicleVectors to the real ones
    trainVect[trainPos].setVehicleVect(tmpTrainVehicleVect);
    trainStationVect[trainStationPos].setVehicleVect(tmpStationVehicleVect);

    //If Train couldn't finish assembly, return false and mark the delays
    if(success == false)
    {
        trainVect[trainPos].setDelay(trainVect[trainPos].getDelay()+10);
        trainVect[trainPos].setDepartureTime(trainVect[trainPos].getDepartureTime()+10);
        trainVect[trainPos].setArrivalTime(trainVect[trainPos].getArrivalTime()+10);
        trainVect[trainPos].setState("INCOMPLETE");
        printEvent(pmTrainNumber, "is waiting for vehicles, trying again at " + HelpFunctions::IntToTime(trainVect[trainPos].getDepartureTime()-30));
        return false;
    }

    printEvent(pmTrainNumber, "is now assembled, arriving at the platform at " + HelpFunctions::IntToTime(trainVect[trainPos].getDepartureTime()-10));
    return success;
}

//Change the state of a train to READY
void Company::changeToReady(const int pmTrainNumber)
{
    ptrdiff_t trainPos = getTrainPos(pmTrainNumber);
    trainVect[trainPos].setState("READY");
}

//Function that adjusts train delay, calculates arrival time and sets velocity/state
int Company::running(const int pmTrainNumber)
{
    ptrdiff_t trainPos = getTrainPos(pmTrainNumber);

    int velocity=trainVect[trainPos].getMaxVelocity();

    for(auto &it: trainVect[trainPos].getVehicleVect())
    {
        //Check if any of the locomotives have lower maxspeed than the train
        if((it->getTypeOfVehicle() == 4 || it->getTypeOfVehicle() == 5) && velocity > it->getParam0())
        {
            velocity=it->getParam0();
        }
    }

    int newArrivalTime=calculateNewArrivalTime(pmTrainNumber, velocity);
    //Check to speed up train if it was delayed
    if(trainVect[trainPos].getDelay() != 0)
    {
        trainVect[trainPos].setArrivalTime(newArrivalTime);
    }

    trainVect[trainPos].setCurrentVelocity(velocity);
    trainVect[trainPos].setState("RUNNING");
    printEvent(pmTrainNumber, "has left the platform, traveling at speed " + std::to_string(velocity) + " (" + std::to_string(trainVect[trainPos].getMaxVelocity()) + ")");
    return trainVect[trainPos].getArrivalTime();
}

//Set state to ARRIVED and print an event message
void Company::arrived(const int pmTrainNumber)
{
    ptrdiff_t trainPos = getTrainPos(pmTrainNumber);
    trainVect[trainPos].setState("ARRIVED");
    printEvent(pmTrainNumber, "has arrived at the platform, disassembly at " + HelpFunctions::IntToTime(theSim->getTime()+20));
}

//Disassembly of train at train station, adds vehicles to train station pool and removes from the arrived train
void Company::disassemble(const int pmTrainNumber)
{
    ptrdiff_t trainPos = getTrainPos(pmTrainNumber);

    ptrdiff_t trainStationPos = distance(trainStationVect.begin(), find_if(trainStationVect.begin(), trainStationVect.end(),
                                                    [&](TrainStation const& ts)
                                                    {return trainVect[trainPos].getDestination() == ts.getStationName();}));

    std::vector<std::shared_ptr<Vehicle>> tmpTrainVehicleVect = trainVect[trainPos].getVehicleVect();
    int counter=0;

    //For every vehicle in the train vector, put it in trainStation vector and reset the train vector to just vehicleTypes
    for(auto &it: tmpTrainVehicleVect)
    {
        trainStationVect[trainStationPos].addVehicle(it);
        std::shared_ptr<Vehicle> tmpVehicle = std::make_shared<Vehicle> (*it);
        tmpVehicle->setIdNumber(-1);
        tmpTrainVehicleVect.erase(tmpTrainVehicleVect.begin()+counter);
        tmpTrainVehicleVect.insert(tmpTrainVehicleVect.begin()+(counter++), tmpVehicle);
        tmpVehicle.reset();
    }

    //Set state, print message and sort vehicles at train station so we always get the vehicle with lowest IdNumber
    trainVect[trainPos].setVehicleVect(tmpTrainVehicleVect);
    trainVect[trainPos].setState("FINISHED");
    printEvent(pmTrainNumber, "is now disassembled.");
    trainStationVect[trainStationPos].sortVehicles();
}

//Print the information from the Event to console and to file ("Trainsim.log")
void Company::printEvent(const int pmTrainNumber, std::string specialMessage)
{
    //If we start the simulation later than 00:00, hide the output with this if statement
    if(printOrNot == false)
    {
        return;
    }

    ptrdiff_t trainPos = getTrainPos(pmTrainNumber);

    //Get all variables
    int currentTime = theSim->getTime(), trainNumber = pmTrainNumber, departTime = trainVect[trainPos].getDepartureTime();
    int delay = trainVect[trainPos].getDelay(), arrivalTime = trainVect[trainPos].getArrivalTime();
    int currentVelocity=trainVect[trainPos].getCurrentVelocity(), arrivalDelay=trainVect[trainPos].getArrivalDelay();
    std::string state = trainVect[trainPos].getState(), origin = trainVect[trainPos].getOrigin(), destination = trainVect[trainPos].getDestination();

    //Put all the info together to a string so we can use it both with cout and ofstream
    std::string output = HelpFunctions::IntToTime(currentTime) + " Train [" + std::to_string(trainNumber) + "]";
    output+= " (" + state + ") from " + origin + " " + HelpFunctions::IntToTime(departTime-delay);
    output+= " (" + HelpFunctions::IntToTime(departTime) + ") to " + destination;
    output+= " " + HelpFunctions::IntToTime(arrivalTime-arrivalDelay) + " (";
    output+= HelpFunctions::IntToTime(arrivalTime) + ") delay (";
    output+= HelpFunctions::IntToTime(arrivalDelay) + ") speed = " + std::to_string(currentVelocity);
    output+= " km/h " + specialMessage + "\n\n";

    //Print with cout and write to file with ofstream
    std::cout << output;
    std::ofstream os;
    os.open("Trainsim.log", std::ios_base::app);
    if(os.is_open())
    {
        os << output;
        os.close();
    }
}

//Print all Trains
void Company::printAllTrains() const
{
    HelpFunctions::clrScreen();
    int counter=0;
    for(auto &it: trainVect)
    {
        if(++counter%50 == 0)
        {
            HelpFunctions::pressEnter();
        }
        it.printTrain(logLevel);
    }
}

//Put all variables back to its original state, clear vectors etc so we can go again
void Company::resetCompany()
{
    simulationEnd=1439;
    simulationStart=0;
    interval=10;
    logLevel="Low";
    FileHandler fileHandler;
    trainVect.clear();
    trainStationVect.clear();
    stationDistanceVect.clear();
    fileHandler.readAllFiles(trainVect, trainStationVect, stationDistanceVect);
    printOrNot=false;
    totalDelay=0;

}

//Creates the start menu
void Company::run()
{
    Menu startMenu;
    startMenu.createStartMenu(simulationStart, simulationEnd);
    int menuChoice;
    do
    {
        startMenu.printTrainASCII();
        startMenu.printMenuItems();
        menuChoice=startMenu.getMenuChoice(0, 3);
        switch(menuChoice)
        {
        case 1: changeSimulationStart();
                break;
        case 2: changeSimulationEnd();
                break;
        case 3: HelpFunctions::clrScreen();
                startSimulation();
                resetCompany();
                break;
        case 0: break;

        default:std::cout << "Error, shouldn't happen.\n\n";
        }

    //Uppdatera menyn så att start/end-time blir rätt
    startMenu.createStartMenu(simulationStart, simulationEnd);
    }while(menuChoice != 0);
}

//Change when the simulation should start (no events gets printed/logged before this)
void Company::changeSimulationStart()
{
    int tmpSimulationStart=(HelpFunctions::TimeToInt(HelpFunctions::validateTimeInput("start")));
    if(tmpSimulationStart >= getSimulationEnd())
    {
        HelpFunctions::clrScreen();
        std::cout << "Error, can't set the start timer after the end timer.\n\n";
        return;
    }
    simulationStart=tmpSimulationStart;

    HelpFunctions::clrScreen();
    std::cout << "Simulation start time changed to " << HelpFunctions::IntToTime(simulationStart) << ".\n\n";
}

//Change when the simulation should end (no trains can leave any station past this time, events after that could still get logged tho)
void Company::changeSimulationEnd()
{
    int tmpSimulationEnd=(HelpFunctions::TimeToInt(HelpFunctions::validateTimeInput("end")));
    if(tmpSimulationEnd <= getSimulationStart())
    {
        HelpFunctions::clrScreen();
        std::cout << "Error, can't set the end timer before the start timer.\n\n";
        return;
    }
    simulationEnd=tmpSimulationEnd;

    HelpFunctions::clrScreen();
    std::cout << "Simulation end time changed to " << HelpFunctions::IntToTime(simulationEnd) << ".\n\n";
}

//Start the simulation, load trains and create simulation menu
void Company::startSimulation()
{
    //Initialize simulation, import events and run until simulationStart
    theSim = new Simulation(simulationEnd);
    this->initialImport();
    theSim->runNextInterval(simulationStart);

    //printOrNot=true prevents the first interval (00:00->simulationStart) to not be recorded
    printOrNot=true;
    HelpFunctions::clrScreen();
    Menu simulationMenu;
    int menuChoice;

    do
    {
        //Set up simulation menu
        simulationMenu.createSimulationMenu(theSim->getTime(), interval, logLevel);
        simulationMenu.printTrainASCII();
        simulationMenu.printMenuItems();
        menuChoice=simulationMenu.getMenuChoice(0, 8);

        //Switch of menuChoice
        switch(menuChoice)
        {
        case 1: changeInterval();
                break;
        case 2: if(theSim->runNextInterval(interval) == false)
                {
                    finishSimulation();
                };
                break;
        case 3: HelpFunctions::clrScreen();
                if(theSim->nextEvent() == false)
                {
                    finishSimulation();
                }
                break;
        case 4: theSim->run();
                finishSimulation();
                break;
        case 5: changeLogLevel();
                break;
        case 6: runTrainMenu();
                break;
        case 7: runStationMenu();
                break;
        case 8: runVehicleMenu();
                break;
        case 0: HelpFunctions::clrScreen();
                break;

        default:std::cout << "Error, shouldn't happen.\n\n";
        }
    }while(menuChoice != 0);

    //Remove pointer to simulation if we exit to the startmenu
    delete theSim;
}

//Change the interval at which we can increment the events
void Company::changeInterval()
{
    HelpFunctions::clrScreen();
    std::cout << "What would you like to set the interval to (in minutes)?: ";
    std::string tmpString;
    getline(std::cin, tmpString);
    interval=HelpFunctions::validateInt(tmpString, 1, 1439);
    std::cout << "Interval changed to " << interval << " minutes.\n\n";
}

//Create and run the menu to change the log level
void Company::changeLogLevel()
{
    HelpFunctions::clrScreen();

    //Create and print menu
    Menu logLevelMenu;
    logLevelMenu.createLogLevelMenu(logLevel);
    logLevelMenu.printTrainASCII();
    logLevelMenu.printMenuItems();

    //Store logLevel in a temp string to know if the user changed the loglevel or not
    std::string tmpLogLevel=logLevel;

    //Get menu choice
    LogLevel menuChoice=static_cast<LogLevel>(logLevelMenu.getMenuChoice(0, 3));
    switch(menuChoice)
    {
        case Low:   logLevel="Low"; //1
                    break;
        case Normal:logLevel="Normal"; //2
                    break;
        case High:  logLevel="High"; //3
                    break;
        case LogLevelReturn: //0
                    HelpFunctions::clrScreen();
                    return;

        default:    std::cout << "Error, shouldn't happen.\n";
    }

    HelpFunctions::clrScreen();
    if(tmpLogLevel == logLevel)
    {
        std::cout << "Nothing changed.\n";
    }
    else
    {
        std::cout << "Log level changed from " << tmpLogLevel << " to " << logLevel << ".\n";
    }
}

//Create and run the finished simulation menu, with a bunch of statistics available
void Company::finishSimulation()
{
    do
    {
        //Set up and print menu
        Menu finishedMenu;
        finishedMenu.createFinishedMenu(logLevel);
        finishedMenu.printTrainASCII();
        finishedMenu.printMenuItems();

        int menuChoice=finishedMenu.getMenuChoice(0, 5);
        switch(menuChoice)
        {
            case 1: changeLogLevel();
                    break;
            case 2: printStatistics();
                    break;
            case 3: runTrainMenu();
                    break;
            case 4: runStationMenu();
                    break;
            case 5: runVehicleMenu();
                    break;
            case 0: HelpFunctions::clrScreen();
                    return;
            default:std::cout << "Error, shouldn't happen.\n";
        }
    }while(true);
}

//Create and runun the menu with train statistics
void Company::runTrainMenu()
{
    HelpFunctions::clrScreen();
    do
    {
        Menu trainMenu;
        trainMenu.createTrainMenu(logLevel);
        trainMenu.printTrainASCII();
        trainMenu.printMenuItems();

        TrainMenuChoice menuChoice=static_cast<TrainMenuChoice> (trainMenu.getMenuChoice(0, 4));
        switch(menuChoice)
        {
        case SearchTrainByNumber:   printTrainByNumber();
                                    break;
        case SearchTrainByVehicleID:printTrainByVehicleID();
                                    break;
        case ShowAllTrains:         printAllTrains();
                                    break;
        case TrainChangeLogLevel:   changeLogLevel();
                                    break;
        case TrainMenuReturn:       HelpFunctions::clrScreen();
                                    return;

        default:                    std::cout << "Error, shouldn't happen.\n";
        }
    }while(true);

}

//Create and run the menu with station statistics
void Company::runStationMenu()
{
    HelpFunctions::clrScreen();
    Menu stationMenu;
    do
    {
        stationMenu.createStationMenu(logLevel);
        stationMenu.printTrainASCII();
        stationMenu.printMenuItems();

        StationMenuChoice menuChoice=static_cast<StationMenuChoice> (stationMenu.getMenuChoice(0, 4));
        switch(menuChoice)
        {
        case ShowStationNames:      printAllStationNames();
                                    break;
        case ShowStationByName:     printStationByName();
                                    break;
        case ShowAllStations:       printAllStations();
                                    break;
        case StationChangeLogLevel: changeLogLevel();
                                    break;
        case StationMenuReturn:     HelpFunctions::clrScreen();
                                    return;

        default:                    std::cout << "Error, shouldn't happen.\n";
        }
    }while(true);

}

//Lets user input a station name, we search it and provide information about it
void Company::printStationByName() const
{
    HelpFunctions::clrScreen();
    std::cout << "Which station would you like to print? (search by name): ";
    std::string tmpString;
    getline(std::cin, tmpString);
    transform(tmpString.begin(), tmpString.end(), tmpString.begin(), ::tolower);
    for(auto it: trainStationVect)
    {
        std::string tmpString2=it.getStationName();
        transform(tmpString2.begin(), tmpString2.end(), tmpString2.begin(), ::tolower);
        if(tmpString == tmpString2)
        {
            it.printTrainStation(logLevel);
        }
    }
}

//Print out all station names
void Company::printAllStationNames() const
{
    HelpFunctions::clrScreen();
    for(auto &it: trainStationVect)
    {
        it.printTrainStation("Low");
    }
}

//Print out all stations, different loglevels provide different printout
void Company::printAllStations() const
{
    HelpFunctions::clrScreen();

    if(logLevel == "Low")
    {
        printAllStationNames();
        return;
    }

    if(logLevel == "Normal" || logLevel == "High")
    {
        for(auto &it: trainStationVect)
        {
            /*std::cout << "Station Name: " << it.getStationName() << "  -  {TypeOfVehicle, Vehicle-ID}" << std::endl;
            std::cout << "Vehicles: ";
            for(auto &it2: it.getVehicleVect())
            {
                std::cout << "{" << it2->getTypeOfVehicle() << ", " << it2->getIdNumber() << "} ";
            }
            std::cout << std::endl << std::endl;*/
            it.printTrainStation(logLevel);
        }
    }
}

//Runs the menu to print vehicles
void Company::runVehicleMenu()
{
    HelpFunctions::clrScreen();
    Menu vehicleMenu;
    do
    {
        vehicleMenu.createVehicleMenu(logLevel);
        vehicleMenu.printTrainASCII();
        vehicleMenu.printMenuItems();

        VehicleMenuChoice menuChoice=static_cast<VehicleMenuChoice> (vehicleMenu.getMenuChoice(0, 3));
        switch(menuChoice)
        {
        case ShowVehicleByID:       printVehicleByID();
                                    break;
        case ShowAllVehicles:       printAllVehicles();
                                    break;
        case VehicleChangeLogLevel: changeLogLevel();
                                    break;
        case VehicleMenuReturn:     HelpFunctions::clrScreen();
                                    return;

        default:                    std::cout << "Error, shouldn't happen.\n";
        }
    }while(true);

}

//Prints all vehicles
void Company::printAllVehicles()
{
    HelpFunctions::clrScreen();
    int counter=0;

    //Prints all vehicles that are at train stations
    for(auto &it: trainStationVect)
    {
        for(auto &it2: it.getVehicleVect())
        {
            if(++counter%50 == 0)
            {
                HelpFunctions::pressEnter();
            }
            it2->printVehicle(logLevel);
        }
    }

    //Prints all vehicles that are connected to a train
    for(auto &it: trainVect)
    {
        for(auto &it2: it.getVehicleVect())
        {
            //Checks to see that it is a real vehicle and not an abstract one
            if(it2->getIdNumber() != -1)
            {
                if(++counter%50 == 0)
                {
                    HelpFunctions::pressEnter();
                }
                it2->printVehicle(logLevel);
            }
        }
    }
}

//Search for vehicle and print info if successful
void Company::printVehicleByID()
{
    HelpFunctions::clrScreen();
    std::cout << "Which vehicle-ID would you like to find?: ";
    std::string tmpString;
    getline(std::cin, tmpString);
    int tmpInt=HelpFunctions::validateInt(tmpString, 1, 99999999);

    //Check for vehicle at Train Stations
    for(auto &it: trainStationVect)
    {
        for(auto &it2: it.getVehicleVect())
        {
            if(it2->getIdNumber() == tmpInt)
            {
                it2->printVehicle(logLevel);
                return;
            }
        }
    }
    //Check for vehicles attached to Trains
    for(auto &it: trainVect)
    {
        for(auto &it2: it.getVehicleVect())
        {
            if(it2->getIdNumber() == tmpInt)
            {
                it2->printVehicle(logLevel);
                return;
            }
        }
    }
    HelpFunctions::clrScreen();
    std::cout << "Couldn't find vehicle.\n\n";
}

//Search for Train and print info if successful
void Company::printTrainByNumber()
{
    HelpFunctions::clrScreen();
    std::cout << "Which train would you like to find? (search train number): ";
    std::string tmpString;
    getline(std::cin, tmpString);
    int tmpInt=HelpFunctions::validateInt(tmpString, 0, 9999999);
    for(auto &it: trainVect)
    {
        if(it.getTrainNumber() == tmpInt)
        {
            it.printTrain(logLevel);
            return;
        }
    }
    HelpFunctions::clrScreen();
    std::cout << "Couldn't find train.\n\n";
}

//Search for vehicle ID and print the Train it's attached to
void Company::printTrainByVehicleID()
{
    HelpFunctions::clrScreen();
    std::cout << "Which vehicle-ID would you like to find?: ";
    std::string tmpString;
    getline(std::cin, tmpString);
    int tmpInt=HelpFunctions::validateInt(tmpString, 1, 99999999);
    for(auto &it: trainVect)
    {
        for(auto &it2: it.getVehicleVect())
        {
            if(it2->getIdNumber() == tmpInt)
            {
                HelpFunctions::clrScreen();
                it.printTrain(logLevel);
                return;
            }
        }
    }
    HelpFunctions::clrScreen();
    std::cout << "Vehicle-ID not currently attached to any train.\n";
}

//Adjust arrival time if the train is delayed
int Company::calculateNewArrivalTime(int pmTrainNumber, int &pmVelocity)
{
    ptrdiff_t trainPos = getTrainPos(pmTrainNumber);

    std::string origin = trainVect[trainPos].getOrigin();
    std::string destination = trainVect[trainPos].getDestination();
    double delay = trainVect[trainPos].getDelay();
    double arrivalDelay = trainVect[trainPos].getArrivalDelay();
    double arrivalTime = trainVect[trainPos].getArrivalTime();
    double departureTime = trainVect[trainPos].getDepartureTime();
    double origArrivalTime = arrivalTime-delay;

    double distance=0;

    //Find distance between the two train stations
    for(auto &it: stationDistanceVect)
    {
        if( (it.getStation1() == origin && it.getStation2() == destination) ||
            (it.getStation2() == origin && it.getStation1() == destination) )
        {
            distance=it.getDistance();
            break;
        }
    }
    double newArrivalTime = arrivalTime;
    if(delay != 0)
    {
        //Calculate the new arrival time
        newArrivalTime=departureTime+((distance/pmVelocity)*60);
        if(newArrivalTime < origArrivalTime)
        {
            newArrivalTime = origArrivalTime;
        }
        //Calculate and set delay
        arrivalDelay=newArrivalTime-origArrivalTime;
        totalDelay+=arrivalDelay;
        trainVect[trainPos].setArrivalDelay(arrivalDelay);
    }

    //Calculate and set delay and velocity
    pmVelocity = static_cast<int> (distance / ((newArrivalTime-departureTime)/60));
    return static_cast<int> (newArrivalTime);
}

//A pretty messy and unnecessary function, but wanted to have the exact printout of the example presentation.
//Could've instead used my predefined functions, but since this is probably the only unnecessary function
//I hope you can forgive me :~)
void Company::printStatistics()
{
    HelpFunctions::clrScreen();

    std::cout << "Number of vehicles at start of simulation: \n";
    for(auto &it: backupTrainStationVect)
    {
        std::cout << it.getStationName() << " = " << it.getVehicleVect().size() << "\n";
    }

    std::cout << "\n\nNumber of vehicles at end of simulation: \n";
    for(auto &it: trainStationVect)
    {
        std::cout << it.getStationName() << " = " << it.getVehicleVect().size() << "\n";
    }

    std::cout << "\n\nTotal Delay: " << HelpFunctions::IntToTime(totalDelay);
    std::cout << "\nEnd time for simulation: " << HelpFunctions::IntToTime(theSim->getTime());

    int counter=0;
    for(auto &it: trainVect)
    {
        if(it.getState() == "INCOMPLETE")
        {
            counter++;
        }
    }

    std::cout << "\n\n\nTrains that never left the station (" << counter << "):\n";

    for(auto &it: trainVect)
    {
        if(it.getState() == "INCOMPLETE")
        {
            std::cout << "Train [" << it.getTrainNumber() << "] from " << it.getOrigin();
            std::cout << " " << HelpFunctions::IntToTime(it.getDepartureTime()-it.getDelay()) << " (";
            std::cout << HelpFunctions::IntToTime(it.getDepartureTime()) << ") to ";
            std::cout << it.getDestination() << " " << HelpFunctions::IntToTime(it.getArrivalTime()-it.getArrivalDelay());
            std::cout << " (" << HelpFunctions::IntToTime(it.getArrivalTime()) << ")\n\tVehicles:\n";

            for(auto &it2: it.getVehicleVect())
            {
                if(it2->getIdNumber() != -1)
                {
                    std::cout << "\t\t";
                    switch(it2->getTypeOfVehicle())
                    {
                        case 0: std::cout << "[Sitting Car] id: " << it2->getIdNumber() << ", Number of seats: " << it2->getParam0();
                                std::cout << ", Internet: ";
                                if(it2->getParam1() == 1)
                                {
                                    std::cout << "Yes\n";
                                }
                                else
                                {
                                    std::cout << "No\n";
                                }
                                break;
                        case 1: std::cout << "[Sleeping Car] id: " << it2->getIdNumber() << ", Number of beds: " << it2->getParam0() << std::endl;
                                break;
                        case 2: std::cout << "[Open Cargo] id: " << it2->getIdNumber() << ", Capacity: " << it2->getParam0() << " tonne, ";
                                std::cout << "Cargo size: " << it2->getParam1() << "m^2\n";
                                break;
                        case 3: std::cout << "[Closed Cargo] id: " << it2->getIdNumber() << ", Cargo volume: " << it2->getParam0() << "m^3.\n";
                                break;
                        case 4: std::cout << "[Electric Locomotive] id: " << it2->getIdNumber() << ", Max speed: " << it2->getParam0() << "km/h, ";
                                std::cout << "Power: " << it2->getParam1() << "kW.\n";
                                break;
                        case 5: std::cout << "[Diesel Locomotive] id: " << it2->getIdNumber() << ", Max speed: " << it2->getParam0() << "km/h, ";
                                std::cout << "Fuel consumption: " << it2->getParam1() << "l/h.\n";
                                break;
                        default:break;
                    }
                }
            }

            std::cout << "\tMissing vehicles: \n";
            for(auto &it2: it.getVehicleVect())
            {
                if(it2->getIdNumber() == -1)
                {
                    std::cout << "\t\t";
                    switch(it2->getTypeOfVehicle())
                    {
                        case 0: std::cout << "Sitting Car\n";
                                break;
                        case 1: std::cout << "Sleeping Car\n";
                                break;
                        case 2: std::cout << "Open Cargo\n";
                                break;
                        case 3: std::cout << "Closed Cargo\n";
                                break;
                        case 4: std::cout << "Electric Locomotive\n";
                                break;
                        case 5: std::cout << "Diesel Locomotive\n";
                                break;
                        default:break;
                    }
                }
            }
            std::cout << "\n\n";
        }
    }





    std::cout << "Delayed trains (";
    counter=0;
    for(auto &it: trainVect)
    {
        if(it.getArrivalDelay() > 0 && it.getState() != "INCOMPLETE")
        {
            counter++;
        }
    }
    std::cout << counter << "):\n";
    for(auto &it: trainVect)
    {
        if(it.getArrivalDelay() > 0 && it.getState() != "INCOMPLETE")
        {
            std::cout << "Train [" << it.getTrainNumber() << "] from " << it.getOrigin();
            std::cout << " " << HelpFunctions::IntToTime(it.getDepartureTime()-it.getDelay()) << " (";
            std::cout << HelpFunctions::IntToTime(it.getDepartureTime()) << ") to ";
            std::cout << it.getDestination() << " " << HelpFunctions::IntToTime(it.getArrivalTime()-it.getArrivalDelay());
            std::cout << " (" << HelpFunctions::IntToTime(it.getArrivalTime()) << ")\n";
            std::cout << "Starting Delay: " << HelpFunctions::IntToTime(it.getDelay()) << "\t";
            std::cout << "Arrival Delay: " << HelpFunctions::IntToTime(it.getArrivalDelay()) << "\n\n";
        }
    }
    std::cout << "\n";
}
