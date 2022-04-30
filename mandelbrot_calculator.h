#pragma once

#include <omp.h>
#include <cmath>

#include "check_util.h"
#include "complex.h"

class ColorPalette;
class Image;

class MandelbrotCalculator {
public:
	MandelbrotCalculator(int width, int height, ColorPalette const& colorPalette)
		:
		HorizontalSamples(width),
		VerticalSamples(height),
		ColorPalette(colorPalette)
	{
		CountBuffer = new int[width * height]();
		ComplexValues = new Complex<float>[width * height]();

		check(CountBuffer, ERR_ALLOC_FAILED);
		check(ComplexValues, ERR_ALLOC_FAILED);
	}

	~MandelbrotCalculator() {
		delete[] CountBuffer;
		delete[] ComplexValues;
	}

	MandelbrotCalculator(MandelbrotCalculator const&) = delete;

	MandelbrotCalculator(MandelbrotCalculator const&&) = delete;

	MandelbrotCalculator operator = (MandelbrotCalculator const&) = delete;

	MandelbrotCalculator operator = (MandelbrotCalculator const&&) = delete;

	void Step(int minSteps = 1);

	inline
	void Update(float centerX, float centerY, float zoom) {
		bool isDirty = false;

		if(centerX != this->CenterX) {
			isDirty = true;

			const float offset = centerX - this->CenterX;

			this->CenterX += offset;
		}

		if(centerY != this->CenterY) {
			isDirty = true;

			const float offset = centerY - this->CenterY;

			this->CenterY += offset;
		}

		zoom = std::powf(2.f, zoom);

		if(zoom != this->Zoom) {
			isDirty = true;

			const float offset = zoom - this->Zoom;

			this->Zoom += offset;
		}

		this->bDirty = isDirty;
	}

	void Visualize(Image& writingBuffer);

	inline
	void Refresh() {
		if(bDirty) {
			Clear();
			bDirty = false;
		}
	}

	inline
	int GetMaxCount() {
		return this->MaxCount;
	}

private:
	inline
	int& CountAt(int x, int y) {
		return CountBuffer[y * HorizontalSamples + x];
	}

	inline
	Complex<float>& ValueAt(int x, int y) {
		return ComplexValues[y * HorizontalSamples + x];
	}

	bool UpdatePoint(int sampleX, int sampleY, Complex<float>& point);

	inline
	void Clear() {
		for(int i = 0; i < HorizontalSamples * VerticalSamples; ++i) {
			CountBuffer[i] = 0;

			ComplexValues[i].Real = 0.f;
			ComplexValues[i].Imaginary = 0.f;
		}

		this->MaxCount = 0;
	}

	int HorizontalSamples;
	int VerticalSamples;

	float CenterX;
	float CenterY;
	float Zoom;

	float WritebackTime;

	int* CountBuffer;
	Complex<float>* ComplexValues;
	int MaxCount = 0;
	bool bDirty = true;

	ColorPalette const& ColorPalette;
};