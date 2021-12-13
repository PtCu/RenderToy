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

#include "img_texture.h"

namespace platinum
{
    ImgTexture::ImgTexture(const std::string &fileName, bool flip)
        : img_(new Image(fileName.c_str(), flip)) {}

    glm::vec3 ImgTexture::GetValue(float u, float v, const glm::vec3 &p) const
    {
        if (!img_->IsValid())
            return glm::vec3(0);

        size_t i = glm::clamp<float>(u * img_->GetWidth(), 0, img_->GetWidth() - 1);
        size_t j = glm::clamp<float>(v * img_->GetHeight(), 0, img_->GetHeight() - 1);

        auto pixel = img_->GetPixel_F(i, j);
        return glm::vec3(pixel.r, pixel.g, pixel.b);
    }

}
