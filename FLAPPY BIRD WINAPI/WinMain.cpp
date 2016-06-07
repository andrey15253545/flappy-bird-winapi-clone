#include "Header.h"
#include <vector>
#include "GAME.h"
#include <iostream>
#include <mmsystem.h>
#include <Digitalv.h>
#define BIRD_SPEED 7
#define BIRD_UP 2
#define BIRD_MID 1
#define BIRD_DOWN 0
#define BRONZE_MEDAL_ID 0
#define SILVER_MEDAL_ID 1
#define GOLDEN_MEDAL_ID 2
#define PLATINUM_MEDAL_ID 3
HDC hdc, _hBuffer1, _hBuffer2, _hBuffer3;
HBITMAP cptBitMap1;
HBITMAP background, title, bird[3], mainmenu;
HBITMAP pipe[2], bigNum, medal[4];
HBITMAP floor_r, gameOver;
int cx = 0, cy = 0;
int floorcx, floorcy;
HINSTANCE hInstance;
POINT pt;
SIZE sz, floorsz, pipesz, gameoversz, birdsz, bignumsz, medalsz;
bool CHECK, gamestart, buf;
int SPEED = 2, bird_index = 0, bird_speed = -2, BUFER = 0, _SPEED = 0;
int birdx = 52, birdy = 287;
int k = 0;
int bufer1, bufer2;
const int qwe = 50;
int trumpet[5][2];
bool gameover = false; bool GAME_OVER();
std::size_t score = 10, best_score = 0, LIFES = 5, Now_Music = 0;
int bignumx = 130 + WNDWIDTH / 4 + 50, bignumy = 80;
std::vector<WIN32_FIND_DATA>File;
MCI_OPEN_PARMS op, gp;
	
void defaultPosPipeAndBird()
{
	birdx = 50;
	birdy = 267;
	bird_speed = -8;
	_SPEED = 0;
	buf = false;
	trumpet[0][0] = WNDWIDTH;
	trumpet[0][1] = ((std::rand() % PIPE_MAX / 3) * 10) + 30;
	std::srand(UINT(time(0)));
	for (int i = 1; i < 4; ++i) {
		trumpet[i][0] = trumpet[i - 1][0] + PRE_SPACE;
		trumpet[i][1] = ((std::rand() % PIPE_MAX / 3) * 10) + 30;
	}
}

void paint_pipe()
{
	for (int i = 0; i < 4; i++)
	{
		if (trumpet[i][0] - PIPE_BACK <= 50 &&
			trumpet[i][0] - PIPE_BACK >= 49)
		{
			++score;
		}
		trumpet[i][0] -= PIPE_SPEED;
		SelectObject(_hBuffer2, pipe[0]);
		TransparentBlt(_hBuffer1,
			trumpet[i][0],
			trumpet[i][1]-pipesz.cy,
			pipesz.cx,
			pipesz.cy,
			_hBuffer2,
			0,
			0,
			pipesz.cx,
			pipesz.cy,
			RGB(254, 254, 254)
			);
		SelectObject(_hBuffer2, pipe[1]);
		TransparentBlt(_hBuffer1,
			trumpet[i][0],
			trumpet[i][1]+SPACE,
			pipesz.cx,
			pipesz.cy,
			_hBuffer2,
			0,
			0,
			pipesz.cx,
			pipesz.cy,
			RGB(254, 254, 254)
			);
		if (trumpet[i][0] <= -65)
		{
			int bufer = 0;
			if (i == 0)
				bufer = 4 - 1;
			else
				bufer = i - 1;
			trumpet[i][0] = trumpet[bufer][0] + PRE_SPACE;
			std::srand(UINT(time(0)));
			trumpet[i][1] = ((std::rand() % PIPE_MAX / 3) * 10) + 30;
		}
	}
}

void paint()
{
	SelectObject(_hBuffer2, background);
	BitBlt(_hBuffer1, 0, 0, WNDWIDTH, WNDHEIGHT, _hBuffer2, 0, 0, SRCCOPY);
	BitBlt(_hBuffer1, WNDWIDTH / 2-20, 0, WNDWIDTH, WNDHEIGHT, _hBuffer2, 0, 0, SRCCOPY);
	BitBlt(_hBuffer1, WNDWIDTH - 50, 0, WNDWIDTH, WNDHEIGHT, _hBuffer2, 0, 0, SRCCOPY);
	//BitBlt(_hBuffer1, WNDWIDTH / 2, 0, WNDWIDTH / 2, 50, _hBuffer2, 0, 0, SRCCOPY);
}

