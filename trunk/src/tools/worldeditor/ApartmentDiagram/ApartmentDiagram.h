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
	// ����guid
	std::string getGuid();
	void setGuid(const std::string &guid);
	// ��ȡ��ǰ����ͼƬ����
	std::string getCurrentDiagram();
	// ��ȡ��ǰ����ͼƬ����
	std::list<std::string> getDiagrams();
	// ���õ�ǰͼƬ
	void setCurrentDiagram(const std::string &diagram);

	bool next();
	bool prev();
	bool first();
	bool last();

	// �п�
	bool empty();

	// ���ͼƬ
	void push(const std::string &file);
	void push(const std::vector<std::string> &vFile);
	// ɾ��ͼƬ
	void remove(const std::string &file);

private:
	std::string m_strGuid;
	std::list<std::string> m_diagram;
	std::list<std::string>::iterator m_iterator;
};