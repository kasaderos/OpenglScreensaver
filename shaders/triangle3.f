#version 330 core
out vec4 FragColor;

struct Material {
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;    
    float shininess;
}; 

struct Light {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

uniform vec3 viewPos;
uniform vec3 lightPos;
void main()
{
    Material material;
    material.diffuse = vec3(0.2);
    material.specular = vec3(1.0);
    material.ambient = vec3(0.2);
    material.shininess = 100.0f;
    Light light;
    light.ambient = vec3(0.2f, 0.2f, 0.2f);
    light.diffuse = vec3(0.5f);
    light.specular = vec3(1.0f);
    light.constant = 0.1f;
    light.linear = 0.09f;
    light.quadratic = 0.032f;
    light.position = lightPos;
    // ambient
    vec3 color = vec3(0.0, 1.0, 1.0);
    
    vec3 ambient = light.ambient * material.ambient * color; 
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse * color;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular  * spec * material.specular * color;
    
    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation;   
      
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 

