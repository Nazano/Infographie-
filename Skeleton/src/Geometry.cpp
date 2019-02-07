#include "Geometry.h"

Geometry::Geometry(){}

Geometry::~Geometry()
{
    if(m_vertices)
        free(m_vertices);
    if(m_normals)
        free(m_normals);
    if(m_uvs)
        free(m_uvs);
}
