#pragma once
#include "Header.h"
#include <vector>
namespace GAME
{
	
	class Others {
	public:
		std::vector<HBITMAP>_bitMap;
		INT Speed;
		std::vector<SIZE>	_size;
		POINT pos;
		INT _back;
	};
	class TRUMPET
	{
	public:
		std::vector<HBITMAP>_bitMap;
		INT		Speed;
		std::vector<SIZE>	_size;
		POINT	_pos;
		INT		_back;
		INT		_diff;
		INT		_diff_dx;
	};

	class BIRDS
	{
	public:
		std::vector<HBITMAP>_bitMap;
		INT		_Num;
		INT		Speed;
		INT		_nAcc;
		INT		_nNowPipe;
		std::vector<SIZE>	_size;
		POINT	_pos;
	};
	class MEDALS {
	public:
		std::vector<HBITMAP>_bitMap;
		std::vector<SIZE>	_size;
		POINT	_pos;
	};
	class MENUS {
	public:
		std::vector<HBITMAP>_bitMap;
		std::vector<SIZE>	_size;
		POINT	_pos;
	};
	
	void init(GAME::Others &,std::vector<WCHAR*>, HINSTANCE);
	void InitDataObj();
	void InitBitMap();
	void StickPics_Play();
	void LoadMusic();
	void StickPics_GameOver();
	void StickPics_Title(BOOL &Title);
	void _Delete();
	void StickPics_MainMenu();
	void Play_Music();
	void Close_Music();
	void Pre_Music();
	void Next_Music();
	void Play_Jump_Music();
	BOOL CheckGameOver();
	void Paint_Background(GAME::Others &a, HDC &buf, HDC &buf2);
	void Paint_Title(GAME::Others &a, HDC &buf, HDC &buf2);
	void Paint_Ex();
	void Paint_Pipe();
	void Paint_Floor();
	void Paint_Bignum();
	void Paint_Bird();
	void Paint_Mainmenu();
	void Paint_Gameover();
	void Paint_Score();
	void Paint_Smallnum();
	void Paint_Medal();
	
}