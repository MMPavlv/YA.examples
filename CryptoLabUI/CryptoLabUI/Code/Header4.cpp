#include "pch.h"
#include "Header4.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

namespace Mathemagics
{
	long RSA::endecrypt(const long msg, const long key, const long pkey)
	{
		long msg_des = 1;
		long root = msg;
		long index = key;
		while (index)
		{
			if (index & 1)
				msg_des = (msg_des * root) % pkey;
			index >>= 1;
			root = (root * root) % pkey;
		}
		return msg_des;
	}

	Key RSA::produce_keys()
	{
		long prime1 = produce_prime();
		long prime2 = produce_prime();
		while (prime2 == prime1)
			prime2 = produce_prime();

		Key key;
		long euler = produce_euler(prime1, prime2);
		key.pkey = produce_pkey(prime1, prime2);
		key.ekey = produce_ekey(euler);
		key.dkey = produce_dkey(key.ekey, euler);
		return key;
	}

	long RSA::produce_pkey(const long prime1, const long prime2)
	{
		return prime1 * prime2;
	}

	long RSA::produce_euler(const long prime1, const long prime2)
	{
		return (prime1 - 1) * (prime2 - 1);
	}

	long RSA::produce_ekey(const long euler)
	{
		long ekey = 2;
		for(ekey; ekey < euler; ekey++)
		{
			if (ekey >= 2 && produce_gcd(ekey, euler) == 1)
				break;
			
		}
		return ekey;
	}

	long RSA::produce_dkey(const long ekey, const long euler)
	{
		long dkey = euler / ekey;
		while (true)
		{
			if (((dkey * ekey) % euler) == 1)
				break;
			else
				++dkey;
		}
		return dkey;
	}

	long RSA::produce_prime()
	{
		long prime = 0;
		srand(time(0));
		while (true)
		{
			prime = rand() % 100 + 100;
			if (IsPrime(prime))
				break;
		}
		return prime;
	}
	long RSA::produce_gcd(const long a, const long b)
	{
		long dividend = a;
		long divisor = b;
		long residual = dividend % divisor;
		while (residual)
		{
			dividend = divisor;
			divisor = residual;
			residual = dividend % divisor;
		}
		return divisor;
	}

	bool RSA::is_prime(const long digit)
	{
		int tmp = 2;
		while (tmp < digit)
			if (!(digit % tmp++))
				break;

		if (tmp == digit)
			return true;
		return false;
	}
}