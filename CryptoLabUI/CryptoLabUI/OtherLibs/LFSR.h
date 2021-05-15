// LFSR.cpp : Defines the entry point for the console application.
//

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <map>
#include <vector>

using namespace std;

//Pomiar czasu
static double PCFreq = 0.0;
static __int64 CounterStart = 0;

//------Pomiar-czasu-------
inline void startTimer()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart);

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
inline double endTimer()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq * 1000;
}
//-------------------------

static unsigned int LENGTH;
static bool* Start;
static bool* LFSR;
static bool bit;
static unsigned long long period;
static unsigned int tap1, tap2;
//--------------------------
inline void initialize(unsigned int length);
inline void clear();
inline void newTaps();
inline void moveBits();
inline void nextBit();
inline bool compare();
inline bool singleLFSR();
inline int loopLFSR();
inline vector<int> display(int tap, unsigned int size);
inline void display2(bool* a, unsigned int sizea);
inline void end();
//--------------------------
inline void initialize(unsigned int length)
{
	LENGTH = length;
	Start = new bool[LENGTH];
	LFSR = new bool[LENGTH];
	period = bit = 0;
	tap1 = 0;
	tap2 = LENGTH - 1;

	Start[LENGTH - 1] = LFSR[LENGTH - 1] = 1;
	for (int i = 0; i < LENGTH - 1; i++)
	{
		Start[i] = LFSR[i] = 0;
	}
}

void clear()
{
	period = bit = 0;

	for (int i = 0; i < LENGTH; i++)
	{
		LFSR[i] = Start[i];
	}
}

void newTaps()
{
	tap1++;
}

void moveBits()
{
	for (int i = LENGTH - 1; i >= 1; i--)
	{
		LFSR[i] = LFSR[i - 1];
	}
}

void nextBit()
{
	bit = LFSR[tap1] ^ LFSR[tap2];
}

bool compare()
{
	for (int i = 0; i < LENGTH; i++)
	{
		if (LFSR[i] != Start[i]) return false;
	}

	return true;
}

bool singleLFSR()
{
	do
	{
		nextBit();
		moveBits();
		LFSR[0] = bit;
		period++;
	} while (!compare());


	if (period == pow(2, LENGTH) - 1) return true;
	else
	{
		//display2(LFSR, LENGTH);
		//display2(Start, LENGTH);

		//cout << period << endl;

		return false;
	}
}

int loopLFSR()
{
	bool irreducible = false;
	unsigned int halfLength = floor(LENGTH / 2);

	do
	{
		//cout << tap1 << endl;
		irreducible = singleLFSR();
		if (irreducible)
		{
			return tap1;
		}
		else
		{
			clear();
			newTaps();
		}
	} while (tap1 <= halfLength);

	return -1;
}

vector<int> display(int tap, unsigned int size) //postac wielomianowa, na podstawie XOR
{
	string disp = "";
	string tmp;
	vector<int> v;
	v.push_back(LENGTH);
	if (tap == -1)
	{
		cout << "Brak" << endl;
		return v;
	}

	for (int i = 0; i < size; i++)
	{
		if (i == tap)
		{
			if (tap == 0)
			{
				disp = "x + " + disp;
			}
			else
			{
				tmp = to_string(tap + 1);
				disp = "x^" + tmp + " + " + disp;
				v.push_back(tap + 1);
			}
		}
	}

	tmp = to_string(LENGTH);
	disp = "x^" + tmp + " + " + disp;
	v.push_back(0);
	disp = "f(x) = " + disp + " 1";
	cout << disp << endl;
	return v;
}

void display2(bool* bits, unsigned int size) //postac binarna, na podstawie tablicy bitow
{
	cout << "x = ";
	for (int i = 0; i <= size - 1; i++)
	{
		cout << bits[i];
	}
	cout << endl;
}

void end()
{
	delete Start;
	Start = 0;
	delete LFSR;
	LFSR = 0;
}

inline vector<int> out(int f)
{
	
	int result = -1;
	unsigned int length = f;
	double time;

	initialize(length);

	startTimer();
	result = loopLFSR();
	time = endTimer();

	auto v = display(result, LENGTH);
	end();
	return v;
}

