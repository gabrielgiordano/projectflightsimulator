#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <cstddef>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

class Stopwatch
{
public:
    Stopwatch();
    ~Stopwatch();

    void start();
    void stop();
    bool isStopped() const;

    double getElapsedMicroseconds();
    double getElapsedMilliseconds();
    double getElapsedSeconds();

private:
    bool _isStopped;

#ifdef WIN32
    LARGE_INTEGER _start;
    LARGE_INTEGER _end;
    LARGE_INTEGER _freq;
#else
    timeval _start;
    timeval _end;
#endif

};

#endif // STOPWATCH_H
