#include <arepa/Timer.h>

Timer::Timer() : m_is_active(false) {}

void Timer::start() {
    m_is_active = true;
    m_begin = std::chrono::system_clock::now();
}

double Timer::stop() {
    m_end = std::chrono::system_clock::now();
    m_is_active = false;

    std::chrono::duration<double> elapsed_sec = m_end - m_begin;

    return elapsed_sec.count() * 1000.0;
}

bool Timer::is_active() const {
    return m_is_active;
}
