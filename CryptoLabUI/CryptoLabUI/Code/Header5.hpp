#pragma once
#include "Header1.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <map>
#include "BigInt.hpp"
#include "LFSR.h"

namespace Mathemagics
{
	static unsigned long long irreducible_polynomials[64] = { 2, 7, 11, 19, 37, 67, 131, 283, 515, 1033, 2053, 4105, 8219, 16417, 32771, 65579, 131081, 262153, 524327, 1048585, 2097157, 4194307, 8388641, 16777243, 33554441, 67108891,
		134217767, 268435459, 536870917, 1073741827, 2147483657, 4294967437, 8589934667, 17179869211, 34359738373, 68719476789, 137438953535, 274877907043, 549755813905, 1099511627833, 2199023255561, 4398046511143, 8796093022297,
		17592186044449, 35184372088859, 70368744177667, 140737488355361, 281474976710701, 562949953421425, 1125899906842653, 2251799813685323, 4503599627370505, 9007199254741063, 18014398509482109, 36028797018964039,
		72057594037928085, 144115188075855889, 288230376151711843, 576460752303423611, 1152921504606846979, 2305843009213693991, 4611686018427388009, 9223372036854775811
	};

	inline unsigned long long pow_(unsigned long long x, unsigned long long p, unsigned long long mod)
	{
		unsigned long long b = 1;

		while (p)
		{
			if (p % 2 == 0)
			{
				p /= 2;
				x = (x*x) % mod;
			}
			else
			{
				p--;
				b = (b*x) % mod;
			}
		}
		return b;
	}


	class GF
	{
	private:
		BigInt q = 2;
		BigInt num_ = 0;
	public:
		GF(int q, unsigned long long n);
		GF(int q, BigInt n);
		GF(BigInt q, BigInt n);
		std::string BinaryOut();
		std::string PolynomOut();
		std::string Out();

		BigInt GetIrreduciblePolynomials();
		std::string static ToBinaryString(BigInt num_);
		BigInt static xor(BigInt a, BigInt b);
		GF GetMultiplicativeInverse();
		GF operator+(GF& rnum);
		GF operator*(GF& rnum);
		GF operator/(GF& rnum);
	};

}
