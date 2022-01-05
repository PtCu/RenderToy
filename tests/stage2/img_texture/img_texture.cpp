#include <render_toy.h>
#include <ROOT_PATH.h>
using namespace platinum;
using namespace glm;
using namespace std;
const static string root_path(ROOT_PATH);
const static string assets_path = root_path + "/assets/";
void some_spheres(Scene& world)
{
    auto sph1 = make_shared<Sphere>(vec3(0, 0, -1), 0.5, make_shared<Lambertian>(make_shared<ImgTexture>(assets_path + "earthmap.jpg")));
    world.AddObject(sph1);
}

int main()
{
    int nx = 800;
    int ny = 600;
    int ns = 10;
    Scene world(true, false);
    some_spheres(world);

    Camera cam;
    Renderer render(nx, ny, 3, "img_texture.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
