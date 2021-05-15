#pragma once
#include "LexicalAnalyzer.hpp"
#include "SetLexem.hpp"
#include <map>
#include <iostream>

namespace FSM
{
	class SyntaxFSM
	{
	private:
		std::vector<lexem> expr;
		std::vector<lexem>::const_iterator index;
		std::map<std::string, SetLexem> variables;

		lexem _left = lexem{ EMPTY, "" };
		lexem _op = lexem{ EMPTY, "" };
		lexem _right = lexem{ EMPTY, "" };

		lexem getEmpty();


		int mode = -1;

		void initHandler();
		void varHandler();
		void opHandler();
		void lParHandler();
		void rParHandler();
		void calculateHandler();
		void truncateHandler();

		lexem calculate();

		int getPriority(lexem l1);
	public:
		SyntaxFSM(std::vector<lexem> lexs):expr(lexs) {};
		lexem getNextLexem();

		SetLexem Evaluate();
	};
}
