#pragma once
#include <vector>
#include "ShaderProgram.h"

class Programs{
    std::vector<ShaderProgram*> programs;
    std::vector<std::string> names;
public:
    Programs(){}
    void add_program(const char * v, const char * f, const char * name){
        std::unordered_map<GLenum, std::string> shaders;
	    shaders[GL_VERTEX_SHADER] = v;
	    shaders[GL_FRAGMENT_SHADER] = f;
        names.push_back(name);
        programs.push_back(new ShaderProgram(shaders));
    }

    ShaderProgram * operator[](const char * name){
        int i = 0;
        for(;i < names.size(); i++){
            if (name == names[i]) break;
        }
        return programs[i];
    }
    ~Programs(){
        for(int i = 0; i < programs.size(); i++){
            delete programs[i];
        }
    }
};