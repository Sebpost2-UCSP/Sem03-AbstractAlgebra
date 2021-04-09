#include <iostream>
#include <vector>   // uso vectores

class chat
{
private:
    int clave1;                    //la clave1 son las filas
    int clave2;                    //la clave2 son las columnas
public:
    void emisorsetclave(int x, int y)        // el emisor crea la clave
    {
        clave1 = x;
        clave2 = y;
    }
    void receptorsetclave()                  // el receptor ingresa la clave del emisor (con cin en este caso)
    {
        std::cout << "Receptor \n Ingrese la clave 1: \n";
        std::cin >> clave1;
        std::cout << "\n Ingrese la clave 2: \n";
        std::cin >> clave2;
        std::cout << "\n";
    }
    void printvector(std::vector<char>b) //solo para imprimir la parte del cifrado del emisor
    {
        for (int i = 0; i < clave1; i++)
        {
            std::cout << "|";
            for (int j = 0; j < clave2; j++)
            {
                std::cout << b[j + (clave2 * i)] << "|";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    void printvector2(std::vector<char>b) //solo para imprimir la parte del descifrado del receptor
    {
        for (int i = 0; i < clave2; i++)
        {
            std::cout << "|";
            for (int j = 0; j < clave1; j++)
            {
                std::cout << b[j + (clave1 * i)] << "|";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    std::string cifrado(std::string mensaje) 
    {
        int counter = 0;   // lo uso para recorrer el string            
        std::string codigo;   // lo uso para almacenar el codigo cifrado       
        std::vector<char> msg;  //creo un vector
    
        for (int i = 0; i < clave1 * clave2; i++)
        {
            if (mensaje[counter] != '\0') //aca solo estoy llenando el vector con las letras
            {
                msg.push_back(mensaje[counter]);
                counter++;
            }
            else
            {
                msg.push_back(' ');
            }
        }

        printvector(msg);

        for (int j = 0; j < clave2; j++) //aca estoy devolviendo las letras (leyendo las columnas primero en vez de filas)
        {
            for (int i = 0; i < clave1; i++)
            {
                codigo += msg[j + (clave2 * i)];
            }
        }

        return codigo;
    }

    std::string descifrado(std::string mensajeincog)
    {
        int counter = 0;
        std::string codigo;
        std::vector<char> msg;

        for (int i = 0; i < clave1 * clave2; i++)
        {
            if (mensajeincog[counter] != '\0') //aca solo estoy creando el vector
            {
                msg.push_back(mensajeincog[counter]);
                counter++;
            }
            else
            {
                msg.push_back(' ');
            }
        }

        printvector2(msg);
        
        for (int i = 0; i < clave1; i++) //aca cambie el valor de columnas por el de filas y tambien leo las columnas en vez de filas
        {
            for (int j = 0; j < clave2; j++)
            {
                codigo += msg[i + (clave1 * j)];
            }

        }

        return codigo;
    }
};

int main()
{
    chat emisor;
    chat receptor;
    std::string mensaje = "Hello world";
    std::string codein;    //este es el mensaje cifrado
    std::string codeout;   //este es el mensaje descifrado

    emisor.emisorsetclave(3, 5);     //el emisor crea la clave aqui
    receptor.receptorsetclave();      //si la clave que da el receptor es igual a la del emisor, entonces lo descifra correctamente, si no son iguales entonces no lo descifra correctamente

    codein = emisor.cifrado(mensaje);
    std::cout << "\n cifrado = " << codein << '\n';    
    codeout = receptor.descifrado(codein);
    std::cout << "\n descifrado = " << codeout << '\n';
}