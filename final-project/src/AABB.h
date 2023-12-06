#pragma once

#include <glm/glm.hpp>
class AABB{
public:
    glm::vec3 maxV;
    glm::vec3 minV;
    void calculateV(glm::mat4 ctm);
};

