// #include "../src/Core/image.h"
// #include "../src/Core/ray.h"
// #include "../src/Core/tCamera.h"
// #include "../src/Core/object.h"
// #include "../src/Material/lambertian.h"
// #include "../src/Math/rand.h"
// #include "../src/Geometry/sphere.h"
// #include "../src/Core/world.h"
// #include "../src/Core/renderer.h"
// #include "../src/Material/light.h"
// #include "../src/Core/vertex.h"
// #include "../src/Texture/noiseTexture.h"
// #include "../src/Geometry/triMesh.h"

// using namespace platinum;
// using namespace glm;
// using namespace std;
// const float pos[] = {
//     0.9, 0.7, -0.5,
//     0.9, 0.1, -0.5,
//     1, 0.1, 0.5,
//     1, 0.1, 0.5,
//     1, 0.7, 0.5,
//     0.9, 0.7, -0.5};

// void createWorld(World &world)
// {
//     // Mesh
//     vector<Vertex> squareVerts;
//     for (size_t i = 0; i < sizeof(data_SquareVertexPos) / sizeof(float); i += 6)
//     {
//         vec3 pos(data_SquareVertexPos[i], data_SquareVertexPos[i + 1], data_SquareVertexPos[i + 2]);
//         vec3 normal(data_SquareVertexPos[i + 3], data_SquareVertexPos[i + 4], data_SquareVertexPos[i + 5]);
//         squareVerts.push_back(Vertex(pos, normal));
//     }
//     auto square = make_shared<TriMesh>(squareVerts);
//     if (!square->IsValid())
//     {
//         printf("ERROR: square is invalid.\n");
//         exit(1);
//     }

//     vector<Vertex> cubeVerts;
//     for (size_t i = 0; i < sizeof(data_CubeVertexPos) / sizeof(float); i += 6)
//     {
//         vec3 pos(data_CubeVertexPos[i], data_CubeVertexPos[i + 1], data_CubeVertexPos[i + 2]);
//         vec3 normal(data_CubeVertexPos[i + 3], data_CubeVertexPos[i + 4], data_CubeVertexPos[i + 5]);
//         cubeVerts.push_back(Vertex(pos, normal));
//     }
//     auto square = make_shared<TriMesh>(cubeVerts);
//     if (!cube->IsValid())
//     {
//         printf("ERROR: cube is invalid.\n");
//         exit(1);
//     }

//     // Mat
//     auto redMat = make_shared<Lambertian>(ConstTexture(vec3(0.65f, 0.05f, 0.05f)));
//     auto greenMat = make_shared<Lambertian>(ConstTexture(vec3(0.12f, 0.45f, 0.15f)));
//     auto grayMat = make_shared<Lambertian>(ConstTexture(vec3(0.73f, 0.73f, 0.73f)));
//     auto lightMat = make_shared<Light>(vec3(4.0f));
//     auto cubeMat = make_shared<Lambertian>(ConstTexture(vec3(1.0f, 1.0f, 1.0f)));

//     // Transform
//     mat4 tfmRight(1.0f);
//     tfmRight = translate(tfmRight, vec3(3, 0, 0));
//     tfmRight = scale(tfmRight, vec3(6));
//     tfmRight = rotate(tfmRight, -Pi / 2, vec3(0, 1, 0));
//     anto redWall=
//     auto redWall = ToPtr(new Transform(tfmRight, square, redMat));

//     mat4 tfmLeft(1.0f);
//     tfmLeft = translate(tfmLeft, vec3(-3, 0, 0));
//     tfmLeft = scale(tfmLeft, vec3(6));
//     tfmLeft = rotate(tfmLeft, Math::PI / 2, vec3(0, 1, 0));
//     auto greenWall = ToPtr(new Transform(tfmLeft, square, greenMat));

//     mat4 tfmBottom(1.0f);
//     tfmBottom = translate(tfmBottom, vec3(0, -3, 0));
//     tfmBottom = scale(tfmBottom, vec3(6));
//     tfmBottom = rotate(tfmBottom, -Math::PI / 2, vec3(1, 0, 0));
//     auto bottomWall = ToPtr(new Transform(tfmBottom, square, grayMat));

//     mat4 tfmTop(1.0f);
//     tfmTop = translate(tfmTop, vec3(0, 3, 0));
//     tfmTop = scale(tfmTop, vec3(6));
//     tfmTop = rotate(tfmTop, Math::PI / 2, vec3(1, 0, 0));
//     auto topWall = ToPtr(new Transform(tfmTop, square, grayMat));

//     mat4 tfmBack(1.0f);
//     tfmBack = translate(tfmBack, vec3(0, 0, -3));
//     tfmBack = scale(tfmBack, vec3(6));
//     auto backWall = ToPtr(new Transform(tfmBack, square, grayMat));

//     mat4 tfmLight(1.0f);
//     tfmLight = translate(tfmLight, vec3(0, 2.999, 0));
//     tfmLight = scale(tfmLight, vec3(2));
//     tfmLight = rotate(tfmLight, Math::PI / 2, vec3(1, 0, 0));
//     auto light = ToPtr(new Transform(tfmLight, square, lightMat));

//     mat4 tfmCube1(1.0f);
//     tfmCube1 = translate(tfmCube1, vec3(1.1, -2.2, 1.5));
//     tfmCube1 = scale(tfmCube1, vec3(1.6));
//     tfmCube1 = rotate(tfmCube1, -Math::PI / 12, vec3(0, 1, 0));
//     auto cube1 = ToPtr(new Transform(tfmCube1, cube, cubeMat));

//     mat4 tfmCube2(1.0f);
//     tfmCube2 = translate(tfmCube2, vec3(-1.1, -1, -0.5));
//     tfmCube2 = scale(tfmCube2, vec3(1.6, 4, 1.6));
//     tfmCube2 = rotate(tfmCube2, Math::PI / 9, vec3(0, 1, 0));
//     auto cube2 = ToPtr(new Transform(tfmCube2, cube, cubeMat));

//     // Scene
//     auto group = ToPtr(new Group);

//     (*group) << greenWall << redWall << bottomWall << topWall << backWall << cube1 << cube2 << light;
// }

// int main()
// {
//     int nx = 1200;
//     int ny = 600;
//     int ns = 30;
//     World world;
//     createWorld(world);
//     vec3 lookfrom(13, 2, 3);
//     vec3 lookat(0, 0, 0);
//     float dist_to_focus = 10.0f;
//     float aperture = 0.1f;

//     shared_ptr<Camera> cam = make_shared<Camera>(lookfrom, lookat, vec3(0, -1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
//     Renderer render(nx, ny, 3, "light.png", ns);
//     render.Render(world, cam);

//     world.Reset();
//     return 0;
// }
