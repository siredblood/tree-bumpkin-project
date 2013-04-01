#ifndef COMMON_PUBLIC
#define COMMON_PUBLIC

class CommonPublic
{
public:
	CommonPublic();

	static CommonPublic & instance();

	//change 是否包含指定的字符串
	//mainStr 需要搜索的字符串 str 搜索的字符
	bool containtString( const std::string &mainStr, const std::string &str );
};

#endif