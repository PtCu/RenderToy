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

#include "perlin.h"

namespace platinum
{
    float Perlin::GenNoise(const glm::vec3 &p)
    {
        // pf 为小数部分
        glm::vec3 pf = p - glm::floor(p);
        // pi 为整数部分
        glm::ivec3 pi = glm::floor(p);
        // 8个位置的向量
        // 单位立方体8个顶点, 每个顶点一个随机向量
        glm::vec3 c[2][2][2];
        for (int dx = 0; dx < 2; dx++)
        {
            for (int dy = 0; dy < 2; dy++)
            {
                for (int dz = 0; dz < 2; dz++)
                {
                    size_t idx = perm_x_[(pi.x + dx) & 255] ^ perm_y_[(pi.y + dy) & 255] ^ perm_z_[(pi.z + dz) & 255];
                    c[dx][dy][dz] = rand_vec_[idx];
                }
            }
        }
        return PerlinInterp(c, pf.x, pf.y, pf.z);
    }
    float Perlin::PerlinInterp(const glm::vec3 c[2][2][2], float u, float v, float w)
    {
        auto f = [](float t) { return t * t * t * (t * (6 * t - 15) + 10); };
        float uu = f(u);
        float vv = f(v);
        float ww = f(w);
        float sum = 0;
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 2; j++)
            {
                for (size_t k = 0; k < 2; k++)
                {
                    // 顶点 到 插值点 的向量
                    glm::vec3 weightVec(u - i, v - j, w - k);
                    // 权值 为 插值点 到 [顶点对角] 的 xyz轴向 的 距离(非负) 的乘积
                    //vec3 absWeightVec = abs(vec3(u-(1-i),v-(1-j),w-(1-k)));
                    //float weight = absWeightVec.x * absWeightVec.y * absWeightVec.z;
                    float weight = (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) * (k * ww + (1 - k) * (1 - ww));
                    // 加权求和, 项为点乘, 从而达到了最值转移的作用(不在整数点上)
                    sum += weight * glm::dot(c[i][j][k], weightVec);
                }
            }
        }
        return sum;
    }

    float Perlin::Turb(const glm::vec3 &p, size_t depth)
    {
        float sum = 0;
        glm::vec3 curP = p;
        float weight = 1.0;
        for (size_t i = 0; i < depth; i++)
        {
            sum += weight * GenNoise(curP);
            // weight = pow(0.5, i);
            weight *= 0.5;
            // curP = p * pow(2, i);
            curP *= 2;
        }
        //float abs --> fabs
        return fabs(sum);
    }

    std::vector<size_t> Perlin::GenPermute(size_t n)
    {
        std::vector<size_t> rst(n);
        for (size_t i = 0; i < n; i++)
            rst[i] = i;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(rst.begin(), rst.end(), std::default_random_engine(seed));
        return rst;
    }

    std::vector<glm::vec3> Perlin::GenRandVec(size_t n)
    {
        std::vector<glm::vec3> rst(n);
        for (size_t i = 0; i < n; ++i)
            rst[i] = Random::RandomInUnitSphere();

        return rst;
    }

    std::vector<glm::vec3> Perlin::rand_vec_ = Perlin::GenRandVec(256);
    std::vector<size_t> Perlin::perm_x_ = Perlin::GenPermute(256);
    std::vector<size_t> Perlin::perm_y_ = Perlin::GenPermute(256);
    std::vector<size_t> Perlin::perm_z_ = Perlin::GenPermute(256);

}