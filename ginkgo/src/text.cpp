#define EXPORT
#include <macros.h>
#include <text.h>
#include <locale.h>  

using namespace std;
using namespace ginkgo;

TTFCharacter::TTFCharacter(wchar_t charcode, int fontSize, const char* font)
{

}

TTFCharacter::~TTFCharacter()
{
	if (id)
	{
		glDeleteTextures(1, &id);
	}
}

void TTFCharacter::loadFont(const char* filePath)
{

}

void TTFCharacter::releaseFont(const char* filePath)
{

}

string Text::ws2s(const wstring& ws)
{
	string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";  

	setlocale(LC_ALL, "chs");

	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	size_t retSize;
	wcstombs_s(&retSize, _Dest, _Dsize, _Source, _Dsize);
	string result = _Dest;
	delete[]_Dest;

	setlocale(LC_ALL, curLocale.c_str());

	return result;
}

wstring Text::s2ws(const string& s)
{
	setlocale(LC_ALL, "chs");

	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	size_t retSize;
	mbstowcs_s(&retSize, _Dest, _Dsize, _Source, _Dsize);
	wstring result = _Dest;
	delete[]_Dest;

	setlocale(LC_ALL, "C");

	return result;
}

Text::Text(Node* parent) :Node(parent)
{

}

void Text::setText(std::string text, TextConfig config)
{

}

string Text::getText()
{
	return text;
}