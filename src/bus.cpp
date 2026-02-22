#include "bus.h"

Bus::Bus(Cartridge* cartridge) : cartridge(cartridge)
{
	bus_buffer.resize(IE_REGISTER_ADDR);
}

void Bus::norm_addr(std::uint16_t& address)
{
	// If it's Echo RAM we convert adress to WRAM
	if (ECHO_RAM_ADDR <= address && address < OAM_ADDR)
	{
		address -= ECHO_RAM_ADDR - WORK_RAM_ADDR;
	}

	address -= VIDEO_RAM_ADDR;
}

std::uint8_t Bus::read8(std::uint16_t address)
{
	std::uint8_t byte;
	read(address, &byte, 1);
	return byte;
}

std::uint16_t Bus::read16(std::uint16_t address)
{
	return static_cast<uint16_t>(read8(address)) | (static_cast<uint16_t>(read8(address + 1)) << 8);
}


void Bus::write8(std::uint16_t address, std::uint8_t value)
{
	write(address, &value, 1);
}

void Bus::write16(std::uint16_t address, std::uint16_t value)
{
	write8(address, static_cast<std::uint8_t>(value & 0xFF));
	write8(address + 1, static_cast<std::uint8_t>((value >> 8) & 0xFF));
}

void Bus::read(std::uint16_t address, std::uint8_t* buffer, std::uint16_t size)
{
	if (address < VIDEO_RAM_ADDR)
	{
		cartridge->read(address, buffer, size);
		return;
	}

	norm_addr(address);

	for (std::uint16_t i = 0; i < size; i++)
	{
		buffer[i] = bus_buffer[address + i];
	}
}

void Bus::write(std::uint16_t address, std::uint8_t* buffer, std::uint16_t size)
{
	if (address < VIDEO_RAM_ADDR)
	{
		cartridge->write(address, buffer, size);
		return;
	}

	norm_addr(address);

	for (std::uint16_t i = 0; i < size; i++)
	{
		bus_buffer[address + i] = buffer[i];
	}
}
