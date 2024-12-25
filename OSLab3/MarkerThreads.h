#ifndef MARKERTHREADS_H
#define MARKERTHREADS_H

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>

class MarkerThreads {
public:
    MarkerThreads(int arraySize, int numThreads);
    ~MarkerThreads();

    void stopThread(int id);
    void waitForAllThreadsToPause();
    void resumeThreads();
    void printArray() const;

private:
    void markerThreadFunc(int id);

    int arraySize;
    int numThreads;
    std::vector<int> array;
    std::vector<std::thread> threads;
    std::vector<HANDLE> threadEvents;
    std::vector<std::vector<int>> markedIndices;
    std::atomic<bool> stopFlag;
    mutable std::mutex mtx;
    std::atomic<int> pausedThreads;
    std::atomic<int> stoppedThreads;
};

#endif