#pragma once

#include <chrono>

class Timer {
public:
    Timer();
    
    void start();
    
    double stop();

    bool is_active() const;
    
private:
    bool m_is_active;
    std::chrono::time_point<std::chrono::system_clock> m_begin, m_end;
};

inline
Timer::Timer() : m_is_active(false) {}

inline
void Timer::start() {
    m_is_active = true;
    m_begin = std::chrono::system_clock::now();
}

inline
double Timer::stop() {
    m_end = std::chrono::system_clock::now();
    m_is_active = false;

    std::chrono::duration<double> elapsed_sec = m_end - m_begin;

    return elapsed_sec.count() * 1000.0;
}

inline
bool Timer::is_active() const {
    return m_is_active;
}
