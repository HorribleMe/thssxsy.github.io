#include "makeitclear.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Mega Plane"),
			MB_OK);

		return 1;
	}

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create,~WS_THICKFRAME  fixed window size
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// WNDWIDTH, WNDHEIGHT: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, //设置窗口样式，不可改变大小，不可最大化
		CW_USEDEFAULT, CW_USEDEFAULT,
		WNDWIDTH, WNDHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Mega Plane"),
			MB_OK);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		//初始化
		Init(hWnd, wParam, lParam);
		PlaySound( MAKEINTRESOURCE(IDR_GAME_MUSIC), GetModuleHandle( NULL ), SND_LOOP|SND_ASYNC|SND_RESOURCE);
		break;
	case WM_PAINT:
		//绘制
		Render(hWnd);
		break;
	case WM_KEYDOWN:
		//键盘事件
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		//左鼠标事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		//定时器事件
		TimerUpdate(hWnd, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BITMAP bmp;
	int i;
	//加载背景位图
	m_hBackgroundBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND1));
	m_hBackground2Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND2));
	m_hBackground3Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND3));
	m_hBackground4Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND4));
	//SIGN
	for(i = 0;i<=3;i++)
	{
		signBmp[i] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(signBmpNames[i]));
	}
	//开始画面
	gamestartBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_GAMESTART));
	//帮助位图
	helpBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HELP));
	//加载子弹位图
	m_hBullet1Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BULLET3));
	m_eneBulletBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_emeBullet));
	bossfireBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BOSSFIRE));
	//加载道具位图
	m_ufo1Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_UFO1));
	m_ufo2Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_UFO2));
	ufo22Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_RUNUFO2));
	tembomb = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BOMB));
	m_ufo3Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_UFO3));
	bumbleBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BUMBLE));
	m_ufo4Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_UFO4));
	//加载hero飞机位图
	m_hHeroBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO));
	herolifeBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HEROLIFE));
	//加载敌机位图
	int k;
	for (k = 0; k < ENEMY_TYPE_NUM; k++)
	{
		m_hEnemyBmp[k] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(m_enemyBmpNames[k]));
		m_hEnemyBmp2[k] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(m_enemyBmpNames2[k]));
		m_hEnemyBmp3[k] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(m_enemyBmpNames3[k]));
		m_hEnemyBmp4[k] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(m_enemyBmpNames4[k]));
	}
	//boss位图
	for(k=0;k<=3;k++)
	{
		bossBmp[k] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
			MAKEINTRESOURCE(bossBmpNames[k]));
	}
	//加载游戏状态位图
	m_hGameStatusBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_GAME_STATUS));

	//初始化Hero飞机
	m_heroPlane = CreateHeroPlane(WNDWIDTH / 2, WNDHEIGHT / 2, 5, 0);
	for(i = 0;i<=3;i++)
	{
		sign[i] = Createsign(i);
	}
	//初始化游戏状态，暂停或继续
	m_gameStatus.isPaused = FALSE;
	GetObject(m_hGameStatusBmp, sizeof(BITMAP), &bmp);
	m_gameStatus.size.cx = bmp.bmWidth;
	m_gameStatus.size.cy = bmp.bmHeight / 4;
	m_gameStatus.hBmp = m_hGameStatusBmp;
	//结束
	gameoverBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_GAMEOVER));
	//初始化分数
	m_totalScore = 0;
	//启动计时器
	SetTimer(hWnd, TIMER, 50, NULL);
	
	srand( GetTickCount());
}

