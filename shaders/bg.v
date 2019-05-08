#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 trans;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 FragPos = vec3(model * trans * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}

