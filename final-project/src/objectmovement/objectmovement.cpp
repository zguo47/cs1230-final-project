#include "objectmovement.h"
#include "glm/gtx/transform.hpp"
#include <iostream>

RenderShapeData Movement::getUpdatedPlayObject(RenderShapeData &shapeData, glm::vec3 direction, float speed, float deltaTime){
    glm::mat4 modelMatrix = shapeData.ctm;

    glm::vec3 displacement = direction * speed * deltaTime;

    modelMatrix = glm::translate(modelMatrix, displacement);

    shapeData.ctm = modelMatrix;
    return shapeData;
}

RenderData Movement::updateMetaData(RenderData metaData, RenderShapeData playobject, const glm::mat4& newCTM, int objectIndex){
//    for (RenderShapeData& shape : metaData.shapes) {
//        if (shape.primitive.object_type == objectType::PLAY_OBJECT){
//            shape.ctm = shapeData.ctm;
//        }
//    }
    if (objectIndex >= 0 && objectIndex < metaData.shapes.size()) {
        // Update the ctm of the specific object
        metaData.shapes[objectIndex].ctm = newCTM;
    } else {
        // Handle invalid index, e.g., log an error
        std::cout<<"invalid index";
    }

    metaData.shapes.push_back(playobject);

    return metaData;
}
