//internal includes
#include "common.h"
#include "ShaderProgram.h"
#include "global.h"
#include "init.h"
#include "programs.h"

//External dependencies
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <random>
#include "textures.h"
#include "model.h"
#include "sphere.h"
#include "triangle.h"
#include "rectangle.h"

int main(int argc, char** argv)
{
	if (Init::init()) return -1;
	
	Programs programs;
	programs.add_program("vertex.v", "sphere.f", "sphere"); GL_CHECK_ERRORS;
	programs.add_program("vertex.v", "rectangle.f", "rectangle"); GL_CHECK_ERRORS;
	programs.add_program("vertex.v", "triangle.f", "triangle"); GL_CHECK_ERRORS;
	programs.add_program("vertex.v", "triangle2.f", "triangle2"); GL_CHECK_ERRORS;
	programs.add_program("vertex.v", "triangle3.f", "triangle3"); GL_CHECK_ERRORS;
	programs.add_program("vertex.v", "rectangle.f", "rectangle"); GL_CHECK_ERRORS;
	programs.add_program("vertex.v", "box.f", "box"); GL_CHECK_ERRORS;
	programs.add_program("bg.v", "bg.f", "bg"); GL_CHECK_ERRORS;
    glfwSwapInterval(1); // force 60 frames per second
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); GL_CHECK_ERRORS;
	Textures textures;
	textures.loadTexture("grass.png"); GL_CHECK_ERRORS;
	textures.loadTexture("dd.jpg"); GL_CHECK_ERRORS;
	vector<Model> models;
	models.push_back(Model("../mesh/globe-sphere.obj"));
	models.push_back(Model("../mesh/box.obj"));
	Triangle::config();
	Rectangle::config();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glViewport(0, 0, WIDTH, HEIGHT);
		clear();

		programs["sphere"]->StartUseShader();
		setUniforms(programs["sphere"]);
		Sphere::setUniforms(programs["sphere"]);
		glBindTexture(GL_TEXTURE_2D, textures["grass.png"]);
		models[0].Draw(*(programs["shpere"]));

		
		programs["box"]->StartUseShader();
		setUniforms(programs["box"]);

		glm::mat4 model(1.0f);
		glm::mat4 trans(1.0f);		
		
		trans = glm::scale(trans, glm::vec3(0.08));
		model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
		model = glm::rotate(model, 90.0f, glm::vec3(0.0, 1.0, 0.0));
		model = glm::rotate(model, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 0.1f, 1.0f));
		programs["box"]->SetUniform("model", model);
		programs["box"]->SetUniform("trans", trans);
		models[1].Draw(*(programs["box"]));

		programs["triangle"]->StartUseShader();
		setUniforms(programs["triangle"]);
		for (int i = 0; i < 4; i++){
			model = glm::mat4(1.0f);
			trans = glm::mat4(1.0f);
			model = glm::translate(model, pos[i]);
			model = glm::rotate(model, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			programs["triangle"]->SetUniform("model", model);
			programs["triangle"]->SetUniform("trans", trans);	
			glBindVertexArray(Triangle::VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		programs["triangle2"]->StartUseShader();
		setUniforms(programs["triangle2"]);
		model = glm::mat4(1.0f);
		trans = glm::mat4(1.0f);
		model = glm::translate(model, pos[5]);
		model = glm::translate(model, glm::vec3(3.5 * sinf(glfwGetTime()), 1.0, 3.5 * cosf(glfwGetTime())));
		model = glm::rotate(model, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		programs["triangle2"]->SetUniform("model", model);
		programs["triangle2"]->SetUniform("trans", trans);	
		glBindVertexArray(Triangle::VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		programs["triangle3"]->StartUseShader();
		setUniforms(programs["triangle3"]);
		model = glm::mat4(1.0f);
		trans = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.5 * sinf(glfwGetTime()), 0.0, 3.5 * cosf(glfwGetTime())));
		model = glm::rotate(model, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		programs["triangle3"]->SetUniform("model", model);
		programs["triangle3"]->SetUniform("trans", trans);	
		glBindVertexArray(Triangle::VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		programs["rectangle"]->StartUseShader();
		setUniforms(programs["rectangle"]);
		model = glm::mat4(1.0f);
		trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3(1.0));
		model = glm::translate(model, glm::vec3(-2.0, -1.0, 1.0));
		model = glm::rotate(model, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		programs["rectangle"]->SetUniform("model", model);
		programs["rectangle"]->SetUniform("trans", trans);
		glBindVertexArray(Rectangle::VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       GL_CHECK_ERRORS;  //

		programs["bg"]->StartUseShader();
		model = glm::mat4(1.0f);
		trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3(20.0));
		model = glm::translate(model, glm::vec3(0.0, 0.0, -10.0));
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);
		view = glm::lookAt(cameraPos, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
		projection = glm::perspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 100.0f);
		programs["bg"]->SetUniform("view", view);
		programs["bg"]->SetUniform("projection", projection);
		programs["bg"]->SetUniform("model", model);
		programs["bg"]->SetUniform("trans", trans);
		glBindTexture(GL_TEXTURE_2D, textures["dd.jpg"]);
		glBindVertexArray(Rectangle::VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);       GL_CHECK_ERRORS;  //
		
		glBindVertexArray(0);
		glfwSwapBuffers(window); 
	}
	Triangle::del();
	Rectangle::del();
	glfwTerminate();
	return 0;
}
