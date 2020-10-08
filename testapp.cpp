#include "testapp.h"

TestApp::TestApp()
{
    simulationStart=0;
    simulationEnd=1439;
    interval=10;
    logLevel="Low";
}

void TestApp::run()
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
                break;
        case 0: break;

        default:std::cout << "Error, shouldn't happen.\n\n";
        }

    //Uppdatera menyn så att start/end-time blir rätt
    startMenu.createStartMenu(simulationStart, simulationEnd);
    }while(menuChoice != 0);
}

void TestApp::changeSimulationStart()
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

void TestApp::changeSimulationEnd()
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

void TestApp::startSimulation()
{
    Simulation *theSim = new Simulation(simulationEnd);
    Company *theCompany = new Company(theSim);
    theCompany->initialImport();
    theSim->runNextInterval(simulationStart);
    theCompany->setPrintOrNot(true);
    HelpFunctions::clrScreen();
    Menu simulationMenu;
    int menuChoice;
    do
    {
        simulationMenu.createSimulationMenu(theSim->getTime(), interval, logLevel);
        simulationMenu.printTrainASCII();
        simulationMenu.printMenuItems();
        menuChoice=simulationMenu.getMenuChoice(0, 8);
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
}

void TestApp::changeInterval()
{
    HelpFunctions::clrScreen();
    std::cout << "What would you like to set the interval to (in minutes)?: ";
    std::string tmpString;
    getline(std::cin, tmpString);
    interval=HelpFunctions::validateInt(tmpString, 1, 1439);
    std::cout << "Interval changed to " << interval << " minutes.\n\n";
}

void TestApp::changeLogLevel()
{
    HelpFunctions::clrScreen();

    Menu logLevelMenu;
    logLevelMenu.createLogLevelMenu(logLevel);
    logLevelMenu.printTrainASCII();
    logLevelMenu.printMenuItems();
    std::string tmpLogLevel=logLevel;

    LogLevel menuChoice=static_cast<LogLevel>(logLevelMenu.getMenuChoice(0, 3));
    switch(menuChoice)
    {
        case Low:   logLevel="Low";
                    break;
        case Normal:logLevel="Normal";
                    break;
        case High:  logLevel="High";
                    break;
        case LogLevelReturn:
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

void TestApp::finishSimulation()
{
    Menu finishedMenu;
    do
    {
        finishedMenu.createFinishedMenu(logLevel);
        finishedMenu.printTrainASCII();
        finishedMenu.printMenuItems();

        int menuChoice=finishedMenu.getMenuChoice(0, 5);
        switch(menuChoice)
        {
            case 1: changeLogLevel();
                    break;
            case 2: //printStatistics();
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

void TestApp::runTrainMenu()
{
    HelpFunctions::clrScreen();
    Menu trainMenu;
    do
    {
        trainMenu.createTrainMenu(logLevel);
        trainMenu.printTrainASCII();
        trainMenu.printMenuItems();

        TrainMenuChoice menuChoice=static_cast<TrainMenuChoice> (trainMenu.getMenuChoice(0, 4));
        switch(menuChoice)
        {
        case SearchTrainByNumber:   //searchTrainByNumber();
                                    break;
        case SearchTrainByVehicleID://searchTrainByVehicleID();
                                    break;
        case ShowAllTrains:         theCompany->showAllTrains();
                                    break;
        case TrainChangeLogLevel:   changeLogLevel();
                                    break;
        case TrainMenuReturn:       HelpFunctions::clrScreen();
                                    return;

        default:                    std::cout << "Error, shouldn't happen.\n";
        }
    }while(true);

}

void TestApp::runStationMenu()
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
        case ShowStationNames:      //showStationNames();
                                    break;
        case ShowStationByName:     //showStationByName();
                                    break;
        case ShowAllStations:       //showAllStations();
                                    break;
        case StationChangeLogLevel: changeLogLevel();
                                    break;
        case StationMenuReturn:     HelpFunctions::clrScreen();
                                    return;

        default:                    std::cout << "Error, shouldn't happen.\n";
        }
    }while(true);

}

void TestApp::runVehicleMenu()
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
        case ShowVehicleByID:        //showVehicleByID();
                                    break;
        case ShowAllVehicles:       //showAllVehicles();
                                    break;
        case VehicleChangeLogLevel: changeLogLevel();
                                    break;
        case VehicleMenuReturn:     HelpFunctions::clrScreen();
                                    return;

        default:                    std::cout << "Error, shouldn't happen.\n";
        }
    }while(true);

}

