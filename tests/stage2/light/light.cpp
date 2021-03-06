#include "../src/Core/image.h"
#include "../src/Core/ray.h"
#include "../src/Core/tCamera.h"
#include "../src/Core/object.h"
#include "../src/Material/lambertian.h"
#include "../src/Math/rand.h"
#include "../src/Geometry/sphere.h"
#include "../src/Core/scene.h"
#include "../src/Core/renderer.h"
#include "../src/Material/light.h"
#include "../src/Core/vertex.h"
#include "../src/Texture/noiseTexture.h"
#include "../src/Geometry/triMesh.h"

using namespace platinum;
using namespace glm;
using namespace std;
const float pos[] = {
    0.9, 0.7, -0.5,
    0.9, 0.1, -0.5,
    1, 0.1, 0.5,
    1, 0.1, 0.5,
    1, 0.7, 0.5,
    0.9, 0.7, -0.5};
void some_spheres(Scene &world)
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
    int nx = 1200;
    int ny = 600;
    int ns = 30;
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
