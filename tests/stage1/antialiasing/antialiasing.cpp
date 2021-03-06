#include "../src/Core/ray.h"
#include "../src/Core/image.h"
#include "../src/Core/scene.h"
#include "../src/Geometry/sphere.h"
#include "../src/Core/camera.h"
#include <limits>
using namespace platinum;
using namespace glm;
using namespace std;

vec3 color(shared_ptr<Ray> &r, Scene &world)
{
    Intersection rec;
    if (world.IntersectAll(r, rec))
    {
        return 0.5f * vec3(rec.vert.normal.x + 1.0f, rec.vert.normal.y + 1.0f, rec.vert.normal.z + 1.0f);
    }
    else
    {
        vec3 unit_direction = normalize(r->GetDirection());
        float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    float u, v;
    Scene world;
    auto sph1 = make_shared<Sphere>(vec3(0, 0, -1), 0.5);
    //  Object *sph1 = new Sphere(vec3(0, 0, -1), 0.5);
    world.AddObject(sph1);
    auto sph2 = make_shared<Sphere>(vec3(0, -100.5, -1), 100);
    //  Object *sph2 = new Sphere(vec3(0, -100.5, -1), 100);
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
                u = static_cast<float>(i + Random::RandomInUnitFloat()) / static_cast<float>(nx);
                v = static_cast<float>(j + Random::RandomInUnitFloat()) / static_cast<float>(ny);
                auto r = cam.GetRay(u, v);
                col += color(r, world);
            }
            col /= static_cast<float>(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * col.x), static_cast<int>(255.99f * col.y), static_cast<int>(255.99f * col.z)));
        }
    }
    img.SaveAsPNG("antialiasing.png");
    world.Reset();
}