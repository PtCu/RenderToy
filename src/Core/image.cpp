#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include  <stb/stb_image_write.h>

using namespace platinum;
using namespace std;

Image::Pixel<unsigned char> Image::Pixel_F2UB(const Pixel<float> &pixel)
{
    Image::Pixel<unsigned char> rst(pixel.channel);
    for (size_t i = 0; i < pixel.channel; i++)
    {
        float mappedVal = 255.99f * pixel[i];
        rst[i] = static_cast<unsigned char>(mappedVal >= 256.0f ? 255 : static_cast<unsigned char>(mappedVal));
    }

    return rst;
}

Image::Pixel<unsigned char> Image::Pixel_D2UB(const Pixel<double> &pixel)
{
    Image::Pixel<unsigned char> rst(pixel.channel);
    for (size_t i = 0; i < pixel.channel; i++)
    {
        double mappedVal = 255.99 * pixel[i];
        rst[i] = static_cast<unsigned char>(mappedVal >= 256.0 ? 255 : static_cast<unsigned char>(mappedVal));
    }

    return rst;
}

Image::Pixel<float> Image::Pixel_UB2F(const Pixel<unsigned char> &pixel)
{
    Image::Pixel<float> rst(pixel.channel);
    for (size_t i = 0; i < pixel.channel; i++)
        rst[i] = 1.0f / 255.0f * pixel[i];

    return rst;
}

Image::Pixel<double> Image::Pixel_UB2D(const Pixel<unsigned char> &pixel)
{
    Image::Pixel<double> rst(pixel.channel);
    for (size_t i = 0; i < pixel.channel; i++)
        rst[i] = 1.0 / 255.0 * pixel[i];

    return rst;
}

//------------

Image::Image()
    : data(NULL), _width(0), _height(0), _channel(0), type(ENUM_SRC_TYPE_INVALID) {}

Image::Image(size_t width, size_t height, size_t channel)
{
    GenBuffer(width, height, channel);
}

Image::Image(const char *fileName, bool flip)
{
    data = NULL;
    type = ENUM_SRC_TYPE_INVALID;
    Load(fileName, flip);
}

Image::~Image()
{
    Free();
}

//-----------

bool Image::IsValid() const
{
    return data != NULL && type != ENUM_SRC_TYPE_INVALID;
}

unsigned char *Image::GetData()
{
    if (!IsValid())
        return NULL;

    return data;
}

const unsigned char *Image::GetConstData() const
{
    if (!IsValid())
        return NULL;

    return data;
}

size_t Image::GetWidth() const
{
    return _width;
}

size_t Image::GetHeight() const
{
    return _height;
}

size_t Image::GetChannel() const
{
    return _channel;
}

//------------

unsigned char &Image::At(size_t x, size_t y, size_t channel)
{
    return data[(y * _width + x) * this->_channel + channel];
}

const unsigned char &Image::At(size_t x, size_t y, size_t channel) const
{
    return data[(y * _width + x) * this->_channel + channel];
}

bool Image::SetPixel(size_t x, size_t y, const Pixel<unsigned char> &pixel)
{
    if (pixel.channel != this->_channel)
        return false;

    for (size_t i = 0; i < _channel; i++)
        At(x, y, i) = pixel[i];

    return true;
}

bool Image::SetPixel(size_t x, size_t y, const Image::Pixel<float> &pixel)
{
    return SetPixel(x, y, Pixel_F2UB(pixel));
}

bool Image::SetPixel(size_t x, size_t y, const glm::vec3 &pixel)
{
    return SetPixel(x, y, Pixel_F2UB(Image::Pixel<float>(pixel.r, pixel.g, pixel.b)));
}

bool Image::SetPixel(size_t x, size_t y, const Image::Pixel<double> &pixel)
{
    return SetPixel(x, y, Pixel_D2UB(pixel));
}

Image::Pixel<unsigned char> Image::GetPixel_UB(size_t x, size_t y) const
{
    Pixel<unsigned char> rst(_channel);
    for (size_t i = 0; i < _channel; i++)
        rst[i] = At(x, y, i);

    return rst;
}

Image::Pixel<float> Image::GetPixel_F(size_t x, size_t y) const
{
    return Pixel_UB2F(GetPixel_UB(x, y));
}

Image::Pixel<double> Image::GetPixel_D(size_t x, size_t y) const
{
    return Pixel_UB2D(GetPixel_UB(x, y));
}

//------------

bool Image::Load(const std::string &fileName, bool flip)
{
    Free();

    stbi_set_flip_vertically_on_load(flip);

    int tmpW, tmpH, tmpC;
    data = stbi_load(fileName.c_str(), &tmpW, &tmpH, &tmpC, 0);
    _width = tmpW;
    _height = tmpH;
    _channel = tmpC;

    if (data == NULL)
    {
        type = ENUM_SRC_TYPE_INVALID;
        return false;
    }

    type = ENUM_SRC_TYPE_STB;
    return true;
}
void Image::GenBuffer(size_t width, size_t height, size_t channel)
{
    Free();
    this->_width = width;
    this->_height = height;
    this->_channel = channel;

    data = new unsigned char[width * height * channel]();
    type = ENUM_SRC_TYPE_NEW;
}

void Image::Free()
{
    if (data != NULL)
    {
        switch (type)
        {
        case Image::ENUM_SRC_TYPE_NEW:
            delete[] data;
            break;
        case Image::ENUM_SRC_TYPE_STB:
            stbi_image_free(data);
            break;
        case Image::ENUM_SRC_TYPE_INVALID:
        default:
            break;
        }
    }

    _width = 0;
    _height = 0;
    _channel = 0;
    data = NULL;
    type = ENUM_SRC_TYPE_INVALID;
}

bool Image::SaveAsPNG(const string &fileName, bool flip) const
{
    stbi_flip_vertically_on_write(flip);
    return stbi_write_png(fileName.c_str(), _width, _height, _channel, data, _width * 3);
}
