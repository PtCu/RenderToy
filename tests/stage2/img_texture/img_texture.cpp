#include "../src/Core/image.h"
#include "../src/Core/ray.h"
#include "../src/Core/camera.h"
#include "../src/Core/object.h"
#include "../src/Material/dielectric.h"
#include "../src/Material/lambertian.h"
#include "../src/Material/metal.h"
#include "../src/Math/rand.h"
#include "../src/Geometry/sphere.h"
#include "../src/Geometry/movingSphere.h"
#include "../src/Core/world.h"
#include "../src/Core/renderer.h"
#include "../src/Texture/imgTexture.h"

using namespace platinum;
using namespace glm;
using namespace std;

void some_spheres(World &world)
{
    auto sph1 = make_shared<Sphere>(vec3(0, 0, -1), 0.5, make_shared<Lambertian>(make_shared<ImgTexture>("../../../../../assets/earthmap.jpg")));
    world.AddObject(sph1);
    
}

int main()
{
    int nx = 1200;
    int ny = 800;
    int ns = 10;
    World world;
    some_spheres(world);

    shared_ptr<Camera> cam = make_shared<Camera>();
    Renderer render(nx, ny, 3, "img_texture.png", ns);
    render.Render(world, cam);

    world.Reset();
    return 0;
}
