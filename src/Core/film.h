// Copyright 2021 ptcup
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CORE_FILM_H_
#define CORE_FILM_H_

#include <glm/glm.hpp>
#include <core/defines.h>
#include <core/image.h>

namespace platinum
{
    class Film
    {
    public:
        Film(const std::string &filename, int width, int height, int channel=3) : _width(width),
                                                                                _height(height),
                                                                                _filename(filename)
        {
            _img_size = _width * _height;
            _framebuffer.resize(_img_size, glm::vec3(0));
            _img.GenBuffer(_width, _height, channel);
        }
        void AddPixelValue(int idx, const glm::vec3 &color) { _framebuffer[idx] += color; }
        void SetPixel(int idx, const glm::vec3 &color) { _framebuffer[idx] = color; }
        glm::vec3 GetPixel(int idx) { return _framebuffer[idx]; }
        int GetWidth() { return _width; }
        int GetHeight() { return _height; }
        int GetImageSize() { return _img_size; }
        void SaveImage();

    private:
        int _width;
        int _height;
        int _img_size;
        std::vector<glm::vec3> _framebuffer;
        Image _img;
        std::string _filename;
    };
}

#endif