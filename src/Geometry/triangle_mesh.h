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

#ifndef GEOMETRY_TRIMESH_H_
#define GEOMETRY_TRIMESH_H_

#include "core/bvh.h"
#include "core/vertex.h"
// #include <OBJ_Loader.hpp>
#include "triangle.h"

namespace objl
{
    class Loader;
}

namespace platinum
{
    class TriMesh : public Object
    {
    public:
        TriMesh(const std::string& filename_, std::shared_ptr<Material> m = NULL);
        TriMesh(const std::vector<Vertex>& vertexs, std::shared_ptr<Material> m = NULL);
        virtual HitRst Intersect(std::shared_ptr<Ray>& r);
        virtual AABB GetBoundingBox() const { return _bounding_box; }
        virtual float GetArea() const;
        virtual void Sample(HitRst& inter, float& pdf) const;
        inline bool IsValid() const { return _valid; };
        std::vector<std::shared_ptr<Object>>& GetTriangles() { return _triangles; }

    protected:
        float _area;
        bool _valid;
        std::vector<std::shared_ptr<Object>> _triangles;
        AABB _bounding_box;
        std::unique_ptr<BVHAccel> _bvh_accel;
        objl::Loader* _loader;
    };
}

#endif
