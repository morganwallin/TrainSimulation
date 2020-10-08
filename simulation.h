/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    simulation.h
    Declarations for the Simulation Class. The Simulation Class manipulates
    the Events in priority_queue.
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include <vector>
#include "event.h"
#include "helpfunctions.h"

class Simulation {
private:
    //Members
    int endTime;
    int currentTime;
    std::priority_queue<Event*, std::vector<Event*>, EventComparison> eventQueue;

public:
    //Constructors
    Simulation (int pmEndTime) : endTime(pmEndTime), currentTime(0), eventQueue() { }
    ~Simulation();

    //Member functions
    void run();
    void scheduleEvent (Event *newEvent);
    bool nextEvent();
    bool runNextInterval(int pmInterval);

    //Getters
    int getTime() const { return currentTime;}
    int getEndTime() const {return endTime;}
};

#endif
