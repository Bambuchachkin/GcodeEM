#include <iostream>
#include <string>
#include <vector>

#include "Parser.h"

std::string Consol_start() {
    std::cout << "Введите путь к преобразовываемому файлу: ";
    std::string file_name;
    std::cin >> file_name;
    return file_name;
}

void Consol_task(Parser &parser) {
    std::map<std::string, std::string> tasks;
    tasks["Standart_Numbers"] = " Пример: `1.` -> `1.0` ";
    tasks["Semicolon_Point"] = " Пример:  `aboba x y z` -> `aboba x y z;` ";
    tasks["From_G1_to_G01"] = " Пример: `G1` -> `G01` ";
    for (auto it = tasks.begin(); it!=tasks.end(); it++) {
        std::cout<<"Выполнить преобразование: " << it->first << it->second << "?" << '\n';
        std::cout << "ДА [y] / НЕТ [n]: ";
        char symbol = ' ';
        std::cin >> symbol;
        if (symbol == 'y') {
            parser.Add_New_Task(it->first);
        }
    }

}

int main() {
    Parser parser;

    std::string File_name = Consol_start();
    Consol_task(parser);

    // parser.Add_New_Task("Standart_Numbers"); // Эмитация task manager
    // parser.Delete_Task("Standart_Numbers");
    // parser.Add_New_Task("Semicolon_Point");
    // parser.Add_New_Task("From_G1_to_G01");

    try {
        parser.Pars_File(File_name);
        // parser.Pars_File("/home/bambuchachkin/CLionProjects/GcodeEM_0/Tests/Boba.txt");
    } catch (const char* error_message) { // Перенести в window
        std::cout<<error_message;
        return false;
    }
    return 0;
}