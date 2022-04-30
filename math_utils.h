#pragma once

#include "opengl_image_wrapper.h"
#include "check_util.h"

namespace mu {
	inline
	void AntialiasingFromSuperscaled(Image const& source, Image& destination) {
		check(source.GetWidth() == destination.GetWidth() * 2, ERR_SHAPE_MISMATCH);
		check(source.GetHeight() == destination.GetHeight() * 2, ERR_SHAPE_MISMATCH);

		for(int y = 0; y < destination.GetHeight(); ++y) {
			const int sourceY1 = y * 2;
			const int sourceY2 = sourceY1 + 1;

			for(int x = 0; x < destination.GetWidth(); ++x) {
				const int sourceX1 = x * 2;
				const int sourceX2 = sourceX1 + 1;

				Image::Color const& color1 = source.At(sourceX1, sourceY1).ColorValue;
				Image::Color const& color2 = source.At(sourceX1, sourceY2).ColorValue;
				Image::Color const& color3 = source.At(sourceX2, sourceY1).ColorValue;
				Image::Color const& color4 = source.At(sourceX2, sourceY2).ColorValue;

				float aMix = (color1.a + color2.a + color3.a + color4.a) / 4.f;
				float rMix = (color1.r + color2.r + color3.r + color4.r) / 4.f;
				float gMix = (color1.g + color2.g + color3.g + color4.g) / 4.f;
				float bMix = (color1.b + color2.b + color3.b + color4.b) / 4.f;

				Image::Color& destinationColor = destination.At(x, y).ColorValue;

				destinationColor.a = aMix;
				destinationColor.r = rMix;
				destinationColor.g = gMix;
				destinationColor.b = bMix;
			}
		}
	}

	inline
	void HSVtoRGB(float hue, float saturation, float value, float& r, float& g, float& b) {
		// thanks https://stackoverflow.com/a/6930407

		float      hh, p, q, t, ff;
		long        i;

		if(saturation <= 0.0) {
			r = value;
			g = value;
			b = value;
			return;
		}
		hh = hue;
		if(hh >= 360.0f) hh = 0.0f;
		hh /= 60.0f;
		i = (long) hh;
		ff = hh - i;
		p = value * (1.0f - saturation);
		q = value * (1.0f - (saturation * ff));
		t = value * (1.0f - (saturation * (1.0f - ff)));

		switch(i) {
			case 0:
				r = value;
				g = t;
				b = p;
				break;
			case 1:
				r = q;
				g = value;
				b = p;
				break;
			case 2:
				r = p;
				g = value;
				b = t;
				break;
			case 3:
				r = p;
				g = q;
				b = value;
				break;
			case 4:
				r = t;
				g = p;
				b = value;
				break;
			case 5:
			default:
				r = value;
				g = p;
				b = q;
				break;
		}
	}

}