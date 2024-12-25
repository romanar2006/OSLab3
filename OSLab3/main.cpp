#include "MarkerThreads.h"
#include <iostream>

int main() {
    int arraySize, numThreads;

    std::cout << "Enter array size: ";
    std::cin >> arraySize;

    std::cout << "Enter number of marker threads: ";
    std::cin >> numThreads;

    MarkerThreads markerThreads(arraySize, numThreads);

    while (true) {
        markerThreads.waitForAllThreadsToPause();
        markerThreads.printArray();

        int threadId;
        std::cout << "Enter marker thread ID to terminate (or -1 to exit): ";
        std::cin >> threadId;

        if (threadId == -1) {
            break;
        }

        markerThreads.stopThread(threadId);

        markerThreads.printArray();
        markerThreads.resumeThreads();
    }

    std::cout << "All marker threads have stopped. Exiting program." << std::endl;

    return 0;
}
