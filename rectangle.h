#pragma once
#include "common.h"
#include <GLFW/glfw3.h>
#include "global.h"
namespace Rectangle{
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    
    void config(){
        GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
        };
        GLuint indices[] = {  // Note that we start from 0!
            0, 1, 3, // First Triangle
            1, 2, 3  // Second Triangle
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // TexCoord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0); // Unbind VAO
    }

    void setUniforms(ShaderProgram * p){
        glm::mat4 model(1.0f);
        glm::mat4 trans(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);

        trans = glm::scale(trans, glm::vec3(5.0));
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
        view = glm::lookAt(cameraPos, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
        projection = glm::perspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 100.0f);
		p->SetUniform("model", model);
		p->SetUniform("trans", trans);
		p->SetUniform("view", view);
		p->SetUniform("projection", projection);
		p->SetUniform("lightPos", lightPos);
    }

    void del(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1,      &VBO);
        glDeleteBuffers(1,      &EBO);
    }

}


