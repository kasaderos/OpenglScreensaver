#pragma once
#include <vector>
#include "common.h"
#include <GLFW/glfw3.h>
#include "SOIL.h"

class Textures{
    std::vector<GLuint*> textures;
    std::vector<std::string> names;
    std::vector<std::pair<int*, int*>> pars;
public:
    Textures(){}
    GLuint operator[](const char * path){
        int i = 0;
        for (; i < names.size(); i++){
            if (path == names[i])
                break;
        }
        return *(textures[i]);
    }
    void loadTexture(const char * path){
        GLuint *texture = new GLuint;
        names.push_back(path);
        textures.push_back(texture);
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
        // Set our texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Load, create texture and generate mipmaps
        int *width = new int;
        int *height = new int;
        pars.push_back(std::pair<int*, int*>(width, height));
        unsigned char* image = SOIL_load_image(path, width, height, 0, SOIL_LOAD_RGB);
        if (!image){
            std::cerr << "error image load" << std::endl;
            exit(1);
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *width, *height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
    }

    ~Textures(){
        for (int i = 0; i < textures.size(); i++){
            delete textures[i];
        }
        for (int i = 0; i < pars.size(); i++){
            delete pars[i].first;
            delete pars[i].second;
        }
    }
};