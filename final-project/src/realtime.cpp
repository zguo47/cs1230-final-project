//#include "realtime.h"
//#include "objectmovement/objectmovement.h"
//#include "shapes/Cone.h"
//#include "shapes/Cube.h"
//#include "shapes/Cylinder.h"
//#include "shapes/Sphere.h"
//#include "utils/shaderloader.h"
//#include "utils/sceneparser.h"
//#include "camera/camera.h"

//#include <QCoreApplication>
//#include <QMouseEvent>
//#include <QKeyEvent>
//#include <iostream>
//#include "settings.h"

//// ================== Project 5: Lights, Camera

//Realtime::Realtime(QWidget *parent)
//    : QOpenGLWidget(parent)
//{
//    m_prev_mouse_pos = glm::vec2(size().width()/2, size().height()/2);
//    setMouseTracking(true);
//    setFocusPolicy(Qt::StrongFocus);

//    m_keyMap[Qt::Key_W]       = false;
//    m_keyMap[Qt::Key_A]       = false;
//    m_keyMap[Qt::Key_S]       = false;
//    m_keyMap[Qt::Key_D]       = false;
//    m_keyMap[Qt::Key_Control] = false;
//    m_keyMap[Qt::Key_Space]   = false;
//    m_keyMap[Qt::Key_M]       = false;

//    // If you must use this function, do not edit anything above this
//}

//void Realtime::finish() {
//    killTimer(m_timer);
//    this->makeCurrent();

//    // Students: anything requiring OpenGL calls when the program exits should be done here
//    // Delete the VBO
//    if (m_vbo) {
//        glDeleteBuffers(1, &m_vbo);
//        m_vbo = 0; // Set to 0 to mark it as 'deleted'
//    }

//    // Delete the VAO
//    if (m_vao) {
//        glDeleteVertexArrays(1, &m_vao);
//        m_vao = 0; // Set to 0 to mark it as 'deleted'
//    }

//    // If you have shaders or shader programs, you should also delete them
//    if (m_shader) {
//        glDeleteProgram(m_shader);
//        m_shader = 0; // Set to 0 to mark it as 'deleted'
//    }

//    if (m_texture_shader) {
//        glDeleteProgram(m_texture_shader);
//        m_texture_shader = 0; // Set to 0 to mark it as 'deleted'
//    }

//    if (m_fullscreen_vbo) {
//        glDeleteBuffers(1, &m_fullscreen_vbo);
//        m_fullscreen_vbo = 0; // Set to 0 to mark it as 'deleted'
//    }

//    if (m_fullscreen_vao) {
//        glDeleteVertexArrays(1, &m_fullscreen_vao);
//        m_fullscreen_vao = 0; // Set to 0 to mark it as 'deleted'
//    }

//    glDeleteTextures(1, &m_fbo_texture); // project6
//    glDeleteRenderbuffers(1, &m_fbo_renderbuffer); // project6
//    glDeleteFramebuffers(1, &m_fbo); // project6

//    this->doneCurrent();
//}

//void Realtime::initializeGL() {
//    m_devicePixelRatio = this->devicePixelRatio();

//    m_timer = startTimer(1000/60);
//    m_elapsedTimer.start();

//    m_defaultFBO = 2;
//    m_screen_width = size().width() * m_devicePixelRatio;
//    m_screen_height = size().height() * m_devicePixelRatio;
//    m_fbo_width = m_screen_width;
//    m_fbo_height = m_screen_height;

//    // Initializing GL.
//    // GLEW (GL Extension Wrangler) provides access to OpenGL functions.
//    glewExperimental = GL_TRUE;
//    GLenum err = glewInit();
//    if (err != GLEW_OK) {
//        std::cerr << "Error while initializing GL: " << glewGetErrorString(err) << std::endl;
//    }
//    std::cout << "Initialized GL: Version " << glewGetString(GLEW_VERSION) << std::endl;

//    // Allows OpenGL to draw objects appropriately on top of one another
//    glEnable(GL_DEPTH_TEST);
//    // Tells OpenGL to only draw the front face
//    glEnable(GL_CULL_FACE);
//    // Tells OpenGL how big the screen is
//    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);

//    // Students: anything requiring OpenGL calls when the program starts should be done here
//    glClearColor(0, 0, 0, 255);

//    m_shader = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert", ":/resources/shaders/default.frag");
//    m_texture_shader = ShaderLoader::createShaderProgram(":/resources/shaders/texture.vert", ":/resources/shaders/texture.frag");

//    loadTexture();

//    initialized = true;
//    glGenBuffers(1, &m_vbo);
//    glGenVertexArrays(1, &m_vao);

//    bindBuffer();
//    sceneChanged();

//}

//void Realtime::loadTexture(){
//    glGenTextures(2, m_textures);

//    m_scene_texture = m_textures[0];
//    glBindTexture(GL_TEXTURE_2D, m_scene_texture);

//    // Set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // Set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // Load image, create texture and generate mipmaps

//    // Prepare filepath
//    QString water_filepath = QString(":/resources/images/water4.png");

//    // Task 1: Obtain image from filepath
//    m_image = QImage(water_filepath);

//    // Task 2: Format image to fit OpenGL
//    m_image = m_image.convertToFormat(QImage::Format_RGBA8888).mirrored();

//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.bits());
//    glBindTexture(GL_TEXTURE_2D, 0);

//    m_scene_texture2 = m_textures[1];
//    glBindTexture(GL_TEXTURE_2D, m_scene_texture2);

//    // Set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // Set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // Load image, create texture and generate mipmaps

//    // Prepare filepath
//    QString bridge_filepath = QString(":/resources/images/daniel.png");

//    // Task 1: Obtain image from filepath
//    m_image = QImage(bridge_filepath);

//    // Task 2: Format image to fit OpenGL
//    m_image = m_image.convertToFormat(QImage::Format_RGBA8888).mirrored();

//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.bits());
//    glBindTexture(GL_TEXTURE_2D, 0);

//}


//void Realtime::bindBuffer(){
//    // ================== Vertex Buffer Objects

//    // Bind the VBO you created here
//    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

//    myCone.updateParams(5, 5);
//    myCube.updateParams(5);
//    mySphere.updateParams(5, 5);
//    myCylinder.updateParams(5, 5);

//    conepoints = myCone.generateShape();
//    spherepoints = mySphere.generateShape();
//    cubepoints = myCube.generateShape();
//    cylinderpoints = myCylinder.generateShape();

//    size_t totalSize = conepoints.size() + spherepoints.size() +
//                       cubepoints.size() + cylinderpoints.size();

//    std::vector<GLfloat> allVertices(totalSize);

//    std::copy(conepoints.begin(), conepoints.end(), allVertices.begin());
//    std::copy(spherepoints.begin(), spherepoints.end(), allVertices.begin() + conepoints.size());
//    std::copy(cubepoints.begin(), cubepoints.end(), allVertices.begin() + conepoints.size() + spherepoints.size());
//    std::copy(cylinderpoints.begin(), cylinderpoints.end(), allVertices.begin() + conepoints.size() + spherepoints.size() + cubepoints.size());


//    glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(GLfloat), allVertices.data(), GL_STATIC_DRAW);

//    // ================== Vertex Array Objects

//    // Task 12: Bind the VAO you created here
//    glBindVertexArray(m_vao);

//    // Task 13: Add position and color attributes to your VAO here
//    GLsizei stride = 6 * sizeof(GLfloat);
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(GLfloat)));

//    // ================== Returning to Default State

//    // Task 14: Unbind your VBO and VAO here
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

//    // Task 10: Set the texture.frag uniform for our texture
//    glUseProgram(m_texture_shader);
//    GLint location = glGetUniformLocation(m_texture_shader, "samp");
//    glUniform1i(location, 0);
//    glUseProgram(0);

//    glUseProgram(m_shader);
//    GLint location_default = glGetUniformLocation(m_shader, "samp");
//    glUniform1i(location_default, 0);
//    glUseProgram(0);

