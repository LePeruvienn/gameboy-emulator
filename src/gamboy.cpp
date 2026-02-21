#include "cartridge.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << argv[0] << ": usage <rom_path>." << std::endl;
		return 1;
	}

	Cartridge* cartrigde = new Cartridge(argv[1]);
	delete cartrigde;

	return 0;
}
