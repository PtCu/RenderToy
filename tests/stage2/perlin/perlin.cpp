#include "../src/Core/image.h"
#include "../src/Core/ray.h"
#include "../src/Core/camera.h"
#include "../src/Core/object.h"
#include "../src/Material/dielectric.h"
#include "../src/Material/lambertian.h"
#include "../src/Material/metal.h"
#include "../src/Math/rand.h"
#include "../src/Geometry/sphere.h"
#include "../src/Geometry/movingSphere.h"
#include "../src/Core/scene.h"
#include "../src/Core/renderer.h"
#include "../src/Texture/noiseTexture.h"

using namespace platinum;
using namespace glm;
using namespace std;

void some_spheres(Scene &world)
{
    float scale = 5;
    auto sph1 = make_shared<Sphere>(vec3(0, 0, -1), 0.5, make_shared<Lambertian>(make_shared<NoiseTexture>(scale, 0)));
    world.AddObject(sph1);
    auto sph2 = make_shared<Sphere>(vec3(0, -100.5, -1), 100, make_shared<Lambertian>(make_shared<NoiseTexture>(scale, 1)));
    world.AddObject(sph2);
    world.AddObject(make_shared<Sphere>(vec3(1, 0, -1), 0.5, make_shared<Lambertian>(make_shared<NoiseTexture>(scale, 2))));
    world.AddObject(make_shared<Sphere>(vec3(-1, 0, -1), 0.5, make_shared<Lambertian>(make_shared<NoiseTexture>(scale, 3))));
}

int main()
{
    int nx = 1200;
    int ny = 800;
    int ns = 10;
    Scene world(true);
    some_spheres(world);
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.f;

    shared_ptr<Camera> cam = make_shared<Camera>();
    Renderer render(nx, ny, 3, "perlin.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
