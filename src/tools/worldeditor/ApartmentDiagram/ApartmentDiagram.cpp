#include "pch.hpp"
#include "ApartmentDiagram.h"


CApartmentDiagram::CApartmentDiagram()
{

}

CApartmentDiagram::~CApartmentDiagram()
{

}

std::string CApartmentDiagram::getGuid()
{
	return m_strGuid;
}

void CApartmentDiagram::setGuid(const std::string &guid)
{
	m_strGuid = guid;
}

std::string CApartmentDiagram::getCurrentDiagram()
{
	if(empty()) return "";
	return *m_iterator;
}

void CApartmentDiagram::setCurrentDiagram(const std::string &diagram)
{
	if(empty()||diagram.empty()) return ;

	for(std::list<std::string>::iterator itr=m_diagram.begin(); itr!=m_diagram.end(); itr++){
		if(*itr==diagram){
			m_iterator = itr;
			break;
		}
	}
}

std::list<std::string> CApartmentDiagram::getDiagrams()
{
	return m_diagram;
}

bool CApartmentDiagram::empty()
{
	return m_diagram.empty();
}

bool CApartmentDiagram::first()
{
	if(empty()) return false;
	m_iterator = m_diagram.begin();
	return true;
}

bool CApartmentDiagram::next()
{
	if(empty()) return false;
	if(m_iterator!=--m_diagram.end()){
		++m_iterator;
		return true;
	}else{
		return false;
	}
}

bool CApartmentDiagram::prev()
{
	if(empty()) return false;
	if(m_iterator!=m_diagram.begin()){
		--m_iterator;
		return true;
	}else{
		return false;
	}
}

bool CApartmentDiagram::last()
{
	if(empty()) return false;
	m_iterator = --m_diagram.end();
	return true;
}

void CApartmentDiagram::push(const std::string &file)
{
	m_diagram.push_back(file);
	m_iterator = m_diagram.begin();
}

void CApartmentDiagram::push(const std::vector<std::string> &vFile)
{
	for(size_t i=0; i<vFile.size(); i++)
		m_diagram.push_back(vFile[i]);
	m_iterator = m_diagram.begin();
}

void CApartmentDiagram::remove(const std::string &file)
{
	m_diagram.remove(file);
	m_iterator = m_diagram.begin();
}