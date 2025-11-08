#pragma once
#include <vector>
#include <cstdint>

#include "Packet.h"
#include "Rgba32.h"

namespace PVRTC
{
	std::vector<Packet> encode_rgba_4bpp(
		const std::vector<uint8_t>& color,
		int width
	);

	std::vector<Packet> encode_rgb_4bpp(
		const std::vector<uint8_t>& color,
		int width
	);
}
