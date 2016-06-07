#include "GAME.h"

void GAME::init(GAME::Others &a,std::vector<WCHAR*> b,HINSTANCE c)
{
	BITMAP bitmap;
	SIZE buf_size;
	WCHAR link[100] = L"";
	HBITMAP buf_s;
	for (auto i : b)
	{
		wcscpy_s(link, i);
		buf_s=(HBITMAP)buf_s = (HBITMAP)LoadImage(c, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(buf_s, sizeof(BITMAP), &bitmap);
		buf_size.cx = bitmap.bmWidth;;
		buf_size.cy = bitmap.bmHeight;
		a._size.push_back(buf_size);
		a._bitMap.push_back(buf_s);
		DeleteObject(buf_s);
		buf_size.cx = 0;
		buf_size.cy = 0;
	}
	a.Speed = BK_UP_SPEED;
	a.pos.x = 0;
	a.pos.y = 0;
	a._back = BK_UP_BACK;
}

void GAME::Paint_Background(GAME::Others &a,HDC &buf,HDC &buf2)
{
	SelectObject(buf2, a._bitMap[0]);
	BitBlt(buf, a.pos.x, a.pos.y, WNDWIDTH * 3, WNDHEIGHT, buf2, 0, 0, SRCCOPY);
	BitBlt(buf, a.pos.x + a._size[0].cx - 1, a.pos.y, WNDWIDTH * 3, WNDHEIGHT, buf2, 0, 0, SRCCOPY);
	BitBlt(buf, a.pos.x + (a._size[0].cx - 1) * 2, a.pos.y, WNDWIDTH * 3, WNDHEIGHT, buf2, 0, 0, SRCCOPY);
	BitBlt(buf, a.pos.x + (a._size[0].cx - 1) * 3, a.pos.y, WNDWIDTH * 3, WNDHEIGHT, buf2, 0, 0, SRCCOPY);

}

void GAME::Paint_Title(GAME::Others & a, HDC & buf, HDC & buf2)
{
	if (a.pos.y > 180)
	{
		return;
	}
	a.pos.y += a.Speed;
	SelectObject(buf, a._bitMap[0]);
	TransparentBlt(buf2, a.pos.x, a.pos.y, a._size[0].cx, a._size[0].cy,
		buf, 0, 0, a._size[0].cx, a._size[0].cy, RGB(254, 254, 254));
}
