
#include <render_toy.h>
#include <ROOT_PATH.h>

using namespace platinum;
using namespace glm;
using namespace std;

const static string root_path(ROOT_PATH);
const static string assets_path = root_path + "/assets/";

void createWorld(Scene& world)
{
    // Mat
    auto redMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.63f, 0.065f, 0.05f)));
    auto greenMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.14f, 0.45f, 0.091f)));
    auto grayMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.725f, 0.71f, 0.68f)));
    auto blueMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.1f, 0.1f, 0.73f)));
    auto lightMat = make_shared<Light>(make_shared<ConstTexture>(8.0f * glm::vec3(0.747f + 0.058f, 0.747f + 0.258f, 0.747f) + 15.6f * glm::vec3(0.740f + 0.287f, 0.740f + 0.160f, 0.740f) + 18.4f * glm::vec3(0.737f + 0.642f, 0.737f + 0.159f, 0.737f)));
    auto cubeMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(1.0f, 1.0f, 1.0f)));

    auto floor = make_shared<TriMesh>(assets_path + "cornellbox/floor.obj", grayMat);
    auto shortbox = make_shared<TriMesh>(assets_path + "cornellbox/shortbox.obj", cubeMat);
    auto tallbox = make_shared<TriMesh>(assets_path + "cornellbox/tallbox.obj", cubeMat);
    auto left = make_shared<TriMesh>(assets_path + "cornellbox/left.obj", redMat);
    auto right = make_shared<TriMesh>(assets_path + "cornellbox/right.obj", greenMat);
    auto light_ = make_shared<TriMesh>(assets_path + "cornellbox/light.obj", lightMat);

    world.AddObject(floor);
    world.AddObject(shortbox);
    world.AddObject(tallbox);
    world.AddObject(left);
    world.AddObject(right);
    world.AddObject(light_);
}

int main()
{
    int nx = 784;
    int ny = 784;
    int ns = 16;
    Scene world(false, true);
    createWorld(world);
    vec3 lookfrom(278, 273, -800);
    vec3 lookat(278, 273, 0);
    float dist_to_focus = 10.0f;
    float aperture = 0.05f;

    Camera cam(lookfrom, lookat, vec3(0, -1, 0), 45, static_cast<float>(nx) / static_cast<float>(ny), aperture, dist_to_focus);
    Renderer render(nx, ny, 3, "cornell.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
