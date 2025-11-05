// FpsCounter.cpp
#include "FpsCounter.hpp"

double FpsCounter::update() {
    auto now = std::chrono::steady_clock::now();
    double deltaTime = std::chrono::duration<double>(now - lastTime).count();
    lastTime = now;

    frameTimes[currentIndex] = deltaTime;
    currentIndex = (currentIndex + 1) % SAMPLE_COUNT;

    if (!bufferFilled && currentIndex == 0) {
        bufferFilled = true;
    }

    int count = bufferFilled ? SAMPLE_COUNT : currentIndex;
    double avgDelta = std::accumulate(frameTimes.begin(), frameTimes.begin() + count, 0.0) / count;

    return avgDelta > 0.0 ? 1.0 / avgDelta : 0.0;
}