#include <iostream>
#include <sstream>

int main()
{
    std::string A;
    int B;
    std::cout << "Ingrese un numero\n";
    std::cin >> A;
    std::stringstream change;
    change << A;
    change >> B;
    std::cout<<"\n";
    std::cout << A;
}

