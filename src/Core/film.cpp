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
#include "film.h"

inline static float clamp(const float &lo, const float &hi, const float &v)
{
    return std::max(lo, std::min(hi, v));
}
namespace platinum
{

    void Film::SaveImage()
    {
#pragma omp parallel for schedule(dynamic, 1024)
        for (int px_id = 0; px_id < _img_size; ++px_id)
        {
            int i = px_id % _width;
            int j = px_id / _width;
            auto col = _framebuffer[px_id];
            col.r = std::pow(clamp(0, 1, col.r), 0.6f);
            col.g = std::pow(clamp(0, 1, col.g), 0.6f);
            col.b = std::pow(clamp(0, 1, col.b), 0.6f);
            glm::vec3 new_col(col.r, col.g, col.b);

            _img.SetPixel(i, j, new_col);
        }
        // UpdateProgress(1.f);
        _img.SaveAsPNG(_filename);
    }
}