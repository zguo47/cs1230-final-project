#include "objectmovement.h"
#include "glm/gtx/transform.hpp"
#include <iostream>

RenderShapeData Movement::getUpdatedPlayObject(RenderShapeData &shapeData, glm::vec3 direction, float speed, float deltaTime, float fallTime, bool isFalling){

    glm::mat4 modelMatrix = shapeData.ctm;
    glm::vec3 displacement;
    if (isFalling){
        const float gravity = 2.0f;

        // Horizontal displacement remains the same
        glm::vec3 horizontalDisplacement = direction * speed * deltaTime;

        // Vertical displacement follows a parabolic trajectory
        // Assuming initial vertical velocity is 0 when falling starts
        float verticalDisplacement = -0.5f * gravity * pow(fallTime, 2.0f);

        // Combine horizontal and vertical displacement
        displacement = horizontalDisplacement + glm::vec3(0.0f, verticalDisplacement, 0.0f);

    }else{
        displacement = direction * speed * deltaTime;
    }

    modelMatrix = glm::translate(modelMatrix, displacement);

    shapeData.ctm = modelMatrix;
    shapeData.invCTM = inverse(modelMatrix);
    return shapeData;
}

RenderData Movement::updateMetaData(RenderData metaData, RenderShapeData playobject, const glm::mat4& newCTM, int objectIndex, bool isFalling){

    if (objectIndex >= 0 && objectIndex < metaData.shapes.size()) {
        // Update the ctm of the specific object
        metaData.shapes[objectIndex].ctm = newCTM;
    } else {
        // Handle invalid index, e.g., log an error
        std::cout<<"invalid index";
    }
    //test

    if (!isFalling){
        metaData.shapes.push_back(playobject);
    }

    return metaData;
}
