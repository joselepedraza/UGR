//------------------------------------------------------------------------
// bomba-s.cc
//------------------------------------------------------------------------

#include <signal.h>
#include <unistd.h>

#include <iostream>
#include <string>

//------------------------------------------------------------------------

void explotar(int)
{
	std::cout << "\n##########################################"
	          << "\n#           booooooooooooom!!!           #"
	          << "\n##########################################" << std::endl;
	exit(1);
}

//------------------------------------------------------------------------

void desactivar(int)
{
	std::cout << "\n##########################################"
	          << "\n#         bomba desactivada :)           #"
	          << "\n##########################################" << std::endl;
	exit(0);
}

//------------------------------------------------------------------------

template <typename T> void comprobar(const T& buena, const char* msg)
{
	T clave;

	std::cout << "Introduzca la " << msg << ": ";
	signal(SIGALRM, explotar);
	alarm(5);
	std::cin >> clave;
	signal(SIGALRM, SIG_DFL);
	if (clave != buena)
		explotar(0);
}

//------------------------------------------------------------------------

int main()
{
	std::string clave1 = "hola";
	int         clave2 =  1234 ;

	comprobar(clave1, "contraseña");
	comprobar(clave2, "código");
	desactivar(0);
}

//------------------------------------------------------------------------