void painty()
{
	SelectObject(_hBuffer2, title);
	pt.y += SPEED;
	if (pt.y > 180) {
		SPEED = 0;
	}
	TransparentBlt(_hBuffer1,
		pt.x,
		pt.y,
		239,
		65,
		_hBuffer2,
		0,
		0,
		239,
		65,
		RGB(254, 254, 254));
}

void paint_medal()
{
	if (score >= BRONZE_MEDAL)SelectObject(_hBuffer2, medal[BRONZE_MEDAL_ID]);
	if (score >= SILVER_MEDAL)SelectObject(_hBuffer2, medal[SILVER_MEDAL_ID]);
	if (score >= GOLD_MEDAL)SelectObject(_hBuffer2, medal[GOLDEN_MEDAL_ID]);
	if (score >= PLATINUM_MEDAL)SelectObject(_hBuffer2, medal[PLATINUM_MEDAL_ID]);
	if (score >= BRONZE_MEDAL)
	{
		TransparentBlt(_hBuffer1, 75 + WNDWIDTH / 4 + 50, 270,
			medalsz.cx, medalsz.cy, _hBuffer2, 0, 0,
			medalsz.cx, medalsz.cy, RGB(254, 254, 254));
	}
}

void paint_gameover()
{
	SelectObject(_hBuffer2, gameOver);
	TransparentBlt(_hBuffer1,
		 WNDWIDTH / 4 + 50 ,
		 150,
		 gameoversz.cx, gameoversz.cy, _hBuffer2, 0, 0,
		 gameoversz.cx, gameoversz.cy, RGB(254, 254, 254)
		);
	paint_medal();
	score = 0;
}

void paint_bird()
{
	SelectObject(_hBuffer2, bird[bird_index]);
	if (CHECK && !gamestart)
	{
	}
	else {
		BUFER += 2;
		k++;
		if (!gamestart) {
			if (_SPEED == qwe)
			{
				bird_speed *= -1;
				_SPEED = 0;
				if (bird_index == 0)
					bird_index = 2;
				else bird_index = 0;
			}
			else if (_SPEED < qwe)
			{
				_SPEED += 2;
			}
			birdy += bird_speed;
			if (BUFER >= bird_speed)
			{
				BUFER = 0;
				//bird_index++;
			}
			if (birdx <= 300)
				birdx += 2;
		}
		else
		{
			if (buf)
			{
				if (_SPEED == 80)
				{
					bird_speed = 1;
					_SPEED = 0;
					buf = false;
					bird_index = BIRD_MID;
				}
				else
				{
					if (_SPEED % 10 == 0)
						bird_speed++;
					_SPEED += 2;
				}
			}
			else
			{
				bird_index = BIRD_DOWN;
				_SPEED += 2;
				if (_SPEED % 10 == 0 && bird_speed < 6)
					bird_speed++;
			}
			birdy += bird_speed;
		}
	}
	if (bird_index == 3)
		bird_index = 0;
	TransparentBlt(_hBuffer1,
		birdx,
		birdy,
		42,
		29,
		_hBuffer2,
		0,0,
		42,29,
		RGB(254,254,254)
		);
	if (gamestart)
		gameover = GAME_OVER();
}

void paint_mainmenu() 
{
	SelectObject(_hBuffer2, mainmenu);
	TransparentBlt(_hBuffer1,
		180,
		-10,
		bufer1,
		bufer2,
		_hBuffer2,
		0,
		0,
		bufer1,
		bufer2,
		RGB(254, 254, 254)
		);
	//BitBlt(_hBuffer1, WNDWIDTH / 4, -4, WNDWIDTH, WNDHEIGHT, _hBuffer2, 0, 0, SRCCOPY);
}

void paint_floor()
{
	SelectObject(_hBuffer2, floor_r);
	BitBlt(_hBuffer1,
		0,
		448,
		WNDWIDTH * 3,
		WNDHEIGHT,
		_hBuffer2,
		0, 0, SRCCOPY
		);
	BitBlt(_hBuffer1,
		floorsz.cx-1,
		448,
		WNDWIDTH * 3,
		WNDHEIGHT,
		_hBuffer2,
		0, 0, SRCCOPY
		);
	/*BitBlt(_hBuffer1,
		floorsz.cx*2,
		floorsz.cy,
		WNDWIDTH * 3,
		WNDHEIGHT,
		_hBuffer2,
		0, 0, SRCCOPY
		);*/
	//TransparentBlt(
	//	_hBuffer1,
	//	0,
	//	448,
	//	WNDWIDTH * 3,
	//	WNDHEIGHT,
	//	_hBuffer2,
	//	0, 0, SRCCOPY
	//	);
}

