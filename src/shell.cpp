#include "shell.hpp"
#include <iostream>
#include <io.h>
#include <sstream>
#include "commands.hpp"

#define STDIN_FILENO 0

Shell::Shell()
{
	this->CmdHandler = new Commands();
}

Shell::~Shell()
{
	delete this->CmdHandler;
}

void Shell::MainLoop()
{
	std::string cmd;

	int i = 0;
	while (1)
	{
		if (i == 1 && _isatty(STDIN_FILENO))
		{
			std::cout << "\n--> ";
		}
		else
		{
			i = 1;
		}

		std::getline(std::cin, cmd);

		if (cmd.compare("exit") == 0 ||
			cmd.compare("quit") == 0)
		{
			break;
		}

		std::vector<std::string> args;

		int i = 0;
		std::stringstream ss(cmd);
		while (ss.good() && i < 7)
		{
			std::string s;
			ss >> s;
			if (i == 0)
			{
				cmd = s;
			}
			else
			{
				args.push_back(s);
			}
			++i;
		}

		if (CmdHandler->Run(cmd, args) == 1)
		{
			std::cout << "An error occurred\n";
			break;
		}
	}
}