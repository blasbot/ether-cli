#pragma once
#include <iostream>
#include <unordered_map>

template <typename T>
using FnPtr = int(*)(T);

struct Function
{
	FnPtr<std::vector<std::string>> f;
	int len;
};

// C style prototypes
int Help(std::vector<std::string>);
int PublicKey(std::vector<std::string>);
int RawTx(std::vector<std::string> args);
int Address(std::vector<std::string>);
int Balance(std::vector<std::string>);
int BalanceOf(std::vector<std::string> args);

class Commands
{
public:
	Commands();

	int Run(std::string cmd, std::vector<std::string> args);
private:
	std::unordered_map<std::string, Function> commands;
};