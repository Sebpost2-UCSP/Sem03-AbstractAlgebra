#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <time.h>
using std::string;

//para el ejercicio 18.9
void condicion(string a) // solo ve si la palabra termina en ay o r
{
	if (a.rfind("ay") == a.length() - 2 || a.rfind("r") == a.length()-1)
	{
		std::cout << "\nSe acepto: " << a;
	}
}

//para el ejercicio 18.12
string chooseword()  // escoge una palabra al azar para el ahorcado
{
	std::vector<string> v(5);
	v[0] = "rinoceronte";
	v[1] = "mariposa";
	v[2] = "perro";
	v[3] = "gato";
	v[4] = "oso";

	int random;
	srand(time(NULL));
	random=(rand() % 5);
	return v[random];
}

//para el ejercicio 18.27
void ordenamientoseleccion(string a[], const int size, bool (*compara)(string,string))
{	
	// un ordenamiento de mayor a menor o menor a mayor
	int menorOmayor;
	for (int i = 0; i < size - 1; i++)
	{
		menorOmayor = i;
		for (int index = i + 1; index < size; index++)
		{
			if (!(*compara)(a[menorOmayor], a[index]))
				menorOmayor = index;

			a[menorOmayor].swap(a[index]);
		}
	}
}
bool ascendente(string x, string y)
{
	return x < y;
}
bool descendente(string x, string y)
{
	return x > y;
}

int main()
{
	string cadena;

	//18.9
	std::cout << "\n Ejercicio 18.9\n";
	cadena = "xh4rawefayejrzldsr";
	condicion(cadena);
	cadena = "asfweiasgpasjd";
	condicion(cadena);
	cadena = "mfwadsfhagway";
	condicion(cadena);
	cadena = "this is a test";
	condicion(cadena);
	cadena = "its almost may";
	condicion(cadena);

	//18.11
	std::cout << "\n\n Ejercicio 18.11\n";
	string cadena1;
	string cadena2;
	std::cout << "\nIngrese UN nombre: \n";
	std::cin >> cadena;
	std::cout << "\nIngrese UN apellido: \n";
	std::cin >> cadena1;
	cadena2.append(cadena + " " + cadena1); //juntando la cadena
	std::cout << "\nNombre completo: " << cadena2;

	//18.12
	std::cout << "\n\n Ejercicio 18.12\n";
	cadena1 = chooseword();
	cadena.erase(0);
	for (int i = 0; i < cadena1.length(); i++)
	{
		cadena += 'x'; // la cadena se llena de x
	}
	int counter = 0; //las vidas
	char letra;  
	while (true)
	{
		std::cout << "\n Ahorcado: \n";
		std::cout << "\n	" << cadena << "\n\n";
		if (cadena.find('x') == -1) //si ya no encuentra las x ganas
		{
			system("cls");
			std::cout << "\n Ejercicio 18.12 \n" << cadena << " era la palabra\nHa ganado, desea intentar denuevo? (y/n): ";
			std::cin >> letra;
			if (letra == 'y')
			{
				counter = 0;
				cadena1 = chooseword();
				cadena.erase(0);
				for (int i = 0; i < cadena1.length(); i++)
				{
					cadena += 'x';
				}
				continue;
			}
			else if (letra == 'n')
			{
				break;
			}
			else
			{
				continue;
			}
		}
		if (counter == 1)
		{
			std::cout << " O";
		}
		else if (counter == 2)
		{
			std::cout << " O\n/";
		}
		else if (counter == 3)
		{
			std::cout << " O\n/|";
		}
		else if (counter == 4)
		{
			std::cout << " O\n/|\\";
		}
		else if (counter == 5)
		{
			std::cout << " O\n/|\\\n |";
		}
		else if (counter == 6)
		{
			std::cout << " O\n/|\\\n |\n/";
		}
		else if (counter == 7)
		{
			std::cout << " O\n/|\\\n |\n/ \\";
		}
		if (counter == 8) //aqui pierde el jugador
		{
			system("cls");
			std::cout << "\n Ejercicio 18.12 \n\n" << "\nHa perdido, desea intentar denuevo? (y/n): ";
			std::cin >> letra;
			if (letra == 'y')
			{
				counter = 0;
				cadena1 = chooseword();
				cadena.erase(0);
				for (int i = 0; i < cadena1.length(); i++)
				{
					cadena += 'x';
				}
				continue;
			}
			else if (letra == 'n')
			{
				break;
			}
			else
			{
				continue;
			}
		}
		std::cout << "\n\n Escriba una letra: \n";
		std::cin >> letra;
		if (cadena1.find(letra) == -1)// si no encuentra la letra te baja una vida
		{
			counter++;
		}
		else
		{
			while (true)
			{
				if (cadena1.find(letra) != -1)//busca todas las letras iguales
				{
					cadena[cadena1.find(letra)] = cadena1[cadena1.find(letra)];
					cadena1[cadena1.find(letra)] = 'x';
				}
				else
				{
					break;
				}
			}
		}
	}

	//18.19
	std::cout << "\n\n Ejercicio 18.19 \n";
	cadena.erase(0);
	std::cout << "\nIngresa UNA palabra: \n";
	std::cin >> cadena;
	if (cadena.length() % 2 == 0) //busca que el string tenga mitad exacta
	{
		cadena.insert(cadena.length() / 2, "*******");
		std::cout << "\n" << cadena;
	}
	else
	{
		std::cout << "\nNo no tiene una mitad exacta\n";
	}

	//18.21
	std::cout << "\n\n Ejercicio 18.21 \nCadena original: ";
	cadena1 = "this.is.only.a.test";
	std::cout << cadena1;
	while (true)
	{
		if (cadena1.find('.') != -1)//busca todos los puntos
		{
			cadena1[cadena1.find('.')] = ' ';
		}
		else
		{
			break;
		}
	}
	std::cout << "\nCadena nueva: " << cadena1;
	//18.22
	std::cout << "\n\n Ejercicio 18.22\n";
	cadena = "Hello world, im here"; //crea un iterador y utiliza for para invertir el string
	std::cout << "Cadena original: " << cadena << "\nCadena nueva: ";
	for (string::const_iterator iterador = cadena.end() - 1; iterador != cadena.begin(); iterador--)
	{
		std::cout << *iterador;
	}
	std::cout << cadena[0];

	//18.27
	std::cout << "\n\n Ejercicio 18.27\n";
	const int size = 10;
	int orden;
	int contador;
	string a[size] = { "cat.",".dog.","Algebra","Abstracta","Peru","arb0l","Matematica","Ciencia","string","char" };
	std::cout << "Escriba 1 para el orden ascedente\nEscriba 2 para el orden descendente: ";
	std::cin >> orden;
	std::cout << "\nElementos de datos en el orden original:\n";
	std::cout << "| ";
	for (contador = 0; contador < size; contador++)
	{
		std::cout << a[contador] <<" | ";
	}
	if (orden == 1)
	{
		ordenamientoseleccion(a, size, ascendente);
		std::cout << "\nElementos de datos en orden ascendente:\n ";
	}
	else if (orden == 2)
	{
		ordenamientoseleccion(a, size, descendente);
		std::cout << "\nElementos de datos en orden descendente:\n ";
	}
	std::cout << "| ";
	for (contador = 0; contador < size; contador++)
	{
		std::cout << a[contador] << " | ";
	}
	std::cout << "\n\n";
}

