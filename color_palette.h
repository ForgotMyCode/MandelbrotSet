#pragma once

#include <cmath>
#include <numbers>

#include "opengl_image_wrapper.h"

class ColorPalette {
public:
	virtual Image::Color GetColorForValue(int value) const = 0;
};

template<float Scale>
class TriCosColorPalette : public ColorPalette {
public:
	Image::Color GetColorForValue(int value) const final override {
		float const r = -std::cosf(float(value) * PERIOD_BYTES<2>);
		float const g = -std::cosf(float(value) * PERIOD_BYTES<3>);
		float const b = -std::cosf(float(value) * PERIOD_BYTES<1>);

		Image::Color resultColor;
		resultColor.a = 0xFF;
		resultColor.r = std::floorf(127.f * (r + 1.f));
		resultColor.g = std::floorf(127.f * (g + 1.f));
		resultColor.b = std::floorf(127.f * (b + 1.f));

		return resultColor;
	}

private:
	template<int N>
	static constexpr float PERIOD_BYTES = Scale * 2.f * std::numbers::pi_v<float> / (float(N) * 255.f);
};

static
Image::Color SOME_NICE_SPECTRUM[16] = {
	{66, 30, 15, 0xFF},
	{25, 7, 26, 0xFF},
	{9, 1, 47, 0xFF},
	{4, 4, 73, 0xFF},
	{0, 7, 100, 0xFF},
	{12, 44, 138, 0xFF},
	{24, 82, 177, 0xFF},
	{57, 125, 209, 0xFF},
	{134, 181, 229, 0xFF},
	{211, 236, 248, 0xFF},
	{241, 233, 191, 0xFF},
	{248, 201, 95, 0xFF},
	{255, 170, 0, 0xFF},
	{204, 128, 0, 0xFF},
	{153, 87, 0, 0xFF},
	{106, 52, 3, 0xFF},
};

class CoolMappingPalette : public ColorPalette {
public:
	Image::Color GetColorForValue(int value) const final override {
		return SOME_NICE_SPECTRUM[value % 16];
	}
};