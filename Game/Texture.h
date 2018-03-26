#pragma once
class Texture
{
	unsigned int texture;
public:
	Texture(const char *);
	void bind();
	virtual ~Texture();
};

