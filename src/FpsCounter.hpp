// FpsCounter.hpp
#pragma once

#include <chrono>
#include <array>
#include <numeric>

class FpsCounter {
private:
    static constexpr int SAMPLE_COUNT = 100;
    std::array<double, SAMPLE_COUNT> frameTimes{};
    int currentIndex = 0;
    bool bufferFilled = false;
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

public:
    double update();
};