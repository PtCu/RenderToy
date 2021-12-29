#include "../src/core/image.h"
#include "../src/core/ray.h"
#include "../src/core/t_camera.h"
#include "../src/core/object.h"
#include "../src/material/lambertian.h"
#include "../src/math/rand.h"
#include "../src/geometry/sphere.h"
#include "../src/core/scene.h"
#include "../src/core/renderer.h"
#include "../src/material/light.h"
#include "../src/geometry/vertex.h"
#include "../src/texture/noise_texture.h"
#include "../src/geometry/triangle_mesh.h"

using namespace platinum;
using namespace glm;
using namespace std;
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
    Scene world(false);
    some_spheres(world);
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.f;

    shared_ptr<Camera> cam = make_shared<Camera>();
    Renderer render(nx, ny, 3, "light.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
