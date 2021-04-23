#include <iostream>
#include <string>
using std::string;

string alfabeto = "abcdefghijklmnopqrstuvwxyz "; //el alfabeto es global

int mimodulo(int x, int y) //es para que el modulo siempre sea positivo
{
    int div = x / y;
    int modulo = -(div * y) + x;
    if (modulo < 0)
        modulo += y;
    return modulo;
}

class chat
{
private:
    int clave;
public:
    void setclave(int a) //crea la clave
    {
        clave = a;
    }
    int checkalfabeto(string mensaje) //se asegura de que todas las letras formen parte del alfabeto
    {
        for (string::const_iterator i = mensaje.begin(); i != mensaje.end(); i++)
        {
            if(alfabeto.find(*i) == -1)
            {
                return 0;
            }
        }
        return 1;
    }
    string codificar(string mensaje) //find(letra del mensaje + clave) % length de alfabeto
    {
        string code;
        if (checkalfabeto(mensaje) == 1)
        {
            for (string::const_iterator i = mensaje.begin(); i != mensaje.end(); i++)
            {
                code+=alfabeto[mimodulo(alfabeto.find(*i)+clave, alfabeto.length())];
            }
            return code;
        }
        else
        {
            std::cout << "\nNo todas las letras forman parte del alfabeto\n";
            return code;
        }
    }
    string decodificar(string mensajecod) //find(letra del mensaje - clave) % length de alfabeto
    {
        string decode;
        if (checkalfabeto(mensajecod) == 1)
        {
            for (string::const_iterator i = mensajecod.begin(); i != mensajecod.end(); i++)
            {
                decode += alfabeto[mimodulo(alfabeto.find(*i) - clave, alfabeto.length())];
            }
            return decode;
        }
        else
        {
            std::cout << "\nNo todas las letras forman parte del alfabeto\n";
            return decode;
        }
    }
};

void criptoanalisis(string codigo) //prueba con todas las claves posibles e imprime los resultados
{
    chat hack;
    int counter = 1;
    std::cout << "\n Cripto analisis: \n";
    while (counter != alfabeto.length())
    {
        string decode;
        hack.setclave(counter);
        decode=hack.decodificar(codigo);
        std::cout << "\n Clave: " << counter << " mensaje: " << decode << "\n";
        counter++;
    }
}

int main()
{
    string msg = "hello world how are you doing today";
    string code;
    string decode;
    chat emisor; 
    emisor.setclave(3);
    chat receptor;
    receptor.setclave(3);
    code = emisor.codificar(msg);
    std::cout << "\nCifrado: " << code;
    decode = receptor.decodificar(code);
    std::cout << "\nDecifrado: " << decode<<"\n";
    criptoanalisis(code);
}