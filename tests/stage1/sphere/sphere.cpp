#include "../src/Core/ray.h"
#include "../src/Core/image.h"
#include "../src/Geometry/sphere.h"
using namespace platinum;
using namespace glm;

bool hit_sphere(const vec3 &center, float radius, const Ray &r)
{
    vec3 oc = r.GetOrigin() - center;
    float a = dot(r.GetDirection(), r.GetDirection());
    float b = 2.0f * dot(oc, r.GetDirection());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

vec3 color(const Ray &r)
{
    if (hit_sphere(vec3(0, 0, -1), 0.5, r))
        return vec3(1, 0, 0);
    vec3 unit_direction = normalize(r.GetDirection());
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    int nx = 200;
    int ny = 100;
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    float u, v;
    Image img(200, 100, 3);
    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            u = static_cast<float>(i) / static_cast<float>(nx);
            v = static_cast<float>(j) / static_cast<float>(ny);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * col.x), static_cast<int>(255.99f * col.y), static_cast<int>(255.99f * col.z)));
        }
    }
    img.SaveAsPNG("shpere.png");
}