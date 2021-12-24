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

#ifndef INTEGRATOR_WHITTED_INTEGRATOR_H_
#define INTEGRATOR_WHITTED_INTEGRATOR_H_

#include "core/integrator.h"

namespace platinum
{

    class WhittedIntegrator : public TiledIntegrator
    {
    public:
        WhittedIntegrator(std::shared_ptr<Camera> camera, int spp, int max_depth = 10) :TiledIntegrator(camera, spp), _max_depth(_max_depth){}
    protected:
        virtual glm::vec3 Li(const Scene& scene, std::shared_ptr<Ray>ray);
    private:
        virtual glm::vec3 Li_rec(const Scene& scene, std::shared_ptr<Ray>ray,int depth);
        int _max_depth;
    };
}

#endif