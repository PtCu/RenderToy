#include "../src/Core/image.h"
#include "../src/Core/ray.h"
#include "../src/Core/tCamera.h"
#include "../src/Core/object.h"
#include "../src/Material/lambertian.h"
#include "../src/Math/rand.h"
#include "../src/Geometry/sphere.h"
#include "../src/Core/world.h"
#include "../src/Core/renderer.h"
#include "../src/Material/light.h"
#include "../src/Core/vertex.h"
#include "../src/Texture/noiseTexture.h"
#include "../src/Geometry/triMesh.h"
#include "../src/Geometry/instance.h"
#include <glm/gtc/matrix_transform.hpp>
#include "box.h"
using namespace platinum;
using namespace glm;
using namespace std;

void createWorld(World &world)
{

    vector<Vertex> cubeVerts;
    for (size_t i = 0; i < sizeof(data_CubeVertexPos) / sizeof(float); i += 6)
    {
        vec3 pos(data_CubeVertexPos[i], data_CubeVertexPos[i + 1], data_CubeVertexPos[i + 2]);
        vec3 normal(data_CubeVertexPos[i + 3], data_CubeVertexPos[i + 4], data_CubeVertexPos[i + 5]);
        cubeVerts.push_back(Vertex(pos, normal));
    }

    // Mat
    auto redMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.65f, 0.05f, 0.05f)));
    auto greenMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.12f, 0.45f, 0.15f)));
    auto grayMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.73f, 0.73f, 0.73f)));
    auto blueMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.1f, 0.1f, 0.73f)));
    auto lightMat = make_shared<Light>(vec3(10.f));
    auto cubeMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(1.0f, 1.0f, 1.0f)));

    auto cube = make_shared<TriMesh>(cubeVerts, redMat);
    if (!cube->IsValid())
    {
        printf("ERROR: cube is invalid.\n");
        exit(1);
    }

    world.AddObject(cube);

    // mat4 tfmCube1(1.0f);
    // tfmCube1 = glm::translate(tfmCube1, vec3(1.1, 2.2, 1.5));
    // tfmCube1 = glm::scale(tfmCube1, vec3(1.6));
    // tfmCube1 = glm::rotate(tfmCube1, PI / 12, vec3(0, 1, 0));
    // world.AddObject(make_shared<Instance>(tfmCube1, cube, grayMat));

    // mat4 tfmCube2(1.0f);
    // tfmCube2 = glm::translate(tfmCube2, vec3(-1.1, 1, -0.5));
    // tfmCube2 = scale(tfmCube2, vec3(1.6, 4, 1.6));
    // tfmCube2 = glm::rotate(tfmCube2, -PI / 9, vec3(0, 1, 0));
    // world.AddObject(make_shared<Instance>(tfmCube2, cube, grayMat));
}

int main()
{
    int nx = 500;
    int ny = 600;
    int ns = 10;
    World world(true);
    createWorld(world);
    vec3 lookfrom(-10, -10, 10);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 8.0f;
    float aperture = 0.05f;

    shared_ptr<Camera> cam = make_shared<Camera>(lookfrom, lookat, vec3(0, 1, 0), 45, float(nx) / float(ny), aperture, dist_to_focus);
    Renderer render(nx, ny, 3, "box.png", ns);
    render.Render(world, cam);
    world.Reset();
    return 0;
}
