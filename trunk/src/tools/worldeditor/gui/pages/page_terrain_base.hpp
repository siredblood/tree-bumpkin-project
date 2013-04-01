#ifndef PAGE_TERRAIN_BASE_HPP
#define PAGE_TERRAIN_BASE_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "controls/auto_tooltip.hpp"


class PageTerrainBase : public CDialog
{
public:
	PageTerrainBase(UINT nIDTemplate);

protected:
	BOOL OnInitDialog();

	DECLARE_AUTO_TOOLTIP(PageTerrainBase, CDialog);
	DECLARE_MESSAGE_MAP()
};


#endif // PAGE_TERRAIN_BASE_HPP
