#include "pch.h"
#include <iostream>
#include <list>
#include <set>
#include <map>


bool Mathemagics::IsPrime(unsigned long long n)
{
	if (n < 2)
		return false;
	else if (n == 2)
		return true;
	else
	{
		for (unsigned long long i = 2; i < n / 2 + 1; i++)
		{
			if (n%i == 0)
				return false;
		}
		return true;
	}
}

std::vector<unsigned long long> Mathemagics::GetPrimesBeforeThreshold(unsigned long long n)
{
	std::vector<unsigned long long> v;
	for (unsigned long long i = 0; i < n; i++)
	{
		if (IsPrime(i))
			v.push_back(i);
	}
	return v;
}

unsigned long long Mathemagics::_gcd(unsigned long long x, unsigned long long y)
{
	return y ? _gcd(y, x%y) : x;
}

bool Mathemagics::CheckCoprimeNumbers(unsigned long long x, unsigned long long y)
{
	return _gcd(x, y) == 1;
}

std::vector<unsigned long long> Mathemagics::GetReducedResidueSystem(unsigned long long m)
{
	std::map<unsigned long long, unsigned long long> map;
	std::vector<unsigned long long> v;
	for (unsigned long long i = 1; i < m; i++)
	{
		if (map.find(m%i) == map.end() && CheckCoprimeNumbers(m, i))
		{
			map[m%i] = i;
			v.push_back(i);
			std::cout << i << std::endl;
		}
	}
	return v;
}

unsigned long long Mathemagics::Phi(unsigned long long m)
{
	unsigned long long j = 0;
	for (unsigned long long i = 1; i < m; i++)
	{
		if (CheckCoprimeNumbers(m, i))
			j++;

	}
	return j;
}

std::map<unsigned long long, unsigned long long> Mathemagics::CanonicalPrimeFactorization(unsigned long long m)
{
	auto n = m;
	std::map<unsigned long long, unsigned long long> map;
	for (unsigned long long i = 1; i < m; i++)
	{
		if (IsPrime(i))
		{
			while (n%i == 0)
			{
				if (map.find(i) == map.end())
					map[i] = 1;
				else
					map[i]++;
				n /= i;
			}
		}
	}

	for (auto it = map.begin(); it != map.end(); it++)
	{
		std::cout << it->first << "^" << it->second << std::endl;
	}
	return map;
}