#include <iostream>
#include <iomanip>
#include "Headers/menu.h"

using namespace std;

    void DisplayMenu(){
        constexpr int INNER_WIDTH = 105;
    std::string horizontalBorder = "+" + std::string(INNER_WIDTH + 2, '-') + "+";

    std::cout << horizontalBorder << "\n";
    std::cout << "| " << std::string(INNER_WIDTH, ' ') << " |\n";

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
    std::cout << std::setw(68) << " Talent Hub \n";
    std::cout << std::setw(90) << "-----------------------------------------------------------------" << "\n \n";
    std::cout << std::setw(30) << "|     " << "1. Student Registration " << std::setw(17) << "|       " << "3. Student Login " << "  |" << "\n \n";
    std::cout << std::setw(90) << "-----------------------------------------------------------------" << "\n \n" ;
    std::cout << std::setw(30) << "|     " << "2. Admin  " << std::setw(32) << "|        " << "4. Exit" << "           |" << "\n \n";
    std::cout << std::setw(90) << "-----------------------------------------------------------------" << "\n \n";

    std::cout << "| " << std::string(INNER_WIDTH, ' ') << " |\n";

    std::cout << horizontalBorder << "\n";
    std::cout << std::setw(70) << "Enter your choice:  ";

    }

