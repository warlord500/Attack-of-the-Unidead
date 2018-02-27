#pragma once
#include <GL/glew.h>
#include <string>
#include <mat4f.h>

struct Mesh {
	GLuint vao;
	GLuint vbo;
	unsigned int vertexCount;
};

struct Material {

};

struct Model {
	Mesh mesh;
	mat4f transformation;
	Material material;
};

Model loadModel(GLfloat* vertices, int vertexCount, GLint* indices, int indiceCount);
Model loadModel(std::string filepath);
void disposeModel(Model& Model);
void bindModel(Model& Model);
void unbindModel();
