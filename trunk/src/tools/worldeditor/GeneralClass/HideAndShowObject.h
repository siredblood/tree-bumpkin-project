#pragma once

class CHideAndShowObject
{
public:
	CHideAndShowObject(void);
	~CHideAndShowObject(void);
	
	static CHideAndShowObject &Instance();
	
	void HideObject( std::vector<ChunkItemPtr> vSelItems );
	void ShowLastObject();
	void ShowAllHidedObject();	
	
	int GetHidedObjectSize();
	
private:
	static CHideAndShowObject instance;
	
	std::vector<ChunkItemPtr> m_vAllHidedObject;	//被隐藏的对象
};
