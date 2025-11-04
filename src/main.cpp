#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>
#include <cstdlib>

void cscreen() {
    static constexpr const char* CLEAR_SCREEN_ANSI = "\033[1;1H\033[2J";
    std::cout << CLEAR_SCREEN_ANSI << std::flush;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <seconds> [--no-beep]\n";
        return 1;
    }

    unsigned int input_seconds = 0;
    bool fbeep_state = true;
    for (int i = 2; i < argc; ++i) {
        if (std::string(argv[i]) == "--no-beep") {
            fbeep_state = false;
        }
    }

    try {
        input_seconds = std::stoul(argv[1]);
    } catch (...) {
        std::cerr << "ERROR: Invalid Argument.\n";
        return 1;
    }

    cscreen();

    for (int i = static_cast<int>(input_seconds); i >= 0; --i) {
        int minutes = i / 60;
        int seconds = i % 60;

        std::cout << "\r" 
                  << std::setw(2) << std::setfill('0') << minutes 
                  << ":" 
                  << std::setw(2) << std::setfill('0') << seconds 
                  << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\r00:00";

    if (fbeep_state) {
        try {
            std::system("play -q -n synth 0.1 sin 880 2>/dev/null &");
        } catch (...) {
            std::cerr << "\nWARNING: Beep alarm execution unavailable. Install Sound eXchange (sox) to activate it.";
        }
    }

    std::cout << "\n\033[1;32mFINISHED!\033[0m\n";

    return 0;
}
