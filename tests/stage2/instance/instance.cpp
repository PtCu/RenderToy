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

using namespace platinum;
using namespace glm;
using namespace std;
const float data_SquareVertexPos[36] = {
    -0.5,
    -0.5,
    0,
    0,
    0,
    1,
    0.5,
    -0.5,
    0,
    0,
    0,
    1,
    -0.5,
    0.5,
    0,
    0,
    0,
    1,
    0.5,
    0.5,
    0,
    0,
    0,
    1,
    -0.5,
    0.5,
    0,
    0,
    0,
    1,
    0.5,
    -0.5,
    0,
    0,
    0,
    1,
};

const float data_CubeVertexPos[216] = {
    //up
    -0.5,
    0.5,
    0.5,
    0,
    1,
    0,
    0.5,
    0.5,
    0.5,
    0,
    1,
    0,
    -0.5,
    0.5,
    -0.5,
    0,
    1,
    0,
    0.5,
    0.5,
    -0.5,
    0,
    1,
    0,
    -0.5,
    0.5,
    -0.5,
    0,
    1,
    0,
    0.5,
    0.5,
    0.5,
    0,
    1,
    0,
    //down
    -0.5,
    -0.5,
    0.5,
    0,
    -1,
    0,
    0.5,
    -0.5,
    0.5,
    0,
    -1,
    0,
    -0.5,
    -0.5,
    -0.5,
    0,
    -1,
    0,
    0.5,
    -0.5,
    -0.5,
    0,
    -1,
    0,
    -0.5,
    -0.5,
    -0.5,
    0,
    -1,
    0,
    0.5,
    -0.5,
    0.5,
    0,
    -1,
    0,
    //left
    -0.5,
    -0.5,
    0.5,
    -1,
    0,
    0,
    -0.5,
    -0.5,
    -0.5,
    -1,
    0,
    0,
    -0.5,
    0.5,
    0.5,
    -1,
    0,
    0,
    -0.5,
    0.5,
    -0.5,
    -1,
    0,
    0,
    -0.5,
    0.5,
    0.5,
    -1,
    0,
    0,
    -0.5,
    -0.5,
    -0.5,
    -1,
    0,
    0,
    //right
    0.5,
    -0.5,
    0.5,
    1,
    0,
    0,
    0.5,
    -0.5,
    -0.5,
    1,
    0,
    0,
    0.5,
    0.5,
    0.5,
    1,
    0,
    0,
    0.5,
    0.5,
    -0.5,
    1,
    0,
    0,
    0.5,
    0.5,
    0.5,
    1,
    0,
    0,
    0.5,
    -0.5,
    -0.5,
    1,
    0,
    0,
    //front
    -0.5,
    -0.5,
    0.5,
    0,
    0,
    1,
    0.5,
    -0.5,
    0.5,
    0,
    0,
    1,
    -0.5,
    0.5,
    0.5,
    0,
    0,
    1,
    0.5,
    0.5,
    0.5,
    0,
    0,
    1,
    -0.5,
    0.5,
    0.5,
    0,
    0,
    1,
    0.5,
    -0.5,
    0.5,
    0,
    0,
    1,
    //back
    -0.5,
    -0.5,
    -0.5,
    0,
    0,
    -1,
    0.5,
    -0.5,
    -0.5,
    0,
    0,
    -1,
    -0.5,
    0.5,
    -0.5,
    0,
    0,
    -1,
    0.5,
    0.5,
    -0.5,
    0,
    0,
    -1,
    -0.5,
    0.5,
    -0.5,
    0,
    0,
    -1,
    0.5,
    -0.5,
    -0.5,
    0,
    0,
    -1,
};
void createWorld(World &world)
{
    // Mesh
    vector<Vertex> squareVerts;
    for (size_t i = 0; i < sizeof(data_SquareVertexPos) / sizeof(float); i += 6)
    {
        vec3 pos(data_SquareVertexPos[i], data_SquareVertexPos[i + 1], data_SquareVertexPos[i + 2]);
        vec3 normal(data_SquareVertexPos[i + 3], data_SquareVertexPos[i + 4], data_SquareVertexPos[i + 5]);
        squareVerts.push_back(Vertex(pos, normal));
    }
    auto square = make_shared<TriMesh>(squareVerts);
    if (!square->IsValid())
    {
        printf("ERROR: square is invalid.\n");
        exit(1);
    }

    vector<Vertex> cubeVerts;
    for (size_t i = 0; i < sizeof(data_CubeVertexPos) / sizeof(float); i += 6)
    {
        vec3 pos(data_CubeVertexPos[i], data_CubeVertexPos[i + 1], data_CubeVertexPos[i + 2]);
        vec3 normal(data_CubeVertexPos[i + 3], data_CubeVertexPos[i + 4], data_CubeVertexPos[i + 5]);
        cubeVerts.push_back(Vertex(pos, normal));
    }
    auto cube = make_shared<TriMesh>(cubeVerts);
    if (!cube->IsValid())
    {
        printf("ERROR: cube is invalid.\n");
        exit(1);
    }

    // Mat
    auto redMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.65f, 0.05f, 0.05f)));
    auto greenMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.12f, 0.45f, 0.15f)));
    auto grayMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.73f, 0.73f, 0.73f)));
    auto lightMat = make_shared<Light>(vec3(10.f));
    auto cubeMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(1.0f, 1.0f, 1.0f)));

    // // Transform
    mat4 tfmRight(1.0f);
    tfmRight = glm::translate(tfmRight, vec3(3, 0, 0));
    tfmRight = glm::scale(tfmRight, vec3(6));
    tfmRight = glm::rotate(tfmRight, -Pi / 2, vec3(0, 1, 0));
    for (auto a : square->GetTriangles())
    {
       // world.AddObject(make_shared<Instance>(tfmRight, a, lightMat));
         world.AddObject(make_shared<Instance>(tfmRight, a, redMat));
    }

    mat4 tfmLeft(1.0f);
    tfmLeft = glm::translate(tfmLeft, vec3(-3, 0, 0));
    tfmLeft = glm::scale(tfmLeft, vec3(6));
    tfmLeft = glm::rotate(tfmLeft, Pi / 2, vec3(0, 1, 0));
    for (auto a : square->GetTriangles())
    {
        //world.AddObject(make_shared<Instance>(tfmLeft, a, lightMat));
        world.AddObject(make_shared<Instance>(tfmLeft, a, greenMat));
    }

    mat4 tfmBottom(1.0f);
    tfmBottom = glm::translate(tfmBottom, vec3(0, -3, 0));
    tfmBottom = glm::scale(tfmBottom, vec3(6));
    tfmBottom = glm::rotate(tfmBottom, -Pi / 2, vec3(1, 0, 0));
    for (auto a : square->GetTriangles())
    {
        //world.AddObject(make_shared<Instance>(tfmBottom, a, lightMat));
        world.AddObject(make_shared<Instance>(tfmBottom, a, grayMat));
    }

    mat4 tfmTop(1.0f);
    tfmTop = glm::translate(tfmTop, vec3(0, 3, 0));
    tfmTop = glm::scale(tfmTop, vec3(6));
    tfmTop = glm::rotate(tfmTop, Pi / 2, vec3(1, 0, 0));
    for (auto a : square->GetTriangles())
    {
        //world.AddObject(make_shared<Instance>(tfmTop, a, lightMat));
        world.AddObject(make_shared<Instance>(tfmTop, a, grayMat));
    }

    mat4 tfmBack(1.0f);
    tfmBack = glm::translate(tfmBack, vec3(0, 0, -3));
    tfmBack = glm::scale(tfmBack, vec3(6));
    for (auto a : square->GetTriangles())
    {
        //world.AddObject(make_shared<Instance>(tfmBack, a, lightMat));
        world.AddObject(make_shared<Instance>(tfmBack, a, grayMat));
    }

    mat4 tfmLight(1.0f);
    tfmLight = glm::translate(tfmLight, vec3(0, 1.5, 0));
    tfmLight = glm::scale(tfmLight, vec3(3));
    tfmLight = glm::rotate(tfmLight, Pi / 2, vec3(1, 0, 0));
    for (auto a : square->GetTriangles())
    {
        world.AddObject(make_shared<Instance>(tfmLight, a, lightMat));
        //world.AddObject(make_shared<Instance>(tfmLight, a, redMat));
    }

    mat4 tfmCube1(1.0f);
    tfmCube1 = glm::translate(tfmCube1, vec3(1.1, -2.2, 1.5));
    tfmCube1 = glm::scale(tfmCube1, vec3(1.6));
    tfmCube1 = glm::rotate(tfmCube1, -Pi / 12, vec3(0, 1, 0));
    for (auto a : cube->GetTriangles())
    {
        world.AddObject(make_shared<Instance>(tfmCube1, a, cubeMat));
    }

    mat4 tfmCube2(1.0f);
    tfmCube2 = glm::translate(tfmCube2, vec3(-1.1, -1, -0.5));
    tfmCube2 = glm::scale(tfmCube2, vec3(1.6, 4, 1.6));
    tfmCube2 = glm::rotate(tfmCube2, Pi / 9, vec3(0, 1, 0));
    for (auto a : cube->GetTriangles())
    {
        world.AddObject(make_shared<Instance>(tfmCube2, a, cubeMat));
    }
}

int main()
{
    int nx = 300;
    int ny = 400;
    int ns = 10;
    World world(false);
    createWorld(world);
    vec3 lookfrom(0, 0, 10);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 8.0f;
    float aperture = 0.05f;

    shared_ptr<Camera> cam = make_shared<Camera>(lookfrom, lookat, vec3(0, -1, 0), 90, float(nx) / float(ny), aperture, dist_to_focus);
    Renderer render(nx, ny, 3, "instance.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
