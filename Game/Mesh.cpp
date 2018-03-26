#include <GL\glew.h>
#include <vector>
#include "Mesh.h"
#include <iostream>
Vertex::Vertex(glm::vec3 pos, glm::vec4 col, glm::vec2 tex)
{
	this->pos = pos;
	this->col = col;
	this->tex = tex;
}

Mesh::Mesh(const Vertex *v, unsigned int nbVer, const unsigned int *ind, unsigned int nbInd)
{
	this -> nbVer = nbVer;
	this ->nbInd = nbInd;
	VBO = new unsigned int[1];
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, nbVer * sizeof(v[0]), v, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(v[0]), (void*)24);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(v[0]), (void*)36);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(v[0]), (void*)8);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * nbInd, ind, GL_STATIC_DRAW);
}


Mesh::~Mesh()
{
	delete[] VBO;
}

void Mesh::actualize()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Mesh::draw()
{

	glDrawElements(GL_TRIANGLES, nbInd, GL_UNSIGNED_INT, 0);
}

void Mesh::convexPoints(const Vertex * v)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int left;
	float l = 1;
	bool convex;
	for (int i = 1; i < nbVer; ++i)
		if (v->pos.x < l)
		{
			left = i;
			l = v->pos.x;
		}
	if (left == 1)
		convex = cross(v[left].pos - v[nbVer - 1].pos, v[2].pos - v[left].pos).z > 0? 1 : -1;
	else
		if (left == nbVer -1)
			convex = cross(v[left].pos - v[nbVer - 2].pos, v[1].pos - v[left].pos).z > 0 ? 1 : -1;
		else
			convex = cross(v[left].pos - v[left - 1].pos, v[left + 1].pos - v[left].pos).z > 0 ? 1 : -1;
	for (int i = 1; i < nbVer - 2; ++i)
	{
		float s = glm::cross(v[i + 1].pos - v[i].pos, v[i + 2].pos - v[i + 1].pos).z;
		if (s / abs(s) == convex)
			glPointSize(6);
		else
			glPointSize(2);
		glDrawArrays(GL_POINTS, i + 1, 1);
	}

	l = glm::cross(v[nbVer - 1].pos - v[nbVer - 2].pos, v[1].pos - v[nbVer -1].pos).z;
	if (l / abs(l) == convex)
		glPointSize(6);
	else
		glPointSize(2);
	glDrawArrays(GL_POINTS, nbVer - 1, 1);

	l = glm::cross(v[1].pos - v[nbVer-1].pos, v[2].pos - v[1].pos).z;
	if (l / abs(l) == convex)
		glPointSize(6);
	else
		glPointSize(2);
	glDrawArrays(GL_POINTS, 1, 1);
}

bool Mesh::inTriangle(glm::vec3 a, glm::mat3 t)
{

	glm::mat3 a1(glm::vec3(a.x, t[0][0], t[1][0]), glm::vec3(a.y, t[0][1], t[1][1]), glm::vec3(1, 1, 1));
	glm::mat3 a2(glm::vec3(a.x, t[0][0], t[2][0]), glm::vec3(a.y, t[0][1], t[2][1]), glm::vec3(1, 1, 1));
	glm::mat3 a3(glm::vec3(a.x, t[1][0], t[2][0]), glm::vec3(a.y, t[1][1], t[2][1]), glm::vec3(1, 1, 1));
	glm::mat3 a4(glm::vec3(t[0][0], t[1][0], t[2][0]), glm::vec3(t[0][1], t[1][1], t[2][1]), glm::vec3(1, 1, 1));
	if (abs(glm::determinant(a4)) == (abs(glm::determinant(a1)) + abs(glm::determinant(a2)) + abs(glm::determinant(a3))))
		return true;
	return false;
}

void Mesh::drawPolygon(std::vector<Vertex> v)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int left, i;
	float l = 1;
	bool convex;
	std::vector<int> ind;
	std::vector<int> pos;

	for (i = 0; i < v.size(); ++i)
		pos.push_back(i);

	for (i = 0; i < v.size(); ++i)
		if (v[i].pos.x < l)
		{
			left = i;
			l = v[i].pos.x;
		}
	convex = cross(v[left].pos - v[(v.size() - 1 + left) % v.size()].pos, v[(1 + left) % v.size()].pos - v[left].pos).z > 0 ? 1 : -1;

	while (v.size() > 4)
	{
		

		for (i = 0; i < v.size(); ++i)
		{
			float s = glm::cross(v[(1 + i) % v.size()].pos - v[i].pos, v[(2 + i) % v.size()].pos - v[(1 + i) % v.size()].pos).z;
			if (s / abs(s) == convex)
			{
				glm::mat3 M(v[i].pos, v[(1 + i) % v.size()].pos, v[(2 + i) % v.size()].pos);
				int j;
				for (j = 0; j < v.size(); ++j)
					if (j != i && j != (1 + i) % v.size() && j != (2 + i) % v.size())
						if (inTriangle(v[j].pos, M))
							break;
				if (j == v.size())
				{
					std::cout << '\n' <<v.size();
					ind.push_back(pos[i]);
					ind.push_back(pos[(1 + i) % v.size()]);
					ind.push_back(pos[(2 + i) % v.size()]);
					v.erase(v.begin() + (1 + i) % v.size());
					pos.erase(pos.begin() + (1 + i) % pos.size());
					break;
				}
			}
		}
	}
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * ind.size(), &ind[0], GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, ind.size(), GL_UNSIGNED_INT, 0);

}

void Mesh::bind()
{
	glBindVertexArray(VAO);
}
