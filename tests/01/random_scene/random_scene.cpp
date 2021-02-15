
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

const float MAXFLOAT = 10.0f;
vec3 color(const Ray &r, World &world, int depth)
{
    Intersection rec;
    if (world.IntersectAll(r, 0.001f, MAXFLOAT, rec))
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
    Sphere *sph = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5)));
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
                    sph = new Sphere(
                        center, 0.2,
                        new Lambertian(vec3(Random::RandomInUnitFloat() * Random::RandomInUnitFloat(),
                                            Random::RandomInUnitFloat() * Random::RandomInUnitFloat(),
                                            Random::RandomInUnitFloat() * Random::RandomInUnitFloat())));
                }
                else if (choose_mat < 0.95)
                { // metal
                    sph = new Sphere(
                        center, 0.2,
                        new Metal(vec3(0.5 * (1 + Random::RandomInUnitFloat()),
                                       0.5 * (1 + Random::RandomInUnitFloat()),
                                       0.5 * (1 + Random::RandomInUnitFloat())),
                                  0.5 * Random::RandomInUnitFloat()));
                }
                else
                { // glass
                    sph = new Sphere(center, 0.2f, new Dielectric(1.5));
                }
                world.AddObject(sph);
            }
        }
    }

    world.AddObject((new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5))));
    world.AddObject((new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4, 0.2, 0.1)))));
    world.AddObject((new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5), 0.0))));

    return world;
}

int main()
{
    int nx = 1200;
    int ny = 800;
    int ns = 10;
    std::cout << "P3\n"
              << nx << " " << ny << "\n255\n";
    World world = random_scene();

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.1f;

    Camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
    Image img(1200, 800,4);
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + Random::RandomInUnitFloat()) / float(nx);
                float v = float(j + Random::RandomInUnitFloat()) / float(ny);
                Ray r = cam.GetRay(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            img.SetPixel(i, j, Image::Pixel<float>(ir, ig, ib));
        }
    }
    img.SaveAsPNG("random_scene.png");
    return 0;
}
