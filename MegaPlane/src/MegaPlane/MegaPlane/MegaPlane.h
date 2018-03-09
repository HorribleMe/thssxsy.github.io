#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "resource.h"

//定义宏变量，WNDWIDTH、WNDHEIGHT为窗口的宽和高，包括边框
#define TIMER                1
#define WNDWIDTH             480
#define WNDHEIGHT            800
#define ENEMY_TYPE_NUM       3
#define ENEMY_PLANE_NUM      100
//定义Hero飞机的尺寸         
#define HERO_SIZE_X          102
#define HERO_SIZE_Y          126
//定义敌机小、中、大的尺寸
#define ENEMY_SMALL_SIZE_X   57 
#define ENEMY_SMALL_SIZE_Y   51
#define ENEMY_MIDDLE_SIZE_X  69
#define ENEMY_MIDDLE_SIZE_Y  95
#define ENEMY_BIG_SIZE_X     169
#define ENEMY_BIG_SIZE_Y     260
#define Bullet_num           500
#define ENEMY_bullet_num     100
//道具
#define UFO1_SIZE_X          58
#define UFO1_SIZE_Y          88
#define UFO2_SIZE_X          60
#define UFO2_SIZE_Y			 107
#define UFO22_SIZE_X         480
#define UFO22_SIZE_Y         227
#define UFO4_SIZE_X          60
#define UFO4_SIZE_Y          60
#define BOSS1_SIZE_X		 200
#define BOSS1_SIZE_Y         200
#define BOSS2_SIZE_X         180
#define BOSS2_SIZE_Y         200
#define BOSS3_SIZE_X         250
#define BOSS3_SIZE_Y         230
#define BOSS4_SIZE_X         160
#define BOSS4_SIZE_Y         193
#define bullet_x             9
#define bullet_y             21
#define BOSS_FIRE            300
#define RECTANGLEHIGHT      10
#define RECTANGLEWIDTH       10        
//飞机结构体，飞机位图、位置、大小、速度、类型
typedef struct
{
	HBITMAP	hBmp;
	POINT	pos;
	SIZE	size;
	int		speed;
	int		type;
	int     blood;
	int     selfmove;
	int		life;
}Plane;

//游戏状态结构体
typedef struct
{
	HBITMAP	hBmp;
	POINT   pos;
	SIZE	size;
	BOOL	isPaused;
}GameStaus;


/*全局变量*/
static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("飞机大战");
int pre_bnum = 0;
int rou_bullet = 0;
int round = 1;
int isboss = 0;
int ispause = 0;

