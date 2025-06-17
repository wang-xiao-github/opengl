

#include <GL/glew.h>  //glew头文件包含必须要在其他拓展之前
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"

#include "Shader.h"

#include "utils.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
        
    //设定相关的GL版本和特定系统的设置
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置了核心配置文件，因此要手动设置顶点数组\
                                                                       兼容OpenGL配置文件时VAO对象0成为默认对象
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS 需要

 
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "hello wa", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE; // 为了确保GLEW加载了最新的扩展，（可加可不加）
    if(glewInit() != GLEW_OK ) //glew的初始化必须在OpenGL的上下文之后
    {
        std::cout << "error\n"; 
    }
 
    std::cout << glGetString(GL_VERSION) << std::endl;
    //创建块状作用域防opengl的循环错误
    {
 
        //顶点数组
        float position[] = 
        {   //102
            0.0, 0.0,
            0.0 , 0.5203376756869016 ,
            0.0020943465091820546 , 0.5433227573341313 ,
            0.01634548146985293 , 0.6078821535689041 ,
            0.0529286376270337 , 0.7016819626665127 ,
            0.11834893353993814 , 0.8068243603716891 ,
            0.2142959280077159 , 0.90322576579748 ,
            0.3372119087311247 , 0.9722740572099455 ,
            0.4786400506023647 , 1.0 ,
            0.6263043764861802 , 0.979133428244743 ,
            0.7657662302945307 , 0.9096896471558316 ,
            0.8824174052200131 , 0.7980773367142973 ,
            0.9635205249603525 , 0.6550516397437989 ,
            1.0 , 0.493076181906682 ,
            0.9877229440466901 , 0.32375130534178154 ,
            0.9280835728223973 , 0.15589623163085942 ,
            0.8278059890117009 , -0.005335510805793975 ,
            0.6979940716772468 , -0.15821721330824856 ,
            0.5525668070763556 , -0.30329010394928 ,
            0.4063068050376797 , -0.44171121543843295 ,
            0.2728058794493513 , -0.5736336125421497 ,
            0.16260623465209356 , -0.6970987279945932 ,
            0.08180685462895387 , -0.8077480794200175 ,
            0.031336375422845286 , -0.8994133292216281 ,
            0.006996024015436086 , -0.9653889424699134 ,
            0.00026341361456760914 , -0.9999999999999998 ,
            -0.0002634136145674981 , -1.0 ,
            -0.006996024015436086 , -0.9653889424699139 ,
            -0.031336375422845064 , -0.8994133292216284 ,
            -0.08180685462895387 , -0.8077480794200176 ,
            -0.16260623465209323 , -0.6970987279945939 ,
            -0.27280587944935053 , -0.5736336125421506 ,
            -0.406306805037679 , -0.4417112154384333 ,
            -0.5525668070763552 , -0.3032901039492806 ,
            -0.6979940716772466 , -0.15821721330824878 ,
            -0.8278059890117001 , -0.005335510805794863 ,
            -0.9280835728223973 , 0.1558962316308592 ,
            -0.9877229440466898 , 0.3237513053417804 ,
            -1.0 , 0.49307618190668157 ,
            -0.9635205249603528 , 0.6550516397437978 ,
            -0.8824174052200137 , 0.7980773367142966 ,
            -0.765766230294532 , 0.9096896471558309 ,
            -0.6263043764861809 , 0.9791334282447428 ,
            -0.4786400506023649 , 1.0 ,
            -0.3372119087311256 , 0.9722740572099455 ,
            -0.21429592800771635 , 0.9032257657974805 ,
            -0.1183489335399387 , 0.80682436037169 ,
            -0.052928637627033814 , 0.7016819626665132 ,
            -0.016345481469853262 , 0.607882153568905 ,
            -0.0020943465091819435 , 0.5433227573341315 ,
            0.0 , 0.5203376756869016 
        }; 

        // //索引缓冲数组
        unsigned int indices[]=
        {
            0 , 1 , 2 ,
            0 , 2 , 3 ,
            0 , 3 , 4 ,
            0 , 4 , 5 ,
            0 , 5 , 6 ,
            0 , 6 , 7 ,
            0 , 7 , 8 ,
            0 , 8 , 9 ,
            0 , 9 , 10 ,
            0 , 10 , 11 ,
            0 , 11 , 12 ,
            0 , 12 , 13 ,
            0 , 13 , 14 ,
            0 , 14 , 15 ,
            0 , 15 , 16 ,
            0 , 16 , 17 ,
            0 , 17 , 18 ,
            0 , 18 , 19 ,
            0 , 19 , 20 ,
            0 , 20 , 21 ,
            0 , 21 , 22 ,
            0 , 22 , 23 ,
            0 , 23 , 24 ,
            0 , 24 , 25 ,
            0 , 25 , 26 ,
            0 , 26 , 27 ,
            0 , 27 , 28 ,
            0 , 28 , 29 ,
            0 , 29 , 30 ,
            0 , 30 , 31 ,
            0 , 31 , 32 ,
            0 , 32 , 33 ,
            0 , 33 , 34 ,
            0 , 34 , 35 ,
            0 , 35 , 36 ,
            0 , 36 , 37 ,
            0 , 37 , 38 ,
            0 , 38 , 39 ,
            0 , 39 , 40 ,
            0 , 40 , 41 ,
            0 , 41 , 42 ,
            0 , 42 , 43 ,
            0 , 43 , 44 ,
            0 , 44 , 45 ,
            0 , 45 , 46 ,
            0 , 46 , 47 ,
            0 , 47 , 48 ,
            0 , 48 , 49 ,
            0 , 49 , 50
        };

        // float position[202];
        // unsigned int indices[300];
        // getPosition(position, indices, 100);


    
// <<<<<<< Opengl-Abstract
//         //创建顶点数组对象 (VAO) 关于使用同一个顶点数组还是每个顶点缓冲都配一个顶点数组，性能情况要具体分析
//         // unsigned int vao;
//         // glGenVertexArrays(1, &vao);
//         // glBindVertexArray(vao);
        
        
//         VertexArray va;
//         VertexBuffer vb(position, sizeof(float) * 2 * 51);
//         VertexBufferLayout layout;
//         layout.Push<float>(2); 
//         va.AddBuffer(vb, layout);
    
//         // glEnableVertexAttribArray(0); //启用
//         // //参数分别为：缓冲区中实际属性的索引对type的计数；归一化（比如颜色0~255归一化成0~1的浮点数）；每个顶点之间的字节数，指向实际属性的指针
//         // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,sizeof(float)*2, 0);
        
//         //索引缓冲区
//         IndexBuffer ib(indices, 3*50);

// =======
//     unsigned int buffer; // 标识缓冲区的id，供后期访问用
//     glGenBuffers(1, &buffer); //生成一个缓冲区
//     glBindBuffer(GL_ARRAY_BUFFER, buffer); //绑定缓冲区，第一个参数是目标，意思是生成的buffer是干嘛用的，这里是当数组；第二个参数传入buffer id
//     //第一个参数同样是目标；第二个，指定缓冲区的新数据存储的字节大小；第三个数实际属性；第四个，绘制方式，静态，动态等，静态修改一次，每帧不会变，
//     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, position, GL_STATIC_DRAW);
  
//     glEnableVertexAttribArray(0); //启用
//     //参数分别为：缓冲区中实际属性的索引对type的计数；归一化（比如颜色0~255归一化成0~1的浮点数）；每个顶点之间的字节数，指向实际属性的指针
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,sizeof(float)*2, 0);


