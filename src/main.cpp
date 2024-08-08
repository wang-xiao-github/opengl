#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "shader.h"
#include "texture.h"
#include "camera.h"

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

    Shader shaderObject("/Users/wangxiao/code/learnOpenGL/res/shders/vertex.shader", "/Users/wangxiao/code/learnOpenGL/res/shders/fragment.shader");
    Shader shaderLighting("/Users/wangxiao/code/learnOpenGL/res/shders/vertex.shader", "/Users/wangxiao/code/learnOpenGL/res/shders/fragmentLighting.shader");

    Texture texture("/Users/wangxiao/code/learnOpenGL/images/container2.png", GL_TEXTURE_2D);
    Texture textureSpec("/Users/wangxiao/code/learnOpenGL/images/container2_specular.png", GL_TEXTURE_2D);
    Texture textureMat("/Users/wangxiao/code/learnOpenGL/images/matrix.jpg", GL_TEXTURE_2D);
    texture.bind(0);
    textureSpec.bind(1);
    textureMat.bind(2);
    

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };


    unsigned int VAOs[2], VBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);



    //解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glEnable(GL_DEPTH_TEST);


    shaderObject.use();
    // shaderObject.setVec3("material.ambient",  {0.1f, 0.05f, 0.1f});
    shaderObject.setInt("material.diffuse",  0);
    shaderObject.setInt("material.specular",  1);
    shaderObject.setInt("textureMat",  2);
    // shaderObject.setVec3("material.specular", {0.5f, 0.5f, 0.5f});
    shaderObject.setFloat("material.shininess", 32.0f);



    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };



    while(!glfwWindowShouldClose(window))
    {   
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //清屏
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window); //输入操作
        glm::vec3 lightPos = glm::vec3(-0.2f, -1.0f, -0.3f) ;


        glBindVertexArray(VAOs[0]);
        shaderObject.use();
        shaderObject.setFloat("matrixlight", (1.0+sin(glfwGetTime()))/2+0.5);
        shaderObject.setFloat("matrixmove", glfwGetTime());

        // shaderObject.setVec3("lightPos", lightPos);

        shaderObject.setVec3("viewPos", camera.cameraPos);
        glm::mat4 view = camera.getViewMatrix();
        shaderObject.setMat4("view", view);
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)(SCR_WIDTH/SCR_HEIGHT), 0.1f, 100.0f);
        shaderObject.setMat4("projection", projection);


        glm::vec3 lightColor(0.2f, 1.0f, 1.0f);
        shaderObject.use();
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.3f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.1f); // low influence

    

        glm::vec3 dirLightDir = view * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

        shaderObject.setVec3("dirLight.direction", dirLightDir);
        shaderObject.setVec3("dirLight.ambient", ambientColor);
        shaderObject.setVec3("dirLight.diffuse", diffuseColor);
        shaderObject.setVec3("dirLight.specular", {0.5f, 0.5f, 0.5f});
        // point light 1
        glm::vec3 pointLightPosition = view * glm::vec4(0.7f,  0.2f,  2.0f, 1.0f);
        shaderObject.setVec3("pointLights[0].position", pointLightPosition);
        shaderObject.setVec3("pointLights[0].ambient", {0.05f, 0.05f, 0.05f});
        shaderObject.setVec3("pointLights[0].diffuse", {0.8f, 0.8f, 0.8f});
        shaderObject.setVec3("pointLights[0].specular", {1.0f, 1.0f, 1.0f});
        shaderObject.setFloat("pointLights[0].constant", 1.0f);
        shaderObject.setFloat("pointLights[0].linear", 0.09f);
        shaderObject.setFloat("pointLights[0].quadratic", 0.032f);

        pointLightPosition = view * glm::vec4( 2.3f, -3.3f, -4.0f, 1.0f);
        shaderObject.setVec3("pointLights[1].position", pointLightPosition);
        shaderObject.setVec3("pointLights[1].ambient", {0.05f, 0.05f, 0.05f});
        shaderObject.setVec3("pointLights[1].diffuse", {0.8f, 0.8f, 0.8f});
        shaderObject.setVec3("pointLights[1].specular", {1.0f, 1.0f, 1.0f});
        shaderObject.setFloat("pointLights[1].constant", 1.0f);
        shaderObject.setFloat("pointLights[1].linear", 0.09f);
        shaderObject.setFloat("pointLights[1].quadratic", 0.032f);

        pointLightPosition = view * glm::vec4(-4.0f,  2.0f, -12.0f, 1.0f);
        shaderObject.setVec3("pointLights[2].position", pointLightPosition);
        shaderObject.setVec3("pointLights[2].ambient", {0.05f, 0.05f, 0.05f});
        shaderObject.setVec3("pointLights[2].diffuse", {0.8f, 0.8f, 0.8f});
        shaderObject.setVec3("pointLights[2].specular", {1.0f, 1.0f, 1.0f});
        shaderObject.setFloat("pointLights[2].constant", 1.0f);
        shaderObject.setFloat("pointLights[2].linear", 0.09f);
        shaderObject.setFloat("pointLights[2].quadratic", 0.032f);

        pointLightPosition = view * glm::vec4(0.0f,  0.0f, -3.0f, 1.0f);
        shaderObject.setVec3("pointLights[3].position", pointLightPosition);
        shaderObject.setVec3("pointLights[3].ambient", {0.05f, 0.05f, 0.05f});
        shaderObject.setVec3("pointLights[3].diffuse", {0.8f, 0.8f, 0.8f});
        shaderObject.setVec3("pointLights[3].specular", {1.0f, 1.0f, 1.0f});
        shaderObject.setFloat("pointLights[3].constant", 1.0f);
        shaderObject.setFloat("pointLights[3].linear", 0.09f);
        shaderObject.setFloat("pointLights[3].quadratic", 0.032f);

        glm::vec3 spotLightDir = view * glm::vec4(camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z, 0.0f);
        glm::vec3 spotLightPos = view * glm::vec4(camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z, 1.0f);;
        shaderObject.setVec3("spotLight.position", spotLightPos);
        shaderObject.setVec3("spotLight.direction", spotLightDir);
        shaderObject.setVec3("spotLight.ambient", {0.0f, 0.0f, 0.0f});
        shaderObject.setVec3("spotLight.diffuse", {1.0f, 1.0f, 1.0f});
        shaderObject.setVec3("spotLight.specular", {1.0f, 1.0f, 1.0f});
        shaderObject.setFloat("spotLight.constant", 1.0f);
        shaderObject.setFloat("spotLight.linear", 0.09f);
        shaderObject.setFloat("spotLight.quadratic", 0.032f);
        shaderObject.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        shaderObject.setFloat("spotLight.outCutOff", glm::cos(glm::radians(15.0f)));     



        for(int i = 0; i < 10; i++)
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)(i*20), glm::vec3(0.2f, 0.1f, 0.7f));
            shaderObject.setMat4("model", model);
            glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view * model))); //转换到 观察空间的法线矩阵
            shaderObject.setMat3("mormalMat", normalMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        shaderLighting.use();
        for(int i = 0; i < 4; i++)
        {
            shaderLighting.setVec3("lightColor", lightColor);

            shaderLighting.setMat4("view", view);
            shaderLighting.setMat4("projection", projection);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            shaderLighting.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        

    
        //交换颜色缓冲，有双重缓冲区
        glfwSwapBuffers(window);   
        //检查有没有触发时间
        glfwPollEvents();   
    }
    glDeleteVertexArrays(2, VAOs);

    glDeleteBuffers(1, &VBO);

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