HBITMAP m_hBackgroundBmp;
HBITMAP m_hBackground2Bmp;
HBITMAP m_hBackground3Bmp;
HBITMAP m_hBackground4Bmp;
HBITMAP m_hHeroBmp;
HBITMAP	m_hEnemyBmp[ENEMY_TYPE_NUM];
HBITMAP m_hEnemyBmp2[ENEMY_TYPE_NUM];
HBITMAP m_hEnemyBmp3[ENEMY_TYPE_NUM];
HBITMAP m_hEnemyBmp4[ENEMY_TYPE_NUM];
HBITMAP m_hGameStatusBmp;
HBITMAP m_hBullet1Bmp;
HBITMAP m_ufo1Bmp;
HBITMAP m_ufo2Bmp;
HBITMAP m_ufo3Bmp;
HBITMAP m_ufo4Bmp;
HBITMAP m_eneBulletBmp;
HBITMAP ufo22Bmp;
HBITMAP bossBmp[4];
HBITMAP signBmp[4];
HBITMAP tembomb;
HBITMAP herolifeBmp;
HBITMAP gameoverBmp;
HBITMAP gamestartBmp;
HBITMAP helpBmp;
HBITMAP bumbleBmp;
HBITMAP bossfireBmp;
RECT herorect;
RECT enemyrect[ENEMY_PLANE_NUM];
//定义飞机类型数组，与m_hEnemyBmp[ENEMY_TYPE_NUM]个数对应，0表示小飞机，1表示中，2表示大
int	m_enemyBmpNames[] = { IDB_ENEMY_SMALL, IDB_ENEMY_MIDDLE, IDB_ENEMY_BIG };
int m_enemyBmpNames2[] = { IDB_2SMALLENEMY, IDB_2MIDDELENEMY, IDB_2BIGENEMY };
int m_enemyBmpNames3[] = { IDB_3SMALLENEMY, IDB_3MIDDELENEMY, IDB_3BIGENEMY };
int m_enemyBmpNames4[] = { IDB_4SMALLENEMY, IDB_4MIDDELENEMY, IDB_4BIGENEMY };
int bossBmpNames[] = {IDB_BOSS1, IDB_BOSS2, IDB_BOSS3, IDB_BOSS4};
int signBmpNames[] = {IDB_SIGN1, IDB_SIGN2, IDB_SIGN3, IDB_SIGN4};
//定义Hero飞机、敌机数组、游戏状态和总分数
Plane m_heroPlane;
Plane m_enemyPlanes[ENEMY_PLANE_NUM];
GameStaus m_gameStatus;
Plane m_hBullet[Bullet_num];
Plane m_ufo1[10];
Plane m_ufo2[10];
Plane m_ufo3[10];
Plane m_eneBullet[ENEMY_bullet_num];
Plane bossfire[BOSS_FIRE];
Plane ufo22[10];
Plane m_ufo4[10];
Plane sign[4];
Plane boss[4];
int m_totalScore;
int backgroudmove = WNDHEIGHT;
int ufo2_num = 1;
int pre_ufo22 = 0;
int goin = 0;
int planeshine = 0;
int shine = 1;
int herolife = 2;
int gameover = 0;
int gamestart = 0;
int ishelp = 0;
int presign = 1;
int isprotect = 0;
int pre_enebullet = 0;
/*全局函数*/
//窗体过程函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//初始化
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam);
//创建Hero飞机，x、y表示矩形左上角的坐标，speed表示速度，type表示飞机类型
Plane CreateHeroPlane(LONG x, LONG y, int speed, int type);
//创建敌机，x、y表示矩形左上角的坐标，speed表示速度，type表示飞机类型，0表示小飞机，1表示中，2表示大
Plane CreateEnemyPlane(LONG x, LONG y, int speed, int type);
//双缓冲绘制
Plane CreateBullet1(LONG x, LONG y, int speed, int type);
//创建炸弹
Plane Createufo22();
//BOSS
Plane Createboss();
Plane Createbossfire(LONG x, LONG y);
//SIGN
Plane Createsign(int i);
VOID Render(HWND hWnd);
//判断是否点击暂停
BOOL Paused(POINT);
//键盘事件处理
VOID KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
//左鼠标点击事件
VOID LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
//定时器事件
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);
//碰撞函数
int crash(Plane a, Plane b)
{
	double downa, downb, righta, rightb;
	downa = a.pos.y + a.size.cy;
	downb = b.pos.y + b.size.cy;
	righta = a.pos.x + a.size.cx;
	rightb = b.pos.x + b.size.cx;
	if(a.pos.y <= downb && a.pos.y >= b.pos.y)
	{
		if(a.pos.x <= rightb && a.pos.x >= b.pos.x)return 1;
		else if(righta <= rightb && righta >= b.pos.x)return 1;
		else return 0;
	}
	else if(downa <= downb && downa >= b.pos.y)
	{
		if(a.pos.x <= rightb && a.pos.x >= b.pos.x)return 1;
		else if(righta <= rightb && righta >= b.pos.x)return 1;
		else return 0;
	}
	else
		return 0;
}
Plane Createufo22()
{
	Plane ufo;
	ufo.pos.x = 0;
	ufo.pos.y = WNDHEIGHT;
	ufo.speed = 10;
	ufo.hBmp = ufo22Bmp;
	ufo.size.cx = UFO22_SIZE_X;
	ufo.size.cy = UFO22_SIZE_Y;
	return ufo;
}
