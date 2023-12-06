#pragma once

// Defined before including GLEW to suppress deprecation messages on macOS
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <utils/sceneparser.h>
#include <camera/camera.h>
#include "shapes/Cone.h"
#include "shapes/Cube.h"
#include "shapes/Cylinder.h"
#include "shapes/Sphere.h"

#include <unordered_map>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>

class Movement {
public:

    RenderShapeData getUpdatedPlayObject(RenderShapeData &shapeData, glm::vec3 direction, float speed, float deltaTime);
    RenderData updateMetaData(RenderData metaData, RenderShapeData playobject, const glm::mat4& newCTM, int objectIndex);
};
