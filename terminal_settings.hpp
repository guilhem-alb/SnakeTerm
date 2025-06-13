#ifndef TERMINAL_SETTINGS_H
#define TERMINAL_SETTINGS_H

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// wrapper class for changing terminal mode
class TerminalSettings {
public:
    TerminalSettings() {
        if(!initialized_) {
                
            std::cout << "\x1b[?25l"; // Hide cursor
            tcgetattr(STDIN_FILENO, &oldt_); // save flags
            termios newt = oldt_;
            newt.c_lflag &= ~(ICANON | ECHO); // flags are : no waiting for enter, no echo, and no waiting for input (in read())
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            oldf_ = fcntl(STDIN_FILENO, F_GETFL, 0); // save file status
            fcntl(STDIN_FILENO, F_SETFL, oldf_ | O_NONBLOCK);
            initialized_ = true;
        }
    }
    ~TerminalSettings() {
        restoreSettings();
    }
    static inline void restoreSettings() { // Reloads old settings
        std::cout << "\x1b[?25h"; // Show cursor
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt_);
        fcntl(STDIN_FILENO, F_SETFL, oldf_);  

    }
private:
    inline static int oldf_; // original file descriptor settings
    inline static termios oldt_; // original terminal settings
    inline static bool initialized_ = false;
};

#endif // TERMINAL_SETTINGS_H