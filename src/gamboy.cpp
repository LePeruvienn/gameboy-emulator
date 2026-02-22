#include "cartridge.h"
#include "bus.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << argv[0] << ": usage <rom_path>." << std::endl;
		return 1;
	}

	Cartridge* cartrigde = new Cartridge(argv[1]);
	Bus* bus = new Bus(cartrigde);

	/* BU TESTS
	std::uint8_t byte;

	bus->read(0x0104, &byte);
	std::cout << "A: " << (int) byte << std::endl;

	bus->read(0x0134, &byte);
	std::cout << "B: " << (char) byte << std::endl;

	byte = 99;
	bus->write(0xC000, &byte);
	bus->read(0xC000, &byte);
	std::cout << "C: " << (int) byte << std::endl;

	bus->read(0xE000, &byte);
	std::cout << "D: " << (int) byte << std::endl;

	byte = 44;
	bus->write(0xFF80, &byte);
	bus->read(0xFF80, &byte);
	std::cout << "E: " << (int) byte << std::endl;

	bus->read(0x8000, &byte);
	std::cout << "F: " << (int) byte << std::endl;
	*/

	delete bus;
	delete cartrigde;

	return 0;
}
