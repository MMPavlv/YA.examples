#pragma once
#include "Header1.hpp"
#include <utility>
#include <vector>

namespace Mathemagics
{
	__declspec(selectany) std::pair<unsigned long long, unsigned long long> prk = std::pair<unsigned long long, unsigned long long>(127, 131);
	__declspec(selectany) std::pair<unsigned long long, unsigned long long> pbk = std::pair<unsigned long long, unsigned long long>(127 * 131, 12345);
	class Rabin
	{
	public:
		static unsigned long long ModuloSubstraction(unsigned long long a, unsigned long long b, unsigned long long N);
		static unsigned long long ReverseModulo(unsigned long long a, unsigned long long N);
		std::pair<unsigned long long, unsigned long long> static GetPrivateKey();
		std::pair<unsigned long long, unsigned long long> static GetPublicKey(std::pair<unsigned long long, unsigned long long> PrivateKey);
		std::pair<unsigned long long, unsigned long long> static QuadraticResidue(unsigned long long a, unsigned long long p);
		unsigned long long static CRT(unsigned long long a, unsigned long long b, unsigned long long p, unsigned long long q);
		std::vector<unsigned long long> static CompositeQuadraticResidue(unsigned long long a, unsigned long long p, unsigned long long q);
		static unsigned long long Encrypt(unsigned long long information, std::pair<unsigned long long, unsigned long long> PublicKey);
		static std::vector<unsigned long long> Decrypt(unsigned long long crypt, std::pair<unsigned long long, unsigned long long> PrivateKey, std::pair<unsigned long long, unsigned long long> PublicKey);
	};

	__declspec(selectany) unsigned long long P = 9973;
	__declspec(selectany) unsigned long long g = 1685;
	__declspec(selectany) unsigned long long x = 1000;
	__declspec(selectany) unsigned long long y = 3313;
	class Elgamal
	{
	
	};
}
