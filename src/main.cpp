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
        std::cerr << "Usage: " << argv[0] << " [-m <minutes>] [-s <seconds>] [--no-beep]\n";
        return 1;
    }

    bool fbeep_state = true;
    unsigned int minutes = 0;
    unsigned int seconds = 0;
    unsigned int total_seconds = 0;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--no-beep") {
            fbeep_state = false;
        } else if (std::string(argv[i]) == "-m" && i + 1 < argc) {
            minutes = std::stoul(argv[i + 1]);
            i++;
        } else if (std::string(argv[i]) == "-s" && i + 1 < argc) {
            seconds = std::stoul(argv[i + 1]);
            i++;
        }
    }

    total_seconds = (minutes * 60) + seconds;

    cscreen();

    for (int i = static_cast<int>(total_seconds); i >= 0; --i) {
        int remaining_minutes = i / 60;
        int remaining_seconds = i % 60;

        std::cout << "\r" 
                  << std::setw(2) << std::setfill('0') << remaining_minutes 
                  << ":" 
                  << std::setw(2) << std::setfill('0') << remaining_seconds 
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
