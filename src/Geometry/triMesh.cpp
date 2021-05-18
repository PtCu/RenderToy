// The MIT License (MIT)

// Copyright (c) 2021 PtCu

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

#include "triMesh.h"
#include <OBJ_Loader.hpp>

namespace platinum
{
    void TriMesh::Sample(Intersection &inter, float &pdf) const
    {
        bvh_accel->Sample(inter, pdf);
    }
    float TriMesh::GetArea() const
    {
        return area;
    }
    TriMesh::TriMesh(const std::string &filename, std::shared_ptr<Material> m) : Object(m)
    {
        loader = new objl::Loader();
        loader->LoadFile(filename);
        area = 0;
        assert(loader->LoadedMeshes.size() == 1);
        auto mesh = loader->LoadedMeshes[0];

        glm::vec3 min_vert = glm::vec3{std::numeric_limits<float>::infinity(),
                                       std::numeric_limits<float>::infinity(),
                                       std::numeric_limits<float>::infinity()};
        glm::vec3 max_vert = glm::vec3{-std::numeric_limits<float>::infinity(),
                                       -std::numeric_limits<float>::infinity(),
                                       -std::numeric_limits<float>::infinity()};
        for (int i = 0; i < mesh.Vertices.size(); i += 3)
        {
            std::array<glm::vec3, 3> face_vertices;

            for (int j = 0; j < 3; j++)
            {
                auto vert = glm::vec3(mesh.Vertices[i + j].Position.X,
                                      mesh.Vertices[i + j].Position.Y,
                                      mesh.Vertices[i + j].Position.Z);
                face_vertices[j] = vert;
                min_vert = glm::min(min_vert, vert);
                max_vert = glm::max(max_vert, vert);
            }
            auto tri = std::make_shared<Triangle>(face_vertices[0], face_vertices[1],
                                                  face_vertices[2], m);
            area += tri->GetArea();
            triangles.emplace_back(tri);
        }

        bounding_box = AABB(min_vert, max_vert);
        bvh_accel = std::make_unique<BVHAccel>(triangles);
    }
    TriMesh::TriMesh(const std::vector<Vertex> &vertexs, std::shared_ptr<Material> material) : Object(material)
    {
        area = 0;
        if (vertexs.size() % 3 != 0)
        {
            isValid = false;
            return;
        }

        for (size_t i = 0; i < vertexs.size(); i += 3)
        {
            auto triangle = std::make_shared<Triangle>(vertexs[i], vertexs[i + 1], vertexs[i + 2], material);
            area += triangle->GetArea();
            triangles.emplace_back(triangle);
            bounding_box.Expand(triangle->GetBoundingBox());
        }
        isValid = true;
        bvh_accel = std::make_unique<BVHAccel>(triangles);
    }

    Intersection TriMesh::Intersect(std::shared_ptr<Ray> &r)
    {
        Intersection intersec;

        if (bvh_accel)
        {
            intersec = bvh_accel->RayCast(r);
        }
        if (intersec.happened)
        {
            int a = 1;
            int b = 1;
        }
        return intersec;
        // Intersection rec;

        // for (auto &tri : triangles)
        // {
        //     auto tmp_inter = tri->Intersect(r);

        //     if (tmp_inter.happened && (rec.happened == false || tmp_inter.ray->GetMaxTime() < rec.ray->GetMaxTime()))
        //     {
        //         // inter = std::move(tmp_inter);

        //         rec = tmp_inter;
        //     }

        // }
        // return rec;
    }
}
