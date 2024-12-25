#include "MarkerThreads.h"
#include <random>
#include <chrono>
#include <iostream>

MarkerThreads::MarkerThreads(int arraySize, int numThreads)
    : arraySize(arraySize), numThreads(numThreads), stopFlag(false), pausedThreads(0), stoppedThreads(0) {
    array.resize(arraySize, 0);
    markedIndices.resize(numThreads);
    threadEvents.resize(numThreads);

    for (int i = 0; i < numThreads; ++i) {
        threadEvents[i] = CreateEvent(NULL, TRUE, TRUE, NULL);
        threads.emplace_back(&MarkerThreads::markerThreadFunc, this, i);
    }
}

MarkerThreads::~MarkerThreads() {
    for (int i = 0; i < numThreads; ++i) {
        if (threads[i].joinable()) {
            stopThread(i);
        }
        CloseHandle(threadEvents[i]);
    }
}

void MarkerThreads::stopThread(int id) {
    if (id < 0 || id >= numThreads) {
        std::cerr << "Invalid thread ID." << std::endl;
        return;
    }

    stopFlag.store(true);
    SetEvent(threadEvents[id]);
    threads[id].join();
    stopFlag.store(false);

    {
        std::lock_guard<std::mutex> lock(mtx);
        for (int idx : markedIndices[id]) {
            array[idx] = 0;
        }
        markedIndices[id].clear();
        ++stoppedThreads;
    }

    std::cout << "Marker " << id << " stopped and cleared its marks." << std::endl;
}

void MarkerThreads::waitForAllThreadsToPause() {
    while (pausedThreads.load() + stoppedThreads.load() < numThreads) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void MarkerThreads::resumeThreads() {
    pausedThreads.store(0);
    for (auto& event : threadEvents) {
        SetEvent(event);
    }
}

void MarkerThreads::printArray() const {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Current array state: ";
    for (int val : array) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void MarkerThreads::markerThreadFunc(int id) {
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, arraySize - 1);

    while (true) {
        WaitForSingleObject(threadEvents[id], INFINITE);

        if (stopFlag.load()) break;

        int index = distribution(generator);

        {
            std::lock_guard<std::mutex> lock(mtx);
            if (array[index] != 0) {
                std::cout << "Marker " << id << ": cannot mark index " << index
                    << ", current value: " << array[index] << std::endl;
                if (WaitForSingleObject(threadEvents[id], 0) == WAIT_OBJECT_0) {
                    ResetEvent(threadEvents[id]);
                    pausedThreads.fetch_add(1);
                }
                continue;
            }
            else {
                array[index] = id + 1;
                markedIndices[id].push_back(index);
                std::cout << "Marker " << id << " marked index " << index << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        for (int idx : markedIndices[id]) {
            array[idx] = 0;
        }
        markedIndices[id].clear();
        std::cout << "Marker " << id << " stopped and cleared its marks." << std::endl;
    }
}
