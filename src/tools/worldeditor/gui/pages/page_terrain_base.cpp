#include "pch.hpp"
#include "worldeditor/gui/pages/page_terrain_base.hpp"


DECLARE_DEBUG_COMPONENT2("WorldEditor", 2)


BEGIN_MESSAGE_MAP(PageTerrainBase, CDialog)
END_MESSAGE_MAP()


PageTerrainBase::PageTerrainBase(UINT nIDTemplate):
    CDialog(nIDTemplate)
{
}


BOOL PageTerrainBase::OnInitDialog()
{
	BOOL ret = CDialog::OnInitDialog();
	INIT_AUTO_TOOLTIP();
	return ret;
}