//    // Task 11: Fix this "fullscreen" quad's vertex data
//    // Task 12: Play around with different values!
//    // Task 13: Add UV coordinates
//    std::vector<GLfloat> fullscreen_quad_data =
//        { //     POSITIONS    //
//         -1.0f,  1.0f, 0.0f,
//         0.0f,  1.0f,
//         -1.0f, -1.0f, 0.0f,
//         0.0f,  0.0f,
//         1.0f, -1.0f, 0.0f,
//         1.0f,  0.0f,
//         1.0f,  1.0f, 0.0f,
//         1.0f,  1.0f,
//         -1.0f,  1.0f, 0.0f,
//         0.0f,  1.0f,
//         1.0f, -1.0f, 0.0f,
//         1.0f,  0.0f,
//         };

//    // Generate and bind a VBO and a VAO for a fullscreen quad
//    glGenBuffers(1, &m_fullscreen_vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, m_fullscreen_vbo);
//    glBufferData(GL_ARRAY_BUFFER, fullscreen_quad_data.size()*sizeof(GLfloat), fullscreen_quad_data.data(), GL_STATIC_DRAW);
//    glGenVertexArrays(1, &m_fullscreen_vao);
//    glBindVertexArray(m_fullscreen_vao);

//    // Task 14: modify the code below to add a second attribute to the vertex attribute array
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

//    // Unbind the fullscreen quad's VBO and VAO
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

//    makeFBO();

//}

//void Realtime::paintGL() {
//    // Students: anything requiring OpenGL calls every frame should be done here
//    // Task 15: Clear the screen here
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    // Task 24: Bind our FBO
//    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

//    // Task 28: Call glViewport
//    glViewport(0, 0, m_fbo_width, m_fbo_height);

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    // Bind the shader
//    glUseProgram(m_shader);

//    // Pass in necessary paramets
//    GLint v_location = glGetUniformLocation(m_shader, "view_matrix");
//    glUniformMatrix4fv(v_location, 1, GL_FALSE, &viewMatrix[0][0]);

//    GLint p_location = glGetUniformLocation(m_shader, "projection_matrix");
//    glUniformMatrix4fv(p_location, 1, GL_FALSE, &projectionMatrix[0][0]);

//    GLint m_location = glGetUniformLocation(m_shader, "model_matrix");

//    GLint n_location = glGetUniformLocation(m_shader, "normalMatrix");

//    GLint mka_location = glGetUniformLocation(m_shader, "ambient");

//    GLint mkd_location = glGetUniformLocation(m_shader, "diffuse");

//    GLint mks_location = glGetUniformLocation(m_shader, "specular");

//    GLint shi_location = glGetUniformLocation(m_shader, "m_shininess");

//    GLint numLightsLocation = glGetUniformLocation(m_shader, "num_lights");
//    glUniform1i(numLightsLocation, metaData.lights.size());

//    for (size_t i = 0; i < metaData.lights.size(); ++i) {
//        std::string lightBase = "lights[" + std::to_string(i) + "]";

//        GLint lightTypeLocation = glGetUniformLocation(m_shader, (lightBase + ".type").c_str());

//        switch(metaData.lights[i].type){
//        case LightType::LIGHT_DIRECTIONAL:
//            glUniform1i(lightTypeLocation, 0);
//            break;
//        case LightType::LIGHT_SPOT:
//            glUniform1i(lightTypeLocation, 1);
//            break;
//        case LightType::LIGHT_POINT:
//            glUniform1i(lightTypeLocation, 2);
//            break;
//        }

//        // Set light position
//        GLint lightPosLocation = glGetUniformLocation(m_shader, (lightBase + ".position").c_str());
//        glUniform4fv(lightPosLocation, 1, &metaData.lights[i].pos[0]);

//        // Set light direction
//        GLint lightDirLocation = glGetUniformLocation(m_shader, (lightBase + ".direction").c_str());
//        glUniform4fv(lightDirLocation, 1, &metaData.lights[i].dir[0]);

//        // Set light intensity/color
//        GLint lightIntensityLocation = glGetUniformLocation(m_shader, (lightBase + ".lightColor").c_str());
//        glUniform4fv(lightIntensityLocation, 1, &metaData.lights[i].color[0]);

//        GLint lightFunctionLocation = glGetUniformLocation(m_shader, (lightBase + ".function").c_str());
//        glUniform3fv(lightFunctionLocation, 1, &metaData.lights[i].function[0]);

//        GLint lightPenumbraLocation = glGetUniformLocation(m_shader, (lightBase + ".penumbra").c_str());
//        glUniform1f(lightPenumbraLocation, metaData.lights[i].penumbra);

//        GLint lightAngleLocation = glGetUniformLocation(m_shader, (lightBase + ".angle").c_str());
//        glUniform1f(lightAngleLocation, metaData.lights[i].angle);

//    }

//    GLint c_location = glGetUniformLocation(m_shader, "camera_pos");
//    glm::vec4 cam_pos = glm::inverse(viewMatrix) * glm::vec4(0.0, 0.0, 0.0, 1.0);
//    glUniform4fv(c_location, 1, &cam_pos[0]);

//    glBindVertexArray(m_vao);

//    GLint coneOffset = 0;
//    GLint sphereOffset = conepoints.size() / 6;
//    GLint cubeOffset = conepoints.size() / 6 + spherepoints.size() / 6;
//    GLint cylinderOffset = conepoints.size() / 6 + spherepoints.size() / 6 + cubepoints.size() / 6;


//    for (const RenderShapeData& shapeData : metaData.shapes) {

//        glm::mat4 modelMatrix = shapeData.ctm; // The model matrix for the shape
//        glUniformMatrix4fv(m_location, 1, GL_FALSE, &modelMatrix[0][0]);

//        glm::mat3 normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelMatrix)));
//        glUniformMatrix3fv(n_location, 1, GL_FALSE, &normalMatrix[0][0]);

//        SceneMaterial material = shapeData.primitive.material;
//        glm::vec4 ambient = material.cAmbient * metaData.globalData.ka;
//        glUniform4fv(mka_location, 1, &ambient[0]);

//        glm::vec4 diffuse = material.cDiffuse * metaData.globalData.kd;
//        glUniform4fv(mkd_location, 1, &diffuse[0]);

//        glm::vec4 specular = material.cSpecular * metaData.globalData.ks;
//        glUniform4fv(mks_location, 1, &specular[0]);

//        float shininess = material.shininess;
//        glUniform1f(shi_location, shininess);

//        GLint offset = 0;
//        GLsizei count = 0;

//        switch(shapeData.primitive.type){
//        case PrimitiveType::PRIMITIVE_CONE:
//            offset = coneOffset;
//            count = conepoints.size() / 6;
//            break;

//        case PrimitiveType::PRIMITIVE_SPHERE:
//            offset = sphereOffset;
//            count = spherepoints.size() / 6;
//            break;

//        case PrimitiveType::PRIMITIVE_CUBE:
//            offset = cubeOffset;
//            count = cubepoints.size() / 6;
//            break;

//        case PrimitiveType::PRIMITIVE_CYLINDER:
//            offset = cylinderOffset;
//            count = cylinderpoints.size() / 6;
//            break;

//        default:
//            break;
//        }

//        GLint b_location4 = glGetUniformLocation(m_shader, "scenetexture_or_not");

//        GLint water_location = glGetUniformLocation(m_shader, "is_water");

//        if (shapeData.primitive.type == PrimitiveType::PRIMITIVE_CUBE &&  shapeData.primitive.textureType == textureType::WATER){
//            is_water = true;
//            glBindTexture(GL_TEXTURE_2D, m_scene_texture);
//            glActiveTexture(GL_TEXTURE0);
//            glUniform1i(b_location4, is_water);
//        }else if (shapeData.primitive.type == PrimitiveType::PRIMITIVE_CUBE && shapeData.primitive.textureType == textureType::BRIDGE){
//            is_bridge = true;
//            glBindTexture(GL_TEXTURE_2D, m_scene_texture2);
//            glActiveTexture(GL_TEXTURE0);
//            glUniform1i(b_location4, is_bridge);
//        }else{
//            glUniform1i(b_location4, false);
//        }

//        glUniform1i(water_location, is_water);

