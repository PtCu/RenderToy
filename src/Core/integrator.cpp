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
#include "integrator.h"

namespace platinum
{
    glm::vec3 Integrator::SpecularReflect(const Ray& ray, const Interaction& inter, const Scene& scene, int depth)const {
        return glm::vec3(0);

    }
    glm::vec3 Integrator::SpecularTransmit(const Ray& ray, const Interaction& inter, const Scene& scene, int depth)const {
        return glm::vec3(0);

    }

    void TiledIntegrator::UpdateProgress(float progress)
    {
        int barWidth = 70;

        std::cout << "[";
        int pos = static_cast<int>(barWidth * progress);
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < pos)
                std::cout << "=";
            else if (i == pos)
                std::cout << ">";
            else
                std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();
    };

    void TiledIntegrator::Render(const Scene& scene)
    {
        auto film = this->_camera->GetFilm();
        int width = film->GetWidth();
        int height = film->GetHeight();
        int img_size = film->GetImageSize();

        int has_finished_num = 0;
        auto calculateRstForEachTile = [&](int rank)
        {
            const RenderTile& tile = _tiles_manager->GetTile(rank);

            for (size_t i = tile.min_x; i < tile.max_x; ++i)
            {
                for (size_t j = tile.min_y; j < tile.max_y; ++j)
                {
                    int px_id = j * width + i;
                    for (int k = 0; k < _spp; k++)
                    {
                        float u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(width);
                        float v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(height);
                        auto r = _camera->GetRay(u, v);
                        auto rst = Li(scene, r, 0);
                        film->AddPixelValue(px_id, rst / static_cast<float>(_spp));
                    }
                    ++has_finished_num;
                    ++px_id;
                }
                // 互斥锁，用于打印处理进程（加上之后影响速度，变为顺序执行）
                // std::lock_guard<std::mutex> g1(_mutex_ins);
                // UpdateProgress(static_cast<float>(has_finished_num) / img_size);
            }
        };

        //concurrency::parallel_for in ppl.h is windows only, so here I just choose thread function.
        std::vector<std::thread> threads(_tiles_manager->GetTilesCount());

        for (int i = 0; i < _tiles_manager->GetTilesCount(); ++i)
        {
            threads[i] = std::move(std::thread(calculateRstForEachTile, i));
        }
        for (auto& th : threads)
        {
            th.join();
        }
        UpdateProgress(1.f);
        film->SaveImage();

        // // 分块计算光线追踪
        // for (int i = 0; i < width; i += kTILESIZE)
        // {
        //     for (int j = 0; j < height; j += kTILESIZE)
        //     {
        //         int min_i = i;
        //         int max_i = std::min(i + kTILESIZE, width);
        //         int min_j = j;
        //         int max_j = std::min(j + kTILESIZE, height);

        //         th[id] = std::thread(calculateRstForEachTile, i,max_i,j,max_j));
        //         id++;
        //     }
        // }
        // for (int i = 0; i < tile_width * tile_height; i++)
        //     th[i].join();

        // for (int cnt = 1; cnt <= _spp; ++cnt)
        // {
        //     for (int px_id = 0; px_id < img_size; ++px_id)
        //     {
        //         int i = px_id % width;
        //         int j = px_id / width;
        //         float u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(width);
        //         float v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(height);

        //         auto r = _camera->GetRay(u, v);
        //         auto rst = scene.CastRay(r);
        //         auto result = rst / static_cast<float>(_spp);
        //         film->AddPixelValue(px_id, result);

        //     }
        //     UpdateProgress(static_cast<float>(cnt) / _spp);
        // }
    }

}