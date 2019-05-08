#pragma once
#include "common.h"
#include <GLFW/glfw3.h>
#include "SOIL.h"

static GLsizei WIDTH = 640, HEIGHT = 480; //размеры окна
glm::vec3 cameraPos(0.0, 0.0, 4.0);
glm::vec3 lightPos(1.0, 0.0, 1.0);

glm::vec3 pos[]={
    glm::vec3(-2.0, 1.0, 0.0),
    glm::vec3(-2.0, 0.0, -2.0),
    glm::vec3(2.0, -1.0, 0.0),
    glm::vec3(-2.0, 1.0, 1.0),
    glm::vec3(-1.0, -1.0, -3.0),
    glm::vec3(0.0, -2.0, 0.0),
    glm::vec3(-0.5, 1.5, 0.0),
};
void clear(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);               GL_CHECK_ERRORS;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
}

void windowResize(GLFWwindow* window, int width, int height)
{
    WIDTH  = width;
    HEIGHT = height;
}

void setUniforms(ShaderProgram * p){
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    view = glm::lookAt(cameraPos, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
    projection = glm::perspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 100.0f);
    p->SetUniform("view", view);
    p->SetUniform("projection", projection);
    p->SetUniform("viewPos", cameraPos);
    p->SetUniform("lightPos", lightPos);
}



