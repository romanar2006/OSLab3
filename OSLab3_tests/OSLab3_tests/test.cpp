#include "../../OSLab3/MarkerThreads.h"
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <chrono>

void shortWait() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

TEST(MarkerThreadsTest, InitializationTest) {
    MarkerThreads markerThreads(10, 3);

    markerThreads.printArray();
}

TEST(MarkerThreadsTest, StopThreadTest) {
    MarkerThreads markerThreads(10, 3);

    shortWait(); 

    markerThreads.stopThread(1);

    shortWait(); 

    markerThreads.printArray(); 
}

TEST(MarkerThreadsTest, PauseAndResumeTest) {
    MarkerThreads markerThreads(10, 3);

    shortWait();

    markerThreads.waitForAllThreadsToPause();

    markerThreads.printArray();

    markerThreads.resumeThreads();
    shortWait();

    markerThreads.printArray();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


#include "pch.h"