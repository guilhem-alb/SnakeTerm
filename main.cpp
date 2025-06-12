#include <chrono>
#include <iostream>
#include <thread>

#include "snake_game.hpp"
#include "terminal_settings.hpp"
int main() {
    const int kTargetFps = 1;
    const std::chrono::milliseconds kFrameDuration(1000/kTargetFps);

    TerminalSettings ts;
    atexit(TerminalSettings::restoreSettings);
    SnakeGame game; // init game

    game.game_board_.print();
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