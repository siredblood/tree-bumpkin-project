#ifndef NEW_PLACEMENT_DLG_HPP
#define NEW_PLACEMENT_DLG_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/resource.h"
#include <afxwin.h>


class NewPlacementDlg : public CDialog
{
	DECLARE_DYNAMIC(NewPlacementDlg)

public:
// Dialog Data
	enum { IDD = IDD_RANDNEWPRESET };

	NewPlacementDlg(CWnd* pParent = NULL);
	~NewPlacementDlg();

	void existingNames(std::vector<std::string> const &names);

	CString newName_;

protected:
	CEdit newNameCtrl_;
	std::vector<std::string> existingNames_;

	void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();
	void OnOK();

	DECLARE_MESSAGE_MAP()

	bool isValidName(CString const &str) const;
public:
	afx_msg void OnBnClickedOk();
};


#endif // NEW_PLACEMENT_DLG_HPP
