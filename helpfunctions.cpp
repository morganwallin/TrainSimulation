/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    helpfunctions.cpp
    Definitions for the HelpFunctions Class. Contains static member functions,
    constants and enums.
*/

#include "helpfunctions.h"

//Clears the screen, cross platform
void HelpFunctions::clrScreen()
{
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
	std::cout << "\033[2J\033[1;1H" << std::endl;
#elif _WIN32
	system("cls");
#else
	std::cout << std::string(100, '\n');
#endif
}

//Tells the user to press enter (used to avoid too much scrolling)
void HelpFunctions::pressEnter()
{
    std::cout << "Press ENTER...";
    std::cin.get();
    clrScreen();
}

//Validates that pmString is an integer in the range pmMin-pmMax
int HelpFunctions::validateInt(std::string pmString, int pmMin, int pmMax)
{
    std::stringstream ss(pmString);
    int tmpInt=0;
    do
    {
        if(ss >> tmpInt && tmpInt >= pmMin && tmpInt <= pmMax)
        {
            break;
        }
        else
        {
            std::cout << "Wrong input, input an integer between " << pmMin << " and " << pmMax << ": ";
            getline(std::cin, pmString);
            std::stringstream().swap(ss);
            ss << pmString;
        }

    }while(true);
    return tmpInt;
}

//Validates that the user has put in a time in "HH:MM"
std::string HelpFunctions::validateTimeInput(std::string whatToChange)
{
    int hour=0, minute=0;
    std::string userInput, tmpString;

    while(true)
    {
        std::cout << "New simulation " << whatToChange << " time (HH:MM): ";
        getline(std::cin, userInput);
        std::stringstream ss(userInput);

        //Check if userInput is a correct time input
        if(ss >> hour && hour >= 0 && hour < 24)
        {
            getline(ss, userInput, ':');

            //Removes for example "20a:00"
            if(userInput.size() > 0){continue;}

            //Checks that minute is < 60 and there are no lingering strings left in the stringstream
            if(ss >> minute && minute >= 0 && minute < 60 && ss.rdbuf()->in_avail() == 0) {break;}
            else {continue;}
        }
        else {continue;}
    }

    if(hour < 10){tmpString = "0";}
    tmpString += std::to_string(hour) + ':';

    if(minute < 10){tmpString += "0";}
    tmpString+= std::to_string(minute);

    return tmpString;
}

//Transfers "HH:MM" to an integer
int HelpFunctions::TimeToInt(std::string pmTime)
{
    std::string tmpString;
    std::stringstream ss(pmTime);

    int hour;
    ss >> hour;
    getline(ss, tmpString, ':');

    int minute;
    ss >> minute;

    int tmpInt=(hour*60)+minute;
    return tmpInt;
}

//Transfers an integer to "HH:MM"
std::string HelpFunctions::IntToTime(int pmInt)
{
    int hour=pmInt/60;
    int minute=pmInt-(hour*60);

    //If time goes past 23:59, we substract to get a correct time
    if(hour > 23)
    {
        hour-=24;
    }
    if(minute > 59)
    {
        minute-=60;
    }

    //Add zeros if hour/minute < 10
    std::string time;
    if(hour < 10)
    {
        time="0";
    }
    time+=std::to_string(hour) + ':';
    if(minute < 10)
    {
        time+="0";
    }
    time+=std::to_string(minute);
    return time;
}
