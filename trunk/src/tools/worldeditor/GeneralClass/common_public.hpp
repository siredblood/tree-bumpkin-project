#ifndef COMMON_PUBLIC
#define COMMON_PUBLIC

class CommonPublic
{
public:
	CommonPublic();

	static CommonPublic & instance();

	//change �Ƿ����ָ�����ַ���
	//mainStr ��Ҫ�������ַ��� str �������ַ�
	bool containtString( const std::string &mainStr, const std::string &str );
};

#endif