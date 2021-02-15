#include "../src/Core/image.h"
#include "../src/Math/rand.h"
using namespace platinum;
int main(int argc, char **argv)
{
    Image img(400, 400, 4);
    for (size_t i = 0; i < 400; i++)
    {
        for (size_t j = 0; j < 400; j++)
        {
            if ((i + j) % 2 == 0)
                img.SetPixel(i, j, Image::Pixel<float>(0, 0, 0, Random::drand48()));
            else
            {
                img.SetPixel(i, j, Image::Pixel<float>(10.0 + i / 400.0, 10.0 + i / 400.0, 0, 0.1));
            }
        }
    }
    img.SaveAsPNG("test.png");
    return 0;
}
