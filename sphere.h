#pragma once
#include "common.h"
#include <GLFW/glfw3.h>
#include "global.h"
namespace Sphere{
    void setUniforms(ShaderProgram *p){
        glm::mat4 model(1.0f);
        glm::mat4 trans(1.0f);
        trans = glm::scale(trans, glm::vec3(1.0));
        model = glm::translate(model, glm::vec3(3.0f, 1.0, -1.0));
        model = glm::rotate(model, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 1.0f, 1.0f));
		p->SetUniform("model", model);
		p->SetUniform("trans", trans);
    }
}