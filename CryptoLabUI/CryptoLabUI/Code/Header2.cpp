#include "pch.h"
#include "Header2.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <valarray>
#include <iostream>

unsigned long long Mathemagics::Rabin::ModuloSubstraction(unsigned long long a, unsigned long long b, unsigned long long N)
{
	b %= N;
	if (a >= b)
		return a - b;
	else
		return N - (b - a);
}

unsigned long long Mathemagics::Rabin::ReverseModulo(unsigned long long a, unsigned long long N)
{
	for (unsigned long long i = 0; i < N; i++)
	{
		if ((i*a) % N == 1)
			return i;
	}
	return 0;
}

std::pair<unsigned long long, unsigned long long> Mathemagics::Rabin::GetPrivateKey()
{
	srand(static_cast<unsigned int>(time(0)));
	unsigned long long a, b;
	do
	{
		a = rand() % 20;
	} while (a % 4 != 3 || !IsPrime(a));

	do
	{
		b = rand() % 1000;
	} while (b % 4 != 3 || !IsPrime(b) || a == b);
	return std::pair<unsigned long long, unsigned long long>(a, b);
}

std::pair<unsigned long long, unsigned long long> Mathemagics::Rabin::GetPublicKey(std::pair<unsigned long long, unsigned long long> PrivateKey)
{
	auto n = PrivateKey.first*PrivateKey.second;

	return std::pair<unsigned long long, unsigned long long>(n, rand() % n);
}

std::pair<unsigned long long, unsigned long long> Mathemagics::Rabin::QuadraticResidue(unsigned long long a, unsigned long long p)
{
	std::pair<unsigned long long, unsigned long long> pair(0, 0);
	bool check = false;
	for (unsigned long long i = 3; i < p; i++)
	{
		if ((i*i) % p == a % p)
		{
			if (!check)
			{
				pair.first = i;
				check = true;
			}
			else
				pair.second = i;
			//std::cout << i << std::endl;
		}
	}
	if (pair.second == 0)
		pair.second = pair.first;
	return pair;
}

unsigned long long Mathemagics::Rabin::CRT(unsigned long long a, unsigned long long b, unsigned long long p, unsigned long long q)
{
	unsigned long long i = 0;
	while (true)
	{
		if (i%p == a && i%q == b)
			return i;
		i++;
	}
	return 0;
}

std::vector<unsigned long long> Mathemagics::Rabin::CompositeQuadraticResidue(unsigned long long a, unsigned long long p, unsigned long long q)
{
	std::vector<unsigned long long> vec;
	auto g1 = QuadraticResidue(a, p);
	auto g2 = QuadraticResidue(a, q);
	vec.push_back(CRT(g1.first, g2.first, p, q));
	std::cout << CRT(g1.first, g2.first, p, q) << std::endl;
	std::cout << CRT(g1.first, g2.second, p, q) << std::endl;
	std::cout << CRT(g1.second, g2.first, p, q) << std::endl;
	std::cout << CRT(g1.second, g2.second, p, q) << std::endl;
	return vec;
}

unsigned long long Mathemagics::Rabin::Encrypt(unsigned long long information, std::pair<unsigned long long, unsigned long long> PublicKey)
{
	return (information*(information + PublicKey.second)) % PublicKey.first;
}

std::vector<unsigned long long> Mathemagics::Rabin::Decrypt(unsigned long long crypt, std::pair<unsigned long long, unsigned long long> PrivateKey, std::pair<unsigned long long, unsigned long long> PublicKey)
{
	auto v = std::vector<unsigned long long>(4);
	auto T = ((PublicKey.second*PublicKey.second) * ReverseModulo(4, PublicKey.first) + crypt) % PublicKey.first;
	std::cout << T << std::endl;
	auto g1 = QuadraticResidue(T, PrivateKey.first);
	auto g2 = QuadraticResidue(T, PrivateKey.second);
	auto p = PrivateKey.first;
	auto q = PrivateKey.second;
	auto S1 = CRT(g1.first, g2.first, p, q);
	auto S2 = CRT(g1.first, g2.second, p, q);
	auto o1 = ModuloSubstraction(S1, PublicKey.second*ReverseModulo(2, PublicKey.first), PublicKey.first);
	auto o2 = ModuloSubstraction(S2, PublicKey.second*ReverseModulo(2, PublicKey.first), PublicKey.first);
	auto o3 = ModuloSubstraction(PublicKey.first - S1, PublicKey.second*ReverseModulo(2, PublicKey.first), PublicKey.first);
	auto o4 = ModuloSubstraction(PublicKey.first - S2, PublicKey.second*ReverseModulo(2, PublicKey.first), PublicKey.first);
	v[0] = o1;
	v[1] = o2;
	v[2] = o3;
	v[3] = o4;
	return v;
}
