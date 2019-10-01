#pragma once;
#include <SDL2/SDL.h>



class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    float dTime;

    int elapsedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    void reset();
    void update();

    //Gets the timer's time
    int get_ticks();
    float deltaTime();
    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};