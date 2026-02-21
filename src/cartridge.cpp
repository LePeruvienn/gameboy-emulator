#include "cartridge.h"
#include <iostream>
#include <fstream>

Cartridge::Cartridge(const std::string& file_path) : file_path(file_path)
{
	std::cout << "Loading rom : " << file_path << std::endl;

	read_data();
	setup_header();
	print_header();
}

void Cartridge::read_data() {

	std::ifstream ifs(file_path, std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::runtime_error("failed to open file.");
	}

	ifs.seekg(0, std::ios::end);
	file_size = ifs.tellg() ;
	ifs.seekg(0, std::ios::beg);

	rom_buffer.resize(file_size);
	ifs.read(reinterpret_cast<char*>(rom_buffer.data()), file_size);

	if (!ifs)
		throw std::runtime_error("failed to read entire file");
}

void Cartridge::setup_header()
{
	char* title_start = reinterpret_cast<char*>(&rom_buffer[GAME_NAME_START_ADDR]);

	header.title = std::string(title_start, GAME_NAME_BYTE_SIZE);

	header.type = rom_buffer[TYPE_ADDR];

	header.rom_size = 1024 * 32 * (1 << rom_buffer[ROM_SIZE_ADDR]);

	switch (rom_buffer[RAM_SIZE_ADDR]) {

		case 0x00: header.ram_size = 0;          break;

		case 0x01: header.ram_size = 2   * 1024; break;
		case 0x02: header.ram_size = 8   * 1024; break;
		case 0x03: header.ram_size = 32  * 1024; break;
		case 0x04: header.ram_size = 128 * 1024; break;
		case 0x05: header.ram_size = 64  * 1024; break;

		default: header.ram_size = 0; break;
	}

	header.nintendo_logo_ok = is_nintendo_logo_ok();
	header.checksum_ok = is_checksum_ok();
	header.global_checksum_ok = is_global_checksum_ok();
}

void Cartridge::print_header()
{
	std::cout << " ---- ROM HEADER ---- \n";
	std::cout << "Title           : " << header.title          << "\n";
	std::cout << "Type            : " << (int) header.type     << "\n";
	std::cout << "ROM size        : " << header.rom_size       << "\n";
	std::cout << "RAM size        : " << header.ram_size       << "\n";
	std::cout << "Logo            : " << (header.nintendo_logo_ok   ? "OK" : "KO!") << std::endl;
	std::cout << "Checksum        : " << (header.checksum_ok        ? "OK" : "KO!") << "\n";
	std::cout << "Global checksum : " << (header.global_checksum_ok ? "OK" : "KO!") << "\n";
	std::cout << " -------------------- \n";
}

bool Cartridge::is_nintendo_logo_ok()
{
	for (size_t i = 0; i < NINTENDO_LOGO_BYTE_SIZE; i++)
	{
		if (nintendo_logo_ref[i] != rom_buffer[NINTENDO_LOGO_START_ADDR + i])
			return false;
	}

	return true;
}

bool Cartridge::is_checksum_ok()
{
	// from https://gbdev.io/pandocs/The_Cartridge_Header.html#014d--header-checksum
	std::uint8_t checksum = 0;
	for (std::uint16_t i = 0x0134; i <= 0x014C; i++)
	{
		checksum = checksum - rom_buffer[i] - 1;
	}

	std::uint8_t checksum_ref = rom_buffer[HEADER_CHECKSUM_ADDR];

	return checksum == checksum_ref;
}

bool Cartridge::is_global_checksum_ok()
{
	std::uint16_t global_checksum = 0;

	std::uint16_t global_checksum_ref =
		(static_cast<std::uint16_t>(rom_buffer[GLOBAL_CHECKSUM_ADDR]) << 8) | rom_buffer[GLOBAL_CHECKSUM_ADDR + 1];

	for (std::uint16_t i = ENTRY_POINT_ADDR; i < GLOBAL_CHECKSUM_ADDR; i++)
	{
		global_checksum += rom_buffer[i];
	}

	// std::cout << global_checksum << " == " << global_checksum_ref << std::endl;

	return global_checksum == global_checksum_ref;
}
