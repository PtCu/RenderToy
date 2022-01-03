#include "../src/core/image.h"
#include "../src/core/ray.h"

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
#include "../src/material/isotropic.h"

#include "../src/geometry/volume.h"
#include <glm/gtc/matrix_transform.hpp>
#include "box.h"
using namespace platinum;
using namespace glm;
using namespace std;

void createWorld(Scene& world)
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
    auto lightMat = make_shared<MaterailLight>(vec3(10.f));
    auto cubeMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(1.0f, 1.0f, 1.0f)));
    auto volMat = make_shared<Isotropic>(make_shared<ConstTexture>(vec3(0.65f, 0.05f, 0.05f)));
    auto cube = make_shared<TriMesh>(cubeVerts);
    if (!cube->IsValid())
    {
        printf("ERROR: cube is invalid.\n");
        exit(1);
    }
    auto vol_cube = make_shared<Volume>(cube, 1.6f, volMat);
    world.AddObject(vol_cube);

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
    Scene world(true);
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
