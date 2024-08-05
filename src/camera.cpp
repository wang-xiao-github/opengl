#include "camera.h"


Camera::Camera(/* args */)
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
float Camera::getFov(){return fov;}
//键盘移动
void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = cameraSpeed * deltaTime;
    if (direction == FORWARD)
        cameraPos += velocity * cameraFront;
    if (direction == BACKWARD)
        cameraPos -= velocity * cameraFront;
    if (direction == LEFT)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
    if (direction == RIGHT)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
    cameraPos.y = 0.0f; //FPS视角，限制在xz平面
};
//鼠标转动方向
void Camera::processMouseMovement(double xpos, double ypos)
{

    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = (lastY - ypos); // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    // glm::vec3 Right = glm::normalize(glm::cross(cameraFront, cameraUp));  //全自由的情况，需要改变相机的向上向量
    // cameraUp  = glm::normalize(glm::cross(Right, front));

}
//鼠标缩放
void Camera::processMouseScroll(double xoffset, double yoffset)
{
    if(fov >= 1.0f && fov <= 80.0f)
        fov -= yoffset;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 80.0f)
        fov = 80.0f;
}