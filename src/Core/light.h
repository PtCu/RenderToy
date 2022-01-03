// Copyright 2022 ptcup
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

#ifndef CORE_LIGHT_CPP_
#define CORE_LIGHT_CPP_
#include <glm/glm.hpp>
#include <core/ray.h>
#include <core/intersection.h>
#include <core/scene.h>

namespace platinum {
    class Light {
    public:
        Light() = default;
        virtual ~Light() = default;;
        virtual glm::vec3 Le(const Ray& r)const { return glm::vec3(0); };
        virtual glm::vec3 SampleLi(const Interaction& inter, float& pdf, glm::vec3& wi, VisibilityTester& vis)const;
        virtual float PdfLi(const Interaction&, const glm::vec3)const;
    };

    class VisibilityTester final {
    public:
        VisibilityTester() = default;
        VisibilityTester(const Interaction& p0, const Interaction& p1) :_p0(p0), _p1(p1) {

        }
        const Interaction& P0()const { return _p0; }
        const Interaction& P1()const { return _p1; }
        bool Unoccluded(const Scene& scene)const;
    private:
        Interaction _p0, _p1;
    };
}

#endif