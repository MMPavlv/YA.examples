#pragma once
#include <vector>
#include <map>

namespace Mathemagics
{
	bool IsPrime(unsigned long long n);
	std::vector<unsigned long long> GetPrimesBeforeThreshold(unsigned long long n);

	unsigned long long _gcd(unsigned long long x, unsigned long long y);
	bool CheckCoprimeNumbers(unsigned long long x, unsigned long long y);
	std::vector<unsigned long long> GetReducedResidueSystem(unsigned long long m);

	unsigned long long Phi(unsigned long long m);

	std::map<unsigned long long, unsigned long long> CanonicalPrimeFactorization(unsigned long long m);

}