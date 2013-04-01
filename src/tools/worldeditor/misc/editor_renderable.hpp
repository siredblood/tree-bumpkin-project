#ifndef EDITOR_RENDERABLE_HPP
#define EDITOR_RENDERABLE_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"


class EditorRenderable: public ReferenceCount
{
public:
	virtual ~EditorRenderable() {};

	virtual void render() = 0;
};


#endif // EDITOR_RENDERABLE_HPP
