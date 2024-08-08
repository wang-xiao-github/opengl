#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec3 FargPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 mormalMat;

void main()
{ 
    FargPos = vec3(view * model * vec4(aPos, 1.0));
    Normal = mormalMat * aNormal;

    gl_Position =  projection * vec4(FargPos, 1.0);
    // LightPos = vec3(view * vec4(lightPos, 1.0));
    TexCoords = aTexCoords;


}