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

#include "whitted_integrator.h"

namespace platinum {
    glm::vec3 WhittedIntegrator::Li_rec(const Scene& scene, std::shared_ptr<Ray> ray, int depth) {
        if (depth == 0) return glm::vec3(0);
        auto hit_rst = scene.RayIntersect(ray);
        if (hit_rst.is_hit) {
            
        }
        return glm::vec3(0);
    }
    glm::vec3 WhittedIntegrator::Li(const Scene& scene, std::shared_ptr<Ray>ray) {
        return Li_rec(scene, ray, _max_depth);
    }
}
