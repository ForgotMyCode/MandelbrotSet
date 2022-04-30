#include "mandelbrot_calculator.h"

#include "complex.h"
#include "opengl_image_wrapper.h"
#include "color_palette.h"

void MandelbrotCalculator::Step(int minSteps) {
	const float xFrom = this->CenterX + (- 1.f / this->Zoom);
	const float xTo = this->CenterX + (1.f / this->Zoom);

	const float yFrom = this->CenterY + (-1.f / this->Zoom);
	const float yTo = this->CenterY + (1.f / this->Zoom);

	const float horizontalStepSize = (xTo - xFrom) / float(this->HorizontalSamples);
	const float verticalStepSize = (yTo - yFrom) / float(this->VerticalSamples);

	#pragma omp parallel for
	for(int y = 0; y < this->VerticalSamples; ++y) {
		Complex<float> samplePoint(0, yFrom + float(horizontalStepSize * float(y)));

		for(int x = 0; x < this->HorizontalSamples; ++x) {
			samplePoint.Real = xFrom + float(verticalStepSize * float(x));

			for(int step = 0; step < minSteps; ++step) {
				bool isUpdated = UpdatePoint(x, y, samplePoint);

				if(!isUpdated) {
					break;
				}
			}
		}
	}

	this->MaxCount += minSteps;
}

void MandelbrotCalculator::Visualize(Image& writingBuffer) {
	for(int y = 0; y < this->VerticalSamples; ++y) {
		for(int x = 0; x < this->HorizontalSamples; ++x) {
			Image::Color& color = writingBuffer.At(x, y).ColorValue;

			const int value = this->CountAt(x, y);

			if(value > 0 && value < MaxCount) {
				color = this->ColorPalette.GetColorForValue(value);
			}
			else {
				color.r = 0;
				color.g = 0;
				color.b = 0;
				color.a = 0xFF;
			}
		}
	}
}

bool MandelbrotCalculator::UpdatePoint(int sampleX, int sampleY, Complex<float>& point) {
	Complex<float>& currentValue = this->ValueAt(sampleX, sampleY);

	if(currentValue.SquaredSize() > 4.f) {
		return false;
	}

	currentValue.Square().Add(point);

	++(this->CountAt(sampleX, sampleY));

	return true;
}