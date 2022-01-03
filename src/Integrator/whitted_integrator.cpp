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
    glm::vec3 WhittedIntegrator::LiRecur(const Scene& scene, const Ray& ray, int depth) {
        if (depth == 0) return glm::vec3(0);
        auto hit_rst = scene.RayIntersect(ray);
        glm::vec3 L;
        SurfaceInteraction inter;
        if (!hit_rst.is_hit) {

            //返回lights emission
            for (const auto& light : scene._lights)
                L += light->Le(ray);
            return L;
        }
        const glm::vec3& n(inter.n);
        glm::vec3 wo(inter.wo);

        inter.computeScatteringFunctions(ray);
        // There is no bsdf funcion
        if (!inter.bsdf)
        {
            // return LiRecur(scene, inter.spawnRay());
        }
        L += inter.Le(wo);

        //对每个光源，计算其贡献
        for (const auto& light : scene._lights) {
            float pdf;
            glm::vec3 wi;
            glm::vec3 Li = light->SampleLi(inter, pdf, wi);
            if (pdf == 0) continue;


        }
        return glm::vec3(0);
    }
    glm::vec3 WhittedIntegrator::Li(const Scene& scene, const Ray& ray) {
        return LiRecur(scene, ray, _max_depth);
    }
}
