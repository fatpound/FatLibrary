#pragma once

#include <vector>

namespace fatpound::win32::d3d11
{
    struct FullScreenQuad
    {
        struct alignas(32) Vertex
        {
            float x;
            float y;
            float z;

            float u;
            float v;
        };

        static auto S_GenerateVertices() -> std::vector<Vertex>;
    };
}
