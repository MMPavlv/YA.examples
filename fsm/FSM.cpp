#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
int main()
{
	FSM::LexicalFSM a("a=5+4");
	auto res = a.Parse();

	for (auto it = res.begin(); it != res.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

	std::cout << std::endl;


	FSM::SyntaxFSM e(res);
	auto rs = e.Evaluate();
	std::cout << rs.getLexem().second << std::endl;

	system("pause");
    return 0;
}