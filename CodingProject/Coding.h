#pragma once
#include <windows.h>
#include <string>
#include <atlstr.h>
#include <vector>

//		@Liv qq:1319923129

using std::string;
using std::vector;

namespace Coding {
	vector<string> split(const string& str, const string& sep);
	string UnicodeToGBK(const string& str);
	string UrlEncode(const string& str);
	string StringToUTF8(const string& str);
	string UTF8ToUnicode(const char* str);
	string UnicodeToUTF8(const wchar_t* str);
	string WcharToString(const wchar_t* str);
};