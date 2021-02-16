#include "../src/Core/ray.h"
#include "../src/Core/image.h"
using namespace platinum;
using namespace glm;

vec3 color(const Ray &r)
{
    vec3 unit_direction = normalize(r.GetDirection());
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    int nx = 200;
    int ny = 100;
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    float u, v;
    Image img(200, 100, 3);
    for (int j = 0; j <ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            u = float(i) / float(nx);
            v = float(j) / float(ny);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            img.SetPixel(i, j, Image::Pixel<unsigned char>((int)255.99*col.x, (int)255.99*col.y, (int)255.99*col.z));
        }
    }
    img.SaveAsPNG("ray.png");
}