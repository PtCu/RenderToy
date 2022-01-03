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

#ifndef CORE_INTEGREATOR_H_
#define CORE_INTEGREATOR_H_

#include <glm/glm.hpp>
#include <core/defines.h>
#include <core/scene.h>
#include <core/camera.h>
#include <core/film.h>
namespace platinum
{
    class Integrator
    {
    public:
        virtual ~Integrator() = default;
        virtual void Render(const Scene& scene) = 0;
        glm::vec3 SpecularReflect(const Ray& ray, const Interaction& inter, const Scene& scene, int depth)const;
        glm::vec3 SpecularTransmit(const Ray& ray, const Interaction& inter, const Scene& scene, int depth)const;
    };
    struct RenderTile
    {
        int min_x, min_y, max_x, max_y;
        static constexpr int kTILE_SIZE = 16; // width = height = kTILE_SIZE

        RenderTile(int minx, int miny, int maxx, int maxy)
            : min_x(minx), min_y(miny), max_x(maxx), max_y(maxy) {}
    };
    class TilesManager
    {
    private:
        int _width;
        int _height;
        std::vector<RenderTile> _tiles;
        bool _is_abort;

    public:
        TilesManager(int x, int y) { init(x, y); }
        void init(int x, int y)
        {
            _width = x;
            _height = y;
            _tiles.clear();
            _is_abort = false;

            //The size of every tile is less or equal to RenderTile::kTILE_SIZE*RenderTile::kTILE_SIZE.
            for (int i = 0; i < x; i += RenderTile::kTILE_SIZE)
            {
                for (int j = 0; j < y; j += RenderTile::kTILE_SIZE)
                {
                    int min_x = i;
                    int min_y = j;
                    int max_x = std::min(min_x + RenderTile::kTILE_SIZE, x);
                    int max_y = std::min(min_y + RenderTile::kTILE_SIZE, y);

                    _tiles.emplace_back(min_x, min_y, max_x, max_y);
                }
            }
        }
        inline const RenderTile& GetTile(const int idx) const
        {
            assert(idx < (int)_tiles.size());
            return _tiles[idx];
        }
        inline int GetTilesCount() const
        {
            return (int)_tiles.size();
        }
        inline int GetWidth() const
        {
            return _width;
        }
        inline int GetHeight() const
        {
            return _height;
        }
        inline void SetAbort(const bool ab)
        {
            _is_abort = ab;
        }
        inline const bool Aborted() const
        {
            return _is_abort;
        }
    };
    class TiledIntegrator : public Integrator
    {
    public:
        TiledIntegrator(std::shared_ptr<Camera> camera, int spp, int max_depth = 10) : _camera(camera), _spp(spp), _max_depth(max_depth)
        {
            _tiles_manager = std::make_unique<TilesManager>(_camera->GetFilm()->GetWidth(), _camera->GetFilm()->GetHeight());
        }
        virtual void Render(const Scene& scene);


    protected:
        // Li() 方法计算有多少光照量沿着
        // 该 Ray 到达成像平面，并把光照量（radiance）保存在 Film 内
        virtual glm::vec3 Li(const Scene& scene, const Ray& ray, int depth) = 0;
        void UpdateProgress(float progress);
        std::shared_ptr<Camera> _camera;
        int _spp;
        std::mutex _mutex_ins;
        std::unique_ptr<TilesManager> _tiles_manager;
        int _max_depth;
    };

}

#endif