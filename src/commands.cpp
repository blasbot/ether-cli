#include "commands.hpp"
#include "shell.hpp"
#include "app.hpp"

Commands::Commands()
{
	this->commands["help"] = Function{ &Help, 0 };
	this->commands["publickey"] = Function{ &PublicKey, 0 };
	this->commands["address"] = Function{ &Address, 0 };
	this->commands["rawtx"] = Function{ &RawTx, 6 };
	this->commands["balance"] = Function{ &Balance, 0 };
	this->commands["balanceof"] = Function{ &BalanceOf, 1 };
}

int Commands::Run(std::string cmd, std::vector<std::string> args)
{
	if (cmd.size() == 0)
		return 0;

	// Check if command exists
	if (this->commands.count(cmd))
	{
		Function& f = commands[cmd];
		if (args.size() != f.len)
		{
			std::cout << "Invalid amount of parameters, please use the help command\n";
			return 0;
		}

		f.f(args);
	}

	return 0;
}

int PublicKey(std::vector<std::string> _)
{
	std::cout << factory->PublicKey() << "\n";
	return 0;
}

int Address(std::vector<std::string> _)
{
	std::cout << factory->WalletAddress() << "\n";
	return 0;
}

int RawTx(std::vector<std::string> args)
{
	std::cout << factory->CreateRawTransaction(args.at(0), args.at(1), args.at(2), args.at(3), args.at(4), args.at(5));
	return 0;
}

int Balance(std::vector<std::string> _)
{
	BalanceResult* result = api->Balance(factory->WalletAddress(), "latest");

	std::string nS = result->balance.str();
	int n = 18 - nS.size();
	if (n > 0)
	{
		std::cout << "0." << std::string(n, '0') << nS;
	}
	else if (n == 0)
	{
		std::cout << "0." << nS;
	}
	else
	{
		std::string a = nS.substr(0, -n);
		std::string b = nS.substr(-n);

		std::cout << a << "." << b;
	}

	delete result;
	return 0;
}

int BalanceOf(std::vector<std::string> args)
{
	BalanceResult* result = api->Balance(args.at(0), "latest");

	std::string nS = result->balance.str();
	int n = 18 - nS.size();
	if (n > 0)
	{
		std::cout << "0." << std::string(n, '0') << nS;
	}
	else if (n == 0)
	{
		std::cout << "0." << nS;
	}
	else
	{
		std::string a = nS.substr(0, -n);
		std::string b = nS.substr(-n);

		std::cout << a << "." << b;
	}

	delete result;
	return 0;
}

int Help(std::vector<std::string> _)
{
	std::cout << "Commands:\n";
	std::cout << " - publickey   >> Get the public key corresponding with your private key.\n";
	std::cout << " - address     >> Get your wallet address.";
	std::cout << " - rawtx       >> Manufacture a raw transaction.";
	std::cout << " - balance     >> Get the balance of the current wallet.";
	std::cout << " - balanceof   >> Get the balance of a given wallet.";
	return 0;
}