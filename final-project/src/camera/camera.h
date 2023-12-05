#pragma once

#include <glm/glm.hpp>
#include "QtCore/qnamespace.h"
#include "utils/scenedata.h"

// A class representing a virtual camera.

// Feel free to make your own design choices for Camera class, the functions below are all optional / for your convenience.
// You can either implement and use these getters, or make your own design.
// If you decide to make your own design, feel free to delete these as TAs won't rely on them to grade your assignments.

class Camera {
public:
    // Returns the view matrix for the current camera settings.
    // You might also want to define another function that return the inverse of the view matrix.
    SceneCameraData cameraMovement(SceneCameraData &camera, float speed, float deltaTime, bool canMove, bool onXDir);

    SceneCameraData getUpdatedRotation(SceneCameraData &camera, int deltaX, int deltaY) const;

    SceneCameraData getUpdatedCameraData(SceneCameraData &camera, std::unordered_map<Qt::Key, bool> m_keyMap, float speed, float deltaTime) const;

    glm::mat4 getViewMatrix(SceneCameraData &camera) const;

    glm::mat4 getProjectionMatrix(SceneCameraData &camera, float aspectRatio, float farPlane, float nearPlane) const;

    // Returns the aspect ratio of the camera.
    float getAspectRatio(int width, int height) const;

    // Returns the height angle of the camera in RADIANS.
    float getHeightAngle(SceneCameraData &camera) const;

    // Returns the focal length of this camera.
    // This is for the depth of field extra-credit feature only;
    // You can ignore if you are not attempting to implement depth of field.
    float getFocalLength(SceneCameraData &camera) const;

    // Returns the focal length of this camera.
    // This is for the depth of field extra-credit feature only;
    // You can ignore if you are not attempting to implement depth of field.
    float getAperture(SceneCameraData &camera) const;
};
