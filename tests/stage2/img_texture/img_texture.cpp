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
#include "../src/texture/img_texture.h"

using namespace platinum;
using namespace glm;
using namespace std;

void some_spheres(Scene &world)
{
    auto sph1 = make_shared<Sphere>(vec3(0, 0, -1), 0.5, make_shared<Lambertian>(make_shared<ImgTexture>("../../../../../assets/earthmap.jpg")));
    world.AddObject(sph1);
}

int main()
{
    int nx = 800;
    int ny = 600;
    int ns = 10;
    Scene world(true);
    some_spheres(world);

    shared_ptr<Camera> cam = make_shared<Camera>();
    Renderer render(nx, ny, 3, "img_texture.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
