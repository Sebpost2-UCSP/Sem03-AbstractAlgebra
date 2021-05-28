#include <iostream>
#include <vector>
#include<time.h>
#include<NTL/ZZ.h>
#include<string>
#include<sstream>
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

ZZ potenciacionZZ(ZZ a, ZZ b){
    int count=0; ZZ resultado;
    resultado=1;
    while(count != b){
       resultado=resultado*a;
       count++;
    }
    return resultado;
}

std::string ZZtostring(ZZ a){
    std::stringstream newstring;
	newstring << a;
	return newstring.str();
}

ZZ stringToZZ(std::string a){
	ZZ newZZ;
	std::stringstream convi(a);
	convi >> newZZ;
	return newZZ;
}

class RSA {
private:
    ZZ q, p, ln;
    std::vector<ZZ>privatekey;
public:
    ZZ n;
    //std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz1234567890-.";
    std::string alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    std::vector<ZZ>publickey;
    RSA(ZZ bits){
        ZZ q,p,x,y,e,d; q = 0; p = 0; x = 0; y = 0; e=0; d=0;
        //creando q y p
        while (primo(q) == false) {
                q=RandomBnd(potenciacionZZ(ZZ(2),bits)-1)+potenciacionZZ(ZZ(2),bits)/2;
            //q = RandomBnd(potenciacionZZ(ZZ(2),bits)-ZZ(1))+(potenciacionZZ(ZZ(2),bits)/ZZ(2));
        }
        while (primo(p) == 0) {
                p=RandomBnd(potenciacionZZ(ZZ(2),bits))+potenciacionZZ(ZZ(2),bits)/2;
            //p = RandomBnd(potenciacionZZ(ZZ(2),bits)-ZZ(1))+(potenciacionZZ(ZZ(2),bits)/ZZ(2));
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
    RSA(ZZ e, ZZ n){
        publickey.push_back(e); publickey.push_back(n);
        ZZ d;d=inversa(e,n);
        privatekey.push_back(d); privatekey.push_back(n);
    }
    void testing(){
        std::cout<<"\nP: "<<p<<"\nQ: "<<q<<"\nN: "<<publickey[1]<<"\nE: "<<publickey[0]<<"\nD: "<<privatekey[0];
    }
    std::string cifrado(std::string msj) {
        std::cout<<"\n\nCIFRADO: \n";
        std::string cifrado;
        std::string mensaje;
        std::string bloques;
        std::string bloquescifr;
        ZZ a, ubicacion, code; a=this->publickey[1];
        int countN=0, ini=0;
        //Numero de digitos de N-1
        while(a!=ZZ(0)){
            a=a/ZZ(10);
            countN++;
        }
        countN--;
        ZZ altcode; int countCODE;
        for (int i=0; i<msj.length();i++){
            ubicacion=this->alfabeto.find(msj[i]);
            countCODE=0; altcode=ubicacion;
            while(altcode!=ZZ(0)){
                altcode=altcode/ZZ(10);
                countCODE++;
            }
            if (countCODE<2){
                mensaje+="0";
            }
            mensaje.insert(mensaje.size(),ZZtostring(ubicacion));
        }
        ZZ final; final=this->alfabeto.size();
        mensaje+=ZZtostring(final);
        std::cout<<"\nmensaje: "<<mensaje;
        for (int i = 1; i*countN < mensaje.length()+countN; i++)
        {
            ZZ value; value=0;
            ZZ number,number2; number=0;
            for (int j=ini; j<countN+ini;j++){
                bloques+=mensaje[j];
            }
            number=stringToZZ(bloques);
            value+=number;
            bloques="";
            std::cout<<"\nvalue: "<<value;
            ini+=countN;
            if (ini>=msj.length()+ini){
                break;
            }
            //key=3; mod=1003;
            code = potenciamodular(value,publickey[0],publickey[1]);
            std::cout<<"\ncode: "<<code;
            countCODE=0; altcode=code;
            while(altcode!=ZZ(0)){
                altcode=altcode/ZZ(10);
                countCODE++;
            }
            std::cout<<"\ncountCODE: "<<countCODE;
            while(ZZ(countCODE)<=countN){
                cifrado+="0";
                countCODE++;
            }
            cifrado.insert(cifrado.size(),ZZtostring(code));
        }
        std::cout << "\ncifrado: " << cifrado;
        return cifrado;
    }
    std::string descifrado(std::string msjcifr) {
        std::cout<<"\n\nDESCIFRADO: \n";
        std::string descifrar;
        std::string bloques;
        std::string coding;
        int countN=0, ini=0, ini2=0;
        ZZ a, ubicacion, decode; a=publickey[1];
        ZZ d;d=privatekey[0];
        std::cout<<"\nd: "<<d;
        //Numero de digitos de N
        while(a!=ZZ(0)){
            a=a/ZZ(10);
            countN++;
        }
        std::cout<<"\nCOUNT_N: "<<countN;
        for (int i = 0; i < msjcifr.size(); i++) {
            for (int j=ini; j<countN+ini;j++){
                bloques+=msjcifr[j];
            }
            ZZ number,value;
            number=stringToZZ(bloques);
            value+=number;
            bloques="";
            ini+=countN;
            if (ini>=msjcifr.size()){
                break;
            }
            std::cout<<"\nvalue: "<<value;
            decode=potenciamodular(value,d,n);
            std::cout<<"\ndecode: "<<decode;
            int countCODE=0; ZZ altcode; altcode=decode;
            while(altcode!=ZZ(0)){
                altcode=altcode/ZZ(10);
                countCODE++;
            }
            std::cout<<"\nCountCODE: "<<countCODE;
            while(ZZ(countCODE)<countN-1){
                coding+="0";
                countCODE++;
            }

            coding.insert(coding.size(),ZZtostring(decode));
        }
        std::cout<<"\ncoding: "<<coding;
        for (int i=ini2; i<coding.size();i++){
             for (int j=ini2; j<2+ini2;j++){
                bloques+=coding[j];
            }
            int bloquesint; ZZ bloquesZZ;bloquesZZ=stringToZZ(bloques);
            std::cout<<"\nbloquesZZ: "<<bloquesZZ;
            conv(bloquesint,bloquesZZ);
            bloques="";
            ini2+=2;
            descifrar+=alfabeto[bloquesint];
            bloques="";
            if (ini2>=coding.size()){
                break;
            }
        }
        return descifrar;
    }
    void setpublickey(int a, int b){
        publickey[0]=a;
        publickey[1]=b;
    }
    void setprivatekey(int a, int b){
        privatekey[0]=a;
        privatekey[1]=b;
    }
};

int main()
{
    std::cout<<"\nRECEPTOR: \n";
    RSA receptor(ZZ(8));
    receptor.testing();
    std::cout<<"\n\nEMISOR: \n";
    RSA emisor(receptor.publickey[0],receptor.publickey[1]);
    //RSA emisor(ZZ(3),ZZ(1003));
    emisor.testing();

    std::string cifrado;
    std::string descifrado;
    std::string msg= "What a beautiful day";

    cifrado=emisor.cifrado(msg);
    //cifrado="023403530811005403060545";
    descifrado = receptor.descifrado(cifrado);
    std::cout << "\ndescifrado: " << descifrado;
}
