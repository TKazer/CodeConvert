#include "Coding.h"

vector<string> Coding::split(const string& str, const string& sep)
{
	vector<string> v;
	string::size_type pos1, pos2;
	pos2 = str.find(sep);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(str.substr(pos1, pos2 - pos1));
		pos1 = pos2 + sep.size();
		pos2 = str.find(sep, pos1);
	}
	if (pos1 != str.length())
		v.push_back(str.substr(pos1));
	return v;
}

string Coding::UnicodeToGBK(const string& str)
{
	vector<string> v_String;
	v_String = split(str, "\\u");
	wchar_t* w_Buffer = new wchar_t[str.length() + 1];
	memset(w_Buffer, 0, (str.length() + 1) * sizeof(wchar_t));
	int j = 0;
	for (vector<string>::iterator it = v_String.begin(); it != v_String.end(); ++it)
	{
		if (it->empty())
			continue;
		unsigned short wcTmp = 0;
		unsigned char cTmp = 0;
		for (size_t k = 0; k < it->length(); ++k)
		{
			cTmp = (unsigned char)(*it)[k];

			if (cTmp <= '9')
				wcTmp |= (cTmp & 0x0f) << (it->length() - k - 1) * 4;
			else if (cTmp >= 'a')
				wcTmp |= (cTmp - 0x57) << (it->length() - k - 1) * 4;
			else
				wcTmp |= (cTmp - 0x37) << (it->length() - k - 1) * 4;
		}
		w_Buffer[j++] = (wchar_t)wcTmp;
	}
	char* c_Buffer = new char[str.length() + 1];
	memset(c_Buffer, 0, (str.length() + 1) * sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, w_Buffer, -1, (char*)c_Buffer, str.length() - 1, NULL, NULL);
	string result(c_Buffer);
	delete[]w_Buffer;
	delete[]c_Buffer;
	return result;
}

string Coding::UrlEncode(const string& str)
{
	string temp = str;
	char hex[] = "0123456789ABCDEF";
	string result;
	for (size_t i = 0; i < temp.size(); ++i)
	{
		unsigned char cc = temp[i];
		if (cc >= 'A' && cc <= 'Z'
			|| cc >= 'a' && cc <= 'z'
			|| cc >= '0' && cc <= '9'
			|| cc == '.'
			|| cc == '_'
			|| cc == '-'
			|| cc == '*')
		{
			if (cc == ' ')
				result += "+";
			else
				result += cc;
		}
		else
		{
			unsigned char c = static_cast<unsigned char>(temp[i]);
			result += '%';
			result += hex[c / 16];
			result += hex[c % 16];
		}
	}
	return result;
}

string Coding::StringToUTF8(const string& str)
{
	int Length = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* w_Buffer = new wchar_t[Length + 1];
	ZeroMemory(w_Buffer, Length * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), w_Buffer, Length);
	int Length_Sc = WideCharToMultiByte(CP_UTF8, 0, w_Buffer, -1, NULL, NULL, NULL, NULL);
	char* c_Buffer = new char[Length_Sc + 1];
	ZeroMemory(c_Buffer, Length_Sc + 1);
	WideCharToMultiByte(CP_UTF8, 0, w_Buffer, Length, c_Buffer, Length_Sc, NULL, NULL);
	c_Buffer[Length_Sc] = '\0';
	string result(c_Buffer);
	delete[] w_Buffer;
	delete[] c_Buffer;
	return result;
}

string Coding::UTF8ToUnicode(const char* str)
{
	USES_CONVERSION;
	int Length = MultiByteToWideChar(CP_UTF8, NULL, str, strlen(str), NULL, 0);
	wchar_t* w_Buffer = new wchar_t[Length + 1];
	MultiByteToWideChar(CP_UTF8, NULL, str, strlen(str), w_Buffer, Length);
	w_Buffer[Length] = '\0';
	CString UnicodeString(w_Buffer);
	delete[] w_Buffer;
	return W2A(UnicodeString.GetBuffer(0));
}

string Coding::UnicodeToUTF8(const wchar_t* str)
{
	int Length = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, 0);
	char* c_Buffer = new char[Length + 1]();
	WideCharToMultiByte(CP_UTF8, 0, str, -1, c_Buffer, Length, NULL, 0);
	c_Buffer[Length] = '\0';
	string result = c_Buffer;
	delete[] c_Buffer;
	return result;
}

string Coding::WcharToString(const wchar_t* str)
{
	int Length = WideCharToMultiByte(CP_OEMCP, 0, str, -1, NULL, 0, NULL, NULL);
	char* c_Buffer = new char[Length + 1]();
	WideCharToMultiByte(CP_OEMCP, 0, str, -1, c_Buffer, Length, NULL, NULL);
	c_Buffer[Length] = '\0';
	string result = c_Buffer;
	delete[] c_Buffer;
	return result;
}