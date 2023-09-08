#include <iostream>
#include <vector>
#include <random>
#include <chrono>

template <typename T>
std::vector<T> randomize(const int& count) {
    //В качестве ГПСЧ используется Вихрь Мерсенна (С++11)
    //https://en.wikipedia.org/wiki/Mersenne_Twister
    //Или тут
    //https://ravesli.com/urok-71-generatsiya-sluchajnyh-chisel-funktsii-srand-i-rand/
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> d(static_cast<T>(0.0), static_cast<T>(1.0));

    std::vector<T> result;
    result.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        result.push_back(d(gen));
    }

    return result;
}

template <typename T>
void simpleMovingAverage(std::vector<T>& result, const std::vector<T>& data, const int& windowSize) {
    result.clear();
    result.reserve(data.size() - windowSize + 1);

    int count = 0;
    T sum = 0.0;

    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
        ++count;

        if (i >= windowSize) {
            sum -= data[i - windowSize];
        }

        if (i >= windowSize - 1) {
            result.push_back(sum / windowSize);
        }
    }
}

int main() {
    const int dataSize = 1000000;
    auto floatVec = randomize<float>(dataSize);
    auto doubleVec = randomize<double>(dataSize);
    const auto floatVecSize = floatVec.size();
    const auto doubleVecSize = doubleVec.size();

    const int windowSizes[]{ 4, 8, 16, 32, 64, 128 };

    for (const auto& windowSize : windowSizes) {
        std::cout << "Window Size Performance: " << windowSize << std::endl;

        auto startFloat = std::chrono::high_resolution_clock::now();
        std::vector<float> floatSMA;
        simpleMovingAverage(floatSMA, floatVec, windowSize);
        auto endFloat = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> floatDuration = endFloat - startFloat;
        std::cout << "Float: " << floatVecSize / floatDuration.count() << " counted/sec\n";

        auto startDouble = std::chrono::high_resolution_clock::now();
        std::vector<double> doubleSMA;
        simpleMovingAverage(doubleSMA, doubleVec, windowSize);
        auto endDouble = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> doubleDuration = endDouble - startDouble;
        std::cout << "Double: " << doubleVecSize / doubleDuration.count() << " counted/sec\n";
        std::cout << '\n';
    }

    return 0;
}