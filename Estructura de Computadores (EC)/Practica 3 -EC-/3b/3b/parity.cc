//------------------------------------------------------------------------------
// parity.cc
//------------------------------------------------------------------------------

#include <x86intrin.h> // __rdtscp

#include <algorithm>   // generate
#include <array>       // array
#include <bitset>      // bitset
#include <chrono>      // now
#include <functional>  // bind
#include <iomanip>     // setw
#include <iostream>    // cout endl
#include <random>      // uniform_int_distribution

//------------------------------------------------------------------------------

const unsigned GAP = 12;   // gap between columns
const unsigned REP = 100;  // how many times we repeat every algorithm

std::array<unsigned, 1 << 16> list; // 64K x 4B = 256KB

//------------------------------------------------------------------------------

unsigned parity00(unsigned elem) // return true if parity of elem is even
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity01(unsigned elem) // return true if parity of elem is even
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity02(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity03(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity04(unsigned elem) // like 3 with an extra "test"
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity05(unsigned elem) // like 3 without the extra "test"
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity06(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity07(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity08(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity09(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity10(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity11(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity12(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity13(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity14(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned parity15(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

template <class _F> void test (_F& __f, const char* msg)
{
	using namespace std::chrono;

	unsigned id; // needed by __rdtscp()

	unsigned long long cycle_overhead = std::numeric_limits<unsigned long long>::max();

	for (unsigned i = 0; i < REP; ++i)
	{
		unsigned long long t1 = __rdtscp(&id);
		unsigned long long t2 = __rdtscp(&id);
		cycle_overhead = std::min(cycle_overhead, t2 - t1);
	}

	unsigned long long cycles = std::numeric_limits<unsigned long long>::max();

	for (unsigned i = 0; i < REP; ++i)
	{
		unsigned long long t1 = __rdtscp(&id);
		__f(list[0]);
		unsigned long long t2 = __rdtscp(&id);
		cycles = std::min(cycles, t2 - t1);
	}
	cycles -= cycle_overhead;

	auto time_overhead = duration<high_resolution_clock::rep, std::nano>::max();

	for (unsigned i = 0; i < REP; ++i)
	{
		auto t1 = high_resolution_clock::now();
		auto t2 = high_resolution_clock::now();
		time_overhead = std::min(time_overhead, t2 - t1);
	}

	unsigned result;
	auto time = duration<high_resolution_clock::rep, std::nano>::max();

	for (unsigned i = 0; i < REP; ++i)
	{
		result = 0;
		auto t1 = high_resolution_clock::now();
		result = std::count_if(list.begin(), list.end(), __f);
		auto t2 = high_resolution_clock::now();
		time = std::min(time, t2 - t1);
	}
	time -= time_overhead;

	std::cout << '"' << std::setw(GAP * 2 - 2) << msg << '"' 
	          << std::setw(GAP) << result
	          << std::setw(GAP) << cycles
	          << std::setw(GAP) << std::fixed << std::setprecision(2)
	          << duration_cast<nanoseconds>(time).count() / static_cast<double>(list.size())
	          << std::setw(GAP) << duration_cast<nanoseconds>(time).count() / 1e6
	          << std::endl;
}

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<unsigned> distribution;
	auto generator = std::bind(distribution, engine);
	std::generate(list.begin(), list.end(), generator);

	std::cout << "#" << std::setw(GAP * 2 - 1) << "parity"
	          << std::setw(GAP) << "value"
	          << std::setw(GAP) << "cycles"
	          << std::setw(GAP) << "time(ns)"
	          << std::setw(GAP) << "total(us)"
	          << std::endl;

	test(parity00, "parity00(empty)");
	test(parity01, "parity01(for)");
	test(parity02, "parity02(while)");
	test(parity03, "parity03(do while)");
	test(parity04, "parity04(asm)");
	test(parity05, "parity05(asm v2)");
	test(parity06, "parity06(tree)");
	test(parity07, "parity07(tree v2)");
	test(parity08, "parity08(asm v3)");
	test(parity09, "parity09(lt8)");
	test(parity10, "parity10(lt16)");
	test(parity11, "parity11(HD)");
	test(parity12, "parity12(builtin)");
	test(parity13, "parity13(bitset)");
	test(parity14, "parity14(recursive)");
	test(parity15, "parity15(lt16 v2)");
}

//------------------------------------------------------------------------------
