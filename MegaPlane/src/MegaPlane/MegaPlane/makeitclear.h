#include "MegaPlane.h"
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
//创建子弹
Plane CreateBullet1(LONG x, LONG y, int speed, int type)
{
	Plane bullet;
	bullet.pos.x = x ;
	bullet.pos.y = y ;
	bullet.type = type;
	bullet.speed = speed;
	switch (type)
	{
	case 1:
		bullet.hBmp = m_hBullet1Bmp;
		break;
	case 2:
		bullet.life = 1;
		bullet.hBmp = m_eneBulletBmp;
		break;
	default:
		break;
	}
	bullet.size.cx = 9;
	bullet.size.cy = 21;
	return bullet;
}
//创建Hero飞机
Plane CreateHeroPlane(LONG x, LONG y, int speed, int type)
{
	Plane plane;
	plane.hBmp = m_hHeroBmp;
	plane.pos.x = x;
	plane.pos.y = y;
	plane.speed = speed;
	plane.type = type;
	plane.blood = 20;
	plane.life = 5;
	plane.selfmove = 0;
	plane.size.cx = HERO_SIZE_X;
	plane.size.cy = HERO_SIZE_Y;
	return plane;
}
//创建道具
Plane Createufo(LONG x, LONG y, int speed, int type)
{
	Plane ufo;
	ufo.speed = speed;
	ufo.pos.x = x;
	ufo.pos.y = y;
	ufo.life = 1;
	switch (type)
	{
	case 1:
		ufo.hBmp = m_ufo1Bmp;
		ufo.size.cx = UFO1_SIZE_X;
		ufo.size.cy = UFO1_SIZE_Y;
		break;
	case 2:
		ufo.hBmp = m_ufo2Bmp;
		ufo.size.cx = UFO2_SIZE_X;
		ufo.size.cy = UFO2_SIZE_Y;
		break;
	case 3:
		ufo.hBmp = m_ufo3Bmp;
		ufo.size.cx = 80;
		ufo.size.cy = 80;
		break;
	case 4:
		ufo.hBmp = m_ufo4Bmp;
		ufo.size.cx = 60;
		ufo.size.cy = 60;
		break;
	default:
		break;
	}
	return ufo;
}
//创建敌机
Plane CreateEnemyPlane(LONG x, LONG y,int speed, int type)
{
	Plane plane;
	plane.pos.x = x;
	plane.pos.y = y;
	plane.speed = speed;
	plane.type = type;
	plane.selfmove = 0;
	switch (type)
	{
	case 0:
		plane.size.cx = ENEMY_SMALL_SIZE_X;
		plane.size.cy = ENEMY_SMALL_SIZE_Y;
		if(round == 1)
		{
		    plane.blood = 1;
			plane.hBmp = m_hEnemyBmp[type];
		}
		else if(round == 2)
		{
		    plane.blood = 2;
			plane.hBmp = m_hEnemyBmp2[type];
		}
		else if(round == 3)
		{
			plane.blood = 3;
			plane.hBmp = m_hEnemyBmp3[type];
		}
		else if(round == 4)
		{
			plane.blood = 4;
			plane.hBmp = m_hEnemyBmp4[type];
		}
		plane.life = 4;
		break;
	case 1:
		plane.size.cx = ENEMY_MIDDLE_SIZE_X;
		plane.size.cy = ENEMY_MIDDLE_SIZE_Y;
		if(round == 1)
		{
			plane.blood = 7;
			plane.hBmp = m_hEnemyBmp[type];
		}
		else if(round == 2)
		{
			plane.blood = 10;
			plane.hBmp = m_hEnemyBmp2[type];
		}
		else if(round == 3)
		{
			plane.hBmp = m_hEnemyBmp3[type];
			plane.blood = 13;
		}
		else if(round == 4)
		{
			plane.blood = 15;
			plane.hBmp = m_hEnemyBmp4[type];
		}
		plane.life = 6;
		break;
	case 2:
		plane.size.cx = ENEMY_BIG_SIZE_X;
		plane.size.cy = ENEMY_BIG_SIZE_Y;
		if(round == 1)
		{
			plane.blood = 40;
			plane.hBmp = m_hEnemyBmp[type];
		}
		else if(round == 2)
		{
			plane.blood = 55;
			plane.hBmp = m_hEnemyBmp2[type];
		}
		else if(round == 3)
		{
			plane.blood = 70;
			plane.hBmp = m_hEnemyBmp3[type];
		}
		else if(round == 4)
		{
			plane.blood = 85;
			plane.hBmp = m_hEnemyBmp4[type];
		}
		plane.life = 9;
		break;
	default:
		break;
	}
	return plane;
}
//SIGN
Plane Createsign(int i)
{
	Plane sign;
	sign.hBmp = signBmp[i];
	sign.size.cx = 450;
	sign.size.cy = 150;
	sign.speed = 5;
	sign.pos.x = -450;
	sign.pos.y = WNDHEIGHT/2 - 100;
	sign.selfmove = 0;
	return sign;
}
//BOSS
Plane Createboss()
{
	Plane boss;
	boss.pos.x = WNDWIDTH/2;
	boss.selfmove = 0;
	switch(round)
	{
	case 1:
		boss.blood = 500;
		boss.pos.y = -BOSS1_SIZE_Y;
		boss.life = 6;
		boss.hBmp = bossBmp[0];
		boss.speed = 4;
		boss.size.cx = BOSS1_SIZE_X;
		boss.size.cy = BOSS1_SIZE_Y;
		boss.type = 1;
		break;
	case 2:
		boss.blood = 600;
		boss.pos.y = -BOSS2_SIZE_Y;
		boss.life = 3;
		boss.hBmp = bossBmp[1];
		boss.speed = 4;
		boss.size.cx = BOSS2_SIZE_X;
		boss.size.cy = BOSS2_SIZE_Y;
		boss.type = 0;
		break;
	case 3:
		boss.blood = 1000;
		boss.pos.y = -BOSS3_SIZE_Y;
		boss.life = 2;
		boss.hBmp = bossBmp[2];
		boss.speed = 2;
		boss.size.cx = BOSS3_SIZE_X;
		boss.size.cy = BOSS3_SIZE_Y;
		boss.type = 1;
		break;
	case 4:
		boss.blood = 900;
		boss.pos.y = -BOSS4_SIZE_Y;
		boss.life = 5;
		boss.hBmp = bossBmp[3];
		boss.speed = 5;
		boss.size.cx = BOSS4_SIZE_X;
		boss.size.cy = BOSS4_SIZE_Y;
		boss.type = 0;
		break;
	default:
		break;
	}
	return boss;
}
Plane Createbossfire(LONG x, LONG y)
{
	Plane bossfire;
	bossfire.pos.x = x;
	bossfire.pos.y = y;
	bossfire.speed = 6;
	bossfire.hBmp = bossfireBmp;
	bossfire.size.cx = 13;
	bossfire.size.cy = 13;
	bossfire.life = 1;
	return bossfire;
}
//暂停
BOOL Paused(POINT ptMouse)
{
	RECT rPause;

	rPause.left = 0;
	rPause.top = 0;
	rPause.right = m_gameStatus.size.cx;
	rPause.bottom = m_gameStatus.size.cy;

	return PtInRect(&rPause, ptMouse);
}
//键盘
VOID KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//TODO
	switch (wParam)
	{
	case VK_LEFT:
		if(m_heroPlane.pos.x != 0 && ispause == 0)
			m_heroPlane.pos.x =(m_heroPlane.pos.x + WNDWIDTH - m_heroPlane.speed) % WNDWIDTH;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case VK_RIGHT:
		if(m_heroPlane.pos.x != 370 && ispause == 0)
			m_heroPlane.pos.x = (m_heroPlane.pos.x + WNDWIDTH + m_heroPlane.speed) % WNDWIDTH;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case VK_UP:
		if(m_heroPlane.pos.y != 0&& ispause == 0)
			m_heroPlane.pos.y = (m_heroPlane.pos.y + WNDHEIGHT - m_heroPlane.speed) % WNDHEIGHT;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case VK_DOWN:
		if(m_heroPlane.pos.y != 630 && ispause == 0)
			m_heroPlane.pos.y = (m_heroPlane.pos.y + WNDHEIGHT + m_heroPlane.speed) % WNDHEIGHT;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case VK_SPACE:
		if(ufo2_num > 0 && ispause == 0)
		{
			ufo2_num--;
			ufo22[pre_ufo22] = Createufo22();
			ufo22[pre_ufo22].life = 1;
			pre_ufo22++;
			if(pre_ufo22 == 10)pre_ufo22 = 0;
			if(isboss == 1)
			boss[round - 1].blood -= 100;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case VK_RETURN:
		gamestart = 1;
		ishelp = 0;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case VK_F1:
		if(gamestart == 0)
		ishelp = 1;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case VK_F2:
		ufo2_num+=10;
		break;
	case VK_F3:
		herolife+=3;
		break;
	default:
		break;
	}
}
//鼠标
VOID LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	POINT ptMouse;
	ptMouse.x = LOWORD(lParam);
	ptMouse.y = HIWORD(lParam);

	//如果点击了继续或暂停图标
	if (Paused(ptMouse))
	{
		if (!m_gameStatus.isPaused)
		{
			KillTimer(hWnd, TIMER);
			m_gameStatus.isPaused = TRUE;
			ispause = 1;
		}
		else
		{
			SetTimer(hWnd, TIMER, 50, NULL);
			m_gameStatus.isPaused = FALSE;
			ispause = 0;
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}
}


