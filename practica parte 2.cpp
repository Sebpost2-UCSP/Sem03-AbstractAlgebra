#include <iostream>
#include <sstream>

int main()
{
    std::string A;
    int B=202;
    std::cout << "Ingrese un numero\n";
    std::cin >> A;
    std::stringstream change;
    change >> A;
    change << B;
    std::cout<<"\n";
    std::cout << A;
}

