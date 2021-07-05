#include <iostream>

#include "Tester/tester.h"
//#include "Parser/parser.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;

    Tester::executeExamples();
    Tester::executeParserPeru();

    return EXIT_SUCCESS;
}
