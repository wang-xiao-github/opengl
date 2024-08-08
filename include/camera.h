#pragma once 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
private:
    float lastX = 400, lastY = 400; //屏幕中心
    float cameraSpeed = 2.0f;  //移动速度
    float sensitivity = 0.05f;  //鼠标灵敏度
    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 45.0f;
    bool firstMouse = true;
    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 6.0f);
    // glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

public:
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 6.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    Camera(/* args */);
    ~Camera();
    glm::mat4 getViewMatrix();
    float getFov() const {return fov;}
    // glm::vec3 getCameraPos() const { return cameraPos; }
    //键盘移动
    void processKeyboard(Camera_Movement direction, float deltaTime);
    //鼠标转动方向
    void processMouseMovement(double xpos, double ypos);
    //鼠标缩放
    void processMouseScroll(double xoffset, double yoffset);
   
};