//        GLint offset_location = glGetUniformLocation(m_shader, "textureOffset");
//        glUniform2fv(offset_location, 1, &textureOffset[0]);

//        glDrawArrays(GL_TRIANGLES, offset, count);

//        if (shapeData.primitive.type == PrimitiveType::PRIMITIVE_CUBE && shapeData.primitive.textureType == textureType::WATER){
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }else if (shapeData.primitive.type == PrimitiveType::PRIMITIVE_CUBE &&  shapeData.primitive.textureType == textureType::BRIDGE){
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }

//        is_water = false;
//        is_bridge = false;

//    }

//    // Task 25: Bind the default framebuffer
//    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);

//    glViewport(0, 0, m_screen_width, m_screen_height);

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    paintTexture(m_fbo_texture, false, false, false, false);

//    glBindVertexArray(0);

//    // Unbind the shader
//    glUseProgram(0);

//    finished_drawing = true;
//}

//void Realtime::resizeGL(int w, int h) {
//    // Tells OpenGL how big the screen is
//    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);

//    // Students: anything requiring OpenGL calls when the program starts should be done here
//    glDeleteTextures(1, &m_fbo_texture);
//    glDeleteRenderbuffers(1, &m_fbo_renderbuffer);
//    glDeleteFramebuffers(1, &m_fbo);

//    m_screen_width = size().width() * m_devicePixelRatio;
//    m_screen_height = size().height() * m_devicePixelRatio;
//    m_fbo_width = m_screen_width;
//    m_fbo_height = m_screen_height;
//    // Task 34: Regenerate your FBOs
//    makeFBO();
//}

//void Realtime::sceneChanged() {
//    RenderData temp;
//    metaData = temp;
//    bool success = SceneParser::parse(configFilePath, metaData);
//    int idx = 0;
//    for (const RenderShapeData& shapeData : metaData.shapes) {
//        if (shapeData.primitive.object_type == objectType::PLAY_OBJECT){
//            playobject = shapeData;
//            playobjectindex = idx;
//        }
//        idx += 1;
//    }
//    viewMatrix = camera.getViewMatrix(metaData.cameraData);
//    float aspectRatio = camera.getAspectRatio(size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
//    projectionMatrix = camera.getProjectionMatrix(metaData.cameraData, aspectRatio, 100.0f, 0.1f);
//    isMoveLeft = true;
//    m_onXDir = true;
//    fall_down = false;
//    currentGroup = 1;
//    update(); // asks for a PaintGL() call to occur
//}

//void Realtime::settingsChanged() {
//    if (initialized){
//        bindBuffer();
//    }
//    update(); // asks for a PaintGL() call to occur
//}

//// ================== Project 6: Action!

//void Realtime::keyPressEvent(QKeyEvent *event) {
//    m_keyMap[Qt::Key(event->key())] = true;
//    if (event->key() == Qt::Key_Space) {
//        // Toggle the isMoveLeft state
//        gameStart = true;
//        fall_timer = 0.0f;
//        isMoveLeft = !isMoveLeft;

//        if(!m_onXDir){
//            m_onXDir = true;
//        }
//        else m_onXDir = false;

//        if (m_first){
//            if(!m_canMove){
//                m_canMove = true;
//            }
//            else m_canMove = false;

//            m_first = false;
//        }

//        for (RenderShapeData &object : metaData.shapes){
//            float distXZ = sqrt(pow(object.originPos.x-playPos.x,2)+pow(object.originPos.z-playPos.z,2));//get x,z distance between play and scene
//            if ((object.primitive.group == currentGroup && distXZ<0.85) ||( object.primitive.group == currentGroup && groupMove)){
//                groupMove = true;
//            }
//        }
//    }

//    if (event->key() == Qt::Key_R) {
//        RenderData temp;
//        metaData = temp;
//        bool success = SceneParser::parse(configFilePath, metaData);
//        if(!success){
//            std::cout << "What do you think you're loading?" << std::endl;
//            exit(1);
//        }

//        int idx = 0;
//        for (const RenderShapeData& shapeData : metaData.shapes) {
//            if (shapeData.primitive.object_type == objectType::PLAY_OBJECT){
//                playobject = shapeData;
//                playobjectindex = idx;
//            }
//            idx += 1;
//        }
//        viewMatrix = camera.getViewMatrix(metaData.cameraData);
//        float aspectRatio = camera.getAspectRatio(size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
//        projectionMatrix = camera.getProjectionMatrix(metaData.cameraData, aspectRatio, 100.0f, 0.1f);
//        isMoveLeft = true;
//        m_onXDir = true;
//        fall_down = false;
//        currentGroup = 1;
//        update(); // asks for a PaintGL() call to occur
//    }
//}

//void Realtime::keyReleaseEvent(QKeyEvent *event) {
//    m_keyMap[Qt::Key(event->key())] = false;
//}

//void Realtime::mousePressEvent(QMouseEvent *event) {
//    if (event->buttons().testFlag(Qt::LeftButton)) {
//        m_mouseDown = true;
//        m_prev_mouse_pos = glm::vec2(event->position().x(), event->position().y());
//    }
//}

//void Realtime::mouseReleaseEvent(QMouseEvent *event) {
//    if (!event->buttons().testFlag(Qt::LeftButton)) {
//        m_mouseDown = false;
//    }
//}

//void Realtime::mouseMoveEvent(QMouseEvent *event) {
//    if (m_mouseDown) {
//        int posX = event->position().x();
//        int posY = event->position().y();
//        int deltaX = posX - m_prev_mouse_pos.x;
//        int deltaY = posY - m_prev_mouse_pos.y;
//        m_prev_mouse_pos = glm::vec2(posX, posY);

//        // Use deltaX and deltaY here to rotate
//        SceneCameraData newcamera = camera.getUpdatedRotation(metaData.cameraData, deltaX, deltaY, 0.1f);
//        viewMatrix = camera.getViewMatrix(newcamera);
//        float aspectRatio = camera.getAspectRatio(size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
//        projectionMatrix = camera.getProjectionMatrix(newcamera, aspectRatio, 100.0f, 0.1f);

//        update(); // asks for a PaintGL() call to occur
//    }
//}

//void Realtime::timerEvent(QTimerEvent *event) {
//    int elapsedms   = m_elapsedTimer.elapsed();
//    float deltaTime = elapsedms * 0.001f;
//    m_elapsedTimer.restart();
//    int z = 0;
//    float speed = 0.6f;
//    int collideBridgeNum = 0;

