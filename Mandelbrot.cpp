// Mandelbrot.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Mandelbrot.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "opengl_image_wrapper.h"
#include "complex.h"
#include "mandelbrot_calculator.h"
#include "mandelbrot_gui.h"
#include "math_utils.h"
#include "color_palette.h"

using namespace std;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void start() {
	const int areaShapeWidth = 1280;
	const int areaShapeHeight = 720;

	bool useSSAA = true;

	Image buffer(areaShapeWidth, areaShapeHeight);
	Image SSAAbuffer(2 * areaShapeWidth, 2 * areaShapeHeight);

	MandelbrotGui gui(buffer, glfw_error_callback);
	gui.Init(); // Initializes OpenGL

	const int minSteps = 10;
	const int maxSteps = 100;

	CoolMappingPalette colorPalette;

	MandelbrotCalculator mandelbrotCalculator(2 * areaShapeWidth, 2 * areaShapeHeight, colorPalette);


	{
		do {
			// Get Configuration (Center + Zoom)
			float cx, cy, zoom;
			gui.GetViewConfiguration(cx, cy, zoom);

			// Apply Configuration
			mandelbrotCalculator.Update(cx, cy, zoom);

			// Refresh, make sure the calculator sees the new values
			mandelbrotCalculator.Refresh();
			

			// Perform Calculation step, this step is Parallel, but synchronized
			if(mandelbrotCalculator.GetMaxCount() < maxSteps) {
				mandelbrotCalculator.Step(minSteps);
			}

			// Visualize
			mandelbrotCalculator.Visualize(SSAAbuffer);

			// Perform antialiasing (Write from SSAA -> buffer)
			mu::AntialiasingFromSuperscaled(SSAAbuffer, buffer);

			// Render everything
			gui.RenderUpdate(-1.0f);
		} while(!gui.EndCondition());

		gui.End();
	}
}

int main(int, char**)
{
	start();

	return 0;
}
