// The MIT License (MIT)

// Copyright (c) 2021 PtCU

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

#include "scene.h"

namespace platinum
{
    Scene::~Scene()
    {
        destroyAll();
    }
    void Scene::destroyAll()
    {
        objects.clear();
    }
    void Scene::BuildBVH()
    {
        this->bvh_accel = std::unique_ptr<BVHAccel>(new BVHAccel(objects));
    }
    void Scene::AddObject(const std::shared_ptr<Object> &obj)
    {
        this->objects.push_back(obj);
    }
    void Scene::AddObject(const std::vector<std::shared_ptr<Object>> &obj)
    {
        this->objects.insert(objects.end(), obj.begin(), obj.end());
    }
    void Scene::AddObject(const std::vector<std::shared_ptr<Object>>::iterator &begin, const std::vector<std::shared_ptr<Object>>::iterator &end)
    {
        this->objects.insert(objects.end(), begin, end);
    }
    void Scene::Reset()
    {
        this->bvh_accel.reset();
        this->destroyAll();
    }
    Intersection Scene ::intersectAll(std::shared_ptr<Ray> &r) const
    {
        return this->bvh_accel->RayCast(r);
    }
    void Scene::sampleLight(Intersection &inter, float &pdf) const
    {
        float emit_area_sum = 0;
        for (uint32_t k = 0; k < objects.size(); ++k)
        {
            //计算发光物体的总面积
            if (objects[k]->GetMaterial()->IsEmit())
            {
                emit_area_sum += objects[k]->GetArea();
            }
        }
        float p = Random::RandomInUnitFloat() * emit_area_sum;
        emit_area_sum = 0;
        for (uint32_t k = 0; k < objects.size(); ++k)
        {
            //找到光源
            if (objects[k]->GetMaterial()->IsEmit())
            {
                emit_area_sum += objects[k]->GetArea();
                if (p <= emit_area_sum)
                {
                    //按概率选取一条光线
                    objects[k]->Sample(inter, pdf);
                    break;
                }
            }
        }
    }
    glm::vec3 Scene::CastRay(std::shared_ptr<Ray> &r) const
    {
        return CastRay(r, max_depth);
    }
    glm::vec3 Scene::CastRay(std::shared_ptr<Ray> &ray, int dep) const
    {

        // auto rec = intersectAll(ray);
        // if (!rec.happened || dep == 0)
        // {
        //     return glm::vec3(1.0001f / 255.0f);
        // }

        // if (rec.happened)
        // {
        //     if (rec.material == NULL)
        //         return glm::vec3(0, 1, 0);
        //     if (rec.material->Scatter(rec))
        //         return CastRay(ray, dep - 1);
        //     else
        //         return ray->GetColor();
        // }

        //求一条光线与场景的交点
        Intersection objInter = intersectAll(ray);
        if (!objInter.happened)
        {
            return glm::vec3(0.f);
        }
        glm::vec3 hitColor(0.f);

        // 采样光源点
        float light_pdf;
        Intersection lightInter;
        sampleLight(lightInter, light_pdf);
        glm::vec3 obj2light = lightInter.vert.pos - objInter.vert.pos;
        glm::vec3 obj2lightDir = glm::normalize(obj2light);
        auto toLightRay = std::make_shared<Ray>(objInter.vert.pos, obj2lightDir);
        glm::vec3 Lo_dir(0.f), Lo_indir(0.f);
        glm::vec3 w_o = -glm::normalize(ray->GetDirection()), w_i;
        glm::vec3 objN = glm::normalize(objInter.vert.normal);
        glm::vec3 lightN = normalize(lightInter.vert.normal);
        if (intersectAll(toLightRay).ray->GetMaxTime() - glm::length(obj2light) > -EPSILON)
        {
            //直接光照
            //入射方向为光源射向物体，出射方向（所求的方向)为参数ray的方向
            glm::vec3 f_r = objInter.material->ScatterPdf(obj2lightDir, w_o, objInter);
            //对光源采样
            float r2 = glm::dot(obj2light, obj2light);
            float cosA = std::max(.0f, glm::dot(objN, obj2lightDir));
            float cosB = std::max(.0f, glm::dot(lightN, -obj2lightDir));
            Lo_dir = lightInter.ray->GetColor() * f_r * cosA * cosB / r2 / light_pdf;
        }
        hitColor += Lo_dir;
        if (Random::RandomInUnitFloat() < RussianRoulette)
        {
            //间接光照
            w_i = glm::normalize(objInter.material->Sample(w_o, objInter));
            float cos = std::max(.0f, glm::dot(w_i, objN));
            glm::vec3 f_r = objInter.material->ScatterPdf(w_o, w_i, objInter);
            float pdf = objInter.material->Pdf(w_o, w_i, objInter);
            auto next_ray = std::make_shared<Ray>(objInter.vert.pos, w_i);
            Lo_indir = CastRay(next_ray, dep) * f_r * cos / pdf / RussianRoulette;
        }
        hitColor += Lo_indir;
        return hitColor;
    }
    bool Scene::IntersectAll(std::shared_ptr<Ray> &r, Intersection &rec) const
    {
        Intersection temp_rec;
        bool hit_anything = false;
        float closest_so_far = std::numeric_limits<float>::max();
        for (int i = 0; i < objects.size(); i++)
        {
            temp_rec = objects[i]->Intersect(r);
            if (temp_rec.happened && temp_rec.ray->GetMaxTime() < closest_so_far)
            {
                hit_anything = true;
                closest_so_far = temp_rec.ray->GetMaxTime();
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
} // namespace platinum