//    bool intersectBridge = false;
//    playPos = playobject.ctm*glm::vec4(0.f,0.f,0.f,1);
//    if (gameStart){
//        for (RenderShapeData &object : metaData.shapes){
//            // collision
//            if (object.primitive.object_type != objectType::PLAY_OBJECT){
//                if(AABB(object)){
//                    if(object.primitive.collision_type == collisionType::collision){
//                        gameStart = false;
//                    }
//                    //if collide with bridge
//                    if (object.primitive.collision_type == collisionType::bridge){
//                        fall_down = true;//make it possible to falldown
//                    }
//                }
//                //if fall_down is true and not colliding with bridge
//                if(object.primitive.collision_type == collisionType::bridge){
//                    if(AABB(object)){
//                        collideBridgeNum+=1;
//                    }
//                }
//            }
//            //movement of the scene
//            if (object.primitive.object_type==objectType::UP_OBJECT and object.primitive.group == currentGroup && groupMove){
//                glm::vec3 direction = glm::normalize(glm::vec3(0.f,1.f,0.f));
//                object = movement.getUpdatedPlayObject(object,direction,12.f,deltaTime,0.0f,false);
//                object.moveTime+=0.1;
//            }
//            if (object.moveTime >= 1.8f and groupMove and object.primitive.group == currentGroup){
//                groupMove = false;
//                currentGroup+=1;
//            }
//        }
//    }
//    if (collideBridgeNum == 0 and fall_down){
//        glm::vec3 direction;
//        if (isMoveLeft){
//            direction = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f));
//        }else{
//            direction = glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f));
//        }
//        fall_timer += deltaTime;
//        playobject = movement.getUpdatedPlayObject(playobject, direction, 12.7f, deltaTime, fall_timer, true);
//        metaData = movement.updateMetaData(metaData, playobject, playobject.ctm, playobjectindex, true);
//        gameStart = false;
//    }
//    // Use deltaTime and m_keyMap here to move around
//    //    SceneCameraData newcamera = camera.getUpdatedCameraData(metaData.cameraData, m_keyMap, speed, deltaTime);
//    if (gameStart){
//        textureOffset += glm::vec2(-0.2f * deltaTime, 0.0f);
//    }
//    if (gameStart){
//        SceneCameraData newcamera;
//        if (playobject.moveTime > 34.0f && playobject.moveTime < 35.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.015f, 0.015f, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 4, 3);
//        }
//        else if (playobject.moveTime >= 35.0f && playobject.moveTime < 36.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.02f, 0.02f, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 7, 3);
//        }
//        else if (playobject.moveTime >= 36.0f && playobject.moveTime < 37.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.02f, 0.018f, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 8, 2);
//        }
//        else if (playobject.moveTime >= 37.0f && playobject.moveTime < 38.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.012f, 0.01f, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 10, 1);
//        }
//        else if (playobject.moveTime >= 38.0f && playobject.moveTime < 40.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.005f, 0.015f, glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 11, 1);
//        }
//        else if (playobject.moveTime >= 40.0f && playobject.moveTime < 41.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.005f, 0.012f, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 10, 1);
//        }
//        else if (playobject.moveTime >= 41.0f && playobject.moveTime < 43.5f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.012f, 0.01f, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 9, 1);
//        }
//        else if (playobject.moveTime >= 43.5f && playobject.moveTime < 45.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.012f, 0.005f, glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 8, 0);
//        }
//        else if (playobject.moveTime >= 45.0f && playobject.moveTime < 46.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.01f, 0.005f, glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 8, 0);
//        }
//        else if (playobject.moveTime >= 46.0f && playobject.moveTime < 47.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.005f, 0.005f, glm::vec4(-1.0f, 0.0f,  0.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 8, 0);
//        }
//        else if (playobject.moveTime >= 47.0f && playobject.moveTime < 48.5f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.005f, glm::vec4(-1.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 8, 0);
//        }
//        else if (playobject.moveTime >= 48.5f && playobject.moveTime < 51.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.005f, glm::vec4(-1.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 8, 0);
//        }
//        else if (playobject.moveTime >= 51.0f && playobject.moveTime < 56.0f){
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.01f, glm::vec4(-1.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 0, -4);
//        }
////        else if (playobject.moveTime >= 52.0f && playobject.moveTime < 53.0f){
////            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.0001f, glm::vec4(3.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 3, 0);
////    }
//        else{
//            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.0f, glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, false, false, 0, 0);
//        }
//        viewMatrix = camera.getViewMatrix(newcamera);
//        float aspectRatio = camera.getAspectRatio(size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
//        projectionMatrix = camera.getProjectionMatrix(newcamera, aspectRatio, 100.0f, 0.1f);

//    }

//    if (gameStart && isMoveLeft) {
//        // Perform action for moving left
//        playobject.moveTime += deltaTime;
//        glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
//        playobject = movement.getUpdatedPlayObject(playobject, direction, 12.3f, deltaTime, 0.0f, false);
//        metaData = movement.updateMetaData(metaData, playobject, playobject.ctm, playobjectindex, false);
//    }
//    else if (gameStart){
//        // Perform action for not moving left
//        playobject.moveTime += deltaTime;
//        glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
//        playobject = movement.getUpdatedPlayObject(playobject, direction, 12.3f, deltaTime, 0.0f, false);
//        metaData = movement.updateMetaData(metaData, playobject, playobject.ctm, playobjectindex, false);
//    }

//    update(); // asks for a PaintGL() call to occur
//}

//bool Realtime::AABB(RenderShapeData object){
//    //get object's max points in play cube space
//    glm::vec4 maxV = playobject.invCTM*object.ctm*glm::vec4(0.5,0.5,0.5,1);
//    glm::vec4 minV = playobject.invCTM*object.ctm*glm::vec4(-0.5,-0.5,-0.5,1);
//    // Check for overlap along the X-axis
//    if (maxV.x < -0.5 || minV.x > 0.5) return false;

//    // Check for overlap along the Y-axis
//    if (maxV.y < -0.5 || minV.y > 0.5) return false;

//    // Check for overlap along the Z-axis
//    if (maxV.z < -0.5 || minV.z > 0.5) return false;
//    // If there is overlap along all axes, collision occurs
//    return true;
//}


//void Realtime::makeFBO(){
//    // Task 19: Generate and bind an empty texture, set its min/mag filter interpolation, then unbind
//    glGenTextures(1, &m_fbo_texture);
//    glBindTexture(GL_TEXTURE_2D, m_fbo_texture);
//    glActiveTexture(GL_TEXTURE0);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_fbo_width, m_fbo_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    glBindTexture(GL_TEXTURE_2D, 0);

//    // Task 20: Generate and bind a renderbuffer of the right size, set its format, then unbind
//    glGenRenderbuffers(1, &m_fbo_renderbuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, m_fbo_renderbuffer);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fbo_width, m_fbo_height);
//    glBindRenderbuffer(GL_RENDERBUFFER, 0);

//    // Task 18: Generate and bind an FBO
//    glGenFramebuffers(1, &m_fbo);
//    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

//    // Task 21: Add our texture as a color attachment, and our renderbuffer as a depth+stencil attachment, to our FBO
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbo_texture, 0);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_fbo_renderbuffer);

//    // Task 22: Unbind the FBO
//    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);

//}

//// Task 31: Update the paintTexture function signature
//void Realtime::paintTexture(GLuint texture, bool filter_or_not, bool blur_or_not, bool gray_or_not, bool scenetexture_or_not){
//    glUseProgram(m_texture_shader);
//    // Task 32: Set your bool uniform on whether or not to filter the texture drawn
//    GLint b_location = glGetUniformLocation(m_texture_shader, "filter_or_not");
//    glUniform1i(b_location, filter_or_not);

//    GLint b_location2 = glGetUniformLocation(m_texture_shader, "blur_or_not");
//    glUniform1i(b_location2, blur_or_not);

//    GLint b_location3 = glGetUniformLocation(m_texture_shader, "gray_or_not");
//    glUniform1i(b_location3, gray_or_not);

//    GLint b_location4 = glGetUniformLocation(m_texture_shader, "scenetexture_or_not");
//    glUniform1i(b_location4, scenetexture_or_not);

//    GLint t_location1 = glGetUniformLocation(m_texture_shader, "texelWidth");
//    glUniform1f(t_location1, 1.0f / m_fbo_width);

//    GLint t_location2 = glGetUniformLocation(m_texture_shader, "texelHeight");
//    glUniform1f(t_location2, 1.0f / m_fbo_height);

//    glBindVertexArray(m_fullscreen_vao);

//    // Task 10: Bind "texture" to slot 0
//    glActiveTexture(GL_TEXTURE0);

//    glBindTexture(GL_TEXTURE_2D, texture);
//    glDrawArrays(GL_TRIANGLES, 0, 6);

//    glBindTexture(GL_TEXTURE_2D, 0);
//    glBindVertexArray(0);
//    glUseProgram(0);
//}

//// DO NOT EDIT
//void Realtime::saveViewportImage(std::string filePath) {
//    // Make sure we have the right context and everything has been drawn
//    makeCurrent();

//    int fixedWidth = 1024;
//    int fixedHeight = 768;

//    // Create Frame Buffer
//    GLuint fbo;
//    glGenFramebuffers(1, &fbo);
//    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

//    // Create a color attachment texture
//    GLuint texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fixedWidth, fixedHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

//    // Optional: Create a depth buffer if your rendering uses depth testing
//    GLuint rbo;
//    glGenRenderbuffers(1, &rbo);
//    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fixedWidth, fixedHeight);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//        std::cerr << "Error: Framebuffer is not complete!" << std::endl;
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//        return;
//    }

//    // Render to the FBO
//    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//    glViewport(0, 0, fixedWidth, fixedHeight);

//    // Clear and render your scene here
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    paintGL();

