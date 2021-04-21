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
// #include "../src/Geometry/instance.h"
// #include <glm/gtc/matrix_transform.hpp>
// #include "instance.h"
// using namespace platinum;
// using namespace glm;
// using namespace std;

// void createWorld(World &world)
// {
   

//     // Mat
//     auto redMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.65f, 0.05f, 0.05f)));
//     auto greenMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.12f, 0.45f, 0.15f)));
//     auto grayMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.73f, 0.73f, 0.73f)));
//     auto blueMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(0.1f, 0.1f, 0.73f)));
//     auto lightMat = make_shared<Light>(vec3(10.f));
//     auto cubeMat = make_shared<Lambertian>(make_shared<ConstTexture>(vec3(1.0f, 1.0f, 1.0f)));

//     mat4 tfmLight(1.0f);
//     tfmLight = glm::translate(tfmLight, vec3(0, 2.99, 0));
//     tfmLight = glm::scale(tfmLight, vec3(3));
//     tfmLight = glm::rotate(tfmLight, -PI / 2, vec3(1, 0, 0));
//     world.AddObject(make_shared<Instance>(tfmLight, square, lightMat));

//     // // // Transform
//     mat4 tfmRight(1.0f);
//     tfmRight = glm::translate(tfmRight, vec3(3, 0, 0));
//     tfmRight = glm::scale(tfmRight, vec3(6));
//     tfmRight = glm::rotate(tfmRight, -PI / 2, vec3(0, 1, 0));
//     world.AddObject(make_shared<Instance>(tfmRight, square, redMat));

//     mat4 tfmLeft(1.0f);
//     tfmLeft = glm::translate(tfmLeft, vec3(-3, 0, 0));
//     tfmLeft = glm::scale(tfmLeft, vec3(6));
//     tfmLeft = glm::rotate(tfmLeft, PI / 2, vec3(0, 1, 0));
//     world.AddObject(make_shared<Instance>(tfmLeft, square, greenMat));

//     mat4 tfmBottom(1.0f);
//     tfmBottom = glm::translate(tfmBottom, vec3(0, -3, 0));
//     tfmBottom = glm::scale(tfmBottom, vec3(6));
//     tfmBottom = glm::rotate(tfmBottom, PI / 2, vec3(1, 0, 0));
//     world.AddObject(make_shared<Instance>(tfmBottom, square, grayMat));

//     mat4 tfmTop(1.0f);
//     tfmTop = glm::translate(tfmTop, vec3(0, 3, 0));
//     tfmTop = glm::scale(tfmTop, vec3(6));
//     tfmTop = glm::rotate(tfmTop, PI / 2, vec3(1, 0, 0));
//     world.AddObject(make_shared<Instance>(tfmTop, square, grayMat));

//     mat4 tfmBack(1.0f);
//     tfmBack = glm::translate(tfmBack, vec3(0, 0, -3));
//     tfmBack = glm::scale(tfmBack, vec3(6));
//     world.AddObject(make_shared<Instance>(tfmBack, square, grayMat));

//     mat4 tfmCube1(1.0f);
//     tfmCube1 = glm::translate(tfmCube1, vec3(1.1, -2.2, 1.5));
//     tfmCube1 = glm::scale(tfmCube1, vec3(1.6));
//     tfmCube1 = glm::rotate(tfmCube1, -PI / 12, vec3(0, 1, 0));
//     world.AddObject(make_shared<Instance>(tfmCube1, cube, lightMat));


//     mat4 tfmCube2(1.0f);
//     tfmCube2 = glm::translate(tfmCube2, vec3(-1.1, -1, -0.5));
//     tfmCube2 = scale(tfmCube2, vec3(1.6, 4, 1.6));
//     tfmCube2 = glm::rotate(tfmCube2, PI / 9, vec3(0, 1, 0));
//     world.AddObject(make_shared<Instance>(tfmCube2, cube, lightMat));

// }

// int main()
// {
//     int nx = 400;
//     int ny = 500;
//     int ns = 10;
//     World world(true);
//     createWorld(world);
//     vec3 lookfrom(0, 0, 10);
//     vec3 lookat(0, 0, 0);
//     float dist_to_focus = 8.0f;
//     float aperture = 0.05f;

//     shared_ptr<Camera> cam = make_shared<Camera>(lookfrom, lookat, vec3(0, 1, 0), 45, float(nx) / float(ny), aperture, dist_to_focus);
//     Renderer render(nx, ny, 3, "instance.png", ns);
//     render.Render(world, cam);

//     world.Reset();
//     return 0;
// }
