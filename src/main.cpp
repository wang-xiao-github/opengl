#include <GL/glew.h>  //glew头文件包含必须要在其他拓展之前
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

//使用宏定义错误
#define ASSERT(x) if (!(x)) __builtin_trap();  //__builtin_trap是mac平台特有的
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

//清楚之前的错误
static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}
//检查错误
static bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error =  glGetError())
    {
        std::cout << "[OpenGL Error] ( " << error << ")" << function << 
        " " << file << ":" << line << std::endl;
        return false;
    };
    return true;
}

struct ShaderProgramSource 
{
    std::string VertexShader;
    std::string FragmentShader;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    enum class ShaderType
    {
        NONE = -1 , VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    // stream.close();
    return { ss[0].str(), ss[1].str() };
}


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); //创建一个shader，返回id
    const char* src = source.c_str(); //返回源码的首地址

    glShaderSource(id, 1, &src, nullptr); //shader的id，有几个源码，指向实际的指针
    glCompileShader(id); //传入着色器id，编译

    //TODO: Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Fileed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message <<std::endl;

        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //指定需要附加的程序 
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    //链接程序
    glLinkProgram(program);

    glValidateProgram(program);

    //删除shader其他的中间等文件
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


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
    window = glfwCreateWindow(640, 480, "PROJECT", NULL, NULL);
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

    //顶点数组
    float position[12] = 
    {
        0.5f,  0.5f,  //0
        -0.5f, 0.5f,  //1
        -0.5f, -0.5f, //2
        0.5f,  -0.5f  //3
    }; 
    //索引缓冲数组
    unsigned int indices[]=
    {
        0, 1, 2,
        2, 3, 0
    };
    //创建顶点数组对象 (VAO) 关于使用同一个顶点数组还是每个顶点缓冲都配一个顶点数组，性能情况要具体分析
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    unsigned int buffer; // 标识缓冲区的id，供后期访问用
    glGenBuffers(1, &buffer); //生成一个缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, buffer); //绑定缓冲区，第一个参数是目标，意思是生成的buffer是干嘛用的，这里是当数组；第二个参数传入buffer id
    //第一个参数同样是目标；第二个，指定缓冲区的新数据存储的字节大小；第三个数实际属性；第四个，绘制方式，静态，动态等，静态修改一次，每帧不会变，
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, position, GL_STATIC_DRAW);
  
    glEnableVertexAttribArray(0); //启用
    //参数分别为：缓冲区中实际属性的索引对type的计数；归一化（比如颜色0~255归一化成0~1的浮点数）；每个顶点之间的字节数，指向实际属性的指针
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,sizeof(float)*2, 0);


    //索引缓冲区
    unsigned int ibo; // 标识缓冲区的id，供后期访问用
    glGenBuffers(1, &ibo); //生成一个缓冲区
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); //绑定缓冲区，第一个参数是目标，意思是生成的buffer是干嘛用的，这里是当数组；第二个参数传入buffer id
    //第一个参数同样是目标；第二个，指定缓冲区的新数据存储的字节大小；第三个数实际属性；第四个，绘制方式，静态，动态等，静态修改一次，每帧不会变，
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * 3 * 2, indices, GL_STATIC_DRAW);


    //读取shader program的字符串
    ShaderProgramSource source = ParseShader("/Users/wangxiao/code/OpenGL/res/shaders/Basic.shaders");
    //创建shader
    unsigned int shader = CreateShader(source.VertexShader, source.FragmentShader);

    glUseProgram(shader);
    //使用同一变量设定color
    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, 0.1f, 0.3f, 0.8f, 1.0f);

    //设定一定的间隔，得到颜色的变化
    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // glDrawArrays(GL_TRIANGLES, 0, 6); //没有index缓冲区绘制的一种方式,第一个参数表示绘制什么；第二个参数从0开始；第三个参数，渲染的索引数。
        {
        if (r > 1.0f) increment = -0.05f;
        if (r < 0.0f) increment = 0.05f;
        r += increment;
        glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
        }
        // 采用索引缓冲区
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
//不自己写一个shader，会有一个默认的shader被提供
//顶点(vertex)着色器和片段(fragment)着色器(也叫像素着色器)
//着色器就是为了告诉位置在窗口的哪一个地方 