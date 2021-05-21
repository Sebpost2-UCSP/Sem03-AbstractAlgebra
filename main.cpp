#include <iostream>
#include <vector>
#include<time.h>
#include<NTL/ZZ.h>
using namespace NTL;

ZZ mimodulo(ZZ x, ZZ y){
    ZZ div = x / y;
    ZZ modulo = -(div * y) + x;
    if (modulo < 0)
        modulo += y;
    return modulo;
}

ZZ mcd(ZZ x, ZZ y){
    ZZ modulo;
    while (y != 0)
    {
        modulo = mimodulo(x, y);
        x = y;
        y = modulo;
    }
    return x;
}

std::vector<ZZ>mcdEx(ZZ a, ZZ b){
    std::vector<ZZ>resultado;
    if (b == 0) {
        for (int i = 0; i < 3; i++)
            resultado.push_back(ZZ(0));
        return resultado;
    }
    ZZ r1, r2, s1, s2, t1, t2, q, r, s, t;
    r1 = a; r2 = b; s1 = 1; s2 = 0; t1 = 0; t2 = 1;
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

ZZ inversa(ZZ a, ZZ b){
    ZZ x;
    std::vector<ZZ>EuclidesEx = mcdEx(a, b);
    x = EuclidesEx[1];
    if (x < 0){
        x = mimodulo(x, b);
    }
    return x;
}

bool primo(ZZ a) {
    if (a == 0 || a == 1)
        return false;
    else {
        ZZ i;
        for (i = 2; i < a/2; i++) {
            if (a % i == 0) {
                return false;
            }
        }
    }
    return true;
}

ZZ potenciamodular(ZZ a, ZZ p, ZZ m) {
    ZZ resultado; resultado=1;
    if (mimodulo(p, ZZ(2)) == ZZ(1)) {
        resultado = a;
    }
    p = p / 2;
    while (p != 0) {
        a = mimodulo((a * a),m);
        if (mimodulo(p, ZZ(2)) == ZZ(1)) {
            resultado = mimodulo((resultado * a),m);
        }
        p = p / 2;
    }
    return resultado;
}

class RSA {
private:
    ZZ q, p, ln;
    std::vector<ZZ>privatekey;
public:
    ZZ n;
    std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz1234567890-.";
    std::vector<ZZ>publickey;
    RSA(){
        ZZ q,p,x,y,e,d; q = 0; p = 0; x = 0; y = 0; e=0; d=0;
        srand(time(NULL));
        //creando q y p
        while (primo(q) == false) {
            q = ZZ(rand());
        }
        while (primo(p) == false) {
            p = ZZ(rand());
        }
        this->q = q; this->p = p;
        this->n = p * q; this->ln = (p - 1) * (q - 1);
        //creando e (clave publica)
        while (x != 1) {
            y=ZZ(rand());
            x = mcd(y, this->ln);
        }//e entre 1 y mcd(e,ln)=1
        x = 0;
        while (x != 1) {
            e = mimodulo(ZZ((rand()+1)),y);
            x = mcd(e, this->ln);
        }
        this->publickey.push_back(e);
        this->publickey.push_back(this->n);
        //creando d (clave privada)
        d = inversa(this->publickey[0], this->ln);
        this->privatekey.push_back(d);
        this->privatekey.push_back(this->n);
    }
    std::vector<ZZ>cifrado(std::string msj, ZZ key, ZZ mod) {
        std::vector<ZZ>cifrado;
        ZZ ubicacion, code;
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
    std::string descifrado(std::vector<ZZ> msjcifr) {
        std::string decode; int ubicacionint;
        for (int i = 0; i < msjcifr.size(); i++) {
            ZZ ubicacion; ubicacion=0;
            ubicacion = potenciamodular(msjcifr[i], this->privatekey[0], this->n);
            ubicacion = potenciamodular(ubicacion, this->privatekey[0], this->n);
            std::cout << "\ndescifrado " << i + 1 << ":" << ubicacion;
            conv(ubicacionint, ubicacion);
            decode += this->alfabeto[ubicacionint];
        }
        return decode;
    }
};

int main()
{
    RSA receptor;
    RSA emisor;

    std::vector<ZZ> cifrado;
    std::string descifrado;
    std::string msg= "I actually did it";

    cifrado=emisor.cifrado(msg, receptor.publickey[0], receptor.publickey[1]);
    descifrado = receptor.descifrado(cifrado);
    std::cout << "\ndescifrado: " << descifrado;
}
