#include <iostream>
#include <string>
#include <vector>

#include "Parser.h"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

#ifdef _WIN32
#include <windows.h> // Для отображения русского текста в консоли windows
#endif

std::string Consol_start() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#else
    std::locale::global(std::locale("ru_RU.utf8"));
    std::cout.imbue(std::locale());
#endif

    std::cout << "Введите путь к преобразовываемому файлу: ";
    std::string file_name;
    std::cin >> file_name;
    Boba:
    for (int i = 0; i!=file_name.size();i++) {
        if (file_name[i] == '"') {
            file_name.erase(i,1);
            goto Boba;
        }
    }
    return file_name;
}

void Consol_task(Parser &parser) {
    std::map<std::string, std::string> tasks;
    tasks["Standart_Numbers"] = " Пример: `1.` -> `1.0` ";
    tasks["Semicolon_Point"] = " Пример:  `aboba x y z` -> `aboba x y z;` ";
    tasks["From_G1_to_G01"] = " Пример: `G1` -> `G01` ";
    tasks["The_Ending_Symbol"] = " Пример: `M02` ";
    for (auto it = tasks.begin(); it!=tasks.end(); it++) {
        std::cout<<"Выполнить преобразование: " << YELLOW << it->first << RESET << it->second << "?" << '\n';
        std::cout << GREEN << "ДА [y]" << RED << " / НЕТ [n]: "<<RESET;
        char symbol = ' ';
        while (symbol!='y' && symbol!='n') {
            std::cin >> symbol;
            if (symbol == 'y') {
                parser.Add_New_Task(it->first);
            } else if (symbol != 'n') {
                std::cout<<RED<< "A bad symbol, please repeat"<<'\n'<<RESET;
            }
        }
    }

}

int main() {
    try {
    Parser parser;

    std::string File_name = Consol_start();
    Consol_task(parser);

    // parser.Add_New_Task("Standart_Numbers"); // Эмитация task manager
    // parser.Delete_Task("Standart_Numbers");
    // parser.Add_New_Task("Semicolon_Point");
    // parser.Add_New_Task("From_G1_to_G01");


        parser.Pars_File(File_name);
        // parser.Pars_File("/home/bambuchachkin/CLionProjects/GcodeEM_0/Tests/Boba.txt");
    } catch (const char* error_message) { // Перенести в window
        std::cout<<RED<<'\n'<<error_message<<'\n' << RESET;
        // return false;
    }

    std::cout << '\n' <<"Введите любой текст для завершения работы программы"<<'\n';
    std::string end;
    std::cin >> end;
    return 0;
}