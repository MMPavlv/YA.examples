#include "pch.h"
#include "Header5.hpp"
#include <bitset>

Mathemagics::GF::GF(int q, unsigned long long n)
{ 
	this->q = q;
	auto n_ = n % static_cast<unsigned long long>(pow(2, q));
	num_ = BigInt(n_);
}

Mathemagics::GF::GF(int q, BigInt n)
{
	this->q = q;
	auto z = pow(BigInt(2), q);
	auto n_ = n % z;
	num_ = n_;
}

Mathemagics::GF::GF(BigInt q, BigInt n)
{
	this->q = q;
	this->num_ = n;
}

std::string Mathemagics::GF::BinaryOut()
{
	return ToBinaryString(num_);
}

std::string Mathemagics::GF::PolynomOut()
{
	auto result = BinaryOut();
	std::string out = "";
	int i = 0;
	for (auto c : result)
	{
		if (c == '1')
			out += "+x^" + std::to_string(result.length() - i - 1);
		i++;
	}
	if (out == "")
		out = "0";
	return out;
}

std::string Mathemagics::GF::Out()
{
	return num_.to_string();
}


BigInt Mathemagics::GF::GetIrreduciblePolynomials()
{
	if (this->q < 64)
		return BigInt(irreducible_polynomials[q.to_int() + 1]);
	
	auto v = out(q.to_long_long());
	BigInt a(0);
	for (auto g : v)
		a += pow(BigInt(2), g);
	return a;
}

std::string Mathemagics::GF::ToBinaryString(BigInt num)
{
	std::string result = "";
	do
	{
		result += (num % 2).to_string();
		num = num / 2;
	} while (num > 0);

	std::reverse(result.begin(), result.end());
	return result;
}

BigInt Mathemagics::GF::xor(BigInt a, BigInt b)
	{
	if (b > a)
		return xor (b, a);
	auto s1 = ToBinaryString(a);
	auto s2 = ToBinaryString(b);
	auto s3 = s1;

	for(auto i = 0; i < s2.length(); i++)
	{
		if (s1[s1.length() - 1 - i] == s2[s2.length() - 1 - i])
			s3[s3.length() - 1 - i] = '0';
		else
			s3[s3.length() - 1 - i] = '1';
	}

	BigInt out(0);

	for (auto i = 0; i < s3.length(); i++)
	{
		if(s3[s3.length() - 1 - i] == '1')
		{
			out += pow(BigInt(2), i);
		}
	}
	return out;
}

Mathemagics::GF Mathemagics::GF::GetMultiplicativeInverse()
{
	for (BigInt i = 0; i < pow(BigInt(2), q.to_long()); i++)
	{
		auto g = GF(this->q, i);//WHAT?!
		auto c = *this * g;
		if (c.num_ == 1)
			return GF(q,g.num_);
	}
	return GF(0,0);
}

Mathemagics::GF Mathemagics::GF::operator+(GF & rnum)
{
	auto z = xor(this->num_, rnum.num_);
	return GF(q, z);
}

Mathemagics::GF Mathemagics::GF::operator*(GF & rnum)
{
	std::map<int, int> mp;
	std::string s1 = ToBinaryString(this->num_);
	std::string s2 = ToBinaryString(rnum.num_);
	for (int i = 0; i < s1.length(); i++)
	{
		for (int j = 0; j < s2.length(); j++)
		{
			if (s1[s1.length() - 1 - i] == '1' && s2[s2.length() - 1 - j] == '1')
			{
				if (mp.find(i*j) == mp.end())
				{
					mp[i + j] = 1;
				}
				else
				{
					mp[i + j] += 1;
				}
			}
		}
	}

	BigInt c = 0;
	for (auto it = mp.rbegin(); it != mp.rend(); ++it)
	{
		it->second %= 2;
		if (it->second == 1)
		{
			c += pow(2, it->first);
		}

	}

	auto a = c;
	auto b = this->GetIrreduciblePolynomials();

	while (a >= b)
	{

		while (ToBinaryString(a).length() != ToBinaryString(b).length())
		{
			b *= 2;
		}
		a = xor(a,b);
		b = this->GetIrreduciblePolynomials();
	}

	if (b > a)
		a = xor(b,a);
	return GF(this->q,a);
}

Mathemagics::GF Mathemagics::GF::operator/(GF & rnum)
{
	for (BigInt i = 0; i < pow(BigInt(2), q.to_long()); i++)
	{
		auto g = GF(this->q,i);
		auto c = rnum * g;
		if (c.num_ == this->num_)
			return GF(this->q,c.num_);
	}
	return GF(0,0);
}
