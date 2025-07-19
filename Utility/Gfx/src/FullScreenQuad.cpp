#include "FullScreenQuad.hpp"

namespace fatpound::utility::gfx
{
    auto FullScreenQuad::S_GenerateVertices() -> std::vector<Vertex>
    {
        return
        {
            Vertex{ .x = -1.0F, .y =  1.0F, .z = 0.5F, .u = 0.0F, .v = 0.0F },
            Vertex{ .x =  1.0F, .y =  1.0F, .z = 0.5F, .u = 1.0F, .v = 0.0F },
            Vertex{ .x =  1.0F, .y = -1.0F, .z = 0.5F, .u = 1.0F, .v = 1.0F },
            Vertex{ .x = -1.0F, .y =  1.0F, .z = 0.5F, .u = 0.0F, .v = 0.0F },
            Vertex{ .x =  1.0F, .y = -1.0F, .z = 0.5F, .u = 1.0F, .v = 1.0F },
            Vertex{ .x = -1.0F, .y = -1.0F, .z = 0.5F, .u = 0.0F, .v = 1.0F }
        };
    }
}
