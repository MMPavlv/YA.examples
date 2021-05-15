#pragma once

#include <string>
#include <iostream>
#include <vector>

namespace FSM
{
	enum lexem_type { VARIABLE, SET, OPERATOR, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, EMPTY, ERROR };
	typedef std::pair<lexem_type, std::string> lexem;

	class LexicalFSM
	{
	private:
		std::string expr;
		std::string::const_iterator index;
		std::string buf;

		enum symbol { LETTER, NUMERAL, OP, LPARENTHESIS, RPARENTHESIS, SPACE, WRONG_SYMBOL, END };
		symbol getType(char c);

		std::vector<lexem> lexems;


		void initHandler();
		void varHandler();
		void setHandler();
		void opHandler();
		void lParHandler();
		void rParHandler();
		void spaceHandler();

	public:
		LexicalFSM(std::string str):expr(str){};
		char getNextChar();
		std::vector<lexem> Parse();
	};
}