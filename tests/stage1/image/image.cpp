#include "../src/Core/image.h"
#include "../src/Math/rand.h"
using namespace platinum;
int main(int argc, char **argv)
{
    int nx = 200, ny = 100;
    Image img(nx, ny, 3);
    glm::vec3 color;
    for (size_t i = 0; i < nx; i++)
    {
        for (size_t j = 0; j < ny; j++)
        {
            color.r = float(i) / float(nx);
            color.g = float(j) / float(ny);
            color.b = 0.5f;
             img.SetPixel(i, j, Image::Pixel<unsigned char>(static_cast<int>(255.99f * color.x), static_cast<int>(255.99f * color.y), static_cast<int>(255.99f * color.z)));
        }
    }
    img.SaveAsPNG("image_test.png");
    return 0;
}
