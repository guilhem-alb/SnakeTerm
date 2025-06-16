#include <chrono>
#include <iostream>
#include <thread>
#include <csignal>

#include "snake_game.hpp"
#include "terminal_settings.hpp"

void handleSigint(int sig_num) {
    TerminalSettings::restoreSettings();
    exit(128 + SIGINT); // termination code for SIGINT
}

int main() {
    const int kTargetFps = 8;
    const std::chrono::milliseconds kFrameDuration(1000/kTargetFps);
    std::signal(SIGINT, handleSigint);
    TerminalSettings ts;
    atexit(TerminalSettings::restoreSettings);

    SnakeGame game; // init game

    // game loop
    while(true) {
        auto frame_start = std::chrono::steady_clock::now();
        game.updateGame();
        auto frame_end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frame_end - frame_start); // calculate time between start and end of frame

        // to keep constant framerate
        if(elapsed < kFrameDuration) {
            std::this_thread::sleep_for(kFrameDuration - elapsed);
        }
        
    }

    // the program should never reach this point
    std::cout << "game loop ended unexpectedly";
    return EXIT_FAILURE;
}