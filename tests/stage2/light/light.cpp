
#include <render_toy.h>
#include <ROOT_PATH.h>

using namespace platinum;
using namespace glm;
using namespace std;

const static string root_path(ROOT_PATH);
const static string assets_path = root_path + "/assets/";

const float pos[] = {
    0.9, 0.7, -0.5,
    0.9, 0.1, -0.5,
    1, 0.1, 0.5,
    1, 0.1, 0.5,
    1, 0.7, 0.5,
    0.9, 0.7, -0.5 };
void some_spheres(Scene& world)
{
    float scale = 5;
    auto light_tex = make_shared<ConstTexture>(vec3(1.5, 1, 1));
    auto noi_tex = make_shared<NoiseTexture>(scale, 1);
    auto sph1 = make_shared<Sphere>(vec3(0, -100, -1), 100, make_shared<Lambertian>(noi_tex));
    world.AddObject(sph1);
    auto sph2 = make_shared<Sphere>(vec3(0, 0, -1), 0.5, make_shared<Lambertian>(noi_tex));
    world.AddObject(sph2);
    auto sph3 = make_shared<Sphere>(vec3(0, 1, -2), 0.4, make_shared<Light>(light_tex));
    world.AddObject(sph3);
    vector<Vertex> vertexs;
    for (size_t i = 0; i < sizeof(pos) / sizeof(float); i += 3)
        vertexs.push_back(Vertex(vec3(pos[i], pos[i + 1], pos[i + 2])));
    auto triMesh = make_shared<TriMesh>(vertexs, make_shared<Light>(light_tex));
    world.AddObject(triMesh);
}

int main()
{
    int nx = 500;
    int ny = 400;
    int ns = 10;
    Scene world(false, false);
    some_spheres(world);
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.f;

    Camera cam{};
    Renderer render(nx, ny, 3, "light.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
