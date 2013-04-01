#ifndef CONVERT_SPACE_DLG_HPP
#define CONVERT_SPACE_DLG_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/resource.h"
#include "controls/auto_tooltip.hpp"
#include "controls/image_control.hpp"
#include "controls/edit_numeric.hpp"
#include <afxwin.h>


class ConvertSpaceDlg : public CDialog
{
	DECLARE_DYNAMIC(ConvertSpaceDlg)

	DECLARE_AUTO_TOOLTIP( ConvertSpaceDlg, CDialog )

public:
	ConvertSpaceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ConvertSpaceDlg();

// Dialog Data
	enum { IDD = IDD_CONVERTSPACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox				heightMapSize_;
	CComboBox				normalMapSize_;
	controls::EditNumeric	holeMapSize_;
	CComboBox				shadowMapSize_;
	controls::EditNumeric	blendMapSize_;
	CStatic iconWarning_;
	CButton buttonCancel_;
	CButton buttonCreate_;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};


#endif // CONVERT_SPACE_DLG_HPP