VOID Render(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	//开始绘制
	hdc = BeginPaint(hWnd, &ps);

	TCHAR	szScore[13];
	TCHAR   bombnum[8];
	TCHAR   lifenum[8];
	HDC	hdcBmp, hdcBuffer;
	HBITMAP	cptBmp;
	int i, len, len2, len3;

	cptBmp = CreateCompatibleBitmap(hdc, WNDWIDTH, WNDHEIGHT);
	hdcBmp = CreateCompatibleDC(hdc);
	hdcBuffer = CreateCompatibleDC(hdc);
	SelectObject(hdcBuffer, cptBmp);
	if(gamestart == 1)
	{
		if(gameover == 0)
		{
			HPEN hpen;
			HBRUSH hbrush;
			switch(round)
			{
			case 1:
				SelectObject(hdcBmp, m_hBackgroundBmp);
				BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
					hdcBmp, 0, backgroudmove, SRCCOPY);
				break;
			case 2:
				SelectObject(hdcBmp, m_hBackground2Bmp);
				BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
					hdcBmp, 0, backgroudmove, SRCCOPY);
				break;
			case 3:
				SelectObject(hdcBmp, m_hBackground3Bmp);
				BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
					hdcBmp, 0, backgroudmove, SRCCOPY);
				break;
			case 4:
				SelectObject(hdcBmp, m_hBackground4Bmp);
				BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
					hdcBmp, 0, backgroudmove, SRCCOPY);
				break;
			default:
				break;
			}
			//炸弹贴图
			SelectObject(hdcBmp, tembomb);
			TransparentBlt(
				hdcBuffer, -40,580,130, 70,
				hdcBmp, 0, 0, 130, 70,
				RGB(255, 255, 255)
				);
			//生命贴图
			SelectObject(hdcBmp, herolifeBmp);
			TransparentBlt(
				hdcBuffer, -10,500,80,80,
				hdcBmp, 0, 0, 80, 80,
				RGB(255, 255, 255)
				);
			for(i = 0;i<=3;i++)
			{
				SelectObject(hdcBmp, sign[i].hBmp);
				TransparentBlt(
					hdcBuffer, sign[i].pos.x, sign[i].pos.y,
					sign[i].size.cx,sign[i].size.cy,
					hdcBmp, 0, sign[i].selfmove, sign[i].size.cx, sign[i].size.cy,
					RGB(255, 255, 255)
					);
			}
			if(isprotect >= 1)
			{
				SelectObject(hdcBmp, bumbleBmp);
				TransparentBlt(
					hdcBuffer, m_heroPlane.pos.x - 28, m_heroPlane.pos.y - 20,
					160, 160,
					hdcBmp, 0, m_heroPlane.selfmove, 160, 160,
					RGB(255, 255, 255)
					);
			}
			//绘制Hero飞机
			if(shine != 1)
			{
				SelectObject(hdcBmp, m_heroPlane.hBmp);
				TransparentBlt(
					hdcBuffer, m_heroPlane.pos.x, m_heroPlane.pos.y,
					m_heroPlane.size.cx, m_heroPlane.size.cy,
					hdcBmp, 0, m_heroPlane.selfmove, m_heroPlane.size.cx, m_heroPlane.size.cy,
					RGB(255, 255, 255)
					);
				hpen = CreatePen ( PS_SOLID, 1,RGB(255, 0, 0));
				hbrush = CreateSolidBrush ( RGB (255, 0, 0));
				SelectObject(hdcBuffer, hpen);
				SelectObject(hdc, hbrush);
				herorect.left = 50;
				herorect.right = 50 + m_heroPlane.blood * RECTANGLEWIDTH * 2;
				herorect.top = 630 - RECTANGLEHIGHT;
				herorect.bottom = 630;
				Rectangle(hdcBuffer,50, 630 - RECTANGLEHIGHT, 50+ m_heroPlane.blood * RECTANGLEWIDTH, 630 );
				FillRect(hdcBuffer, &herorect, hbrush);
				DeleteObject(hbrush);
			}
			else
			{
				if(planeshine%5 == 0)
				{
					SelectObject(hdcBmp, m_heroPlane.hBmp);
					TransparentBlt(
					hdcBuffer, m_heroPlane.pos.x, m_heroPlane.pos.y,
					m_heroPlane.size.cx, m_heroPlane.size.cy,
					hdcBmp, 0, m_heroPlane.selfmove, m_heroPlane.size.cx, m_heroPlane.size.cy,
					RGB(255, 255, 255)
					);
					hpen = CreatePen ( PS_SOLID, 1,RGB(255, 0, 0));
					hbrush = CreateSolidBrush ( RGB (255, 0, 0));
					SelectObject(hdcBuffer, hpen);
					SelectObject(hdc, hbrush);
					herorect.left = 50;
					herorect.right = 50 + m_heroPlane.blood * RECTANGLEWIDTH * 2;
					herorect.top = 630 - RECTANGLEHIGHT;
					herorect.bottom = 630;
					Rectangle(hdcBuffer,50, 630 - RECTANGLEHIGHT, 50+ m_heroPlane.blood * RECTANGLEWIDTH,630 );
					FillRect(hdcBuffer, &herorect, hbrush);
					DeleteObject(hbrush);
				}
				if(planeshine == 20)
				{
					planeshine = 0;
					shine = 0;
				}
			}
			//绘制子弹
			for(i=0;i<Bullet_num;i++)
			{
			SelectObject(hdcBmp, m_hBullet[i].hBmp);
			TransparentBlt(
				hdcBuffer, m_hBullet[i].pos.x, m_hBullet[i].pos.y,
				m_hBullet[i].size.cx, m_hBullet[i].size.cy,
				hdcBmp, 0, 0, m_hBullet[i].size.cx, m_hBullet[i].size.cy,
				RGB(255, 255, 255)
				);
			}
			for(i=0;i<ENEMY_bullet_num;i++)
			{
				SelectObject(hdcBmp, m_eneBullet[i].hBmp);
				TransparentBlt(
					hdcBuffer, m_eneBullet[i].pos.x, m_eneBullet[i].pos.y,
					m_eneBullet[i].size.cx, m_eneBullet[i].size.cy,
					hdcBmp, 0, 0, m_eneBullet[i].size.cx, m_eneBullet[i].size.cy,
					RGB(255, 255, 255)
					);
			}
			for(i=0;i<BOSS_FIRE;i++)
			{
				SelectObject(hdcBmp, bossfire[i].hBmp);
				TransparentBlt(
					hdcBuffer, bossfire[i].pos.x, bossfire[i].pos.y,
					bossfire[i].size.cx,bossfire[i].size.cy,
					hdcBmp, 0, 0, bossfire[i].size.cx, bossfire[i].size.cy,
					RGB(255, 255, 255)
					);
			}
			//绘制道具
			for(i=0;i<=9;i++)
			{
				SelectObject(hdcBmp, m_ufo1[i].hBmp);
				TransparentBlt(
					hdcBuffer, m_ufo1[i].pos.x, m_ufo1[i].pos.y,
					m_ufo1[i].size.cx, m_ufo1[i].size.cy,
					hdcBmp, 0,0, m_ufo1[i].size.cx, m_ufo1[i].size.cy,
					RGB(255, 255, 255)
					);
				SelectObject(hdcBmp, m_ufo2[i].hBmp);
				TransparentBlt(
					hdcBuffer, m_ufo2[i].pos.x, m_ufo2[i].pos.y,
					m_ufo2[i].size.cx, m_ufo2[i].size.cy,
					hdcBmp, 0,0, m_ufo2[i].size.cx, m_ufo2[i].size.cy,
					RGB(255, 255, 255)
					);
				SelectObject(hdcBmp, m_ufo3[i].hBmp);
				TransparentBlt(
					hdcBuffer, m_ufo3[i].pos.x, m_ufo3[i].pos.y,
					m_ufo3[i].size.cx, m_ufo3[i].size.cy,
					hdcBmp, 0,0, m_ufo3[i].size.cx, m_ufo3[i].size.cy,
					RGB(255, 255, 255)
					);
				SelectObject(hdcBmp, m_ufo4[i].hBmp);
				TransparentBlt(
					hdcBuffer, m_ufo4[i].pos.x, m_ufo4[i].pos.y,
					m_ufo4[i].size.cx, m_ufo4[i].size.cy,
					hdcBmp, 0,0, m_ufo4[i].size.cx, m_ufo4[i].size.cy,
					RGB(255, 255, 255)
					);
			}
		for(i = 0;i <= 9;i++)
		{
		SelectObject(hdcBmp, ufo22Bmp);
		TransparentBlt(
			hdcBuffer, ufo22[i].pos.x, ufo22[i].pos.y,
			ufo22[i].size.cx, ufo22[i].size.cy,
			hdcBmp, 0, 0,ufo22[i].size.cx, ufo22[i].size.cy,
			RGB(255, 255, 255)
			);
		}
		//绘制敌机
		for(i=0;i<ENEMY_PLANE_NUM;i++)
		{
			SelectObject(hdcBmp, m_enemyPlanes[i].hBmp);
		TransparentBlt(
			hdcBuffer, m_enemyPlanes[i].pos.x, m_enemyPlanes[i].pos.y,
			m_enemyPlanes[i].size.cx, m_enemyPlanes[i].size.cy,
			hdcBmp, 0, m_enemyPlanes[i].selfmove, m_enemyPlanes[i].size.cx, m_enemyPlanes[i].size.cy,
			RGB(255, 255, 255)
			);
		
		Rectangle(hdcBuffer, m_enemyPlanes[i].pos.x, m_enemyPlanes[i].pos.y - RECTANGLEHIGHT, m_enemyPlanes[i].pos.x + m_enemyPlanes[i].blood * RECTANGLEWIDTH, m_enemyPlanes[i].pos.y );
		}
		//BOSS
		for(i=0;i<=3;i++)
		{
			SelectObject(hdcBmp,boss[i].hBmp);
			TransparentBlt(
				hdcBuffer, boss[i].pos.x, boss[i].pos.y,
				boss[i].size.cx, boss[i].size.cy,
				hdcBmp, 0,boss[i].selfmove, boss[i].size.cx, boss[i].size.cy,
				RGB(255, 255, 255)
				);
			Rectangle(hdcBuffer, boss[i].pos.x - 200, boss[i].pos.y - RECTANGLEHIGHT, boss[i].pos.x - 200 + boss[i].blood * RECTANGLEWIDTH, boss[i].pos.y );
		}
		//贴暂停或继续位图
		SelectObject(hdcBmp, m_gameStatus.hBmp);
		TransparentBlt(hdcBuffer, 0, 0, m_gameStatus.size.cx, m_gameStatus.size.cy,
			hdcBmp, 0, m_gameStatus.size.cy * m_gameStatus.isPaused * 2,
			m_gameStatus.size.cx, m_gameStatus.size.cy, RGB(255, 255, 255));
		//显示分数
		SetTextColor(hdcBuffer, RGB(185, 122, 87));
		SetBkMode(hdcBuffer, TRANSPARENT);
		len = wsprintf(szScore, _T("分数:%d"), m_totalScore);
		TextOut(hdcBuffer, 60, 15, szScore, len);
		//显示炸弹个数
		SetTextColor(hdcBuffer, RGB(185, 122, 87));
		SetBkMode(hdcBuffer, TRANSPARENT);
		len2 = wsprintf(bombnum, _T("必杀:%d"), ufo2_num);
		TextOut(hdcBuffer, 60, 600, bombnum, len2);
		//显示生命
		SetTextColor(hdcBuffer, RGB(185, 122, 87));
		SetBkMode(hdcBuffer, TRANSPARENT);
		len3 = wsprintf(lifenum, _T("生命:%d"), herolife);
		TextOut(hdcBuffer, 60, 540, lifenum, len3);
		}
		//结束
		else if(gameover == 1)
		{
			SelectObject(hdcBmp, gameoverBmp);
			BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
			hdcBmp, 0, 0, SRCCOPY);
			SetTextColor(hdcBuffer, RGB(185, 122, 87));
			SetBkMode(hdcBuffer, TRANSPARENT);
			len = wsprintf(szScore, _T("%d"), m_totalScore);
			TextOut(hdcBuffer, WNDWIDTH/2, WNDHEIGHT/2, szScore, len);
		}
    }
	else
	{
		SelectObject(hdcBmp, gamestartBmp);
		BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
			hdcBmp, 0, 0, SRCCOPY);
		if(ishelp == 1)
		{
			SelectObject(hdcBmp, helpBmp);
			BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
				hdcBmp, 0, 0, SRCCOPY);
			InvalidateRect(hWnd, NULL, FALSE);
		}
	}
	//最后将所有的信息绘制到屏幕上
	BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, hdcBuffer, 0, 0, SRCCOPY);
	//回收资源所占的内存
	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	//结束绘制
	EndPaint(hWnd, &ps);
}


VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if(gamestart == 1&&gameover==0)
	{//TODO
	rou_bullet++;
	if(shine == 1)
	{
		planeshine++;
	}
	int i, k, tem;
	static int time = 0,difficulty = 0, preene = 0, planespeed = 2, preufo1 = 0, preufo2 = 0, preufo3 = 0, preufo4 = 0, ufo1_level = 1;
	static int fire = 0, prefire = 0, bossmove = 0, tracktime = 16;
	time++;
	//道具
	if((time%(ufo1_level*300+ufo1_level*100*ufo1_level)) == 0)
	{
		m_ufo1[preufo1] = Createufo((rand() % (WNDWIDTH - UFO1_SIZE_X) ),-UFO1_SIZE_Y-50,4,1);
		preufo1++;
	}
	if(ufo2_num>0)
	{
		if((time%(ufo2_num*200+ufo2_num*150*ufo2_num)) == 0)
		{
			m_ufo2[preufo2] = Createufo((rand() % (WNDWIDTH - UFO2_SIZE_X) ),-UFO2_SIZE_Y-50,4,2);
			preufo2++;
		}
	}
	else if((time % 500) == 0)
	{
		m_ufo2[preufo2] = Createufo((rand() % (WNDWIDTH - UFO2_SIZE_X) ),-UFO2_SIZE_Y-50,4,2);
		preufo2++;
	}
	if(isprotect == 0 &&(time%800) == 0)
	{
		m_ufo3[preufo3] = Createufo((rand() % (WNDWIDTH - UFO2_SIZE_X) ),-UFO2_SIZE_Y-50,4,3);
		preufo3++;
	}
	if((time%1000) == 0)
		{
			m_ufo4[preufo4] = Createufo((rand() % (WNDWIDTH - UFO2_SIZE_X) ),-UFO2_SIZE_Y-50,4,4);
			preufo4++;
	}
	for(i = 0;i<=preufo1;i++)
	{
		m_ufo1[i].pos.y = (m_ufo1[i].pos.y + m_ufo1[i].speed);
		if(crash(m_ufo1[i],m_heroPlane) == 1&&m_ufo1[i].life == 1)
		{
			m_ufo1[i] = m_ufo1[i+1];
			if(ufo1_level < 5)
			ufo1_level++;
			preufo1--;
		}
		if(m_ufo1[i].pos.y > WNDHEIGHT)
		{
			m_ufo1[i] = m_ufo1[i+1];
			preufo1--;
		}
	}
	for(i = 0;i<=preufo2-1;i++)
	{
		m_ufo2[i].pos.y = (m_ufo2[i].pos.y + m_ufo2[i].speed);
		if(crash(m_ufo2[i],m_heroPlane) == 1&&m_ufo2[i].life == 1)
		{
			m_ufo2[i]= m_ufo2[i+1];
			ufo2_num++;
			preufo2--;
		}
		if(m_ufo2[i].pos.y > WNDHEIGHT)
		{
			m_ufo2[i] = m_ufo2[i+1];
			preufo2--;
		}
	}
	for(i = 0;i<=preufo3-1;i++)
	{
		m_ufo3[i].pos.y = (m_ufo3[i].pos.y + m_ufo3[i].speed);
		if(crash(m_ufo3[i],m_heroPlane) == 1&&m_ufo3[i].life == 1)
		{
			m_ufo3[i]= m_ufo3[i+1];
			isprotect++;
			preufo3--;
		}
		if(m_ufo3[i].pos.y > WNDHEIGHT)
		{
			m_ufo3[i] = m_ufo3[i+1];
			preufo3--;
		}
	}
	for(i = 0;i<=preufo4-1;i++)
	{
		m_ufo4[i].pos.y = (m_ufo4[i].pos.y + m_ufo4[i].speed);
		if(crash(m_ufo4[i],m_heroPlane) == 1&&m_ufo4[i].life == 1)
		{
			m_ufo4[i]= m_ufo4[i+1];
			m_heroPlane.blood += 8;
			preufo4--;
		}
		if(m_ufo4[i].pos.y > WNDHEIGHT)
		{
			m_ufo4[i] = m_ufo4[i+1];
			preufo4--;
		}
	}
	if(isprotect >= 1)
	{
		isprotect++;
		if(isprotect >= 300)isprotect = 0;
	}
	//SIGN
	if(presign == round)
	{
		sign[presign - 1].pos.x += sign[presign - 1].speed;
		if(sign[presign - 1].pos.x >= WNDWIDTH + sign[i].size.cx)
		{
			sign[presign - 1].pos.y = 10000;
			presign++;
		}
	}
	//敌机
	if(isboss != 1)
	{
		if((time%20) == 0) 
		{
			m_enemyPlanes[preene] = CreateEnemyPlane((rand() % (WNDWIDTH - ENEMY_SMALL_SIZE_X) ),-ENEMY_SMALL_SIZE_Y, planespeed,0);
			preene++;
		}
		if((time%60) == 0)
		{
			m_enemyPlanes[preene] = CreateEnemyPlane((rand()%(WNDWIDTH - ENEMY_MIDDLE_SIZE_X)), -ENEMY_MIDDLE_SIZE_Y, planespeed,1);
			preene++;
		}
		if((time%500) == 0)
		{
			m_enemyPlanes[preene] = CreateEnemyPlane((rand()%(WNDWIDTH - ENEMY_BIG_SIZE_X)), -ENEMY_BIG_SIZE_Y,planespeed -1 ,2);
			preene++;
		}
	}
	//移动敌机
	for (i = 0; i < ENEMY_PLANE_NUM; i++)
	{
		m_enemyPlanes[i].pos.y = (m_enemyPlanes[i].pos.y + m_enemyPlanes[i].speed) % WNDHEIGHT;
	}
	//创建子弹
	if(rou_bullet == 1)
	{
		if(ufo1_level == 1)
		{
			m_hBullet[pre_bnum]= CreateBullet1(m_heroPlane.pos.x + 48, m_heroPlane.pos.y, 12, 1);
			pre_bnum++;
		}
		if(ufo1_level == 2)
		{
			m_hBullet[pre_bnum] = CreateBullet1(m_heroPlane.pos.x + 30, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 1] = CreateBullet1(m_heroPlane.pos.x + 63, m_heroPlane.pos.y, 12, 1);
			pre_bnum+=2;
		}
		if(ufo1_level == 3)
		{
			m_hBullet[pre_bnum] = CreateBullet1(m_heroPlane.pos.x + 25, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 1] = CreateBullet1(m_heroPlane.pos.x + 45, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 2] = CreateBullet1(m_heroPlane.pos.x + 65, m_heroPlane.pos.y, 12, 1);
			pre_bnum+=3;
		}
		if(ufo1_level == 4)
		{
			m_hBullet[pre_bnum] = CreateBullet1(m_heroPlane.pos.x + 25, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 1] = CreateBullet1(m_heroPlane.pos.x + 40, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 2] = CreateBullet1(m_heroPlane.pos.x + 55, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 3] = CreateBullet1(m_heroPlane.pos.x + 70, m_heroPlane.pos.y, 12, 1);
			pre_bnum+=4;
		}
		if(ufo1_level == 5)
		{
			m_hBullet[pre_bnum] = CreateBullet1(m_heroPlane.pos.x + 15, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 1] = CreateBullet1(m_heroPlane.pos.x + 30, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 2] = CreateBullet1(m_heroPlane.pos.x + 45, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 3] = CreateBullet1(m_heroPlane.pos.x + 60, m_heroPlane.pos.y, 12, 1);
			m_hBullet[pre_bnum + 4] = CreateBullet1(m_heroPlane.pos.x + 75, m_heroPlane.pos.y, 12, 1);
			pre_bnum+=5;
		}
		rou_bullet = -5;
	}
	//敌机子弹
	for(i=0;i<ENEMY_PLANE_NUM;i++)
	{
		if(m_enemyPlanes[i].life > 0)
		{
			switch(m_enemyPlanes[i].type)
			{
			case 0:
				if((time%800) == 0)
				{
					m_eneBullet[pre_enebullet] = CreateBullet1(m_enemyPlanes[i].pos.x, m_enemyPlanes[i].pos.y,6,2);
					pre_enebullet++;
				}
				break;
			case 1:
				if((time%600) == 0)
				{
				m_eneBullet[pre_enebullet] = CreateBullet1(m_enemyPlanes[i].pos.x, m_enemyPlanes[i].pos.y,6,2);
				pre_enebullet++;
				}
				break;
			case 2:
				if((time%500) == 0)
				{
					m_eneBullet[pre_enebullet] = CreateBullet1(m_enemyPlanes[i].pos.x, m_enemyPlanes[i].pos.y,6,2);
				pre_enebullet++;
				}
				break;
			default:
				break;
			}
		}
	}
	for(i=0;i<pre_enebullet;i++)
	{
		m_eneBullet[i].pos.y += m_eneBullet[i].speed;
		if(m_eneBullet[i].pos.y > WNDHEIGHT && m_eneBullet[i].life == 1)
		{
			for(tem=i;tem<pre_enebullet;tem++)
			{
				m_eneBullet[tem] = m_eneBullet[tem+1];
			}
			pre_enebullet--;
			i--;
		}
		if(crash(m_eneBullet[i],m_heroPlane) == 1 && m_eneBullet[i].life == 1)
		{
			if(shine == 0&&isprotect == 0)
				m_heroPlane.blood--;
			for(tem=i;tem<pre_enebullet;tem++)
			{
				m_eneBullet[tem] = m_eneBullet[tem+1];
			}
			pre_enebullet--;
			i--;
		}
	}
	//创建炸弹
	for(i = 0;i<=9;i++)
	{
		if(ufo22[i].life == 1)
		ufo22[i].pos.y -= ufo22[i].speed;
		if(ufo22[i].pos.y <= -UFO22_SIZE_Y)
		{
			ufo22[i].pos.y = 10000;
			ufo22[i].life = 0;
		}
		for(k = 0;k<ENEMY_PLANE_NUM;k++)
		{
			if(m_enemyPlanes[k].pos.y >= ufo22[i].pos.y && m_enemyPlanes[k].life > 0&&ufo22[i].life == 1)
					{
						m_enemyPlanes[k].blood = 0;
					}
		}
	} 
	//子弹与敌机碰撞
	for(i=0;i<=pre_bnum - 1;i++)
	{
		m_hBullet[i].pos.y -= (m_hBullet[i].speed);
			for(k=0;k<ENEMY_PLANE_NUM;k++)
			{
				if(crash(m_hBullet[i],m_enemyPlanes[k]) == 1 && m_enemyPlanes[k].life > 0)
				{
					m_enemyPlanes[k].blood--;
					for(tem=i;tem<pre_bnum;tem++)
					{
						m_hBullet[tem] = m_hBullet[tem+1];
					}
					pre_bnum--;
					i--;
				}
			}
			if(m_hBullet[i].pos.y < 0)
			{
				for(tem=i;tem<pre_bnum;tem++)
				{
					m_hBullet[tem] = m_hBullet[tem+1];
				}
				pre_bnum--;
				i--;
			}
	}
	//飞机间的碰撞
	for(i=0;i<ENEMY_PLANE_NUM;i++)
	{
		if(crash(m_enemyPlanes[i],m_heroPlane) == 1)
		{
			if(isprotect == 0&&shine == 0)
			m_heroPlane.blood = 0;
			m_enemyPlanes[i].blood = 0;
		}
	}
	if(m_heroPlane.blood <= 0 && m_heroPlane.life>0)
	{
		m_heroPlane.selfmove+=HERO_SIZE_Y;
		m_heroPlane.life--;
		if(m_heroPlane.life == 0)
		{
			m_heroPlane.pos.x = 1000;
		}
	}
	//hero重生
	if(herolife >= 1&&m_heroPlane.blood <= 0)
	{
		herolife--;
		m_heroPlane = CreateHeroPlane(WNDWIDTH / 2, WNDHEIGHT / 2, 5, 0);
		shine = 1;
	}
	else if(herolife == 0&&m_heroPlane.blood <= 0)
		gameover = 1;
	//判断敌机是否空血
	for(i=0;i<ENEMY_PLANE_NUM;i++)
	{
		if(m_enemyPlanes[i].life > 0)
		{
			switch(m_enemyPlanes[i].type)
			{
				case 0:
					if(m_enemyPlanes[i].blood <= 0)
					{
						m_enemyPlanes[i].selfmove += ENEMY_SMALL_SIZE_Y;
						m_enemyPlanes[i].life--;
						if(m_enemyPlanes[i].life == 0)
						{
							m_enemyPlanes[i].pos.x = 10000;
							if(isboss != 1)
							m_totalScore += 10;
						}
					}
					break;
				case 1:
					if(m_enemyPlanes[i].blood <= 0)
					{
						m_enemyPlanes[i].selfmove += ENEMY_MIDDLE_SIZE_Y;
						m_enemyPlanes[i].life--;
						if(m_enemyPlanes[i].life == 0)
						{
						m_enemyPlanes[i].pos.x = 10000;
						if(isboss != 1)
						m_totalScore += 50;
						}
					}
					break;
				case 2:
					if(m_enemyPlanes[i].blood <= 0)
					{
						m_enemyPlanes[i].selfmove += ENEMY_BIG_SIZE_Y;
						m_enemyPlanes[i].life--;
						if(m_enemyPlanes[i].life == 0)
						{
							m_enemyPlanes[i].pos.x = 10000;
							if(isboss != 1)
							m_totalScore += 150;
						}
					}
					break;
				default:
					break;
			
			}
		}	
	}
	//移动屏幕
	if(backgroudmove == 0)backgroudmove = WNDHEIGHT;
	backgroudmove = backgroudmove - 2;
	if(time == 10000)
		time = 0;
	if(preene == ENEMY_PLANE_NUM - 1)preene = 0;
	//增加难度
	if(m_totalScore >= 1200 && difficulty == 0&&isboss == 0)
	{
		prefire = 0;
		difficulty++;
		planespeed+=3;
		round++;
		goin = 0;
	}
	if(m_totalScore >= 3200 && difficulty == 1&&isboss== 0)
	{
		prefire = 0;
		difficulty++;
		planespeed+=1;
		round++;
		goin = 0;
	}
	if(m_totalScore >= 5200 && difficulty == 2&&isboss == 0)
	{
		prefire = 0;
		difficulty++;
		planespeed+=1;
		goin = 0;
	}
	//创建BOSS
	if(m_totalScore >= 900 && difficulty == 0 && isboss == 0)
	{
		boss[0] = Createboss();
		isboss = 1;
	}
	if(m_totalScore >= 2900 && difficulty == 1 && isboss == 0)
	{
		boss[1] = Createboss();
		isboss = 1;
	}
	if(m_totalScore >= 4900 && difficulty == 2 && isboss == 0)
	{
		boss[2] = Createboss();
		isboss = 1;
	}
	if(m_totalScore >= 5900 && difficulty == 3 && isboss == 0)
	{
		boss[3] = Createboss();
		isboss = 1;
	}
	//移动BOSS,1向左，0向右
	if(isboss == 1)
	{
		bossmove++;
			if(boss[round - 1].pos.y <= (boss[round - 1].size.cy - 50) && goin == 0)
				boss[round - 1].pos.y += boss[round - 1].speed;
			else goin = 1;
			if(goin == 1)
			{
				if(bossmove >= 20 && bossmove <= 200)
				{
					if(boss[round - 1].type == 1)
					boss[round - 1].pos.x += boss[round - 1].speed;
				else boss[round - 1].pos.x -= boss[round - 1].speed;
				if(boss[round - 1].pos.x >= WNDWIDTH - boss[round - 1].size.cx)boss[round - 1].type = 0;
				if(boss[round - 1].pos.x <= 0)boss[round - 1].type = 1;
				}
				if(bossmove >= 100 && bossmove <= 300)
				{
					if(boss[round - 1].type == 1)
						boss[round - 1].pos.y += boss[round - 1].speed;
					else boss[round - 1].pos.y -= boss[round - 1].speed;
					if(boss[round - 1].pos.y >= WNDHEIGHT - 600)boss[round - 1].type = 0;
					if(boss[round - 1].pos.y <= 0)boss[round - 1].type = 1;
				}
			}
	}
	//BOSS子弹
	if(isboss == 1)
	{
		
		if((time%16) == 0)
		{
			fire++;
		switch (round)
		{
		case 1:
			if(fire >= 1 && fire <= 30)
			{
				bossfire[prefire] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire].type = 1;
				bossfire[prefire + 1] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 10,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 1].type = 2;
				bossfire[prefire + 2] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2+ 10,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 2].type = 3;
				prefire += 3;
			}
			if(fire >= 32 && fire <= 60)
			{
				if((tracktime%3)==0)
				bossfire[prefire] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire].type = 4;
				bossfire[prefire + 1] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 20,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 1].type = 4;
				bossfire[prefire + 2] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2+ 20,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 2].type = 5;
				bossfire[prefire + 3] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 40,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 3].type = 4;
				bossfire[prefire + 4] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 + 40,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 4].type = 5;
				bossfire[prefire + 5] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 60,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 5].type = 4;
				bossfire[prefire + 6] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2+ 60,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 6].type = 5;
				bossfire[prefire + 7] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 20,boss[0].pos.y + boss[0].size.cy + 20);
				bossfire[prefire + 7].type = 4;
				bossfire[prefire + 8] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 + 20,boss[0].pos.y + boss[0].size.cy + 20);
				bossfire[prefire + 8].type = 5;
				bossfire[prefire + 9] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 40,boss[0].pos.y + boss[0].size.cy + 20);
				bossfire[prefire + 9].type = 4;
				bossfire[prefire + 10] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2+ 40,boss[0].pos.y + boss[0].size.cy + 20);
				bossfire[prefire + 10].type = 5;
				bossfire[prefire + 11] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 60,boss[0].pos.y + boss[0].size.cy + 20);
				bossfire[prefire + 11].type = 4;
				bossfire[prefire + 12] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 + 60,boss[0].pos.y + boss[0].size.cy + 20);
				bossfire[prefire + 12].type = 5;
				bossfire[prefire + 13] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 10 ,boss[0].pos.y + boss[0].size.cy + 20);
				bossfire[prefire + 13].type = 4;
				bossfire[prefire + 14] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 + 10,boss[0].pos.y + boss[0].size.cy + 20);
				bossfire[prefire + 14].type = 5;
				prefire += 15;
			}
			if(fire >=50 && fire <=70)
			{
				bossfire[prefire] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire].type = 0;
				bossfire[prefire + 1] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 20,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 1].type = 0;
				bossfire[prefire + 2] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 + 20,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 2].type = 0;
				bossfire[prefire + 3] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 - 40,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 3].type = 0;
				bossfire[prefire + 4] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2 + 40,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire + 4].type = 0;
				prefire += 5;
			}
			if(fire >= 72 && fire <= 99)
			{
				bossfire[prefire] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2,boss[0].pos.y + boss[0].size.cy);
				bossfire[prefire].type = 6;
				bossfire[prefire + 1] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2,boss[0].pos.y + boss[0].size.cy - 20);
				bossfire[prefire + 1].type = 6;
				bossfire[prefire + 2] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2,boss[0].pos.y + boss[0].size.cy - 40);
				bossfire[prefire + 2].type = 6;
				bossfire[prefire + 3] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2,boss[0].pos.y + boss[0].size.cy - 60);
				bossfire[prefire + 3].type = 6;
				bossfire[prefire + 4] = Createbossfire(boss[0].pos.x + boss[0].size.cx/2,boss[0].pos.y + boss[0].size.cy - 80);
				bossfire[prefire + 4].type = 6;
				prefire+=5;
			}
			break;
		case 2:
			if(fire >= 1 && fire <= 50)
			{
				bossfire[prefire] = Createbossfire(boss[1].pos.x + boss[1].size.cx/2,boss[1].pos.y + boss[1].size.cy);
				bossfire[prefire].type = 1;
				bossfire[prefire + 1] = Createbossfire(boss[1].pos.x + boss[1].size.cx/2 - 10,boss[1].pos.y + boss[1].size.cy);
				bossfire[prefire + 1].type = 2;
				bossfire[prefire + 2] = Createbossfire(boss[1].pos.x + boss[1].size.cx/2+ 10,boss[1].pos.y + boss[1].size.cy);
				bossfire[prefire + 2].type = 3;
				prefire += 3;
			}
			if(fire >=60 && fire <=100)
			{
				bossfire[prefire] = Createbossfire(boss[1].pos.x + boss[1].size.cx/2,boss[1].pos.y + boss[1].size.cy);
				bossfire[prefire].type = 0;
				bossfire[prefire + 1] = Createbossfire(boss[1].pos.x + boss[1].size.cx/2 - 20,boss[1].pos.y + boss[1].size.cy);
				bossfire[prefire + 1].type = 0;
				bossfire[prefire + 2] = Createbossfire(boss[1].pos.x + boss[1].size.cx/2 + 20,boss[1].pos.y + boss[1].size.cy);
				bossfire[prefire + 2].type = 0;
				bossfire[prefire + 3] = Createbossfire(boss[1].pos.x + boss[1].size.cx/2 - 40,boss[1].pos.y + boss[1].size.cy);
				bossfire[prefire + 3].type = 0;
				bossfire[prefire + 4] = Createbossfire(boss[1].pos.x + boss[1].size.cx/2 + 40,boss[1].pos.y + boss[1].size.cy);
				bossfire[prefire + 4].type = 0;
				prefire += 5;
			}
			break;
		case 3:
			if(fire >= 1 && fire <= 50)
			{
				bossfire[prefire] = Createbossfire(boss[2].pos.x + boss[2].size.cx/2,boss[2].pos.y + boss[2].size.cy);
				bossfire[prefire].type = 1;
				bossfire[prefire + 1] = Createbossfire(boss[2].pos.x + boss[2].size.cx/2 - 10,boss[2].pos.y + boss[2].size.cy);
				bossfire[prefire + 1].type = 2;
				bossfire[prefire + 2] = Createbossfire(boss[2].pos.x + boss[2].size.cx/2+ 10,boss[2].pos.y + boss[2].size.cy);
				bossfire[prefire + 2].type = 3;
				prefire += 3;
			}
			if(fire >=60 && fire <=100)
			{
				bossfire[prefire] = Createbossfire(boss[2].pos.x + boss[2].size.cx/2,boss[2].pos.y + boss[2].size.cy);
				bossfire[prefire].type = 0;
				bossfire[prefire + 1] = Createbossfire(boss[2].pos.x + boss[2].size.cx/2 - 20,boss[2].pos.y + boss[2].size.cy);
				bossfire[prefire + 1].type = 0;
				bossfire[prefire + 2] = Createbossfire(boss[2].pos.x + boss[2].size.cx/2 + 20,boss[2].pos.y + boss[2].size.cy);
				bossfire[prefire + 2].type = 0;
				bossfire[prefire + 3] = Createbossfire(boss[2].pos.x + boss[2].size.cx/2 - 40,boss[2].pos.y + boss[2].size.cy);
				bossfire[prefire + 3].type = 0;
				bossfire[prefire + 4] = Createbossfire(boss[2].pos.x + boss[2].size.cx/2 + 40,boss[2].pos.y + boss[2].size.cy);
				bossfire[prefire + 4].type = 0;
				prefire += 5;
			}
			break;
		case 4:
			if(fire >= 1 && fire <= 50)
			{
				bossfire[prefire] = Createbossfire(boss[3].pos.x + boss[3].size.cx/2,boss[3].pos.y + boss[3].size.cy);
				bossfire[prefire].type = 1;
				bossfire[prefire + 1] = Createbossfire(boss[3].pos.x + boss[3].size.cx/2 - 10,boss[3].pos.y + boss[3].size.cy);
				bossfire[prefire + 1].type = 2;
				bossfire[prefire + 2] = Createbossfire(boss[3].pos.x + boss[3].size.cx/2+ 10,boss[3].pos.y + boss[3].size.cy);
				bossfire[prefire + 2].type = 3;
				prefire += 3;
			}
			if(fire >=60 && fire <=100)
			{
				bossfire[prefire] = Createbossfire(boss[3].pos.x + boss[3].size.cx/2,boss[3].pos.y + boss[3].size.cy);
				bossfire[prefire].type = 0;
				bossfire[prefire + 1] = Createbossfire(boss[3].pos.x + boss[3].size.cx/2 - 20,boss[3].pos.y + boss[3].size.cy);
				bossfire[prefire + 1].type = 0;
				bossfire[prefire + 2] = Createbossfire(boss[3].pos.x + boss[3].size.cx/2 + 20,boss[3].pos.y + boss[3].size.cy);
				bossfire[prefire + 2].type = 0;
				bossfire[prefire + 3] = Createbossfire(boss[3].pos.x + boss[3].size.cx/2 - 40,boss[3].pos.y + boss[3].size.cy);
				bossfire[prefire + 3].type = 0;
				bossfire[prefire + 4] = Createbossfire(boss[3].pos.x + boss[3].size.cx/2 + 40,boss[3].pos.y + boss[3].size.cy);
				bossfire[prefire + 4].type = 0;
				prefire += 5;
			}
			
			break;
		default:
			break;
			}
	}
	}
	for(i=0;i<BOSS_FIRE;i++)
	{
		if(bossfire[i].type == 1 || bossfire[i].type == 0)
			bossfire[i].pos.y+=bossfire[i].speed;
		if(bossfire[i].type == 3)
		{
			bossfire[i].pos.y+=bossfire[i].speed;
			bossfire[i].pos.x+=bossfire[i].speed;
		}
		if(bossfire[i].type == 2)
		{
			bossfire[i].pos.y+=bossfire[i].speed;
			bossfire[i].pos.x-=bossfire[i].speed;
		}	
		if(bossfire[i].type == 4)
		{
			bossfire[i].pos.y+=2;
			bossfire[i].pos.x-=3;
		}
		else if(bossfire[i].type == 5)
		{
			bossfire[i].pos.y+=10;
			bossfire[i].pos.x+=3;
		}
		else if(bossfire[i].type == 6)
		{
			bossfire[i].pos.y+=20;
		}
	}
	if(isboss == 1)
	{
		for(i=0;i<prefire;i++)
		{
			if(crash(bossfire[i],m_heroPlane) == 1 && bossfire[i].life == 1)
			{
				if(shine == 0&&isprotect == 0)
					m_heroPlane.blood--;
				for(tem=i;tem<prefire;tem++)
				{
					bossfire[tem] = bossfire[tem + 1];
				}
				prefire--;
				i--;
			}
			if(bossfire[i].pos.x > WNDWIDTH || bossfire[i].pos.y > WNDHEIGHT)
			{
				for(tem=i;tem<prefire;tem++)
				{
					bossfire[tem] = bossfire[tem + 1];
				}
				prefire--;
				i--;
			}
		}
	}
	//KILL BOSS
	if(isboss == 1)
	{
		for(i=0;i<=pre_bnum - 1;i++)
		{
			if(crash(m_hBullet[i],boss[round - 1]))
			{
				boss[round - 1].blood--;
				for(tem=i;tem<pre_bnum;tem++)
				{
					m_hBullet[tem] = m_hBullet[tem+1];
				}
				pre_bnum--;
				i--;
			}
		}
	}
	if(boss[round - 1].blood <= 0)
	{
		switch (round)
		{
		case 1:
			boss[0].selfmove += BOSS1_SIZE_Y;
			break;
		case 2:
			boss[1].selfmove += BOSS2_SIZE_Y;
			break;
		case 3:
			boss[2].selfmove += BOSS3_SIZE_Y;
			break;
		case 4:
			boss[3].selfmove += BOSS4_SIZE_Y;
			break;
		default:
			break;
		}
		boss[round - 1].life--;
		if(boss[round - 1].life == 0)
		{
			boss[round - 1].pos.x = 10000;
			m_totalScore += 310;
			isboss = 0;
			goin = 0;
		}
	}
	if(isboss == 1)
	{
		if(crash(boss[round - 1], m_heroPlane)==1)
		{
			if(shine == 0&&isprotect == 0)
			m_heroPlane.blood = 0;
		}
	}
	if(m_heroPlane.blood >= 28)
	{
		m_heroPlane.blood = 20;
		herolife++;
	}
	if(fire >= 103)fire = 0;
	if(bossmove >= 350)bossmove = 0;
	InvalidateRect(hWnd, NULL, FALSE);
	}
}