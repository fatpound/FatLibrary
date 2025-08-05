#include "FullScreenQuad.hpp"

namespace fatpound::win32::d3d11
{
    auto FullScreenQuad::S_GenerateVertices() -> std::vector<Vertex>
    {
        return
        {
            Vertex{ .x = -1.0F, .y =  1.0F, .z = 0.5F, .u = 0.0F, .v = 0.0F },
            Vertex{ .x =  3.0F, .y =  1.0F, .z = 0.5F, .u = 2.0F, .v = 0.0F },
            Vertex{ .x = -1.0F, .y = -3.0F, .z = 0.5F, .u = 0.0F, .v = 2.0F }
        };
    }
}
