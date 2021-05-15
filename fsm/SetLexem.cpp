#include "SetLexem.hpp"
#include <iterator>
#include <algorithm>

FSM::SetLexem::SetLexem(std::string str)
{
	for (char c: str)
	{
		if (isdigit(c))
			_set.insert(std::stoi(std::string{ c }));
		else
		{
			_set.clear();
			return;
		}
	}
}

std::set<int> FSM::SetLexem::getSet()
{
	return _set;
}

FSM::lexem FSM::SetLexem::getLexem()
{
	std::string res;
	for (auto el : _set)
	{
		res += std::to_string(el);
	}
	return lexem{SET, res};
}

FSM::SetLexem FSM::SetLexem::Union(SetLexem & s1, SetLexem & s2)
{
	std::set<int> res;
	auto st1 = s1.getSet();
	auto st2 = s2.getSet();
	std::set_union(st1.begin(), st1.end(), st2.begin(), st2.end(), std::inserter(res, res.begin()));
	return SetLexem(res);
}

FSM::SetLexem FSM::SetLexem::Difference(SetLexem & s1, SetLexem & s2)
{
	std::set<int> res;
	auto st1 = s1.getSet();
	auto st2 = s2.getSet();
	std::set_difference(st1.begin(), st1.end(), st2.begin(), st2.end(), std::inserter(res, res.begin()));
	return SetLexem(res);
}

FSM::SetLexem FSM::SetLexem::Intersection(SetLexem & s1, SetLexem & s2)
{
	std::set<int> res;
	auto st1 = s1.getSet();
	auto st2 = s2.getSet();
	std::set_intersection(st1.begin(), st1.end(), st2.begin(), st2.end(), std::inserter(res, res.begin()));
	return SetLexem(res);
}

FSM::SetLexem FSM::SetLexem::SymmetricDifference(SetLexem & s1, SetLexem & s2)
{
	std::set<int> res;
	auto st1 = s1.getSet();
	auto st2 = s2.getSet();
	std::set_symmetric_difference(st1.begin(), st1.end(), st2.begin(), st2.end(), std::inserter(res, res.begin()));
	return SetLexem(res);
}
