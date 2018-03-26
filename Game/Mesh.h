#pragma once
#include <glm\glm.hpp>


class Vertex
{
public:
	glm::vec4 col;
	glm::vec3 pos;
	glm::vec2 tex;
	Vertex(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec4 col = glm::vec4(1, 1, 1, 1), glm::vec2 tex = glm::vec2(0, 0));
	virtual ~Vertex() {}
};

class Mesh
{
	unsigned int nbVer;
	unsigned int nbInd;
	unsigned int VAO;
	unsigned int* VBO;
	unsigned int EBO;

public:
	Mesh(const Vertex *, unsigned int, const unsigned int *, unsigned int);
	virtual ~Mesh();
	virtual void draw();
	void convexPoints(const Vertex *);
	void bind();
	void drawPolygon(std::vector<Vertex>);
	bool inTriangle(glm::vec3, glm::mat3);
	void actualize();
};

