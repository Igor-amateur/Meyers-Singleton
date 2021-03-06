// Singleton Maiersa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "ppl.h"
#include<iostream>

using namespace concurrency;
using namespace std;


class singleton
{
public:

	static singleton * instance() 
	{
		static singleton * inst(new singleton());
		return inst;
	}
private:

	singleton() { cout << "!!!" << endl; }//= default;                                  // Private constructor
	~singleton() = default;
	singleton(const singleton&) = delete;                 // Prevent copy-construction
	singleton& operator=(singleton&) = delete;      // Prevent assignment

	void * operator new (std::size_t aSize) 
	{
		return malloc(aSize);
	}

		void operator delete(void* obj)
	{
		free(obj);
	}

	void * operator new[] (std::size_t aSize)
	{
		return malloc(aSize);
	}

	void operator delete[](void* obj)
	{
		free(obj);
	}
};


int main()
{
	auto s1 = singleton::instance();
	auto s2 = singleton::instance();

	const int MAX_SIZE(10);
	critical_section cs;
	singleton* sinMass[MAX_SIZE];
	parallel_for(0, MAX_SIZE, [&](size_t i)
	{
		
		cs.lock();
		cout << i << endl;
		sinMass[i] = singleton::instance();
		cs.unlock();
	});

	for (auto n : sinMass)
	{
		if (n == s1 && n == s2)
		{
			cout << "This is singleton object" << endl;
			cout << "n == sinMass[0]" << " and " << n << " == " << sinMass[0] << endl;
		}
		else
		{
			cout << "This is not singleton object" << endl;
			cout << "n == sinMass[0]" << " and " << n << " == " << sinMass[0] << endl;
		}
	}

	if (s1 == s2)
	{
		cout << "This is singleton object" << endl;
		cout << "s1 == s2" << " and " << s1 << " == " << s2 << endl;
	}
	else
	{
		cout << "This is not singleton object" << endl;
		cout << "s1 != s2" << " and " << s1 << " != " << s2 << endl;
	}


    return 0;
}

