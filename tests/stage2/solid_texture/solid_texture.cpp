

#include <render_toy.h>
#include <ROOT_PATH.h>

using namespace platinum;
using namespace glm;
using namespace std;

const static string root_path(ROOT_PATH);
const static string assets_path = root_path + "/assets/";

void two_spheres(Scene& world)
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
    Scene world(true, false);
    two_spheres(world);
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.f;

    Camera cam(lookfrom, lookat, vec3(0, -1, 0), 45, static_cast<float>(nx) / static_cast<float>(ny), aperture, dist_to_focus);
    Renderer render(nx, ny, 3, "solid_texture.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
