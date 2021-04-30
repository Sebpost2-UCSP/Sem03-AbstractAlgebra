#include <iostream>
#include<time.h>
#include<vector>
#include <string>
using std::string;

//FUNCIONES MATEMATICAS
int mimodulo(int x, int y)
{
    int div = x / y;
    int modulo = -(div * y) + x;
    if (modulo < 0)
        modulo += y;
    return modulo;
}

int mcd(int x, int y)
{
    int modulo;
    while (y != 0)
    {
        modulo = mimodulo(x, y);
        x = y;
        y = modulo;
    }
    return x;
}

std::vector<int>mcdEx(int a, int b)
{
    std::vector<int>resultado;
    if (b == 0) {
        for (int i = 0; i < 3; i++)
            resultado.push_back(0);
        return resultado;
    }
    int r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1, q, r, s, t;
    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2; r2 = r;
        s = s1 - (q * s2);
        s1 = s2; s2 = s;
        t = t1 - (q * t2);
        t1 = t2; t2 = t;
    }
    resultado.push_back(r1);
    resultado.push_back(s1);
    resultado.push_back(t1);
    return resultado;
}

int inversa(int a, int b)
{
    int x;
    std::vector<int>EuclidesEx = mcdEx(a, b);
    x = EuclidesEx[1];
    if (x < 0)
    {
        x = mimodulo(x, b);
    }
    return x;
}

//ALGORITMO AFIN

class afin
{
private:
    int a;
    int b;
    int inva;
    string alfabeto;
    void generarclaves()
    {
        int x = 0, y = 0, size = 0;
        size = alfabeto.length();
        srand(time(NULL)); 
        while (x != 1)
        {
            y = mimodulo(rand(), 1000);
            x = mcd(size,y);
        }
        a = y; //mcd(a,alf.length())=1; b=random;
        b = mimodulo(mimodulo(rand(), 1000),size);
    }
public:

    //CONSTRUCTORES
    afin()
    {
        this->alfabeto="ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz1234567890-.";
        generarclaves();
    }
    afin(int a, int b, string alfabeto)
    {
        this->alfabeto = alfabeto;
        this->inva = inversa(a,alfabeto.length());
        this->b = b;
    }

    //GETTERS
    int getA() { return a; } 
    int getB() { return b; }
    string getAlf() { return alfabeto; }

    //CIFRADO Y DECIFRADO
    string cifrado(string msj)
    {
        string cifrado;
        int ubicacion;
        int code;
        for (int i = 0; i < msj.length(); i++)
        {
        ubicacion = alfabeto.find(msj[i]);
        code = (ubicacion * a) + b;
        code = mimodulo(code, alfabeto.length());
        cifrado += alfabeto[code];
        }
        return cifrado;
    }

    string descifrado(string msjci)
    {
        string descifrado;
        int ubicacion;
        int decode;
        for (int i = 0; i < msjci.length(); i++)
        {
            ubicacion = alfabeto.find(msjci[i]);
            decode = inva*(ubicacion - b);
            decode = mimodulo(decode, alfabeto.length());
            descifrado += alfabeto[decode];
        }
        return descifrado;
    }
  
};

int main()
{
    afin emisor;
    afin receptor(emisor.getA(), emisor.getB(), emisor.getAlf());
    std::cout << "\nclave a y b " << emisor.getA()<<" "<< emisor.getB();
    
    string msg = "VERY cool";
    string code = emisor.cifrado(msg);
    std::cout << "\ncifrado = " << code;
    string decode = receptor.descifrado(code);
    std::cout << "\ndescifrado = " << decode;
}
