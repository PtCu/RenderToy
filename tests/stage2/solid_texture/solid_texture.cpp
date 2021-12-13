
#include "../src/Core/image.h"
#include "../src/Core/ray.h"
#include "../src/Core/camera.h"
#include "../src/Core/object.h"
#include "../src/Material/dielectric.h"
#include "../src/Material/lambertian.h"
#include "../src/Material/metal.h"
#include "../src/Math/rand.h"
#include "../src/Geometry/sphere.h"
#include "../src/Geometry/moving_sphere.h"
#include "../src/Core/scene.h"
#include "../src/Core/renderer.h"
#include "../src/Texture/checker_texture.h"
#include "../src/Texture/const_texture.h"

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