void paint_bignum()
{
	SelectObject(_hBuffer2, bigNum);
	TransparentBlt(_hBuffer1, bignumx, bignumy,
		BIG_NUM_SPACE, bignumsz.cy, _hBuffer2, BIG_NUM_SPACE * (score / 100 % 10), 0,
		BIG_NUM_SPACE, bignumsz.cy, RGB(254, 254, 254));
	TransparentBlt(_hBuffer1, bignumx + BIG_NUM_SPACE, bignumy,
		BIG_NUM_SPACE, bignumsz.cy, _hBuffer2, BIG_NUM_SPACE * (score / 10 % 10), 0,
		BIG_NUM_SPACE, bignumsz.cy, RGB(254, 254, 254));
	TransparentBlt(_hBuffer1, bignumx + BIG_NUM_SPACE * 2, bignumy,
		BIG_NUM_SPACE, bignumsz.cy, _hBuffer2, BIG_NUM_SPACE * (score % 10), 0,
		BIG_NUM_SPACE, bignumsz.cy, RGB(254, 254, 254));
}

void playMusic()
{
	if (File.size() == 0)
		return;
	op.dwCallback = NULL;
	op.lpstrAlias = NULL;
	op.lpstrDeviceType = L"mpegvideo";
	//WCHAR tmp[255] = L"E:\\Music\\Music\\";
	WCHAR tmp[255] = L"Musics\\";
	op.lpstrElementName = wcscat(tmp, File[Now_Music].cFileName);
	op.wDeviceID = NULL;
	UINT rs;
	rs = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&op);
	if (rs == 0)
	{
		MCI_PLAY_PARMS pp;
		pp.dwCallback = NULL;
		pp.dwFrom = 0;
		mciSendCommand(op.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)&pp);
	}
}

void generateIndexMusic()
{
	if (File.size() == 0)
		return;
	std::srand(UINT(time(0)));
	Now_Music = std::rand() % File.size();
}

void loadMusic()
{
	WIN32_FIND_DATA p;
	//HANDLE h = FindFirstFile(L"E:\\Music\\Music\\*.mp3", &p);
	HANDLE h = FindFirstFile(L"Musics\\*.mp3", &p);
	do
	{
		if (p.cFileName[0] != '.')File.push_back(p);
	} while (FindNextFile(h, &p));
	generateIndexMusic();
}

void closeMusic()
{
	gp.dwCallback = NULL;
	mciSendCommand(op.wDeviceID, MCI_CLOSE, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)&gp);
}

