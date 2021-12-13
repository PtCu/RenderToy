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
#include "defines.h"

namespace platinum
{
    struct RenderTile
    {
        int min_x, min_y, max_x, max_y;
        static const int TILE_SIZE = 32;

        RenderTile(int minx, int miny, int maxx, int maxy)
            : min_x(minx), min_y(miny), max_x(maxx), max_y(maxy) {}
    };

    class TaskSynchronizer
    {
    private:
        int m_x, m_y;
        std::vector<RenderTile> m_tiles;

        bool m_abort;

    public:
        TaskSynchronizer(const int x, const int y)
        {
            init(x, y);
        }

        void init(const int x, const int y)
        {
            m_x = x;
            m_y = y;
            m_tiles.clear();
            m_abort = false;

            for (int i = 0; i < y; i += RenderTile::TILE_SIZE)
            {
                for (int j = 0; j < x; j += RenderTile::TILE_SIZE)
                {
                    int min_x = j;
                    int min_y = i;
                    int max_x = glm::min(min_x + RenderTile::TILE_SIZE, x);
                    int max_y = glm::min(min_y + RenderTile::TILE_SIZE, y);

                    m_tiles.emplace_back(min_x, min_y, max_x, max_y);
                }
            }
        }

        inline const RenderTile &getTile(const int idx) const
        {
            assert(idx < (int)m_tiles.size());
            return m_tiles[idx];
        }
        inline int getTilesCount() const
        {
            return (int)m_tiles.size();
        }
        inline int getX() const
        {
            return m_x;
        }
        inline int getY() const
        {
            return m_y;
        }
        inline void setAbort(const bool ab)
        {
            m_abort = ab;
        }
        inline const bool aborted() const
        {
            return m_abort;
        }
    };

    class Integrator
    {
    public:
        Integrator(const TaskSynchronizer &task, const uint32_t &spp)
            : m_task(task), m_spp(spp) {}

        virtual void render(const Scene *scene, const Camera *camera) = 0;
        virtual ~Integrator() {}

    protected:
        const TaskSynchronizer &m_task;
        const uint32_t &m_spp;
    };
}

#endif