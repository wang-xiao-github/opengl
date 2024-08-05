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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("/Users/wangxiao/code/learnOpenGL/res/shders/vertex.shader", "/Users/wangxiao/code/learnOpenGL/res/shders/fragment.shader");
    Shader shaderColor("/Users/wangxiao/code/learnOpenGL/res/shders/vertex.shader", "/Users/wangxiao/code/learnOpenGL/res/shders/fragmentColor.shader");

    Texture texture2D("/Users/wangxiao/code/learnOpenGL/images/awesomeface.png", GL_TEXTURE_2D);
    Texture texture2D2("/Users/wangxiao/code/learnOpenGL/images/container.jpg", GL_TEXTURE_2D);
    
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    texture2D.bind(); //这个必许创建所有纹理之后相继激活纹理单元
    texture2D2.bind(1);



    // float position[] = 
    // {
    //     0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    //     -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //     0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    // };
    float position[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int indices2[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VAOs[2], EBOs[2];
    unsigned int VBO;

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, EBOs);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
    // glEnableVertexAttribArray(2);

    // glBindVertexArray(VAOs[1]);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
    // glEnableVertexAttribArray(2);

    //解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float mix_mun = 0.0f;
    float iter = 0.001f;
    glEnable(GL_DEPTH_TEST);

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


    while(!glfwWindowShouldClose(window))
    {   
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mix_mun += iter;

        if (mix_mun > 1) iter = -0.001f;
        if (mix_mun < -1) iter = 0.001f; 


        processInput(window); //输入操作
        
        shader.use();
   
        glBindVertexArray(VAOs[0]);
        shader.setFloat("mix_num", mix_mun);

        //定义模型矩阵
        // glm::mat4 model(1.0f);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //定义视图矩阵
        // glm::mat4 view(1.0f);
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        //定义相机（xz平面绕y轴旋转）


        glm::mat4 view = camera.getViewMatrix();

        
        shader.setMat4("view", view);

        //定义投影矩阵
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)(SCR_WIDTH/SCR_HEIGHT), 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        for(int i = 0; i < 10; i++)
        {
            glm::mat4 model(1.0f);

            model = glm::translate(model, cubePositions[i]);

            float angle = 20.0f * i + 20.0f;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.3f));
        
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);


        // glBindVertexArray(VAOs[1]);
        // shaderColor.use();
        // glm::mat4 trans1(1.0f);
        // trans1 = glm::translate(trans1, glm::vec3(-0.5f, 0.5f, 0.0f));
        // trans1 = glm::rotate(trans1, -(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // trans = glm::scale(trans1, glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime())));

        // unsigned int transformUniformPos1 =  glGetUniformLocation(shader.getShaderID(), "transform");
        // glUniformMatrix4fv(transformUniformPos1, 1, GL_FALSE, glm::value_ptr(trans));
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        
        //交换颜色缓冲，有双重缓冲区
        glfwSwapBuffers(window);   
        //检查有没有触发时间
        glfwPollEvents();   
    }
    glDeleteVertexArrays(2, VAOs);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(2, EBOs);

    // glDeleteProgram(shaderProgram);

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
