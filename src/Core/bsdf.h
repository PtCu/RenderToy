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

#ifndef CORE_BSDF_CPP_
#define CORE_BSDF_CPP_

#include <core/defines.h>
#include <core/intersection.h>

namespace platinum {
    class BSDF {
    public:
        BSDF() = default;
        float Pdf(const glm::vec3& wo, const glm::vec3& wi) const;
        glm::vec3 F(const glm::vec3& woW, const glm::vec3& wiW)const;
        glm::vec3 SampleF(const glm::vec3& wo, const glm::vec3& wi, float& pdf)const;
    };
}


#endif