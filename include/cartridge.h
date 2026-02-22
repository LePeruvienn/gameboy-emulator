#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <string>
#include <cstdint>
#include <vector>

typedef struct header_s
{
	std::string title;
	std::uint8_t type;
	std::uint64_t rom_size;
	std::uint64_t ram_size;
	bool nintendo_logo_ok;
	bool checksum_ok;
	bool global_checksum_ok;

} header_t;

class Cartridge
{

public:

	Cartridge(const std::string& rom_str);
	void read(std::uint16_t adress, std::uint8_t* buffer, std::uint16_t size = 1);
	void write(std::uint16_t adress, std::uint8_t* buffer, std::uint16_t size = 1);

private:

	static constexpr std::uint16_t ENTRY_POINT_ADDR = 0x0100;
	static constexpr std::uint16_t NINTENDO_LOGO_START_ADDR = 0x0104;
	static constexpr std::uint16_t NINTENDO_LOGO_END_ADDR = 0x0133;
	static constexpr std::uint16_t GAME_NAME_START_ADDR = 0x0134;
	static constexpr std::uint16_t GAME_NAME_END_ADDR = 0x0143;

	static constexpr std::uint16_t TYPE_ADDR = 0x0147;
	static constexpr std::uint16_t ROM_SIZE_ADDR = 0x0148;
	static constexpr std::uint16_t RAM_SIZE_ADDR = 0x0149;

	static constexpr std::uint16_t HEADER_CHECKSUM_ADDR = 0x014D;
	static constexpr std::uint16_t GLOBAL_CHECKSUM_ADDR = 0x014E;

	static constexpr std::uint16_t GAME_NAME_BYTE_SIZE = GAME_NAME_END_ADDR - GAME_NAME_START_ADDR + 1;
	static constexpr std::uint16_t NINTENDO_LOGO_BYTE_SIZE = NINTENDO_LOGO_END_ADDR - NINTENDO_LOGO_START_ADDR + 1;

	static constexpr std::uint8_t nintendo_logo_ref[NINTENDO_LOGO_BYTE_SIZE] = { 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
	                                                                             0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
	                                                                             0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
	                                                                             0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
	                                                                             0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
	                                                                             0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

	std::string file_path;
	std::uint64_t file_size;

	std::vector<std::uint8_t> rom_buffer;
	header_t header;

	void read_data();

	void setup_header();
	void print_header();

	bool is_nintendo_logo_ok();
	bool is_checksum_ok();
	bool is_global_checksum_ok();
};

#endif // CARTRIDGE_H
