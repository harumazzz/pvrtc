#include "Encode.h"
#include "Morton.h"
#include "Common.h"
#include "ColorRGB.h"
#include "ColorRGBA.h"

namespace PVRTC
{
	std::vector<Packet> encode_rgba_4bpp(
		const std::vector<uint8_t>& color,
		int width
	)
	{
		auto blocks = width >> 2;
		auto blockMask = blocks - 1;
		auto result = std::vector<Packet>{};
		result.resize(((width * width) >> 4));
		auto min_color = Rgba32{};
		auto max_color = Rgba32{};

		for (int y = 0; y < blocks; ++y)
		{
			for (int x = 0; x < blocks; ++x)
			{
				calculate_bounding_box(color, width, x, y, min_color, max_color);
				
				auto packet = Packet{};
				packet.set_use_punch_through_alpha(false);
				packet.set_color_alpha_color_rgba(min_color);
				packet.set_color_blue_color_rgba(max_color);
				result[get_morton_number(x, y)] = packet;
			}
		}

		for (int y = 0; y < blocks; ++y)
		{
			for (int x = 0; x < blocks; ++x)
			{
				auto factorfather = Packet::BILINEAR_FACTORS;
				int factor_index = 0;
				auto data_index = (y << 2) * width + (x << 2);
				auto modulation_data = static_cast<uint32_t>(0);

				for (int py = 0; py < 4; ++py)
				{
					auto y_pos = (py < 2) ? -1 : 0;
					auto y0 = (y + y_pos) & blockMask;
					auto y1 = (y0 + 1) & blockMask;

					for (int px = 0; px < 4; ++px)
					{
						auto factor = factorfather[factor_index];
						auto x_pos = (px < 2) ? -1 : 0;
						auto x0 = (x + x_pos) & blockMask;
						auto x1 = (x0 + 1) & blockMask;

						auto p0 = result[get_morton_number(x0, y0)];
						auto p1 = result[get_morton_number(x1, y0)];
						auto p2 = result[get_morton_number(x0, y1)];
						auto p3 = result[get_morton_number(x1, y1)];

						auto ca = p0.get_color_alpha_color_rgba() * factor[0] + p1.get_color_alpha_color_rgba() * factor[1] + p2.get_color_alpha_color_rgba() * factor[2] + p3.get_color_alpha_color_rgba() * factor[3];
						auto cb = p0.get_color_blue_color_rgba() * factor[0] + p1.get_color_blue_color_rgba() * factor[1] + p2.get_color_blue_color_rgba() * factor[2] + p3.get_color_blue_color_rgba() * factor[3];

						auto pixel_index = (data_index + py * width + px) * 4;
						auto d = cb - ca;
						auto p = ColorRGBA(
							color[pixel_index] << 4,
							color[pixel_index + 1] << 4,
							color[pixel_index + 2] << 4,
							color[pixel_index + 3] << 4);
						auto v = p - ca;
						auto projection = (v % d) << 4;
						auto length_squared = d % d;

						if (projection > 3 * length_squared){
							++modulation_data;
						}
						if (projection > 8 * length_squared){
							++modulation_data;
						}
						if (projection > 13 * length_squared){
							++modulation_data;
						}
						modulation_data = rotate_right(modulation_data, 2);
						++factor_index;
					}
				}

				result[get_morton_number(x, y)].set_modulation_data(modulation_data);
			}
		}

		return result;
	}

	std::vector<Packet> encode_rgb_4bpp(
		const std::vector<uint8_t>& color,
		int width
	)
	{
		auto blocks = width >> 2;
		auto blockMask = blocks - 1;
		auto result = std::vector<Packet>{};
		result.resize(((width * width) >> 4));
		auto min_color = Rgba32{};
		auto max_color = Rgba32{};

		for (int y = 0; y < blocks; ++y)
		{
			for (int x = 0; x < blocks; ++x)
			{
				calculate_bounding_box(color, width, x, y, min_color, max_color);
				
				auto packet = Packet{};
				packet.set_use_punch_through_alpha(false);
				packet.set_color_alpha_color_rgb(min_color);
				packet.set_color_blue_color_rgb(max_color);
				result[get_morton_number(x, y)] = packet;
			}
		}

		for (int y = 0; y < blocks; ++y)
		{
			for (int x = 0; x < blocks; ++x)
			{
				auto factorfather = Packet::BILINEAR_FACTORS;
				int factor_index = 0;
				auto data_index = (y << 2) * width + (x << 2);
				auto modulation_data = static_cast<uint32_t>(0);

				for (int py = 0; py < 4; ++py)
				{
					auto y_pos = (py < 2) ? -1 : 0;
					auto y0 = (y + y_pos) & blockMask;
					auto y1 = (y0 + 1) & blockMask;

					for (int px = 0; px < 4; ++px)
					{
						auto factor = factorfather[factor_index];
						auto x_pos = (px < 2) ? -1 : 0;
						auto x0 = (x + x_pos) & blockMask;
						auto x1 = (x0 + 1) & blockMask;

						auto p0 = result[get_morton_number(x0, y0)];
						auto p1 = result[get_morton_number(x1, y0)];
						auto p2 = result[get_morton_number(x0, y1)];
						auto p3 = result[get_morton_number(x1, y1)];

						auto ca = p0.get_color_alpha_color_rgb() * factor[0] + p1.get_color_alpha_color_rgb() * factor[1] + p2.get_color_alpha_color_rgb() * factor[2] + p3.get_color_alpha_color_rgb() * factor[3];
						auto cb = p0.get_color_blue_color_rgb() * factor[0] + p1.get_color_blue_color_rgb() * factor[1] + p2.get_color_blue_color_rgb() * factor[2] + p3.get_color_blue_color_rgb() * factor[3];

						auto pixel_index = (data_index + py * width + px) * 4;
						auto d = cb - ca;
						auto p = ColorRGB(
							color[pixel_index] << 4,
							color[pixel_index + 1] << 4,
							color[pixel_index + 2] << 4
						);
						auto v = p - ca;
						auto projection = (v % d) << 4;
						auto length_squared = d % d;

						if (projection > 3 * length_squared) {
							++modulation_data;
						}
						if (projection > 8 * length_squared) {
							++modulation_data;
						}
						if (projection > 13 * length_squared) {
							++modulation_data;
						}
						modulation_data = rotate_right(modulation_data, 2);
						++factor_index;
					}
				}

				result[get_morton_number(x, y)].set_modulation_data(modulation_data);
			}
		}

		return result;
	}
}