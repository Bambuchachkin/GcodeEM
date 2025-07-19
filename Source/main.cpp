#include <iostream>
#include <string>
#include "Parser.h"

int main() {
    Parser parser;
    std::cout<<"ABOBA"<<'\n';
    parser.Pars_File_from_to("/home/bambuchachkin/CLionProjects/GcodeEM_0/Aboba.txt", "Aboba");
    std::cout<<'\n'<<"BOBA"<<'\n';
    parser.Pars_File_from_to("/home/bambuchachkin/CLionProjects/GcodeEM_0/Boba.txt", "Aboba");
    // std::string a = "aboba";
    // std::cout<<a[a.size()-3];
    // std::cout<<a.substr(a.size()-3, a.size()-1);
    return 0;
}