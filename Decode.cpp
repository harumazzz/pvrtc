#include "Decode.h"
#include "Morton.h"

namespace PVRTC
{
	std::vector<uint8_t> decode_4bpp(
		const std::vector<Packet>& packets,
		int width
	)
	{
		auto blocks = width >> 2;
		auto blockMask = blocks - 1;
		auto result = std::vector<uint8_t>((width * width) * 4, 0x00);

		for (int y = 0; y < blocks; ++y)
		{
			for (int x = 0; x < blocks; ++x)
			{
				auto packet = packets[get_morton_number(x, y)];
				auto mod = packet.get_modulation_data();
				auto weights = Packet::WEIGHTS;
				auto weightindex = packet.get_use_punch_through_alpha() ? 16 : 0;
				auto factorfather = Packet::BILINEAR_FACTORS;
				int factorindex = 0;

				for (int py = 0; py < 4; ++py)
				{
					auto yOffset = (py < 2) ? -1 : 0;
					auto y0 = (y + yOffset) & blockMask;
					auto y1 = (y0 + 1) & blockMask;

					for (int px = 0; px < 4; ++px)
					{
						auto factor = factorfather[factorindex];
						auto xOffset = (px < 2) ? -1 : 0;
						auto x0 = (x + xOffset) & blockMask;
						auto x1 = (x0 + 1) & blockMask;

						auto p0 = packets[get_morton_number(x0, y0)];
						auto p1 = packets[get_morton_number(x1, y0)];
						auto p2 = packets[get_morton_number(x0, y1)];
						auto p3 = packets[get_morton_number(x1, y1)];

						auto ca = p0.get_color_alpha_color_rgba() * factor[0] + p1.get_color_alpha_color_rgba() * factor[1] + p2.get_color_alpha_color_rgba() * factor[2] + p3.get_color_alpha_color_rgba() * factor[3];
						auto cb = p0.get_color_blue_color_rgba() * factor[0] + p1.get_color_blue_color_rgba() * factor[1] + p2.get_color_blue_color_rgba() * factor[2] + p3.get_color_blue_color_rgba() * factor[3];

						auto index = weightindex + (((int)mod & 0b11) << 2);
						auto current_index = ((py + (y << 2)) * width + px + (x << 2)) * 4;

						result[current_index] = static_cast<uint8_t>(((ca.red) * weights[index] + cb.red * weights[index + 1]) >> 7);
						result[current_index + 1] = static_cast<uint8_t>(((ca.green * weights[index] + cb.green * weights[index + 1]) >> 7));
						result[current_index + 2] = static_cast<uint8_t>(((ca.blue * weights[index] + cb.blue * weights[index + 1]) >> 7));
						result[current_index + 3] = static_cast<uint8_t>(((ca.alpha * weights[index + 2] + cb.alpha * weights[index + 3]) >> 7));

						mod >>= 2;
						++factorindex;
					}
				}
			}
		}

		return result;
	}
}