//     //索引缓冲区
//     unsigned int ibo; // 标识缓冲区的id，供后期访问用
//     glGenBuffers(1, &ibo); //生成一个缓冲区
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); //绑定缓冲区，第一个参数是目标，意思是生成的buffer是干嘛用的，这里是当数组；第二个参数传入buffer id
//     //第一个参数同样是目标；第二个，指定缓冲区的新数据存储的字节大小；第三个数实际属性；第四个，绘制方式，静态，动态等，静态修改一次，每帧不会变，
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * 3 * 2, indices, GL_STATIC_DRAW);


//     //读取shader program的字符串
//     ShaderProgramSource source = ParseShader("/Users/wangxiao/code/OpenGL/res/shaders/Basic.shaders");
//     //创建shader
//     unsigned int shader = CreateShader(source.VertexShader, source.FragmentShader);

//     glUseProgram(shader);
//     //使用同一变量设定color
//     int location = glGetUniformLocation(shader, "u_Color");
//     glUniform4f(location, 0.1f, 0.3f, 0.8f, 1.0f);

//     //设定一定的间隔，得到颜色的变化
//     float r = 0.0f;
//     float increment = 0.05f;
//     //test
//     /* Loop until the user closes the window */
//     while (!glfwWindowShouldClose(window))
//     {
//         /* Render here */
//         glClear(GL_COLOR_BUFFER_BIT);
// >>>>>>> main

        //读取shader program的字符串
        Shader shader("/Users/wangxiao/code/OpenGL/res/shaders/Basic.shaders");
        shader.Bind();

        //使用同一变量设定color
        shader.SetUniform4f("u_Color",0.1f, 0.3f, 0.8f, 1.0f);
   
        shader.Unbind();


        Renderer render;
        //设定一定的间隔，得到颜色的变化
        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            render.Clear();//清屏

            // glDrawArrays(GL_TRIANGLES, 0, 6); //没有index缓冲区绘制的一种方式,第一个参数表示绘制什么；第二个参数从0开始；第三个参数，渲染的索引数。
            {
            if (r > 1.0f) increment = -0.05f;
            if (r < 0.0f) increment = 0.05f;
            r += increment;
            shader.Bind();
            shader.SetUniform4f("u_Color", 1.0f, 0.3f, r, 1.0f);
            }
            render.Draw(va, ib, shader);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Pol l for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}

void test2()
{
    
}

//不自己写一个shader，会有一个默认的shader被提供
//顶点(vertex)着色器和片段(fragment)着色器(也叫像素着色器)
//着色器就是为了告诉位置在窗口的哪一个地方 
