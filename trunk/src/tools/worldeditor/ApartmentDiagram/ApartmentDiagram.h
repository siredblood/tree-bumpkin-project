#pragma 

#include <list>
#include <string>
#include <vector>

class CApartmentDiagram
{
public:
	CApartmentDiagram();
	~CApartmentDiagram();

public:
	// 户型guid
	std::string getGuid();
	void setGuid(const std::string &guid);
	// 获取当前户型图片名称
	std::string getCurrentDiagram();
	// 获取当前户型图片集合
	std::list<std::string> getDiagrams();
	// 设置当前图片
	void setCurrentDiagram(const std::string &diagram);

	bool next();
	bool prev();
	bool first();
	bool last();

	// 判空
	bool empty();

	// 添加图片
	void push(const std::string &file);
	void push(const std::vector<std::string> &vFile);
	// 删除图片
	void remove(const std::string &file);

private:
	std::string m_strGuid;
	std::list<std::string> m_diagram;
	std::list<std::string>::iterator m_iterator;
};