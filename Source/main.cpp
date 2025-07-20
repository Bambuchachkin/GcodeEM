#include <iostream>
#include <string>
#include "Parser.h"

int main() {
    Parser parser;

    parser.Add_New_Task("Standart_Numbers"); // Эмитация task manager
    // parser.Delete_Task("Standart_Numbers");
    parser.Add_New_Task("Semicolon_Point");
    parser.Add_New_Task("From_G1_to_G01");

    try {
        parser.Pars_File("/home/bambuchachkin/CLionProjects/GcodeEM_0/Tests/Boba.txt");
    } catch (const char* error_message) { // Перенести в window
        std::cout<<error_message;
        return false;
    }
    return 0;
}