//    // Read pixels from framebuffer
//    std::vector<unsigned char> pixels(fixedWidth * fixedHeight * 3);
//    glReadPixels(0, 0, fixedWidth, fixedHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

//    // Unbind the framebuffer to return to default rendering to the screen
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);

//    // Convert to QImage
//    QImage image(pixels.data(), fixedWidth, fixedHeight, QImage::Format_RGB888);
//    QImage flippedImage = image.mirrored(); // Flip the image vertically

//    // Save to file using Qt
//    QString qFilePath = QString::fromStdString(filePath);
//    if (!flippedImage.save(qFilePath)) {
//        std::cerr << "Failed to save image to " << filePath << std::endl;
//    }

//    // Clean up
//    glDeleteTextures(1, &texture);
//    glDeleteRenderbuffers(1, &rbo);
//    glDeleteFramebuffers(1, &fbo);
//}
#include "realtime.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "objectmovement/objectmovement.h"
#include "shapes/Cone.h"
#include "shapes/Cube.h"
#include "shapes/Cylinder.h"
#include "shapes/Sphere.h"
#include "utils/shaderloader.h"
#include "utils/sceneparser.h"
#include "camera/camera.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>
#include "settings.h"

// ================== Project 5: Lights, Camera

Realtime::Realtime(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_prev_mouse_pos = glm::vec2(size().width()/2, size().height()/2);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    m_keyMap[Qt::Key_W]       = false;
    m_keyMap[Qt::Key_A]       = false;
    m_keyMap[Qt::Key_S]       = false;
    m_keyMap[Qt::Key_D]       = false;
    m_keyMap[Qt::Key_Control] = false;
    m_keyMap[Qt::Key_Space]   = false;
    m_keyMap[Qt::Key_M]       = false;

    // If you must use this function, do not edit anything above this
}

void Realtime::finish() {
    killTimer(m_timer);
    this->makeCurrent();

    // Students: anything requiring OpenGL calls when the program exits should be done here
    // Delete the VBO
    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0; // Set to 0 to mark it as 'deleted'
    }

    // Delete the VAO
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0; // Set to 0 to mark it as 'deleted'
    }

    // If you have shaders or shader programs, you should also delete them
    if (m_shader) {
        glDeleteProgram(m_shader);
        m_shader = 0; // Set to 0 to mark it as 'deleted'
    }

    if (m_texture_shader) {
        glDeleteProgram(m_texture_shader);
        m_texture_shader = 0; // Set to 0 to mark it as 'deleted'
    }

    if (m_fullscreen_vbo) {
        glDeleteBuffers(1, &m_fullscreen_vbo);
        m_fullscreen_vbo = 0; // Set to 0 to mark it as 'deleted'
    }

    if (m_fullscreen_vao) {
        glDeleteVertexArrays(1, &m_fullscreen_vao);
        m_fullscreen_vao = 0; // Set to 0 to mark it as 'deleted'
    }

    glDeleteTextures(1, &m_fbo_texture); // project6
    glDeleteRenderbuffers(1, &m_fbo_renderbuffer); // project6
    glDeleteFramebuffers(1, &m_fbo); // project6

    this->doneCurrent();
}

void Realtime::initializeGL() {
    m_devicePixelRatio = this->devicePixelRatio();

    m_timer = startTimer(1000/60);
    m_elapsedTimer.start();

    m_defaultFBO = 2;
    m_screen_width = size().width() * m_devicePixelRatio;
    m_screen_height = size().height() * m_devicePixelRatio;
    m_fbo_width = m_screen_width;
    m_fbo_height = m_screen_height;

    // Initializing GL.
    // GLEW (GL Extension Wrangler) provides access to OpenGL functions.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error while initializing GL: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Initialized GL: Version " << glewGetString(GLEW_VERSION) << std::endl;

    // Allows OpenGL to draw objects appropriately on top of one another
    glEnable(GL_DEPTH_TEST);
    // Tells OpenGL to only draw the front face
    glEnable(GL_CULL_FACE);
    // Tells OpenGL how big the screen is
    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);

    // Students: anything requiring OpenGL calls when the program starts should be done here
    glClearColor(0, 0, 0, 255);

    m_shader = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert", ":/resources/shaders/default.frag");
    m_texture_shader = ShaderLoader::createShaderProgram(":/resources/shaders/texture.vert", ":/resources/shaders/texture.frag");

    loadTexture();

    initialized = true;
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);

    bindBuffer();
    sceneChanged();

}

void Realtime::loadTexture(){
    glGenTextures(2, m_textures);

    m_scene_texture = m_textures[0];
    glBindTexture(GL_TEXTURE_2D, m_scene_texture);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps

    // Prepare filepath
    QString water_filepath = QString(":/resources/images/water4.png");

    // Task 1: Obtain image from filepath
    m_image = QImage(water_filepath);

    // Task 2: Format image to fit OpenGL
    m_image = m_image.convertToFormat(QImage::Format_RGBA8888).mirrored();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.bits());
    glBindTexture(GL_TEXTURE_2D, 0);

    m_scene_texture2 = m_textures[1];
    glBindTexture(GL_TEXTURE_2D, m_scene_texture2);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps

    // Prepare filepath
    QString bridge_filepath = QString(":/resources/images/daniel.png");

    // Task 1: Obtain image from filepath
    m_image = QImage(bridge_filepath);

    // Task 2: Format image to fit OpenGL
    m_image = m_image.convertToFormat(QImage::Format_RGBA8888).mirrored();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.bits());
    glBindTexture(GL_TEXTURE_2D, 0);

}


void Realtime::bindBuffer(){
    // ================== Vertex Buffer Objects

    // Bind the VBO you created here
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    myCone.updateParams(5, 5);
    myCube.updateParams(5);
    mySphere.updateParams(5, 5);
    myCylinder.updateParams(5, 5);

    conepoints = myCone.generateShape();
    spherepoints = mySphere.generateShape();
    cubepoints = myCube.generateShape();
    cylinderpoints = myCylinder.generateShape();

    size_t totalSize = conepoints.size() + spherepoints.size() +
                       cubepoints.size() + cylinderpoints.size();

    std::vector<GLfloat> allVertices(totalSize);

    std::copy(conepoints.begin(), conepoints.end(), allVertices.begin());
    std::copy(spherepoints.begin(), spherepoints.end(), allVertices.begin() + conepoints.size());
    std::copy(cubepoints.begin(), cubepoints.end(), allVertices.begin() + conepoints.size() + spherepoints.size());
    std::copy(cylinderpoints.begin(), cylinderpoints.end(), allVertices.begin() + conepoints.size() + spherepoints.size() + cubepoints.size());


    glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(GLfloat), allVertices.data(), GL_STATIC_DRAW);

    // ================== Vertex Array Objects

    // Task 12: Bind the VAO you created here
    glBindVertexArray(m_vao);

    // Task 13: Add position and color attributes to your VAO here
    GLsizei stride = 6 * sizeof(GLfloat);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    // ================== Returning to Default State

    // Task 14: Unbind your VBO and VAO here
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Task 10: Set the texture.frag uniform for our texture
    glUseProgram(m_texture_shader);
    GLint location = glGetUniformLocation(m_texture_shader, "samp");
    glUniform1i(location, 0);
    glUseProgram(0);

    glUseProgram(m_shader);
    GLint location_default = glGetUniformLocation(m_shader, "samp");
    glUniform1i(location_default, 0);
    glUseProgram(0);

    // Task 11: Fix this "fullscreen" quad's vertex data
    // Task 12: Play around with different values!
    // Task 13: Add UV coordinates
    std::vector<GLfloat> fullscreen_quad_data =
        { //     POSITIONS    //
         -1.0f,  1.0f, 0.0f,
         0.0f,  1.0f,
         -1.0f, -1.0f, 0.0f,
         0.0f,  0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,
         -1.0f,  1.0f, 0.0f,
         0.0f,  1.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  0.0f,
         };

    // Generate and bind a VBO and a VAO for a fullscreen quad
    glGenBuffers(1, &m_fullscreen_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_fullscreen_vbo);
    glBufferData(GL_ARRAY_BUFFER, fullscreen_quad_data.size()*sizeof(GLfloat), fullscreen_quad_data.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &m_fullscreen_vao);
    glBindVertexArray(m_fullscreen_vao);

    // Task 14: modify the code below to add a second attribute to the vertex attribute array
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    // Unbind the fullscreen quad's VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    makeFBO();
}

