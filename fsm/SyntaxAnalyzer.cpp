#include "SyntaxAnalyzer.hpp"

FSM::lexem FSM::SyntaxFSM::getEmpty()
{
	return lexem{EMPTY, ""};
}

void FSM::SyntaxFSM::initHandler()
{
	index = expr.begin();

	if (index == expr.end())
		return;

	auto c = *index;

	switch (c.first)
	{
	case VARIABLE:
		_left = c;
		varHandler();
		break;
	case SET:
		_left = c;
		varHandler();
		break;
	case OPERATOR: //ERROR
		break;
	case LEFT_PARENTHESIS:
		lParHandler();
		break;
	case RIGHT_PARENTHESIS: //ERROR
		break;
	case EMPTY:
		break;
	default:
		break;
	}
}

void FSM::SyntaxFSM::varHandler()
{
	auto c = getNextLexem();

	switch (c.first)
	{
	case VARIABLE: //ERROR
		break;
	case SET: //ERROR
		break;
	case OPERATOR:
		if(_right.first == EMPTY)
		{
			_op = c;
			opHandler();
		}
		else
		{
			if(getPriority(c) > getPriority(_op))
			{
				_left = _right;
				_op = c;
				_right = getEmpty();
				opHandler();
			}
			else
			{
				calculateHandler();
			}
		}
		break;
	case LEFT_PARENTHESIS: //ERROR
		break;
	case RIGHT_PARENTHESIS:
		if(_right.first == EMPTY)
		{
			truncateHandler();
		}
		else
		{
			calculateHandler();
		}
		break;
	case EMPTY:
		calculateHandler();
		break;
	default:
		break;
	}
}

void FSM::SyntaxFSM::opHandler()
{
	auto c = getNextLexem();

	switch (c.first)
	{
	case VARIABLE:
		_right = c;
		varHandler();
		break;
	case SET:
		_right = c;
		varHandler();
		break;
	case OPERATOR: //ERROR
		break;
	case LEFT_PARENTHESIS:
		_left = getEmpty();
		_op = getEmpty();
		_right = getEmpty();
		break;
	case RIGHT_PARENTHESIS: //ERROR
		break;
	case EMPTY: //ERROR
		break;
	default:
		break;
	}
}

void FSM::SyntaxFSM::lParHandler()
{
	auto c = getNextLexem();

	switch (c.first)
	{
	case VARIABLE:
		_left = c;
		varHandler();
		break;
	case SET:
		_left = c;
		varHandler();
		break;
	case OPERATOR: //ERROR
		break;
	case LEFT_PARENTHESIS:
		lParHandler();
		break;
	case RIGHT_PARENTHESIS:
		break;
	case EMPTY: //ERROR
		break; 
	default:
		break;
	}
}

void FSM::SyntaxFSM::rParHandler()
{
	auto c = getNextLexem();

	switch (c.first)
	{
	case VARIABLE: //ERROR
		break;
	case SET: //ERROR
		break;
	case OPERATOR:
		_op = c;
		opHandler();
		break;
	case LEFT_PARENTHESIS: //ERROR
		break;
	case RIGHT_PARENTHESIS:
		rParHandler();
		break;
	case EMPTY:
		break;
	default:
		break;
	}
}

void FSM::SyntaxFSM::calculateHandler()
{	
	auto new_l = calculate();
	index -= 3;
	int pos = index - expr.begin();

	expr.erase(index, index + 3);

	expr.insert(expr.begin()+pos, new_l);

	_left = getEmpty();
	_op = getEmpty();
	_right = getEmpty();
}

void FSM::SyntaxFSM::truncateHandler()
{
	if(index->first == RIGHT_PARENTHESIS && ((index-1)->first == SET || (index - 1)->first == VARIABLE) && (index-2)->first == LEFT_PARENTHESIS)
	{
		auto new_l = *(index - 1);
		index -= 2;
		int pos = index - expr.begin();
		expr.erase(index, index+3);

		expr.insert(expr.begin() + pos, new_l);
	}
}

FSM::lexem FSM::SyntaxFSM::calculate()
{
	if (_op.second == "=")
	{
		if(_left.first == VARIABLE)
		{
			std::string new_var_name = _left.second;
			variables[new_var_name] = SetLexem(_right.second);
			_left.second = _right.second;
			return variables[new_var_name].getLexem();
		}
		else
		{
			return lexem{ ERROR,"" };
		}
	}

	SetLexem first;
	SetLexem second;

	if(_left.first == VARIABLE)
	{
		if (variables.find(_left.second) != variables.end())
			first = variables[_left.second];
		else
			return lexem{ ERROR,"" };
	}
	else
	{
		first = SetLexem(_left.second);
	}

	if (_right.first == VARIABLE)
	{
		if (variables.find(_right.second) != variables.end())
			second = variables[_right.second];
		else
			return lexem{ ERROR,"" };
	}
	else
	{
		second = SetLexem(_right.second);
	}

	//

	if(_op.second == "+")
	{
		return SetLexem::Union(first, second).getLexem();
	}

	if(_op.second == "-")
	{
		return SetLexem::Difference(first, second).getLexem();
	}

	if (_op.second == "/")
	{
		return SetLexem::Intersection(first, second).getLexem();
	}

	if (_op.second == "~")
	{
		return SetLexem::SymmetricDifference(first, second).getLexem();
	}

	return lexem{ ERROR,"" };
}

int FSM::SyntaxFSM::getPriority(lexem l1)
{
	if (l1.first != OPERATOR )
		return 10;

	if (l1.second == "/" || l1.second == "~")
		return 2;

	if (l1.second == "+" || l1.second == "-")
		return 1;

	if (l1.second == "/=")
		return 0;

	return -1;
}

FSM::lexem FSM::SyntaxFSM::getNextLexem()
{
	if (++index == expr.end())
		return lexem{EMPTY, ""};

	return *index;
}

FSM::SetLexem FSM::SyntaxFSM::Evaluate()
{
	if (expr.empty())
		return SetLexem("");

	while(expr.size() != 1)
	{
		initHandler();
	}

	return SetLexem(expr[0].second);
}
