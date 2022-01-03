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

#ifndef INTEGRATOR_PATH_INTEGRATOR_H_
#define INTEGRATOR_PATH_INTEGRATOR_H_

#include <core/integrator.h>

namespace platinum
{

    class PathIntegrator : public TiledIntegrator
    {
    public:
        PathIntegrator(std::shared_ptr<Camera> camera, int spp, int max_depth,float rr_threshold = 0.8) :TiledIntegrator(camera, spp,max_depth), _rr_threshold(rr_threshold) {}
    protected:
        virtual glm::vec3 Li(const Scene& scene, const Ray& ray,int depth);
        float _rr_threshold;
    };
}
#endif