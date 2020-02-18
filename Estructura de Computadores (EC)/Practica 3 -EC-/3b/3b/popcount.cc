//------------------------------------------------------------------------------
// popcount.cc
// http://www.dalkescientific.com/writings/diary/archive/2011/11/02/faster_popcount_update.html
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
const unsigned REP = 100;  // how many times we repeat the experiment

std::array<unsigned, 1 << 16> list; // 64K x 4B = 256KB

//------------------------------------------------------------------------------

unsigned popcount00(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount01(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount02(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount03(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount04(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount05(unsigned elem) // from o'hallaron
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount06(unsigned elem) // gustavo
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount07(unsigned elem) // from wikipedia
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount08(unsigned elem) // by Wegner
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount09(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount10(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount11(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount12(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount13(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount14(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount15(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount16(unsigned elem)
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
		std::for_each(list.begin(), list.end(), [&](unsigned x){ result += __f(x); });
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

	std::cout << "#" << std::setw(GAP * 2 - 1) << "popcount"
	          << std::setw(GAP) << "value"
	          << std::setw(GAP) << "cycles"
	          << std::setw(GAP) << "time(ns)"
	          << std::setw(GAP) << "total(us)"
	          << std::endl;

	test(popcount00, "popcount00(empty)");
	test(popcount01, "popcount01(for)");
	test(popcount02, "popcount02(while)");
	test(popcount03, "popcount03(inline)");
	test(popcount04, "popcount04(inline v2)");
	test(popcount05, "popcount05(0'hallaron)");
	test(popcount06, "popcount06(gus)");
	test(popcount07, "popcount07(wikipedia)");
	test(popcount08, "popcount08(Wegner)");
	test(popcount09, "popcount09(lt8)");
	test(popcount10, "popcount10(lt8 v2)");
	test(popcount11, "popcount11(lt8 v3)");
	test(popcount12, "popcount12(lt8 v4)");
	test(popcount13, "popcount13(lt16)");
	test(popcount14, "popcount14(builtin)");
	test(popcount15, "popcount15(bitset)");
	test(popcount16, "popcount16(recursive)");
}

//------------------------------------------------------------------------------
