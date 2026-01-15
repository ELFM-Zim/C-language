#include "assert.h"
#include "stdint.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


uint32_t pixel[] = {
    0xFF000000, 0x000000FF,
};

int main()
{

    int ok = stbi_write_jpg("pixel_art.jpg", 2, 1, 4, pixel, 2);
    assert(ok);
    return 0;
}

