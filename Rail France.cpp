#include <iostream>
#include <vector>

class chat
{
private:
    int clave1;      //numero de filas
public:
    int clave2;      //numero de columnas == longitud del mensaje

    void emisorsetclave(int x, int y)       // el emisor crea la clave
    {
        clave1 = x;
        clave2 = y;
    }
    void receptorsetclave(int y)        // el receptor ingresa la clave
    {
        std::cout << "Receptor \n Ingrese numero de filas: \n";
        std::cin >> clave1;
        clave2 = y;
    }
    void printvector(std::vector<char>b) //aca solo imprimo el vector
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
    std::string cifrado(std::string mensaje) 
    {
        int counter = 0;        // counter lo utilizo para recorrer el string mensaje
        std::string codigo;           //en codigo almaceno el mensaje encriptado
        std::vector<char> msg(clave1*clave2);   //creo el vector con su respectivo size
        bool backwards = false;    // con este bool identifico cuando las filas estan llendo hacia abajo o hacia arriba

        int filas = 0;
        int columnas = 0;

        while (counter <= clave2) 
        {

            if (backwards == false)
            {
                msg[columnas + (clave2 * filas)] = mensaje[counter]; //ingreso la letra en la posicion correcta
                counter++;
                columnas++; // si las filas van hacia abajo sumo las columnas +1  y filas+1
                filas++;
                if (filas >= clave1) // esto detecta cuando las filas llegan al limite 
                {
                    backwards = true;
                    filas = filas - 2;
                }               
            }
            else
            {
                msg[columnas + (clave2 * filas)] = mensaje[counter];
                counter++;
                columnas++; // si las filas van hacia arriba sumo columnas+1 y resto filas-1
                filas--;
                if (filas <= -1) // tambien detecta si las filas llegan a su limite
                {
                    backwards = false;
                    filas = filas + 2;
                }
            }
        }

        printvector(msg);

        for (int i = 0; i < clave1; i++)
        {
            for (int j = 0; j < clave2; j++)
            {
                codigo += msg[j + (clave2 * i)]; // solo lee toda la matriz e impreme el mensaje
            }

        }

        return codigo;
    }

    std::string descifrado(std::string mensajeincog) // lo mismo que el cifrado pero con el mensaje encripatdo
    {
        int counter = 0;
        std::string codigo;
        std::vector<char> msg ;
        bool backwards = false;

        for (int i = 0; i < clave1 * clave2; i++) //aqui solo estoy rellenando la matriz)
        {
            if (counter <= mensajeincog.size()) 
            {
                msg.push_back(mensajeincog[counter]);
                counter++;
            }
            else
            {
                msg.push_back(' ');
            }
        }

        counter = 0;

        printvector(msg);

        int filas = 0;
        int columnas = 0;

        while (counter <= clave2)
        {

            if (backwards == false)
            {
                codigo += msg[columnas + (clave2 * filas)]; // en vez de ingresar una letra, agrego esta al codigo
                counter++;
                columnas++;
                filas++;
                if (filas >= clave1)
                {
                    backwards = true;
                    filas = filas - 2;
                }
            }
            else
            {
                codigo += msg[columnas + (clave2 * filas)];
                counter++;
                columnas++;
                filas--;
                if (filas <= -1)
                {
                    backwards = false;
                    filas = filas + 2;
                }
            }
        }

        return codigo;
    }
};


int main()
{
    chat emisor;
    chat receptor;
    std::string mensaje = "Hola como estan";
    std::string codein;    //este es el mensaje cifrado
    std::string codeout;   //este es el mensaje descifrado

    int col = mensaje.size();

    emisor.emisorsetclave(5, col);     //el emisor crea la clave aqui
    receptor.receptorsetclave(col);      //si la clave que da el receptor es igual a la del emisor, entonces lo descifra correctamente, si no son iguales entonces no lo descifra correctamente

    codein = emisor.cifrado(mensaje);
    std::cout << "\n cifrado = " << codein << '\n';
    codeout = receptor.descifrado(codein);
    std::cout << "\n descifrado = " << codeout << '\n';
}

