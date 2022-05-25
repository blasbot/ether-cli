#pragma once
#include "commands.hpp"

class Shell
{
public:
	Shell();
	~Shell();

	void MainLoop();

private:
	Commands* CmdHandler;
};