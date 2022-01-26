//------------------------------------------------------------------------
// bomba-g.cc
//------------------------------------------------------------------------

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

//------------------------------------------------------------------------

void explotar()
{
	std::cout << "\n##########################################"
	          << "\n#            booooooooooooom!!!          #"
	          << "\n##########################################" << std::endl;
	exit(1);
}

//------------------------------------------------------------------------

void desactivar()
{
	std::cout << "\n##########################################"
	          << "\n#          bomba desactivada :)          #"
	          << "\n##########################################" << std::endl;
	exit(0);
}

//------------------------------------------------------------------------

template<typename T> void comparar(const T& viejo, const char* msg)
{
	T nuevo;

	std::cout << "Introduzca " << msg << ": " << std::flush;

	auto fin = std::chrono::system_clock::now() + std::chrono::seconds(5);

	std::cin >> nuevo;

	if (nuevo != viejo || std::chrono::system_clock::now() > fin)
		explotar();
}

//------------------------------------------------------------------------

int main()
{
	std::string clave1 = "hola";
	        int clave2 =  1234 ;

	comparar(clave1, "contraseña");
	comparar(clave2, "código");
	desactivar();
}

//------------------------------------------------------------------------

