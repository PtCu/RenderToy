#include "../src/Core/ray.h"
#include "../src/Core/image.h"
#include "../src/Core/scene.h"
#include "../src/Geometry/sphere.h"
#include "../src/Core/camera.h"
#include "../src/Material/metal.h"
#include "../src/Material/lambertian.h"
#include "../src/Material/dielectric.h"
#include <limits>
using namespace platinum;
using namespace glm;
using namespace std;

vec3 color(shared_ptr<Ray> &ray, Scene &world, int dep)
{

        Intersection rec;
    if (world.IntersectAll(ray, rec))
    {
        if (dep == 0)
            return glm::vec3(0, 0, 0);

        if (rec.material == NULL)
            return glm::vec3(1, 0, 1);
        if (rec.material->Scatter(rec))
            return color(ray, world, dep - 1);
        else
            return ray->GetColor();
    }
    else
    {
        vec3 unit_direction = normalize(ray->GetDirection());
        float t = 0.5f * (unit_direction.y + 1.0f);
        return ray->GetColor() * ((1.0f - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1));
    }
}

int main()
{
    int nx = 2000;
    int ny = 1000;
    int ns = 10;
    float u, v;
    Scene world;
    auto sph1 = make_shared<Sphere>(vec3(0, 0, -1), 0.5, make_shared<Lambertian>(vec3(0.5, 0.5, 0.5)));
    world.AddObject(sph1);
    auto sph2 = make_shared<Sphere>(vec3(0, -100.5, -1), 100, make_shared<Lambertian>(vec3(0.5, 0.5, 0.5)));
    world.AddObject(sph2);
    Image img(nx, ny, 3);
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
                col += color(r, world, 50);
            }
            col /= static_cast<float>(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * col.x), static_cast<int>(255.99f * col.y), static_cast<int>(255.99f * col.z)));
        }
    }
    img.SaveAsPNG("diffuse.png");
    world.Reset();
}