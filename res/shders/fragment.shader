#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;   
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 direction;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outCutOff;
};

#define NR_POINT_LIGHTS 4

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform Material material;


out vec4 FragColor;

in vec3 Normal;
in vec3 FargPos;
in vec2 TexCoords;

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fargPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 fargPos, vec3 viewDir);


void main()
{   
    vec3 norm = normalize(Normal);
    vec3 viewDir  = normalize(-FargPos);

    vec3 lightReult = CalcDirLight(dirLight, norm, viewDir);
    // vec3 lightReult = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i <NR_POINT_LIGHTS; i++)
    {
        lightReult += CalcPointLight(pointLights[i], norm, FargPos, viewDir);
    }
    
    lightReult += CalcSpotLight(spotLight, norm, FargPos, viewDir);
   

    FragColor = vec4((lightReult), 1.0);

}

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewDir)
{
    //环境光
    vec3 ambient = texture(material.diffuse, TexCoords).rgb * light.ambient;
    //漫反射
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = texture(material.diffuse, TexCoords).rgb * light.diffuse * diff;
    //高光
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular, TexCoords).rgb * spec * light.specular;

    return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fargPos, vec3 viewDir)
{
    //环境光
    vec3 ambient = texture(material.diffuse ,TexCoords).rgb * light.ambient;
    //漫反射
    vec3 lightDir = normalize(light.position - fargPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = texture(material.diffuse, TexCoords).rgb * diff * light.diffuse;
    //高光
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular, TexCoords).rgb * spec * light.specular;
    //衰弱
    float distance = length(light.position - fargPos); 
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    

    return (ambient + diffuse + specular) * attenuation;
}
vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 fargPos, vec3 viewDir)
{
   //环境光
    vec3 ambient = texture(material.diffuse ,TexCoords).rgb * light.ambient;
    //漫反射
    vec3 lightDir = normalize(light.position - fargPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = texture(material.diffuse, TexCoords).rgb * diff * light.diffuse;
    //高光
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular, TexCoords).rgb * spec * light.specular;
    //衰弱
    float distance = length(light.position - fargPos); 
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    //切光角
    float theta = dot(-lightDir, light.direction);
    float epsilon = light.cutOff - light.outCutOff;
    float intensity = clamp((theta - light.outCutOff) / epsilon, 0.0, 1.0);

    

    return (ambient + (diffuse + specular) ) * attenuation * intensity;
}


