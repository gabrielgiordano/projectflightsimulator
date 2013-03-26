#include "../headers/stopwatch.h"

Stopwatch::Stopwatch() {

#ifdef WIN32
    QueryPerformanceFrequency(&_freq);
    _start.QuadPart = 0;
    _end.QuadPart = 0;
#else
    _start.tv_sec = 0;
    _start.tv_usec = 0;
    _end.tv_sec = 0;
    _end.tv_usec = 0;

#endif

    _isStopped = true;
}

Stopwatch::~Stopwatch() {
}

void Stopwatch::start() {
#ifdef WIN32
    QueryPerformanceCounter(&_start);
#else
    gettimeofday(&_start, NULL);
#endif
    _isStopped = false;
}

void Stopwatch::stop() {
#ifdef WIN32
    QueryPerformanceCounter(&_end);
#else
    gettimeofday(&_end, NULL);
#endif

    _isStopped = true;
}

bool Stopwatch::isStopped() const {
    return _isStopped;
}

double Stopwatch::getElapsedMicroseconds() {
    double microSecond = 0;

    if(!_isStopped) {
#ifdef WIN32
        QueryPerformanceCounter(&_end);
#else
        gettimeofday(&_end, NULL);
#endif
    }

#ifdef WIN32
    if(_start.QuadPart != 0 && _end.QuadPart != 0) {
        microSecond = (_end.QuadPart - _start.QuadPart) * (1000000.0 / _freq.QuadPart);
    }
#else
    microSecond = (_end.tv_sec * 1000000.0 + _end.tv_usec) - (_start.tv_sec * 1000000.0 + _start.tv_usec);
#endif

    return microSecond;
}

double Stopwatch::getElapsedMilliseconds() {
    return getElapsedMicroseconds() / 1000.0;
}

double Stopwatch::getElapsedSeconds() {
    return getElapsedMicroseconds() / 1000000.0;
}
