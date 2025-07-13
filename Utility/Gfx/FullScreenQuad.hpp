#pragma once

#include <vector>

namespace fatpound::utility::gfx
{
    struct FullScreenQuad final
    {
        struct alignas(32) Vertex
        {
            float x;
            float y;
            float z;

            float u;
            float v;
        };

        static auto GenerateVertices() -> std::vector<Vertex>;
    };
}
