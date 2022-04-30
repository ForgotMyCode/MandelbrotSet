#pragma once

#include <algorithm>
#include <bit>

#include "check_util.h"

class Image {

private:

	using byte = unsigned char;

	/*
	template<decltype(std::endian::native) endianity>
	struct __Color {};

	template<>
	struct __Color<std::endian::big> {
		byte r : 8;
		byte g : 8;
		byte b : 8;
		byte a : 8;
	};

	template<>
	struct __Color<std::endian::little> {
		byte a : 8;
		byte b : 8;
		byte g : 8;
		byte r : 8;
	};
	*/

	struct __Color {
		byte r : 8;
		byte g : 8;
		byte b : 8;
		byte a : 8;
	};

public:

	//using Color = __Color<std::endian::native>;
	using Color = __Color;

	union Pixel {
		uint32_t IntValue;
		Color ColorValue;
	};

	Image() {}

	Image(int const width, int const height) 
		:
		Width(width),
		Height(height)
	{
		check(width * height >= 0, ERR_BAD_DIMENSION);

		this->Data = new Pixel[width * height]();

		check(this->Data, ERR_ALLOC_FAILED);
	}

	~Image() {
		if(Data)
			delete[] Data;
	}

	Image(Image const& image)
		:
		Width(image.GetWidth()),
		Height(image.GetHeight())
	{
		const int size = image.GetWidth() * image.GetHeight();

		check(size >= 0, ERR_BAD_DIMENSION);

		this->Data = new Pixel[size];
		std::copy(image.GetData(), image.GetData() + size, this->Data);
	}

	Image(Image&& image)
		:
		Width(image.GetWidth()),
		Height(image.GetHeight()),
		Handle(image.Handle)
	{
		std::swap(this->Data, image.Data);
	}

	Image operator = (Image const& image) = delete;

	Image operator = (Image const&& image) = delete;

	inline
	int GetWidth() const {
		return Width;
	}

	inline
	int GetHeight() const {
		return Height;
	}

	inline
	Pixel const* GetData() const {
		return Data;
	}

	inline
	Pixel& operator [] (int index) {
		return Data[index];
	}

	inline
	Pixel const& operator [] (int index) const {
		return Data[index];
	}

	inline
	Pixel& At(int x, int y) {
		return Data[y * Width + x];
	}

	inline
	Pixel const& At(int x, int y) const {
		return Data[y * Width + x];
	}

	inline
	unsigned int GetOpenGLtextureHandle() const {
		return Handle;
	}

	void RegisterOpenGLtexture();

	void UpdateOpenGLtexture() const;

	inline
	void SwapBufferWith(Image& other) {
		std::swap(this->Data, other.Data);
	}

private:
	const int Width = -1, Height = -1;
	Pixel* Data = nullptr;
	unsigned int Handle = 0;
};

static_assert(sizeof(Image::Pixel) == 4, "Color representation incompatible.");
