#include "pch.h"
#include "Stage2.hpp"
#include <iostream>
#include <cmath>
#include <intrin.h>

unsigned long long Mathemagics::PowerOf2Divider(unsigned long long num)
{
	return static_cast<unsigned long long>(std::floor(std::log2((num & (~(num - 1))))));
}

unsigned long long Mathemagics::Closest2Divider(unsigned long long num)
{
	return static_cast<unsigned long long>(std::floor(std::log2(num)));
}

unsigned long long Mathemagics::AllBitsXor(unsigned long long num)
{
	if (__popcnt64(num) % 2 == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

unsigned long long Mathemagics::CyclicShiftLeft(unsigned long long num, int pos)
{
	auto bits_len = (int)log2(num) + 1;
	pos %= bits_len;
	auto l1 = (num << pos) & static_cast<int>(pow(2, bits_len)) - 1;
	auto l2 = num >> (bits_len - pos);
	return l1 + l2;
}

unsigned long long Mathemagics::CyclicShiftRight(unsigned long long num, int pos)
{
	auto bits_len = (int)log2(num) + 1;
	pos %= bits_len;
	auto r1 = (num << (bits_len - pos)) & static_cast<int>(pow(2, bits_len)) - 1;
	auto r2 = num >> pos;
	return r1 + r2;
}
