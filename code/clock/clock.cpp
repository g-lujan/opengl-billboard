#include "clock.hpp"

Clock CLOCK;

Clock::Clock(): now_{SDL_GetPerformanceCounter()}, 
                last_{0}, 
                delta_{0.f} 
{}

void Clock::update_delta() {
    last_ = now_;
    now_ = SDL_GetPerformanceCounter();
    delta_ =  (now_ - last_) / (float)SDL_GetPerformanceFrequency();
}