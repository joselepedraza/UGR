//------------------------------------------------------------------------
// bomba-e.cc
//------------------------------------------------------------------------

#include <chrono>
#include <iostream>
#include <string>

//------------------------------------------------------------------------

std::string explotar = "\n##########################################"
                       "\n#           booooooooooooom!!!           #"
                       "\n##########################################",
          desactivar = "\n##########################################"
                       "\n#         bomba desactivada :)           #"
                       "\n##########################################";

//------------------------------------------------------------------------

template <typename T> void comprobar(const T& buena, const char* msg)
{
	T clave;
	std::cout << "Introduzca la " << msg << ": ";
	auto t0 = std::chrono::high_resolution_clock::now();
	std::cin >> clave;
	auto retraso = std::chrono::high_resolution_clock::now() - t0;
	if (clave != buena || retraso > std::chrono::seconds(5))
		throw explotar;
}

//------------------------------------------------------------------------

int main()
{
	std::string clave1 = "hola";
	int clave2 = 1234;

	try
	{
		comprobar(clave1, "contraseña");
		comprobar(clave2, "código");
		throw desactivar;
	}
	catch(std::string& s)
	{
		std::cout << s << std::endl;
	}
}

//------------------------------------------------------------------------

