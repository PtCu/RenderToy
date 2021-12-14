
#include "../src/core/image.h"
#include "../src/core/ray.h"
#include "../src/core/t_camera.h"
#include "../src/core/object.h"
#include "../src/material/dielectric.h"
#include "../src/material/lambertian.h"
#include "../src/material/metal.h"
#include "../src/math/rand.h"
#include "../src/geometry/sphere.h"
#include "../src/geometry/moving_sphere.h"
#include "../src/core/scene.h"
#include "../src/core/renderer.h"

using namespace platinum;
using namespace glm;
using namespace std;

void random_scene(Scene &world)
{
    int n = 500;
    shared_ptr<Object> sph;
    sph = make_shared<Sphere>(vec3(0, -1000, 0), 1000, make_shared<Lambertian>(vec3(0.5, 0.5, 0.5)));
    world.AddObject(sph);
    int i = 1;
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            float choose_mat = Random::RandomInUnitFloat();
            vec3 center(a + 0.9 * Random::RandomInUnitFloat(), 0.2, b + 0.9 * Random::RandomInUnitFloat());
            if (length(center - vec3(4, 0.2, 0)) > 0.9)
            {
                if (choose_mat < 0.8)
                { // diffuse
                    sph = make_shared<MovingSphere>(center,
                                                    center + vec3(0, 0.5 * Random::RandomInUnitFloat(), 0),
                                                    0.0, 1.0, 0.2,
                                                    make_shared<Lambertian>(vec3(Random::RandomInUnitFloat() * Random::RandomInUnitFloat(),
                                                                                 Random::RandomInUnitFloat() * Random::RandomInUnitFloat(),
                                                                                 Random::RandomInUnitFloat() * Random::RandomInUnitFloat())));
                }
                else if (choose_mat < 0.95)
                { // metal
                    sph = make_shared<Sphere>(center, 0.2f,
                                              make_shared<Metal>(vec3(0.5 * (1 + Random::RandomInUnitFloat()),
                                                                      0.5 * (1 + Random::RandomInUnitFloat()),
                                                                      0.5 * (1 + Random::RandomInUnitFloat())),
                                                                 0.5 * Random::RandomInUnitFloat()));
                }
                else
                { // glass
                    sph = make_shared<Sphere>(center, 0.2f,
                                              make_shared<Dielectric>(1.5));
                }

                world.AddObject(sph);
            }
        }
    }

    world.AddObject(make_shared<Sphere>(vec3(0, 1, 0), 1.0, make_shared<Dielectric>(1.5)));
    world.AddObject(make_shared<Sphere>(vec3(-4, 1, 0), 1.0, make_shared<Lambertian>(vec3(0.4, 0.2, 0.1))));
    world.AddObject(make_shared<Sphere>(vec3(4, 1, 0), 1.0, make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0)));
}

int main()
{
    int nx = 1200;
    int ny = 800;
    int ns = 100;
    Scene world(true);
    random_scene(world);

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.1f;

    shared_ptr<Camera> cam = make_shared<TCamera>(lookfrom, lookat, vec3(0, -1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus, 0.f, 1.f);
    Renderer render(nx, ny, 3, "motion.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
