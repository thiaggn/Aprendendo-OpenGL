#include <iostream>
#include <string>

int main()
{
    std::string name;
    int age;

    std::cin >> name >> age;

    std::cout << "Bem vindo, " << name << "!" << std::endl;
    std::cout << "Voce certamente nasceu em " << (2024 - age) << " se ja tiver feito aniversario!" << std::endl;

    return 0;
}