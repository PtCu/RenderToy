// The MIT License (MIT)

// Copyright (c) 2021 PtCu

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#ifndef CORE_IMAGE_H_
#define CORE_IMAGE_H_

#include <string>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include  <stb/stb_image.h>
namespace platinum
{
	class Image
	{
	public:
		template <typename T>
		struct Pixel
		{
			Pixel(size_t channel)
				: channel(channel){};
			Pixel(T r, T g, T b)
				: r(r), g(g), b(b), channel(3){};
			Pixel(T r, T g, T b, T a)
				: r(r), g(g), b(b), a(a), channel(4){};

			T &operator[](size_t idx);
			const T &operator[](size_t idx) const;

			T r;
			T g;
			T b;
			T a;
			const size_t channel;
		};

		Image();
		Image(size_t width, size_t height, size_t channel);
		Image(const char *fileName, bool flip = false);
		~Image();
		//------------
		bool IsValid() const;
		unsigned char *GetData();
		const unsigned char *GetConstData() const;
		size_t GetWidth() const;
		size_t GetHeight() const;
		size_t GetChannel() const;
		//------------
		bool SetPixel(size_t x, size_t y, const Pixel<unsigned char> &pixel);
		bool SetPixel(size_t x, size_t y, const Pixel<float> &pixel);
		bool SetPixel(size_t x, size_t y, const Pixel<double> &pixel);
		bool SetPixel(size_t x, size_t y, const glm::vec3 &pixel);
		Pixel<unsigned char> GetPixel_UB(size_t x, size_t y) const;
		Pixel<float> GetPixel_F(size_t x, size_t y) const;
		Pixel<double> GetPixel_D(size_t x, size_t y) const;
		unsigned char &At(size_t x, size_t y, size_t channel);
		const unsigned char &At(size_t x, size_t y, size_t channel) const;
		//------------
		bool Load(const std::string &fileName, bool flip = false);
		void GenBuffer(size_t width, size_t height, size_t channel);
		void Free();
		bool SaveAsPNG(const std::string &fileName, bool flip = false) const;
		//------------
		static Pixel<unsigned char> Pixel_F2UB(const Pixel<float> &pixel);
		static Pixel<unsigned char> Pixel_D2UB(const Pixel<double> &pixel);
		static Pixel<float> Pixel_UB2F(const Pixel<unsigned char> &pixel);
		static Pixel<double> Pixel_UB2D(const Pixel<unsigned char> &pixel);
		//------------
		Image &operator=(const Image &img) = delete;

	private:
		enum ENUM_SRC_TYPE
		{
			ENUM_SRC_TYPE_INVALID,
			ENUM_SRC_TYPE_NEW,
			ENUM_SRC_TYPE_STB,
		};

		unsigned char *data;
		size_t width;
		size_t height;
		size_t channel;
		ENUM_SRC_TYPE type;
	};

	//------------

	template <typename T>
	T &Image::Pixel<T>::operator[](size_t idx)
	{
		switch (idx)
		{
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		case 3:
			return a;
		}
	}

	template <typename T>
	const T &Image::Pixel<T>::operator[](size_t idx) const
	{
		switch (idx)
		{
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		case 3:
			return a;
		}
	}

} // namespace platinum

#endif
