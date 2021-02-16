#include "../src/Core/ray.h"
#include "../src/Core/image.h"
#include "../src/Core/world.h"
#include "../src/Geometry/sphere.h"
#include "../src/Core/camera.h"
#include <limits>
using namespace platinum;
using namespace glm;

vec3 color(const Ray &r, World &world)
{
    Intersection rec;
    if (world.IntersectAll(r, 0.0f, std::numeric_limits<float>::max(), rec))
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
    int ns = 100;
    float u, v;
    World world;
    Object *sph1 = new Sphere(vec3(0, 0, -1), 0.5);
    world.AddObject(sph1);
    Object *sph2 = new Sphere(vec3(0, -100.5, -1), 100);
    world.AddObject(sph2);
    Image img(200, 100, 3);
    Camera cam;
    for (int j = 0; j < ny; ++j)
    {

        for (int i = 0; i < nx; ++i)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; ++s)
            {
                u = float(i + Random::RandomInUnitFloat()) / float(nx);
                v = float(j + Random::RandomInUnitFloat()) / float(ny);
                Ray r = cam.GetRay(u, v);
                col += color(r, world);
            }
            col /= float(ns);
            img.SetPixel(i, j, Image::Pixel<unsigned char>((int)255.99f * col.x, (int)255.99f * col.y, (int)255.99f * col.z));
        }
    }
    img.SaveAsPNG("antialiasing.png");
    world.DestroyAll();
}