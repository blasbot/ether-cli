#include <iostream>
#include "shell.hpp"
#include "wrapper.hpp"
#include "sender.hpp"
#include "app.hpp"
#include <filesystem>
#include <fstream>

Getter* getter = nullptr;
Sender* sender = nullptr;

namespace fs = std::filesystem;

void prep(std::string* rpcUri, std::string* privKey)
{
	std::cout << "Please enter the RPC-uri you would like to use (http://localhost:8545): ";

	std::cin >> *rpcUri;
	if ((*rpcUri).size() == 0)
	{
		*rpcUri = "http://localhost:8545";
	}

	if (!fs::exists("wallets") || !fs::is_directory("wallets"))
	{
		fs::create_directory("wallets");
	}

	for (;;)
	{
		std::string walletName;
		std::cout << "Name the wallet you would like to open/create: ";
		std::cin >> walletName;

		walletName = ("wallets/" + walletName + ".eth");

		FILE* f = fopen(walletName.c_str(), "r");
		if (f == NULL)
		{
			Keypair kp = sender->CreatePair();
			*privKey = kp.privateKey;

			std::ofstream nf;
			nf.open(walletName);
			nf << kp.privateKey;
			nf.close();

			std::cout << "New wallet created!\n";
			break;
		}
		else
		{
			char* key = new char[65];
			size_t n = 0;
			int c;

			while ((c = fgetc(f)) != EOF && n < 64)
			{
				key[n++] = (char)c;
			}
			key[n] = '\0';

			fclose(f);

			if (n == 64)
			{
				std::string s(key);
				*privKey = s;
				break;
			}

			std::cout << "Invalid key.\n";
		}
	}
}

int main()
{
	std::string rpcUri, privKey;
	prep(&rpcUri, &privKey); // Now we at least have a clean main function

	Wrapper wr = Wrapper(rpcUri);
	getter = new Getter(&wr);
	sender = new Sender(&wr, privKey);

	// Start the main loop
	Shell shell = Shell();
	shell.MainLoop();

	// Cleanup
	delete getter;
	delete sender;

	return 0;
}
