#ifndef BUS_H
#define BUS_H

#include "cartridge.h"
#include <cstdint>
#include <vector>

class Bus
{

public:

	Bus(Cartridge* cartridge);

	std::uint8_t read8(std::uint16_t address);
	std::uint16_t read16(std::uint16_t address);

	void write8(std::uint16_t address, std::uint8_t value);
	void write16(std::uint16_t address, std::uint16_t value);

	void read(std::uint16_t address, std::uint8_t* buffer, std::uint16_t size = 1);
	void write(std::uint16_t address, std::uint8_t* buffer, std::uint16_t size = 1);

private:

	static constexpr std::uint16_t VIDEO_RAM_ADDR = 0x8000;
	static constexpr std::uint16_t EXTERNAL_RAM_ADDR = 0xA000;
	static constexpr std::uint16_t WORK_RAM_ADDR = 0xC000;
	static constexpr std::uint16_t ECHO_RAM_ADDR = 0xE000;
	static constexpr std::uint16_t OAM_ADDR = 0xFE00;
	static constexpr std::uint16_t UNUSED_ADDR = 0xFEA0;
	static constexpr std::uint16_t IO_REGISTERS_ADDR = 0xFF00;
	static constexpr std::uint16_t HIGH_RAM_ADDR = 0xFF80;
	static constexpr std::uint16_t IE_REGISTER_ADDR = 0xFFFF;

	static constexpr std::uint16_t WORK_RAM_SIZE = 8192;
	static constexpr std::uint16_t HIGH_RAM_SIZE = 127;
	static constexpr std::uint16_t IO_REGISTERS_SIZE = 128;

	Cartridge* cartridge;

	std::vector<std::uint8_t> bus_buffer;

	void norm_addr(std::uint16_t& address);
};

#endif // BUS_H
