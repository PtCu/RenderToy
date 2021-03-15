
#include "../src/Core/image.h"
#include "../src/Core/ray.h"
#include "../src/Core/camera.h"
#include "../src/Core/object.h"
#include "../src/Material/dielectric.h"
#include "../src/Material/lambertian.h"
#include "../src/Material/metal.h"
#include "../src/Math/rand.h"
#include "../src/Geometry/sphere.h"
#include "../src/Core/world.h"

using namespace platinum;
using namespace glm;
using namespace std;

vec3 color(const Ray &r, World &world, int depth)
{
    Intersection rec;
    if (world.IntersectAll(r, rec))
    {
        Ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.material->Scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
    }
    else
    {
        vec3 unit_direction = normalize(r.GetDirection());
        float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

World random_scene()
{
    int n = 500;
    World world;
    auto sph = make_shared<Sphere>(vec3(0, -1000, 0), 1000, make_shared<Lambertian>(vec3(0.5, 0.5, 0.5)));
    world.AddObject(sph);
    int i = 1;
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            float choose_mat = Random::RandomInUnitFloat();
            vec3 center(a + 0.9 * Random::RandomInUnitFloat(), 0.2, b + 0.9 * Random::RandomInUnitFloat());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9)
            {
                if (choose_mat < 0.8)
                { // diffuse
                    sph.reset(new Sphere(
                        center, 0.2,
                        make_shared<Lambertian>(vec3(Random::RandomInUnitFloat() * Random::RandomInUnitFloat(),
                                                     Random::RandomInUnitFloat() * Random::RandomInUnitFloat(),
                                                     Random::RandomInUnitFloat() * Random::RandomInUnitFloat()))));
                }
                else if (choose_mat < 0.95)
                { // metal
                    sph.reset(new Sphere(
                        center, 0.2,
                        make_shared<Metal>(vec3(0.5 * (1 + Random::RandomInUnitFloat()),
                                                0.5 * (1 + Random::RandomInUnitFloat()),
                                                0.5 * (1 + Random::RandomInUnitFloat())),
                                           0.5 * Random::RandomInUnitFloat())));
                }
                else
                { // glass
                    sph.reset(new Sphere(center, 0.2f, make_shared<Dielectric>(1.5)));
                }
                world.AddObject(sph);
            }
        }
    }

    world.AddObject(make_shared<Sphere>(vec3(0, 1, 0), 1.0, make_shared<Dielectric>(1.5)));
    world.AddObject(make_shared<Sphere>(vec3(-4, 1, 0), 1.0, make_shared<Lambertian>(vec3(0.4, 0.2, 0.1))));
    world.AddObject(make_shared<Sphere>(vec3(4, 1, 0), 1.0, make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    return world;
}

int main()
{
    int nx = 1200;
    int ny = 800;
    int ns = 10;
    std::cout << "Start rendering..." << std::endl;
    World world = random_scene();

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.1f;

    Camera cam(lookfrom, lookat, vec3(0, -1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
    Image img(1200, 800, 3);
    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float u = static_cast<float>(i) / static_cast<float>(nx);
                float v = static_cast<float>(j) / static_cast<float>(ny);
                Ray r = cam.GetRay(u, v);
                col += color(r, world, 0);
            }
            col /= static_cast<float>(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * col.x), static_cast<int>(255.99f * col.y), static_cast<int>(255.99f * col.z)));
        }
    }
    img.SaveAsPNG("random_scene.png");
    std::cout << "Rendering finished" << std::endl;
    world.DestroyAll();
    return 0;
}
