#pragma once
#include "LexicalAnalyzer.hpp"
#include <set>

namespace FSM
{
	class SetLexem
	{
	private:
		std::set<int> _set;

	public:
		SetLexem() = default;
		SetLexem(std::string str);
		SetLexem(std::set<int> s):_set(s) {}
		std::set<int> getSet();
		lexem getLexem();

		static SetLexem Union(SetLexem &s1, SetLexem &s2);
		static SetLexem Difference(SetLexem &s1, SetLexem &s2);
		static SetLexem Intersection(SetLexem &s1, SetLexem &s2);
		static SetLexem SymmetricDifference(SetLexem &s1, SetLexem &s2);
	};
}
