#include <iostream>
#include <string>
#include <iomanip>
#include <numeric>

int main() {
    // Total internal width required to frame the "WELCOME TO" block cleanly
    const int INNER_WIDTH = 105;
    std::string horizontalBorder = "+" + std::string(INNER_WIDTH + 2, '-') + "+";

    // Top border
    std::cout << horizontalBorder << "\n";
    std::cout << "| " << std::string(INNER_WIDTH, ' ') << " |\n"; // Top spacer

    std:: cout << R"(
     |          _ _ _  ______   __      _____   ___     ___  ___  ______       _____    ___            |
     |         | | | | | ____  |  |    / /    // _ \\  |  \\//  | | ____      | --- | // _ \\          |
     |         | | | | | |___  |  |___ | |   || |-| || | | || | | | |___        | |  || |-| ||         |
     |         |_____| |______ |__|___ \_\___ \\___//  |_|\\//|_| |______       |_|   \\___//          |
     |           _____     _       _       ______  _   _  _______      _    _ _    _ ____              |
     |          |_   _|   / \     | |     |  ____ | \ | ||__   __|    | |  | | |  | |  _ \             |
     |            | |    / _ \    | |     | |__   |  \| |   | |       | |__| | |  | | |_) |            |
     |            | |   / ___ \   | |     |  __|  | . ` |   | |       |  __  | |  | |  _ <             |
     |            | |  /_/   \_\  | |____ | |____ | |\  |   | |       | |  | | |__| | |_) |            |
     |            |_| / /     \ \ |______ |______ |_| \_|   |_|       |_|  |_|\____/|____/             |
     |                                                                                                 |
     |                                                                                                 |
     |                               Connecting skills with opportunity                                |
     |                                                                                                 |
)";

    std::cout << "| " << std::string(INNER_WIDTH, ' ') << " |\n";
    std::cout << horizontalBorder << "\n";

    std::cout << "| " << std::string(INNER_WIDTH, ' ') << " |\n";
    std::cout << std::setw(60) << " Why are you here ?" << "\n";
    std::cout << std::setw(80) << "-----------------------------------------------------------------" << "\n" << "\n";
    std::cout << std::setw(20) << "|     " << "1. Student Registration " << std::setw(17) << "|       " << "3. Student Login " << "  |" << "\n" "\n";
    std::cout << std::setw(80) << "-----------------------------------------------------------------" << "\n" << "\n" ;
    std::cout << std::setw(20) << "|     " << "2. Admin Login " << std::setw(27) << "|        " << "4. Exit" << "           |" << "\n" "\n";
    std::cout << std::setw(80) << "-----------------------------------------------------------------" << "\n";

    std::cout << "| " << std::string(INNER_WIDTH, ' ') << " |\n";



    std::cout << horizontalBorder << "\n";





    return 0;
}
