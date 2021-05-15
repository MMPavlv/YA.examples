#pragma once
#include <fstream>
#include <iterator>
#include <vector>
#include <fstream>
namespace Mathemagics
{
	__declspec(selectany) std::vector<byte> table;
	__declspec(selectany) int init_it = 0;
	void Encrypt(Platform::String^  path);
	///////

}