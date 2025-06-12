#ifndef TERMINAL_SETTINGS_H
#define TERMINAL_SETTINGS_H

#include <termios.h>
#include <unistd.h>

// wrapper class for changing terminal mode
class TerminalSettings {
public:
    TerminalSettings() {
        if(!initialized_) {
            tcgetattr(STDIN_FILENO, &oldt_);
            termios newt = oldt_;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            initialized_ = true;
        }
    }
    ~TerminalSettings() {
        restoreSettings();
    }
    static inline void restoreSettings() {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt_);  // Restores original settings
    }
private:
    inline static termios oldt_; // original settings
    inline static bool initialized_ = false;
};

#endif // TERMINAL_SETTINGS_H