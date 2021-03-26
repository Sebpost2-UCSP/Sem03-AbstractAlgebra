#include <iostream>

char** matriz;              //en este codigo utilizo arrays

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
    }
    std::string cifrado(std::string mensaje) //cifrado y descifrado solo tienen como parametro un mensaje
    {
        int counter = 0;              //counter lo uso para entrar a una determinada letra del string codigo
        std::string codigo;           //codigo es el mensaje que devuelve la funcion (cifrado o descifrado)

        matriz = new char* [clave1];            //aqui creo mi matriz de (x) filas y (y) columnas
        for (int i = 0; i < clave1; i++)
        {
            matriz[i] = new char[clave2];
            for (int j = 0; j < clave2; j++)
            {
                if (mensaje[counter] != '\0')    //cuando mensaje[counter] devuelve el '\0' significa que esta en el final asi que luego agrego ' ' para llenar el resto de la matriz         
                {
                    matriz[i][j] = mensaje[counter];
                    counter++;
                }
                else
                {
                    matriz[i][j] = ' ';
                }
            }
        }

        for (int j = 0; j < clave2; j++)
        {
            for (int i = 0; i < clave1; i++)
            {
                codigo += matriz[i][j];     //despues de crear la matriz leo las columnas primero en vez de las filas y agrego las letras al string codigo
            }
        }
        return codigo;
    }

    std::string descifrado(std::string mensajeincog)
    {
        int counter = 0;
        std::string codigo;

        for (int j = 0; j < clave2; j++)     //aqui creo mi matriz de (y) filas y (x) columnas 
        {
            for (int i = 0; i < clave1; i++)
            {
                if (mensajeincog[counter] != '\0')
                {
                    matriz[i][j] = mensajeincog[counter];
                    counter++;
                }
                else
                {
                    matriz[i][j] = ' ';
                }
            }
        }

        counter = 0;
        for (int i = 0; i < clave1; i++)
        {
            for (int j = 0; j < clave2; j++)
            {
                codigo += matriz[i][j];     //igual que antes leo las columnas de la matriz primero y agrego las letras a mi string
            }
        }

        for (int i = 0; i < clave1; i++) //aqui solo estoy borrando la memoria que cree antes
        {
            delete[] matriz[i];
        }
        delete[] matriz;

        return codigo;
    }
};

int main()
{
    chat emisor;
    chat receptor;
    std::string mensaje = "and so discovers the continuity of the message. And the parchment";
    std::string codein;    //este es el mensaje cifrado
    std::string codeout;   //este es el mensaje descifrado

    emisor.emisorsetclave(11, 7);     //el emisor crea la clave aqui
    receptor.receptorsetclave();      //si la clave que da el receptor es igual a la del emisor, entonces lo descifra correctamente, si no son iguales entonces no lo descifra correctamente

    codein = emisor.cifrado(mensaje);
    std::cout << "\n cifrado = " << codein << '\n';
    codeout = receptor.descifrado(codein);
    std::cout << "\n descifrado = " << codeout << '\n';
}