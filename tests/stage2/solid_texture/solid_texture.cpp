
#include "../src/core/image.h"
#include "../src/core/ray.h"
#include "../src/core/camera.h"
#include "../src/core/object.h"
#include "../src/material/dielectric.h"
#include "../src/material/lambertian.h"
#include "../src/material/metal.h"
#include "../src/math/rand.h"
#include "../src/geometry/sphere.h"
#include "../src/geometry/moving_sphere.h"
#include "../src/core/scene.h"
#include "../src/core/renderer.h"
#include "../src/texture/checker_texture.h"
#include "../src/texture/const_texture.h"

using namespace platinum;
using namespace glm;
using namespace std;

void two_spheres(Scene &world)
{
    auto checker = make_shared<CheckerTexture>(make_shared<ConstTexture>(vec3(0.2, 0.3, 0.1)), make_shared<ConstTexture>(vec3(0.9, 0.9, 0.9)));
    world.AddObject(make_shared<Sphere>(vec3(0, -10, 0), 10, make_shared<Lambertian>(checker)));
    world.AddObject(make_shared<Sphere>(vec3(0, 10, 0), 10, make_shared<Lambertian>(checker)));
}

int main()
{
    int nx = 1200;
    int ny = 800;
    int ns = 10;
    Scene world(true);
    two_spheres(world);
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.f;

    shared_ptr<Camera> cam = make_shared<Camera>(lookfrom, lookat, vec3(0, -1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
    Renderer render(nx, ny, 3, "solid_texture.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
