#include <iostream>
#include <vector>
#include<time.h>

int mimodulo(int x, int y){
    int div = x / y;
    int modulo = -(div * y) + x;
    if (modulo < 0)
        modulo += y;
    return modulo;
}

int mcd(int x, int y){
    int modulo;
    while (y != 0)
    {
        modulo = mimodulo(x, y);
        x = y;
        y = modulo;
    }
    return x;
}

std::vector<int>mcdEx(int a, int b){
    std::vector<int>resultado;
    if (b == 0) {
        for (int i = 0; i < 3; i++)
            resultado.push_back(0);
        return resultado;
    }
    int r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1, q, r, s, t;
    while (r2 > 0){
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

int inversa(int a, int b){
    int x;
    std::vector<int>EuclidesEx = mcdEx(a, b);
    x = EuclidesEx[1];
    if (x < 0){
        x = mimodulo(x, b);
    }
    return x;
}

bool primo(int a) {
    if (a == 0 || a == 1)
        return false;
    else {
        for (int i = 2; i < a/2; i++) {
            if (a % i == 0) {
                return false;
            }
        }
    }
    return true;
}

int potenciamodular(int a, int p, int m) {
    int resultado = 1;
    if (mimodulo(p, 2) == 1) {
        resultado = a;
    }
    p = p / 2;
    while (p != 0) {
        a = mimodulo((a * a),m);
        if (mimodulo(p, 2) == 1) {
            resultado = mimodulo((resultado * a),m);
        }
        p = p / 2;
    }
    return resultado;
}

class RSA {
private:
    int q, p, ln;
    std::vector<int>privatekey;
public:
    int n;
    std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz1234567890-.";
    std::vector<int>publickey;
    RSA(){
        int q = 0, p = 0, x = 0, y = 0, e=0, d=0;
        srand(time(NULL));
        //creando q y p
        while (primo(q) == false) {
            q = mimodulo(rand(), 100);
        }
        while (primo(p) == false) {
            p = mimodulo(rand(), 100);
        }
        this->q = q; this->p = p;
        this->n = p * q; this->ln = (p - 1) * (q - 1);
        //creando e (clave publica)
        while (x != 1) {
            y=mimodulo(rand(),100);
            x = mcd(y, this->ln);
        }//e entre 1 y mcd(e,ln)=1
        x = 0;
        while (x != 1) {
            e = mimodulo((rand()+1),y);
            x = mcd(e, this->ln);
        }
        this->publickey.push_back(e);
        this->publickey.push_back(this->n);
        //creando d (clave privada)
        d = inversa(this->publickey[0], this->ln);
        this->privatekey.push_back(d);
        this->privatekey.push_back(this->n);
    }
    std::vector<int>cifrado(std::string msj, int key, int mod) {
        std::vector<int>cifrado;
        int ubicacion, code;
        for (int i = 1; i < msj.length()+1; i++)
        {
            ubicacion = this->alfabeto.find(msj[i-1]);
            ubicacion = potenciamodular(ubicacion, key,mod);
            code = potenciamodular(ubicacion, key,mod);
            cifrado.push_back(code);
            std::cout << "\ncifrado " << i << ": " << cifrado[i-1];
        }
        return cifrado;
    }
    std::string descifrado(std::vector<int> msjcifr) {
        std::string decode;
        for (int i = 0; i < msjcifr.size(); i++) {
            int ubicacion = 0;
            ubicacion = potenciamodular(msjcifr[i], this->privatekey[0], this->n);
            ubicacion = potenciamodular(ubicacion, this->privatekey[0], this->n);
            std::cout << "\ndescifrado " << i + 1 << ":" << ubicacion;
            decode += this->alfabeto[ubicacion];
        }
        return decode;
    }
};

int main()
{
    RSA receptor;
    RSA emisor;

    std::vector<int> cifrado;
    std::string descifrado;
    std::string msg= "Ii";

    cifrado=emisor.cifrado(msg, receptor.publickey[0], receptor.publickey[1]);
    descifrado = receptor.descifrado(cifrado);
    std::cout << "\ndescifrado: " << descifrado;
}