void Realtime::paintGL() {
    // Students: anything requiring OpenGL calls every frame should be done here
    // Task 15: Clear the screen here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Task 24: Bind our FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Task 28: Call glViewport
    glViewport(0, 0, m_fbo_width, m_fbo_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind the shader
    glUseProgram(m_shader);

    // Pass in necessary paramets
    GLint v_location = glGetUniformLocation(m_shader, "view_matrix");
    glUniformMatrix4fv(v_location, 1, GL_FALSE, &viewMatrix[0][0]);

    GLint p_location = glGetUniformLocation(m_shader, "projection_matrix");
    glUniformMatrix4fv(p_location, 1, GL_FALSE, &projectionMatrix[0][0]);

    GLint m_location = glGetUniformLocation(m_shader, "model_matrix");

    GLint n_location = glGetUniformLocation(m_shader, "normalMatrix");

    GLint mka_location = glGetUniformLocation(m_shader, "ambient");

    GLint mkd_location = glGetUniformLocation(m_shader, "diffuse");

    GLint mks_location = glGetUniformLocation(m_shader, "specular");

    GLint shi_location = glGetUniformLocation(m_shader, "m_shininess");

    GLint numLightsLocation = glGetUniformLocation(m_shader, "num_lights");
    glUniform1i(numLightsLocation, metaData.lights.size());

    for (size_t i = 0; i < metaData.lights.size(); ++i) {
        std::string lightBase = "lights[" + std::to_string(i) + "]";

        GLint lightTypeLocation = glGetUniformLocation(m_shader, (lightBase + ".type").c_str());

        switch(metaData.lights[i].type){
        case LightType::LIGHT_DIRECTIONAL:
            glUniform1i(lightTypeLocation, 0);
            break;
        case LightType::LIGHT_SPOT:
            glUniform1i(lightTypeLocation, 1);
            break;
        case LightType::LIGHT_POINT:
            glUniform1i(lightTypeLocation, 2);
            break;
        }

        // Set light position
        GLint lightPosLocation = glGetUniformLocation(m_shader, (lightBase + ".position").c_str());
        glUniform4fv(lightPosLocation, 1, &metaData.lights[i].pos[0]);

        // Set light direction
        GLint lightDirLocation = glGetUniformLocation(m_shader, (lightBase + ".direction").c_str());
        glUniform4fv(lightDirLocation, 1, &metaData.lights[i].dir[0]);

        // Set light intensity/color
        GLint lightIntensityLocation = glGetUniformLocation(m_shader, (lightBase + ".lightColor").c_str());
        glUniform4fv(lightIntensityLocation, 1, &metaData.lights[i].color[0]);

        GLint lightFunctionLocation = glGetUniformLocation(m_shader, (lightBase + ".function").c_str());
        glUniform3fv(lightFunctionLocation, 1, &metaData.lights[i].function[0]);

        GLint lightPenumbraLocation = glGetUniformLocation(m_shader, (lightBase + ".penumbra").c_str());
        glUniform1f(lightPenumbraLocation, metaData.lights[i].penumbra);

        GLint lightAngleLocation = glGetUniformLocation(m_shader, (lightBase + ".angle").c_str());
        glUniform1f(lightAngleLocation, metaData.lights[i].angle);

    }

    GLint c_location = glGetUniformLocation(m_shader, "camera_pos");
    glm::vec4 cam_pos = glm::inverse(viewMatrix) * glm::vec4(0.0, 0.0, 0.0, 1.0);
    glUniform4fv(c_location, 1, &cam_pos[0]);

    glBindVertexArray(m_vao);

    GLint coneOffset = 0;
    GLint sphereOffset = conepoints.size() / 6;
    GLint cubeOffset = conepoints.size() / 6 + spherepoints.size() / 6;
    GLint cylinderOffset = conepoints.size() / 6 + spherepoints.size() / 6 + cubepoints.size() / 6;


    for (const RenderShapeData& shapeData : metaData.shapes) {

        glm::mat4 modelMatrix = shapeData.ctm; // The model matrix for the shape
        glUniformMatrix4fv(m_location, 1, GL_FALSE, &modelMatrix[0][0]);

        glm::mat3 normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelMatrix)));
        glUniformMatrix3fv(n_location, 1, GL_FALSE, &normalMatrix[0][0]);

        SceneMaterial material = shapeData.primitive.material;
        glm::vec4 ambient = material.cAmbient * metaData.globalData.ka;
        glUniform4fv(mka_location, 1, &ambient[0]);

        glm::vec4 diffuse = material.cDiffuse * metaData.globalData.kd;
        glUniform4fv(mkd_location, 1, &diffuse[0]);

        glm::vec4 specular = material.cSpecular * metaData.globalData.ks;
        glUniform4fv(mks_location, 1, &specular[0]);

        float shininess = material.shininess;
        glUniform1f(shi_location, shininess);

        GLint offset = 0;
        GLsizei count = 0;

        switch(shapeData.primitive.type){
        case PrimitiveType::PRIMITIVE_CONE:
            offset = coneOffset;
            count = conepoints.size() / 6;
            break;

        case PrimitiveType::PRIMITIVE_SPHERE:
            offset = sphereOffset;
            count = spherepoints.size() / 6;
            break;

        case PrimitiveType::PRIMITIVE_CUBE:
            offset = cubeOffset;
            count = cubepoints.size() / 6;
            break;

        case PrimitiveType::PRIMITIVE_CYLINDER:
            offset = cylinderOffset;
            count = cylinderpoints.size() / 6;
            break;

        default:
            break;
        }

        GLint b_location4 = glGetUniformLocation(m_shader, "scenetexture_or_not");

        GLint water_location = glGetUniformLocation(m_shader, "is_water");

        if (shapeData.primitive.type == PrimitiveType::PRIMITIVE_CUBE &&  shapeData.primitive.textureType == textureType::WATER){
            is_water = true;
            glBindTexture(GL_TEXTURE_2D, m_scene_texture);
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(b_location4, is_water);
        }else if (shapeData.primitive.type == PrimitiveType::PRIMITIVE_CUBE && shapeData.primitive.textureType == textureType::BRIDGE){
            is_bridge = true;
            glBindTexture(GL_TEXTURE_2D, m_scene_texture2);
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(b_location4, is_bridge);
        }else{
            glUniform1i(b_location4, false);
        }

        glUniform1i(water_location, is_water);

        GLint offset_location = glGetUniformLocation(m_shader, "textureOffset");
        glUniform2fv(offset_location, 1, &textureOffset[0]);

        glDrawArrays(GL_TRIANGLES, offset, count);

        if (shapeData.primitive.type == PrimitiveType::PRIMITIVE_CUBE && shapeData.primitive.textureType == textureType::WATER){
            glBindTexture(GL_TEXTURE_2D, 0);
        }else if (shapeData.primitive.type == PrimitiveType::PRIMITIVE_CUBE &&  shapeData.primitive.textureType == textureType::BRIDGE){
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        is_water = false;
        is_bridge = false;

    }

    // Task 25: Bind the default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);

    glViewport(0, 0, m_screen_width, m_screen_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    paintTexture(m_fbo_texture, false, false, false, false);

    glBindVertexArray(0);

    // Unbind the shader
    glUseProgram(0);

    finished_drawing = true;
}

void Realtime::resizeGL(int w, int h) {
    // Tells OpenGL how big the screen is
    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);

    // Students: anything requiring OpenGL calls when the program starts should be done here
    glDeleteTextures(1, &m_fbo_texture);
    glDeleteRenderbuffers(1, &m_fbo_renderbuffer);
    glDeleteFramebuffers(1, &m_fbo);

    m_screen_width = size().width() * m_devicePixelRatio;
    m_screen_height = size().height() * m_devicePixelRatio;
    m_fbo_width = m_screen_width;
    m_fbo_height = m_screen_height;
    // Task 34: Regenerate your FBOs
    makeFBO();
}

