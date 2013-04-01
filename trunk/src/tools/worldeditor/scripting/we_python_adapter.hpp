#ifndef WE_PYTHON_ADAPTER_HPP
#define WE_PYTHON_ADAPTER_HPP

#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"

#include "common/python_adapter.hpp"

class WEPythonAdapter : public PythonAdapter
{
public:
	WEPythonAdapter();
	~WEPythonAdapter();

	void onPageControlTabSelect( const std::string& fnPrefix, const std::string& theTabName );

	void onBrowserObjectItemSelect( const std::string& tabName, 
							const std::string& itemName, bool dblClick );
	void onBrowserObjectItemAdd();

	void onBrowserTextureItemSelect( const std::string& itemName );
	
	void setTerrainPaintMode(int mode);

    void setTerrainPaintBrush( TerrainPaintBrushPtr paintBrush );

	void onLimitSliderAdjust( const std::string& name, float pos, float min, float max );
	void limitSliderUpdate( LimitSlider* control, const std::string& controlName );

	void selectFilterChange( const std::string& value );
	void selectFilterUpdate( CComboBox* comboList );

	void coordFilterChange( const std::string& value );
	void coordFilterUpdate( CComboBox* comboList );

	void projectLock(const std::string& commitMessage);
	void commitChanges(const std::string& commitMessage, bool keepLocks);
	void discardChanges(const std::string& commitMessage, bool keepLocks);
	void updateSpace();
	void calculateMap();
	void exportMap();

	bool canSavePrefab();
	void saveSelectionPrefab( std::string fileName );

private:
	void fillFilterKeys( CComboBox* comboList );
	void fillCoordFilterKeys( CComboBox* comboList );
};


#endif // WE_PYTHON_ADAPTER_HPP
