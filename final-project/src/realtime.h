#pragma once

// Defined before including GLEW to suppress deprecation messages on macOS
#include "objectmovement/objectmovement.h"
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

class Realtime : public QOpenGLWidget
{
public:
    Realtime(QWidget *parent = nullptr);
    void loadTexture();
    void bindBuffer();
    void clearLights();
    void finish();                                      // Called on program exit
    void sceneChanged();
    void settingsChanged();
    void saveViewportImage(std::string filePath);
    void makeFBO();
    void paintTexture(GLuint texture, bool filter_or_not, bool blur_or_not, bool gray_or_not, bool gamestart);

public slots:
    void tick(QTimerEvent* event);                      // Called once per tick of m_timer

protected:
    void initializeGL() override;                       // Called once at the start of the program
    void paintGL() override;                            // Called whenever the OpenGL context changes or by an update() request
    void resizeGL(int width, int height) override;      // Called when window size changes

private:
    bool fall_down = false; //fall out of the bridge
    bool initialized = false;
    bool finished_drawing = false;
    bool isMoveLeft = true;
    bool gameStart = false;
    bool m_onXDir = true;
    bool m_canMove = false;
    bool m_first = true;
    bool is_water = false;
    bool is_bridge = false;

    std::string configFilePath = ":/final_scenefiles/finishedv4.json";

    int playobjectindex = 0;

    RenderShapeData playobject;

    GLuint m_shader; // Stores id of shader program
    GLuint m_vbo;    // Stores id of VBO
    GLuint m_vao;    // Stores id of VAO

    GLuint m_defaultFBO;
    int m_fbo_width;
    int m_fbo_height;
    int m_screen_width;
    int m_screen_height;

    GLuint m_texture_shader;
    GLuint m_fullscreen_vbo;
    GLuint m_fullscreen_vao;
    QImage m_image;
    GLuint m_fbo;
    GLuint m_fbo_texture;
    GLuint m_fbo_renderbuffer;

    GLuint m_textures[2];
    GLuint m_scene_texture;
    GLuint m_scene_texture2;
    GLuint m_scene_texture3;

    RenderData metaData;
    Camera camera;
    Movement movement;

    Cone myCone;
    Cube myCube;
    Sphere mySphere;
    Cylinder myCylinder;

    std::vector<GLfloat> conepoints;
    std::vector<GLfloat> spherepoints;
    std::vector<GLfloat> cubepoints;
    std::vector<GLfloat> cylinderpoints;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec2 textureOffset = glm::vec2(0.0f, 0.0f);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    // Tick Related Variables
    int m_timer;                                        // Stores timer which attempts to run ~60 times per second
    QElapsedTimer m_elapsedTimer;                       // Stores timer which keeps track of actual time between frames

    float fall_timer = 0.0f;

    // Input Related Variables
    bool m_mouseDown = false;                           // Stores state of left mouse button
    glm::vec2 m_prev_mouse_pos;                         // Stores mouse position
    std::unordered_map<Qt::Key, bool> m_keyMap;         // Stores whether keys are pressed or not

    // Device Correction Variables
    int m_devicePixelRatio;
    bool AABB(RenderShapeData object);
    int currentGroup = 1;
    glm::vec4 playPos;
    bool groupMove = false;
};
