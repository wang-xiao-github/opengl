#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include "shader.h"
#include "texture.h"
#include "camera.h"

#include "model.h"



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Camera camera;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //注册窗口回调函数
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  //隐藏鼠标



    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // stbi_set_flip_vertically_on_load(true);  //翻转

    Model ourModel("/Users/wangxiao/code/learnOpenGL/nanosuit/nanosuit.obj");   

    Shader shaderObject("/Users/wangxiao/code/learnOpenGL/res/shders/vertex.shader", "/Users/wangxiao/code/learnOpenGL/res/shders/fragment.shader");
    // Shader shaderTest("/Users/wangxiao/code/learnOpenGL/res/shders/vertexTest.shader", "/Users/wangxiao/code/learnOpenGL/res/shders/fragmentLighting.shader");





    glEnable(GL_DEPTH_TEST);






    while(!glfwWindowShouldClose(window))
    {   
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //清屏
        glClearColor(0.6f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window); //输入操作
        glm::vec3 lightPos = glm::vec3(-0.2f, -1.0f, -0.3f) ;


   
        shaderObject.use();


        // shaderObject.setVec3("lightPos", lightPos);


        glm::mat4 view = camera.getViewMatrix();
        shaderObject.setMat4("view", view);
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)(SCR_WIDTH/SCR_HEIGHT), 0.1f, 100.0f);
        shaderObject.setMat4("projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shaderObject.setMat4("model", model);
        
        ourModel.Draw(shaderObject);

 

    
        //交换颜色缓冲，有双重缓冲区
        glfwSwapBuffers(window);   
        //检查有没有触发时间
        glfwPollEvents();   
    }


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window , GLFW_KEY_UP) == GLFW_PRESS)
        camera.processKeyboard(UP, deltaTime);
    if (glfwGetKey(window , GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.processKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window , GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // 取消鼠标光标隐藏
    if (glfwGetKey(window , GLFW_KEY_E) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  //隐藏鼠标

        
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);  //设置窗口的维度
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.processMouseMovement(xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(xoffset, yoffset);
}
