#pragma once

#include <vector>

namespace fatpound::util::gfx
{
    struct FullScreenQuad final
    {
        struct alignas(32) Vertex final
        {
            float x;
            float y;
            float z;

            float u;
            float v;
        };

        static auto GenerateVertices() -> ::std::vector<Vertex>
        {
            return ::std::vector<Vertex>
            {
                Vertex{ .x = -1.0f, .y =  1.0f,  .z = 0.5f,  .u = 0.0f,  .v = 0.0f },
                Vertex{ .x =  1.0f, .y =  1.0f,  .z = 0.5f,  .u = 1.0f,  .v = 0.0f },
                Vertex{ .x =  1.0f, .y = -1.0f,  .z = 0.5f,  .u = 1.0f,  .v = 1.0f },
                Vertex{ .x = -1.0f, .y =  1.0f,  .z = 0.5f,  .u = 0.0f,  .v = 0.0f },
                Vertex{ .x =  1.0f, .y = -1.0f,  .z = 0.5f,  .u = 1.0f,  .v = 1.0f },
                Vertex{ .x = -1.0f, .y = -1.0f,  .z = 0.5f,  .u = 0.0f,  .v = 1.0f }
            };
        }
    };
}
