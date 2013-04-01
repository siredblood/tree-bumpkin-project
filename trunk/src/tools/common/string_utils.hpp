/**
 *	StringUtils: String utility methods.
 */

#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP
#include "math/matrix.hpp"

class StringUtils
{
public:
	static std::string vectorToString( const std::vector<std::string>& vec, char separator = ';' );
	static void vectorFromString( const std::string str, std::vector<std::string>& vec, char* separators = ",;" );
	static bool matchExtension( const std::string& fname, const std::vector<std::string>& extensions );
	static bool matchSpecCaseSensitive(const char* fname, const char* spec);
	static bool matchSpec( const std::string& fname, const std::vector<std::string>& specs );
	static bool findInVector( const std::string& str, const std::vector<std::string>& vec );
	static void filterSpecVector( std::vector<std::string>& vec, const std::vector<std::string>& exclude );
	static void toLowerCase( std::string& str );
	static void toUpperCase( std::string& str );
	static void toMixedCase( std::string& str );
	static const std::string lowerCase( const std::string& str );
	static const std::string upperCase( const std::string& str );
	static void replace( std::string& str, char ch, char rep );
	static void replace( std::string& str, const std::string& from, const std::string& to );
    enum IncrementStyle { IS_EXPLORER, IS_END };
    static void increment( std::string& str, IncrementStyle incrementStyle );
    static bool copyToClipboard( const std::string & str );
    static bool canCopyFromClipboard();
    static bool copyFromClipboard( std::string & str );
    static bool makeValidFilename( std::string & str, char replaceChar = '_', bool allowSpaces = true );
	static char * retrieveCmdToken( char * & cmd );
	
	//[7/27/2011] ¾ØÕó×ª»»³É×Ö·û´®
	static std::string matrixToString( const Matrix& transform, char separator = ';' );

	//[7/27/2011] ×Ö·û´®×ª»»³É¾ØÕó
	static void matrixFromString( const std::string& str, Matrix& transform, char* separator = ";" );
};

#endif // STRING_UTILS_HPP
