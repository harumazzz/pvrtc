#pragma once
#include <vector>
#include <cstdint>

#include "Packet.h"

namespace PVRTC
{
	std::vector<uint8_t> decode_4bpp(
		const std::vector<Packet>& packets,
		int width
	);
}