void init()
{
	
	BITMAP bitmap;
	WCHAR link[100] = L"";

	wcscpy_s(link, L"Images\\Background\\bk_day.bmp");
	background = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(background, sizeof(BITMAP), &bitmap);

	wcscpy_s(link, L"Images\\Background\\title.bmp");
	title = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(title, sizeof(BITMAP), &bitmap);

	wcscpy_s(link, L"Images\\Bird\\bird_down.bmp");
	bird[0] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(bird[0], sizeof(BITMAP), &bitmap);

	wcscpy_s(link, L"Images\\Bird\\bird_mid.bmp");
	bird[1] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(bird[1], sizeof(BITMAP), &bitmap);

	wcscpy_s(link, L"Images\\Bird\\bird_up.bmp");
	bird[2] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(bird[2], sizeof(BITMAP), &bitmap);
	birdsz.cx = bitmap.bmWidth;
	birdsz.cy = bitmap.bmHeight;

	wcscpy_s(link, L"Images\\Guide\\guide.bmp");
	mainmenu = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(mainmenu, sizeof(BITMAP), &bitmap);
	bufer1 = bitmap.bmWidth;
	bufer2 = bitmap.bmHeight;

	wcscpy_s(link, L"Images\\Background\\bk_floor.bmp");
	floor_r = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(floor_r, sizeof(BITMAP), &bitmap);
	floorsz.cx = bitmap.bmWidth;
	floorsz.cy = bitmap.bmHeight;


	wcscpy_s(link, L"Images\\Pipe\\pipe_down.bmp");
	pipe[1] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wcscpy_s(link, L"Images\\Pipe\\pipe_up.bmp");
	pipe[0] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(pipe[0], sizeof(BITMAP), &bitmap);
	pipesz.cx = 68;
	pipesz.cy = 1000;

	trumpet[0][0] = WNDWIDTH;
	trumpet[0][1] = ((std::rand() % PIPE_MAX / 3) * 10) + 30;
	std::srand(UINT(time(0)));
	for (int i = 1; i < 4; ++i) {
		trumpet[i][0] = trumpet[i - 1][0] + PRE_SPACE;
		trumpet[i][1] = ((std::rand() % PIPE_MAX / 3) * 10) + 30;
	}

	wcscpy_s(link, L"Images\\Other\\gameover.bmp");
	gameOver = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(gameOver, sizeof(BITMAP), &bitmap);
	gameoversz.cx = bitmap.bmWidth;
	gameoversz.cy = bitmap.bmHeight;

	wcscpy_s(link, L"Images\\Num\\bignum.bmp");
	bigNum = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(bigNum, sizeof(BITMAP), &bitmap);
	bignumsz.cx = bitmap.bmWidth;
	bignumsz.cy = bitmap.bmHeight;

	wcscpy_s(link, L"Images\\Medal\\bronze_medal.bmp");
	medal[0] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wcscpy_s(link, L"Images\\Medal\\sliver_medal.bmp");
	medal[1] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wcscpy_s(link, L"Images\\Medal\\gold_medal.bmp");
	medal[2] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wcscpy_s(link, L"Images\\Medal\\platinum_medal.bmp");
	medal[3] = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(medal[0], sizeof(BITMAP), &bitmap);
	medalsz.cx = bitmap.bmWidth;
	medalsz.cy = bitmap.bmHeight;
	/*wcscpy_s(link, L"Images\\Other\\Press-any-key-to-continue.bmp");
	pressAnyKey = (HBITMAP)LoadImage(hInstance, link, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(pressAnyKey, sizeof(BITMAP), &bitmap);
	pressAnysz.cx = bitmap.bmWidth;
	pressAnysz.cy = bitmap.bmHeight;*/
//	pressAnyKey = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_PAK), IMAGE_BITMAP, 0, 0, LR_COPYFROMRESOURCE);
	freopen("Data\\bestscore.txt", "r", stdin);
	std::cin >> best_score;
	fclose(stdin);
	loadMusic();
}

void _DELETE()
{
	DeleteDC(hdc);
	DeleteDC(_hBuffer2);
	DeleteDC(_hBuffer1);
	DeleteObject(background);
	DeleteObject(gameOver);
	DeleteObject(cptBitMap1);
	DeleteObject(title);
	DeleteObject(mainmenu);
	for (std::size_t i = 0; i < 2; i++)
		DeleteObject(pipe[i]);
	for (std::size_t i = 0; i < 3; i++)
		DeleteObject(bird[i]);
	DeleteObject(floor_r);
	DeleteObject(bigNum);
	for (std::size_t i = 0; i < 4; i++)
		DeleteObject(medal[i]);
}

void _FILES()
{
	/*WCHAR* link = L"Images\\Background\\bk_day.bmp";
	FILES_N.push_back(link);
	link = L"Images\\Background\\title.bmp";
	FILES_A.push_back(link);*/
	//FILES_N.push_back((WCHAR)(L"Images\\Background\\bk_day.bmp"));
}

void checkHighScore()
{
	if (score > best_score)
	{
		freopen("Data\\bestscore.txt", "w", stdout);
		std::cout << score;
		fclose(stdout);
	}
}

bool GAME_OVER()
{
	if (birdy > 415)
	{
		return true;
	}
	int x[4], y[4];
	x[0] = birdx + BIRD_BODY; y[0] = birdy + BIRD_BODY;
	x[1] = birdx + BIRD_BODY, y[1] = birdy + birdsz.cy - BIRD_BODY;
	x[2] = birdx + birdsz.cx - BIRD_BODY, y[2] = birdy + BIRD_BODY;
	x[3] = birdx + birdsz.cx - BIRD_BODY, y[3] = birdy + birdsz.cy - BIRD_BODY;
	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			if (x[j] > trumpet[i][0] && x[j] < trumpet[i][0] + pipesz.cx && (y[j] < trumpet[i][1] || y[j] > trumpet[i][1] + SPACE))
			{
				checkHighScore();
				return true;
			}
		}
	}
	return false;
}

void paint_pressAnyKey(const bool st, int x = 100, int y = 335)
{
	/*SelectObject(_hBuffer2, pressAnyKey);
	TransparentBlt(_hBuffer1, x, y, 400,400, _hBuffer2, 0, 0, 400, 400, RGB(0, 0, 0));*/
}

LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
	/*	_FILES();
		GAME::init(backGR, FILES_N,hInstance);
		GAME::init(Title, FILES_A, hInstance);*/
		init();
	//	PlaySound(L"Musics\\main.wav", NULL, SND_ASYNC);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		/*WORD xPos, yPos, nSize;
		TCHAR szBuf[80];
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		hdc = GetDC(hwnd);
		nSize = wsprintf(szBuf, TEXT("(%d, %d)"), xPos, yPos);
		TextOut(hdc, xPos, yPos, szBuf, nSize);
		ReleaseDC(hwnd, hdc);*/
		if (!CHECK && !gamestart)
		{
			birdx = 50;
			birdy = 267;
			bird_speed = -8;
			_SPEED = 0;
			buf = false;
		}
		if (CHECK && !gamestart) {
			if (gameover) {
				closeMusic();
				generateIndexMusic();
				playMusic();
			}
			gamestart = true;
			gameover = false;
		}
		else if (CHECK && gamestart)
		{
			bird_index = BIRD_UP;
			bird_speed = -6;
			_SPEED = 0;
			buf = true;
		}
		CHECK = true;
		break;
	}
	break;
	case WM_RBUTTONDOWN:
	{
		if (!CHECK && !gamestart)
		{
			birdx = 50;
			birdy = 267;
			bird_speed = -8;
			_SPEED = 0;
			buf = false;
			
		}
		if (CHECK && !gamestart) {
			if (gameover) {
				closeMusic();
				generateIndexMusic();
				playMusic();
			}
			gamestart = true;
			birdx = 50;
			birdy = 267;
			bird_speed = 2;
			_SPEED = 0;
			buf = false;
			gameover = false;
		}
		else {
			CHECK = true;
			paint();
			paint_mainmenu();
		//	paint_pressAnyKey(false);
		//	paint_floor();
			BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, _hBuffer1, 0, 0, SRCCOPY);
		}
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
		//EndDialog(hwnd, 0);
	}
	break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prehInstance, LPSTR cmdLine, INT nCmdShow)
{
	buf = false; 
	WCHAR link[100];
	wcscpy_s(link, L"Images\\Other\\ICON.ico");
	WNDCLASS wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = 0;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = (HICON)LoadImage(hInstance, link, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = TEXT("Flappy Bird");
	wndclass.lpszMenuName = 0;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndclass);
	HWND hwnd = CreateWindow(
		TEXT("Flappy Bird"),
		TEXT("Flappy Bird ©BADAEV™"),
		WS_OVERLAPPEDWINDOW,//^WS_THICKFRAME^WS_MAXIMIZEBOX,
		0, 0,
		WNDWIDTH, WNDHEIGHT,
		0,0,
		hInstance, 0
		);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	hdc = GetDC(hwnd);
	_hBuffer1 = CreateCompatibleDC(hdc);
	_hBuffer2 = CreateCompatibleDC(hdc);
	_hBuffer3 = CreateCompatibleDC(hdc);
	cptBitMap1 = CreateCompatibleBitmap(hdc, WNDWIDTH, WNDHEIGHT);
	SelectObject(_hBuffer1, cptBitMap1);
	sz.cx = 239;
	sz.cy = 65;
	pt.x = 260;
	pt.y = -100;
	//paint();
	CHECK = false;
	gameover = false;
	gamestart = false;
	playMusic();
	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			if (msg.message == WM_QUIT)break;
			DispatchMessage(&msg);
		}
		else if (!CHECK && !gamestart) {
			paint();
			painty();
			paint_bird();
			paint_floor();
			BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, _hBuffer1, 0, 0, SRCCOPY);
			Sleep(10);
		}
		else 	if(CHECK && !gamestart) {
			if (!gameover) {
				paint();
				paint_bird();
				paint_mainmenu();
				BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, _hBuffer1, 0, 0, SRCCOPY);
			}
		}
		else if (CHECK && gamestart)
		{
			if (gameover)
			{
				gamestart = false;
				defaultPosPipeAndBird();
				paint();
				paint_floor();
				paint_gameover();
			}
			else {
				paint();
				paint_pipe();
				paint_bird();
				paint_floor();
				paint_bignum();
			}
			BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, _hBuffer1, 0, 0, SRCCOPY);
			if (birdy < 0)
			{
				birdy = 0;
			}
			
			Sleep(10);
		}
	}
	_DELETE();
	return msg.wParam;
}