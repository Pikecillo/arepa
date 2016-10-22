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
