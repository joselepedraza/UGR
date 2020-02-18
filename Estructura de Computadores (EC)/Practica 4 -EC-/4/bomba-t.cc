//------------------------------------------------------------------------
// bomba-t.cc
//------------------------------------------------------------------------

#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

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
	std::cout << std::endl
	          << "\n##########################################"
	          << "\n#          bomba desactivada :)          #"
	          << "\n##########################################" << std::endl;
	exit(0);
}

//------------------------------------------------------------------------

template<typename T> void comparar(const T& viejo, const char* msg)
{
	std::atomic<bool> bomba_armada{true};
	T nuevo;

	std::thread t([&]
	{
		auto fin = std::chrono::high_resolution_clock::now() + 
		           std::chrono::seconds(5);
		while (bomba_armada.load())
		{
			std::this_thread::yield();
			if (std::chrono::high_resolution_clock::now() > fin)
				explotar();
		}
	});

	std::cout << "Introduzca " << msg << ": ";
	std::cin >> nuevo;
	bomba_armada = false;

	if (nuevo != viejo)
		explotar();

	t.join();
}

//------------------------------------------------------------------------

int main()
{
	std::string clave1 = "hola";
	int clave2 = 1234;

	comparar(clave1, "contraseña");
	comparar(clave2, "código");
	desactivar();
}

//------------------------------------------------------------------------

