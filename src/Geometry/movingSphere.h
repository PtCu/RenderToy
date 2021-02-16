// // The MIT License (MIT)

// // Copyright (c) 2021 PtCu

// //  Permission is hereby granted, free of charge, to any person obtaining a
// //  copy of this software and associated documentation files (the "Software"),
// //  to deal in the Software without restriction, including without limitation
// //  the rights to use, copy, modify, merge, publish, distribute, sublicense,
// //  and/or sell copies of the Software, and to permit persons to whom the
// //  Software is furnished to do so, subject to the following conditions:
// //
// //  The above copyright notice and this permission notice shall be included in
// //  all copies or substantial portions of the Software.
// //
// //  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// //  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// //  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// //  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// //  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// //  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// //  DEALINGS IN THE SOFTWARE.

// #ifndef GEOMETRY_MOVESPHERE_H_
// #define GEOMETRY_MOVESPHERE_H_

// #include "../Core/object.h"

// namespace platinum
// {
//     class MovingSphere : public Object
//     {
//     public:
//         MovingSphere() {}
//         MovingSphere(glm::vec3 cen0, glm::vec3 cen1, PFloat t0, PFloat t1, PFloat r, Material *m)
//             : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), material(m){};
//         virtual bool Intersect(const Ray &r, PFloat tmin, PFloat tmax, Intersection &rec) const;
//         virtual bool BoundingBox(PFloat t0, PFloat t1, AABB &box) const;
//         glm::vec3 GetCenter(PFloat time) const;
//         glm::vec3 center0, center1;
//         PFloat time0, time1;
//         PFloat radius;
//         Material *material;
//     };

//     glm::vec3 MovingSphere::GetCenter(PFloat time) const
//     {
//         return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
//     }
// } // namespace platinum

// #endif