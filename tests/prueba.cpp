#include <iostream>

int main(){
    std::string aux = "lastname = null";
    auto name = aux.substr(aux.find_last_of(' ')+1,aux.back());
    std::cout << name << std::endl;
}