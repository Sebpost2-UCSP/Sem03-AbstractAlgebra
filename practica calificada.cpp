#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using std::string;

int main()
{
    string cadena;
    int size;
    std::cout << "Ingrese por teclado una cadena de caracteres:\n";
    //nose porque el cin no acepta espacios " " 
    std::cin >> cadena;
    std::cout << "\nIngrese por teclado el numero de caracteres que tendra cada bloque:\n";
    std::cin>> size;
    std::vector<string>a;
    int counter=0;
    string cadena1;
    for (int i = 0; i < cadena.length(); i++)
    {
        if (i*size + size <= cadena.length())
        {
            std::cout << cadena.substr((size*i), size) << "*";    
            a.push_back(cadena.substr(i *size, size));
        }
        else
        { 
            if (size + (i * size) == cadena.length())
            {
                break;
            }
            cadena1.append(cadena.substr(i * size, cadena.length() - (size + (i * size))));

            while (cadena1.length() != size)
            {
                cadena1 += "x";
            }
            std::cout << cadena1;
            a.push_back(cadena1);
        }
    }
    std::cout << "\nImprimiendo vector:\n";
    std::cout << "|";
    for (int i = 0; i < a.size(); i++)
    {
        std::cout << a[i]<<"|";
    }

}