void Realtime::sceneChanged() {
    RenderData temp;
    metaData = temp;
    bool success = SceneParser::parse(configFilePath, metaData);
    int idx = 0;
    for (const RenderShapeData& shapeData : metaData.shapes) {
        if (shapeData.primitive.object_type == objectType::PLAY_OBJECT){
            playobject = shapeData;
            playobjectindex = idx;
        }
        idx += 1;
    }
    viewMatrix = camera.getViewMatrix(metaData.cameraData);
    float aspectRatio = camera.getAspectRatio(size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
    projectionMatrix = camera.getProjectionMatrix(metaData.cameraData, aspectRatio, 100.0f, 0.1f);
    isMoveLeft = true;
    m_onXDir = true;
    fall_down = false;
    currentGroup = 1;
    update(); // asks for a PaintGL() call to occur
}

void Realtime::settingsChanged() {
    if (initialized){
        bindBuffer();
    }
    update(); // asks for a PaintGL() call to occur
}

// ================== Project 6: Action!

void Realtime::keyPressEvent(QKeyEvent *event) {
    m_keyMap[Qt::Key(event->key())] = true;
    if (event->key() == Qt::Key_Space) {
        // Toggle the isMoveLeft state
        gameStart = true;
        fall_timer = 0.0f;
        isMoveLeft = !isMoveLeft;

        if(!m_onXDir){
            m_onXDir = true;
        }
        else m_onXDir = false;

        if (m_first){
            if(!m_canMove){
                m_canMove = true;
            }
            else m_canMove = false;

            m_first = false;
        }

        for (RenderShapeData &object : metaData.shapes){
            float distXZ = sqrt(pow(object.originPos.x-playPos.x,2)+pow(object.originPos.z-playPos.z,2));//get x,z distance between play and scene
            if ((object.primitive.group == currentGroup && distXZ<0.85) ||( object.primitive.group == currentGroup && groupMove)){
                groupMove = true;
            }
        }

        std::cout << currentGroup << std::endl;
    }

    if (event->key() == Qt::Key_R) {
        RenderData temp;
        metaData = temp;
        bool success = SceneParser::parse(configFilePath, metaData);
        if(!success){
            std::cout << "What do you think you're loading?" << std::endl;
            exit(1);
        }

        int idx = 0;
        for (const RenderShapeData& shapeData : metaData.shapes) {
            if (shapeData.primitive.object_type == objectType::PLAY_OBJECT){
                playobject = shapeData;
                playobjectindex = idx;
            }
            idx += 1;
        }
        viewMatrix = camera.getViewMatrix(metaData.cameraData);
        float aspectRatio = camera.getAspectRatio(size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
        projectionMatrix = camera.getProjectionMatrix(metaData.cameraData, aspectRatio, 100.0f, 0.1f);
        isMoveLeft = true;
        m_onXDir = true;
        fall_down = false;
        currentGroup = 1;
        update(); // asks for a PaintGL() call to occur
    }
}

void Realtime::keyReleaseEvent(QKeyEvent *event) {
    m_keyMap[Qt::Key(event->key())] = false;
}

void Realtime::mousePressEvent(QMouseEvent *event) {
    if (event->buttons().testFlag(Qt::LeftButton)) {
        m_mouseDown = true;
        m_prev_mouse_pos = glm::vec2(event->position().x(), event->position().y());
    }
}

void Realtime::mouseReleaseEvent(QMouseEvent *event) {
    if (!event->buttons().testFlag(Qt::LeftButton)) {
        m_mouseDown = false;
    }
}

void Realtime::mouseMoveEvent(QMouseEvent *event) {
    if (m_mouseDown) {
        int posX = event->position().x();
        int posY = event->position().y();
        int deltaX = posX - m_prev_mouse_pos.x;
        int deltaY = posY - m_prev_mouse_pos.y;
        m_prev_mouse_pos = glm::vec2(posX, posY);

        // Use deltaX and deltaY here to rotate
        SceneCameraData newcamera = camera.getUpdatedRotation(metaData.cameraData, deltaX, deltaY, 0.1f);
        viewMatrix = camera.getViewMatrix(newcamera);
        float aspectRatio = camera.getAspectRatio(size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
        projectionMatrix = camera.getProjectionMatrix(newcamera, aspectRatio, 100.0f, 0.1f);

        update(); // asks for a PaintGL() call to occur
    }
}

void Realtime::timerEvent(QTimerEvent *event) {
    int elapsedms   = m_elapsedTimer.elapsed();
    float deltaTime = elapsedms * 0.001f;
    m_elapsedTimer.restart();
    int z = 0;
    float speed = 0.6f;
    bool collideBridge = false;

    playPos = playobject.ctm * glm::vec4(0.f, 0.f, 0.f, 1.f);

    // check for collision of each type
    for (RenderShapeData &object : metaData.shapes){

        // Check if the object is not a PLAY_OBJECT and there is an AABB collision
        if (object.primitive.object_type != objectType::PLAY_OBJECT && AABB(object)) {

            // Check the collision type
            switch (object.primitive.collision_type) {
            // If collided obstacles, then end the game
            case collisionType::collision:
                gameStart = false;
                break;

                // Handle bridge collision type
            case collisionType::bridge:
                collideBridge = true;
                fall_down = true;

                break;

            case collisionType::no_collision:
                break;
            }
        }

        //movement of the scene
        glm::vec3 direction;

        // if the curret
        if (object.primitive.group == currentGroup && groupMove) {
            // Check object type for UP_OBJECT
            if (object.primitive.object_type == objectType::UP_OBJECT) {
                direction = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
            }
            // Check object type for DOWN_OBJECT
            else if (object.primitive.object_type == objectType::DOWN_OBJECT) {
                direction = glm::normalize(glm::vec3(0.f, -1.f, 0.f));
            }
        }

        float distXZ = glm::length(glm::vec2(object.originPos.x - playPos.x, object.originPos.z - playPos.z));

        if (groupMove && object.primitive.group == currentGroup && currentGroup >= 1 && currentGroup <= 35) {
            float speed = (currentGroup <= 10) ? 9.f : 12.f;
            float maxMoveTime = (currentGroup <= 10) ? 2.36f : 1.0f;
            object = movement.getUpdatedPlayObject(object, direction, speed, deltaTime, 0.0f, false);
            object.moveTime += 0.1;

            if (object.moveTime >= maxMoveTime) {
                groupMove = false;
                currentGroup += 1;
            }
        }

        if (object.primitive.group == 100 && distXZ < 1.2 && object.moveTime<1.5){
            direction = glm::normalize(glm::vec3(0.f, 1.f, 0.f));
            object = movement.getUpdatedPlayObject(object, direction, 38.2f, deltaTime, 0.0f, false);
            object.moveTime+=0.1;
        }

        if (object.primitive.group == 101 && object.moveTime < 6.1f){
            float distXYZ = glm::distance(object.originPos,playPos);
            if (distXYZ < 1.7f){
                direction = glm::normalize(glm::vec3(0.f, -1.f, 0.f));
                object = movement.getUpdatedPlayObject(object, direction, 4.65f, deltaTime, 0.0f, false);
                object.moveTime+=0.1;
            }
        }

        if (object.primitive.group == 102 && distXZ < 2.0f && object.moveTime < 4.7f){
            direction = glm::vec3(0.f, 1.f, 0.f);
            object = movement.getUpdatedPlayObject(object, direction, 0.93f, deltaTime, 0.0f, false);
            object.moveTime+=0.1;
        }
//        if (object.primitive.group == 102 && distXZ < 2.0f){
//            glm::vec4 currentPos = object.ctm * glm::vec4(0.f,0.f,0.f,1);
//            if (currentPos.y-object.originPos.y < 1.4f){
//                direction = glm::vec3(0.f, 1.f, 0.f);
//                object = movement.getUpdatedPlayObject(object, direction, 1.f, deltaTime, 0.0f, false);
//            }
//        }

        if(object.primitive.group == 103 && distXZ < 0.8f && object.moveTime < 2.1f){
            direction = glm::vec3(0.f, 1.f, 0.f);
            object = movement.getUpdatedPlayObject(object, direction, 2.03f, deltaTime, 0.f, false);
            object.moveTime += 0.1f;
        }
    }
//    if (collideBridge && fall_down){
//        gameStart = true; //poor fix for part 2 bug
//    }

    glm::vec3 direction = (isMoveLeft) ? glm::vec3(0.0f, 0.0f, -1.0f) : glm::vec3(1.0f, 0.0f, 0.0f);

    // if it is not colliding with bridge and also have fall_down, it moved beyond the area of bridge and should start to fall.
    if (!collideBridge && fall_down){
        fall_timer += deltaTime;
        playobject = movement.getUpdatedPlayObject(playobject, direction, 12.7f, deltaTime, fall_timer, true);
        metaData = movement.updateMetaData(metaData, playobject, playobject.ctm, playobjectindex, true);
        gameStart = false;
    }
    // Use deltaTime and m_keyMap here to move around

    // if the game is started
    if (gameStart){

        // ensures the water texture is dynamic rather than static
        textureOffset += glm::vec2(-0.2f * deltaTime, 0.0f);

        SceneCameraData newcamera;
        if (playobject.moveTime > 34.0f && playobject.moveTime < 35.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.015f, 0.018f, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 3, 3);
        }
        else if (playobject.moveTime >= 35.0f && playobject.moveTime < 36.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.02f, 0.02f, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 6, 3);
        }
        else if (playobject.moveTime >= 36.0f && playobject.moveTime < 37.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.02f, 0.02f, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 7, 2);
        }
        else if (playobject.moveTime >= 37.0f && playobject.moveTime < 38.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.012f, 0.01f, glm::vec4(0.0f, 0.0f, -1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 7, 1);
        }
        else if (playobject.moveTime >= 38.0f && playobject.moveTime < 40.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.005f, 0.012f, glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 7, 1);
        }
        else if (playobject.moveTime >= 40.0f && playobject.moveTime < 41.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.005f, 0.012f, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, true, 7, 1);
        }
        else if (playobject.moveTime >= 41.0f && playobject.moveTime < 43.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.008f, 0.012f, glm::vec4(1.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 7, 0);
        }
        else if (playobject.moveTime >= 43.0f && playobject.moveTime < 45.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.008f, 0.002f, glm::vec4(-1.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 7, 0);
        }
        else if (playobject.moveTime >= 45.0f && playobject.moveTime < 46.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.008f, 0.005f, glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 7, 0);
        }
        else if (playobject.moveTime >= 46.0f && playobject.moveTime < 47.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.005f, 0.005f, glm::vec4(-1.0f, 0.0f,  0.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 6, 0);
        }
        else if (playobject.moveTime >= 47.0f && playobject.moveTime < 52.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.005f, glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 5, 0);
        }
        else if (playobject.moveTime >= 52.0f && playobject.moveTime < 53.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.005f, glm::vec4(-1.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 4, -1);
        }
        else if (playobject.moveTime >= 53.0f && playobject.moveTime < 56.0f){
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.005f, glm::vec4(-1.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, true, false, 0, -2);
        }
        else{
            newcamera = camera.cameraMovement(metaData.cameraData, speed, 0.0f, 0.0f, glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), deltaTime, m_canMove, m_onXDir, m_keyMap, false, false, 0, 0);
        }

        // generate new view matrix, aspect ration and projection matrix
        viewMatrix = camera.getViewMatrix(newcamera);
        float aspectRatio = camera.getAspectRatio(size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);
        projectionMatrix = camera.getProjectionMatrix(newcamera, aspectRatio, 100.0f, 0.1f);

        playobject.moveTime += deltaTime;
        // update play object's position and metadata
        playobject = movement.getUpdatedPlayObject(playobject, direction, 12.3f, deltaTime, 0.0f, false);
        metaData = movement.updateMetaData(metaData, playobject, playobject.ctm, playobjectindex, false);
    }

    update(); // asks for a PaintGL() call to occur
}

