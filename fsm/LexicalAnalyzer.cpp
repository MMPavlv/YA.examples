#include "LexicalAnalyzer.hpp"
#include <locale>
#include <cctype>

char FSM::LexicalFSM::getNextChar()
{
	if (++index == expr.end())
		return '\n';

	return *index;
}

std::vector<FSM::lexem> FSM::LexicalFSM::Parse()
{
	initHandler();

	return lexems;
}

FSM::LexicalFSM::symbol FSM::LexicalFSM::getType(char c)
{
	if (std::isalpha(c)) 
		return LETTER;

	if (std::isdigit(c))
		return NUMERAL;

	if (c == '@' || c == '+' || c == '-' || c == '~' || c == '/' || c == '=')
		return OP;

	if (c == '(')
		return LPARENTHESIS;

	if (c == ')')
		return RPARENTHESIS;

	if (c == ' ')
		return SPACE;

	if (c == '\n')
		return END;

	return WRONG_SYMBOL;
}

void FSM::LexicalFSM::initHandler()
{
	index = expr.begin();

	if(index == expr.end())
		return;

	auto c = *index;

	switch (getType(c))
	{
	case LETTER:
		buf += c;
		varHandler();
		break;
	case NUMERAL:
		buf += c;
		setHandler();
		break;
	case OP: //ERROR
		break;
	case LPARENTHESIS:
		buf = c;
		lParHandler();
		break;
	case RPARENTHESIS: //ERROR
		break;
	case SPACE:
		buf = "";
		spaceHandler();
		break;
	case WRONG_SYMBOL: //ERROR
		break;
	case END:
		break;
	}
}

void FSM::LexicalFSM::varHandler()
{
	auto c = getNextChar();

	switch (getType(c))
	{
	case LETTER:
		buf += c;
		varHandler();
		break;
	case NUMERAL: //ERROR
		break;
	case OP:
		lexems.emplace_back(VARIABLE, buf);
		buf = c;
		opHandler();
		break;
	case LPARENTHESIS: //ERROR
		break;
	case RPARENTHESIS:
		lexems.emplace_back(VARIABLE, buf);
		buf = c;
		rParHandler();
		break;
	case SPACE:
		lexems.emplace_back(VARIABLE, buf);
		buf = "";
		spaceHandler();
		break;
	case WRONG_SYMBOL: //ERROR
		break;
	case END:
		lexems.emplace_back(VARIABLE, buf);
		break;
	}
}

void FSM::LexicalFSM::setHandler()
{
	auto c = getNextChar();

	switch (getType(c))
	{
	case LETTER: //ERROR
		break;
	case NUMERAL:
		buf += c;
		setHandler();
		break;
	case OP:
		lexems.emplace_back(SET, buf);
		buf = c;
		opHandler();
		break;
	case LPARENTHESIS: //ERROR
		break;
	case RPARENTHESIS:
		lexems.emplace_back(SET, buf);
		buf = c;
		rParHandler();
		break;
	case SPACE:
		lexems.emplace_back(SET, buf);
		buf = "";
		spaceHandler();
		break;
	case WRONG_SYMBOL: //ERROR
		break;
	case END:
		lexems.emplace_back(SET, buf);
		break;;
	}
}

void FSM::LexicalFSM::opHandler()
{
	auto c = getNextChar();

	switch (getType(c))
	{
	case LETTER:
		lexems.emplace_back(OPERATOR, buf);
		buf = c;
		varHandler();
		break;
	case NUMERAL: //ERROR
		lexems.emplace_back(OPERATOR, buf);
		buf = c;
		setHandler();
		break;
	case OP: //ERROR
		break;
	case LPARENTHESIS:
		lexems.emplace_back(OPERATOR, buf);
		buf = c;
		lParHandler();
		break;
	case RPARENTHESIS: //ERROR
		break;
	case SPACE:
		lexems.emplace_back(OPERATOR, buf);
		buf = "";
		spaceHandler();
		break;
	case WRONG_SYMBOL: //ERROR
		break;
	case END: //ERROR
		break;
	}
}

void FSM::LexicalFSM::lParHandler()
{
	auto c = getNextChar();

	switch (getType(c))
	{
	case LETTER:
		lexems.emplace_back(LEFT_PARENTHESIS, buf);
		buf = c;
		varHandler();
		break;
	case NUMERAL:
		lexems.emplace_back(LEFT_PARENTHESIS, buf);
		buf = c;
		setHandler();
		break;
	case OP: //ERROR
		break;
	case LPARENTHESIS:
		lexems.emplace_back(LEFT_PARENTHESIS, buf);
		buf = c;
		lParHandler();
		break;
	case RPARENTHESIS: 
		lexems.emplace_back(LEFT_PARENTHESIS, buf);
		buf = c;
		rParHandler();
		break;
	case SPACE:
		lexems.emplace_back(LEFT_PARENTHESIS, buf);
		buf = "";
		spaceHandler();
		break;
	case WRONG_SYMBOL: //ERROR
		break;
	case END: //ERROR
		break;;
	}
}

void FSM::LexicalFSM::rParHandler()
{
	auto c = getNextChar();

	switch (getType(c))
	{
	case LETTER: //ERROR
		break;
	case NUMERAL: //ERROR
		break;
	case OP: 
		lexems.emplace_back(RIGHT_PARENTHESIS, buf);
		buf = c;
		opHandler();
		break;
	case LPARENTHESIS: //ERROR
		break;
	case RPARENTHESIS:
		lexems.emplace_back(RIGHT_PARENTHESIS, buf);
		buf = c;
		rParHandler();
		break;
	case SPACE:
		lexems.emplace_back(RIGHT_PARENTHESIS, buf);
		buf = "";
		spaceHandler();
		break;
	case WRONG_SYMBOL: //ERROR
		break;
	case END:
		lexems.emplace_back(RIGHT_PARENTHESIS, buf);
		break;
	}
}

void FSM::LexicalFSM::spaceHandler()
{
	auto c = getNextChar();

	switch (getType(c))
	{
	case LETTER:
		buf += c;
		varHandler();
		break;
	case NUMERAL:
		buf += c;
		setHandler();
		break;
	case OP: //ERROR
		break;
	case LPARENTHESIS:
		buf = c;
		lParHandler();
		break;
	case RPARENTHESIS: //ERROR
		break;
	case SPACE:
		buf = "";
		spaceHandler();
		break;
	case WRONG_SYMBOL: //ERROR
		break;
	case END:
		break;
	}
}
