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

#include <core/scene.h>

namespace platinum
{
    Scene::~Scene()
    {
        destroyAll();
    }
    void Scene::destroyAll()
    {
        objects_.clear();
    }
    void Scene::BuildBVH()
    {
        this->bvh_accel_ = std::unique_ptr<BVHAccel>(new BVHAccel(objects_));
    }
    void Scene::AddObject(const std::shared_ptr<Object>& obj)
    {
        this->objects_.push_back(obj);
    }
    void Scene::AddObject(const std::vector<std::shared_ptr<Object>>& obj)
    {
        this->objects_.insert(objects_.end(), obj.begin(), obj.end());
    }
    void Scene::AddObject(const std::vector<std::shared_ptr<Object>>::iterator& begin, const std::vector<std::shared_ptr<Object>>::iterator& end)
    {
        this->objects_.insert(objects_.end(), begin, end);
    }
    void Scene::Reset()
    {
        this->bvh_accel_.reset();
        this->destroyAll();
    }
    HitRst Scene::Hit(const Ray& r) const
    {
        return this->bvh_accel_->RayCast(r);
    }
    void Scene::sampleLight(HitRst& inter, float& pdf) const
    {
        float emit_area_sum = 0;
        for (uint32_t k = 0; k < objects_.size(); ++k)
        {
            //计算发光物体的总面积
            if (objects_[k]->GetMaterial()->IsEmit())
            {
                emit_area_sum += objects_[k]->GetArea();
            }
        }
        float p = Random::RandomInUnitFloat() * emit_area_sum;
        emit_area_sum = 0;
        for (uint32_t k = 0; k < objects_.size(); ++k)
        {
            //找到光源
            if (objects_[k]->GetMaterial()->IsEmit())
            {
                emit_area_sum += objects_[k]->GetArea();
                if (p <= emit_area_sum)
                {
                    //按概率选取一条光线
                    objects_[k]->Sample(inter, pdf);
                    break;
                }
            }
        }
    }
    glm::vec3 Scene::CastRay(const Ray& r) const
    {
        if (mode == 0)
            return castRay(r, max_depth_);
        else if (mode == 1)
            return castRayPdf(r);
    }
    glm::vec3 Scene::castRay(const Ray& ray, int dep) const
    {
        if (dep == 0)
            return glm::vec3(1.0001f / 255.0f);

        auto rst = Hit(ray);

        if (rst.is_hit)
        {
            if (rst.material == NULL)
                return glm::vec3(0, 1, 0);
            //正常情况下，对于漫反射物质继续反射追踪，直到遇到光源则更新颜色并返回
            if (rst.material->ComputeScatteringFunctions(rst))
                return castRay(ray, dep - 1);
            else
                return ray.GetColor();
        }
        else
        {
            if (!default_light)
                return glm::vec3(1.0001f / 255.0f);

            // //TODO: Make it configurable
            // environmental light
            // glm::vec3 unit_direction = glm::normalize(ray->GetDirection());
            // float t = 0.5f * (unit_direction.y + 1.0f);
            // return ray->GetColor() * ((1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.75, 0.85, 1.0));
        }
    }
    glm::vec3 Scene::castRayPdf(const Ray& ray) const
    {
        //求一条光线与场景的交点
        HitRst obj_rst = Hit(ray);
        if (!obj_rst.is_hit)
            return glm::vec3(0.f);

        glm::vec3 hit_color(0.f);
        if (obj_rst.material->IsEmit())
            return obj_rst.material->Emit();

        //采样光源点
        float light_pdf = 1;
        HitRst light_rst;
        sampleLight(light_rst, light_pdf);
        glm::vec3 obj2light = light_rst.record.vert.position_ - obj_rst.record.vert.position_;
        glm::vec3 obj2light_dir = glm::normalize(obj2light);
        //确定一条从物体到光源的射线
        Ray to_light_ray{ obj_rst.record.vert.position_, obj2light_dir };
        glm::vec3 Lo_dir(0.f), Lo_indir(0.f);
        glm::vec3 w_o = -glm::normalize(ray.GetDirection());
        glm::vec3 obj_n = glm::normalize(obj_rst.record.vert.normal_);
        glm::vec3 light_n = normalize(light_rst.record.vert.normal_);

        //测试是否有遮挡.向光源打出一条射线
        auto bounce_back = Hit(to_light_ray);
        if (bounce_back.is_hit && glm::length(bounce_back.record.vert.position_ - light_rst.record.vert.position_) < EPSILON)
        {
            //直接光照
            //入射方向为光源射向物体，出射方向（所求的方向)为参数ray的方向
            glm::vec3 f_r = obj_rst.material->ScatterPdf(obj2light_dir, w_o, obj_rst);
            //对光源采样
            float r2 = glm::dot(obj2light, obj2light);
            float cosA = std::max(.0f, glm::dot(obj_n, obj2light_dir));
            float cosB = std::max(.0f, glm::dot(light_n, -obj2light_dir));
            Lo_dir = light_rst.emit * f_r * cosA * cosB / r2 / light_pdf;
        }
        hit_color += Lo_dir;
        if (Random::RandomInUnitFloat() > RussianRoulette)
            return hit_color;

        //间接光照

        //按材质采样一条射线
        glm::vec3 w_i = glm::normalize(obj_rst.material->Sample(w_o, obj_rst));
        Ray next_ray(obj_rst.record.vert.position_, w_i);
        auto next_inter = Hit(next_ray);
        //下一个物体不发光
        if (next_inter.is_hit && !next_inter.material->IsEmit())
        {
            float cos = std::max(.0f, glm::dot(w_i, obj_n));
            glm::vec3 f_r = obj_rst.material->ScatterPdf(w_o, w_i, obj_rst);
            float pdf = obj_rst.material->Pdf(w_o, w_i, obj_rst);
            Lo_indir = castRayPdf(next_ray) * f_r * cos / pdf / RussianRoulette;
        }

        hit_color += Lo_indir;
        return hit_color;
    }
    // bool Scene::IntersectAll(const Ray& &r, HitRst &rst) const
    // {
    //     HitRst temp_rec;
    //     bool hit_anything = false;
    //     float closest_so_far = std::numeric_limits<float>::max();
    //     for (int i = 0; i < objects.size(); i++)
    //     {
    //         temp_rec = objects[i]->Intersect(r);
    //         if (temp_rec.isHit && temp_rec.record.ray->GetMaxTime() < closest_so_far)
    //         {
    //             hit_anything = true;
    //             closest_so_far = temp_rec.record.ray->GetMaxTime();
    //             rst = temp_rec;
    //         }
    //     }
    //     return hit_anything;
    // }
} // namespace platinum
