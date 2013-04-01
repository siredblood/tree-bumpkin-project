#ifndef EDITOR_TICKABLE_HPP
#define EDITOR_TICKABLE_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"


class EditorTickable: public ReferenceCount
{
public:
	virtual ~EditorTickable() {};

	virtual void tick() = 0;
};


typedef SmartPointer<EditorTickable> EditorTickablePtr;


#endif // EDITOR_TICKABLE_HPP
