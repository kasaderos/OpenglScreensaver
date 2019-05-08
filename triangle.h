#pragma once
#include "common.h"
#include <GLFW/glfw3.h>

namespace Triangle{
    GLuint VBO;
    GLuint VAO;
    
    void config(){
        float trianglePos[] =
        {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f, +0.5f,
        };
        VBO = 0;
        GLuint vertexLocation = 0; // simple layout, assume have only positions at location = 0

        glGenBuffers(1, &VBO);                                                        GL_CHECK_ERRORS;
        glBindBuffer(GL_ARRAY_BUFFER, VBO);                                           GL_CHECK_ERRORS;
        glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(GLfloat), (GLfloat*)trianglePos, GL_STATIC_DRAW); GL_CHECK_ERRORS;

        glGenVertexArrays(1, &VAO);                                                    GL_CHECK_ERRORS;
        glBindVertexArray(VAO);                                                        GL_CHECK_ERRORS;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);                                           GL_CHECK_ERRORS;
        glEnableVertexAttribArray(vertexLocation);                                                     GL_CHECK_ERRORS;
        glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);                            GL_CHECK_ERRORS;

        glBindVertexArray(0);
    }  
    void del(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1,      &VBO);
    }
}