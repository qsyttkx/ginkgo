#include <iostream>
#include <Windows.h>
#include "game.h"
#include <stdio.h>

using namespace std;

void printChar(wchar_t c);

int main()
{
	GameConfig c = readConfiguration("res/config.json");
	
	std::wstring str = Text::s2ws("你好世界");

	for (auto iter = str.begin(); iter != str.end(); iter++)
	{
		printChar(*iter);
	}

	TestGame* test = new TestGame(c);
	test->run();
	delete(test);
	return 0;
}


#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
char ttf_buffer[1 << 25];

void printChar(wchar_t c)
{
	stbtt_fontinfo font;
	unsigned char *bitmap;
	int w, h, i, j, s = 20;

	FILE* fp;
	if (fopen_s(&fp, "C:/Windows/Fonts/simhei.ttf", "rb"))
	{
		cout << "找不到字体文件" << endl;
		return;
	};
	
	fread(ttf_buffer, 1, 1 << 25, fp);
	//fread(ttf_buffer, 1, 1 << 25, fopen("res/zkklt2016.ttf", "rb"));
	//fread(ttf_buffer, 1, 1 << 25, fopen("res/方正书宋简体.ttf", "rb"));

	stbtt_InitFont(&font, (unsigned char*)ttf_buffer, stbtt_GetFontOffsetForIndex((unsigned char*)ttf_buffer, 0));
	bitmap = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, (float)s), c, &w, &h, 0, 0);

	for (j = 0; j < h; ++j) {
		for (i = 0; i < w; ++i)
		{
			putchar(" .:ioVM@"[bitmap[j*w + i] >> 5]);
			putchar(" .:ioVM@"[bitmap[j*w + i] >> 5]);
		}
		putchar('\n');
	}
}