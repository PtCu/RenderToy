#include "../src/Core/ray.h"
#include "../src/Core/image.h"
#include "../src/Core/world.h"
#include "../src/Geometry/sphere.h"
#include <limits>
using namespace platinum;
using namespace glm;
using namespace std;

vec3 color(const Ray &r, World &world)
{
    Intersection rec;
    if (world.IntersectAll(r,  rec))
    {
        return 0.5f * vec3(rec.normal.x + 1.0f, rec.normal.y + 1.0f, rec.normal.z + 1.0f);
    }
    else
    {
        vec3 unit_direction = normalize(r.GetDirection());
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
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
    World world;
    auto sph1 = make_shared<Sphere>(vec3(0, 0, -1), 0.5);
    world.AddObject(sph1);
    auto sph2 = make_shared<Sphere>(vec3(0, -100.5, -1), 100);
    world.AddObject(sph2);
    Image img(200, 100, 3);
    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            u = static_cast<float>(i) / static_cast<float>(nx);
            v = static_cast<float>(j) / static_cast<float>(ny);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r, world);
            img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * col.x), static_cast<int>(255.99f * col.y), static_cast<int>(255.99f * col.z)));
        }
    }
    img.SaveAsPNG("multi_object.png");
    world.DestroyAll();
}