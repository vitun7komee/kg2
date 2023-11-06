#pragma once

#include <string>
#include <vector>
#include "Vector2D.h"

class Loader
{
public:
	Loader(const std::string& path);
	~Loader();
	void Read2DModel();
	std::vector<Vector2D> vertices() const;
	std::vector<int> indices() const;
	void printVertices() const;
	void printIndices() const;

private:
	bool isLoad();

	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;

	std::string m_path;
};
