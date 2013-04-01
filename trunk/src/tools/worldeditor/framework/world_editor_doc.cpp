#include "pch.hpp"
#include "worldeditor/framework/world_editor_doc.hpp"
#include "worldeditor/framework/world_editor_app.hpp"


namespace
{
	WorldEditorDoc	*s_instance = NULL;
}


IMPLEMENT_DYNCREATE(WorldEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(WorldEditorDoc, CDocument)
END_MESSAGE_MAP()



WorldEditorDoc::WorldEditorDoc()
{
}


/*static*/ WorldEditorDoc& WorldEditorDoc::instance()
{
	return *s_instance;
}


WorldEditorDoc::~WorldEditorDoc()
{
	s_instance = NULL;
}


BOOL WorldEditorDoc::OnNewDocument()
{
	ASSERT(!s_instance);
	s_instance = this;

	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


BOOL WorldEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	ASSERT(!s_instance);
	s_instance = this;
	return TRUE;
}


void WorldEditorDoc::OnCloseDocument()
{
	CDocument::OnCloseDocument();
}
