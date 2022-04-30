#pragma once

#include <functional>
#include <GLFW/glfw3.h>

class Image;

class MandelbrotGui {
public:
	MandelbrotGui(Image& imageBuffer, GLFWerrorfun errorCallback)
		:
		fErrorCallback(errorCallback),
		Image(imageBuffer)
	{
	}

	void Init();

	void RenderUpdate(float deltaMs);

	void End();

	bool EndCondition() const;

	inline
	void GetViewConfiguration(float& centerX, float& centerY, float& zoom) const {
		centerX = this->CenterX;
		centerY = this->CenterY;
		zoom = this->Zoom;
	}

private:

	GLFWerrorfun fErrorCallback;

	int DisplayWidth = 1280;
	int DisplayHeight = 720;
	float CenterX = 0.f, CenterY = 0.f;
	float Zoom = 1.f;

	Image& Image;
	GLuint TextureHandle = 0;
	GLFWwindow* Window = nullptr;
};