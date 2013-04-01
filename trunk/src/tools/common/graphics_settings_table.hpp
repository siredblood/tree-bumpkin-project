#pragma once
#include "common/editor_views.hpp"


class GeneralEditor;
typedef SmartPointer<GeneralEditor> GeneralEditorPtr;


class GraphicsSettingsTable : public PropertyTable
{
public:
	explicit GraphicsSettingsTable( UINT dlgId );
	virtual ~GraphicsSettingsTable();

	bool needsRestart() const { return needsRestart_; }
	virtual void needsRestart( const std::string& setting );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LRESULT OnUpdateControls(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectPropertyItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangePropertyItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDblClkPropertyItem(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	bool inited_; 
	GeneralEditorPtr editor_;
	bool needsRestart_;
	std::set<std::string> changedSettings_;

	bool init();
	void tagNameToString( std::string& label );
};