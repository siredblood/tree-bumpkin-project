#ifndef WORLD_EDITOR_PROGRESS_BAR_HPP
#define WORLD_EDITOR_PROGRESS_BAR_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "ashes/gui_attachment.hpp"
#include "ashes/text_gui_component.hpp"
#include "romp/super_model_progress.hpp"
#include "moo/node.hpp"


class WorldEditorProgressBar : public SuperModelProgressDisplay
{
public:
	WorldEditorProgressBar();
	~WorldEditorProgressBar();

	virtual void fini();

	void drawOther(float dTime);
	void escapable( bool escape );
	void setLabel( const std::string& label );

private:
	SmartPointer<Moo::Node>				taskNode_;
	SmartPointer<GuiAttachment>			taskAttachment_;
	SmartPointer<TextGUIComponent>		taskText_;
	SmartPointer<TextGUIComponent>		escapeText_;
	SmartPointer<GUIShader>				textPosition_;
	SmartPointer<PyMatrix>				textTransform_;

	bool escapable_;
	bool inited_;
};


#endif // WORLD_EDITOR_PROGRESS_BAR_HPP