bool Realtime::AABB(RenderShapeData object){
    //get object's max points in play cube space
    glm::vec4 maxV = playobject.invCTM * object.ctm * glm::vec4(0.5f, 0.5f, 0.5f, 1.f);
    glm::vec4 minV = playobject.invCTM*object.ctm*glm::vec4(-0.5f, -0.5f, -0.5f, 1.f);
    // Check for overlap along the X-axis
    if (maxV.x < -0.5 || minV.x > 0.5) return false;

    // Check for overlap along the Y-axis
    if (maxV.y < -0.5 || minV.y > 0.5) return false;

    // Check for overlap along the Z-axis
    if (maxV.z < -0.5 || minV.z > 0.5) return false;

    // If there is overlap along all axes, collision occurs
    return true;
}


void Realtime::makeFBO(){
    // Task 19: Generate and bind an empty texture, set its min/mag filter interpolation, then unbind
    glGenTextures(1, &m_fbo_texture);
    glBindTexture(GL_TEXTURE_2D, m_fbo_texture);
    glActiveTexture(GL_TEXTURE0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_fbo_width, m_fbo_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Task 20: Generate and bind a renderbuffer of the right size, set its format, then unbind
    glGenRenderbuffers(1, &m_fbo_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_fbo_renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fbo_width, m_fbo_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Task 18: Generate and bind an FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Task 21: Add our texture as a color attachment, and our renderbuffer as a depth+stencil attachment, to our FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbo_texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_fbo_renderbuffer);

    // Task 22: Unbind the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);

}

// Task 31: Update the paintTexture function signature
void Realtime::paintTexture(GLuint texture, bool filter_or_not, bool blur_or_not, bool gray_or_not, bool scenetexture_or_not){
    glUseProgram(m_texture_shader);
    // Task 32: Set your bool uniform on whether or not to filter the texture drawn
    GLint b_location = glGetUniformLocation(m_texture_shader, "filter_or_not");
    glUniform1i(b_location, filter_or_not);

    GLint b_location2 = glGetUniformLocation(m_texture_shader, "blur_or_not");
    glUniform1i(b_location2, blur_or_not);

    GLint b_location3 = glGetUniformLocation(m_texture_shader, "gray_or_not");
    glUniform1i(b_location3, gray_or_not);

    GLint b_location4 = glGetUniformLocation(m_texture_shader, "scenetexture_or_not");
    glUniform1i(b_location4, scenetexture_or_not);

    GLint t_location1 = glGetUniformLocation(m_texture_shader, "texelWidth");
    glUniform1f(t_location1, 1.0f / m_fbo_width);

    GLint t_location2 = glGetUniformLocation(m_texture_shader, "texelHeight");
    glUniform1f(t_location2, 1.0f / m_fbo_height);

    glBindVertexArray(m_fullscreen_vao);

    // Task 10: Bind "texture" to slot 0
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

// DO NOT EDIT
void Realtime::saveViewportImage(std::string filePath) {
    // Make sure we have the right context and everything has been drawn
    makeCurrent();

    int fixedWidth = 1024;
    int fixedHeight = 768;

    // Create Frame Buffer
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Create a color attachment texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fixedWidth, fixedHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    // Optional: Create a depth buffer if your rendering uses depth testing
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fixedWidth, fixedHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Error: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }

    // Render to the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, fixedWidth, fixedHeight);

    // Clear and render your scene here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintGL();

    // Read pixels from framebuffer
    std::vector<unsigned char> pixels(fixedWidth * fixedHeight * 3);
    glReadPixels(0, 0, fixedWidth, fixedHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // Unbind the framebuffer to return to default rendering to the screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Convert to QImage
    QImage image(pixels.data(), fixedWidth, fixedHeight, QImage::Format_RGB888);
    QImage flippedImage = image.mirrored(); // Flip the image vertically

    // Save to file using Qt
    QString qFilePath = QString::fromStdString(filePath);
    if (!flippedImage.save(qFilePath)) {
        std::cerr << "Failed to save image to " << filePath << std::endl;
    }

    // Clean up
    glDeleteTextures(1, &texture);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(1, &fbo);
}
