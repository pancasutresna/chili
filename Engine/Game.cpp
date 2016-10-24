/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		x_mobile -= 1;
	} 


	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		x_mobile += 1;
	}

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		y_mobile -= 1;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		y_mobile += 1;
	}

	x_mobile = ClampScreenX(x_mobile);
	y_mobile = ClampScreenY(y_mobile);

	colliding = OverlapTest(x_mobile, y_mobile, x_fixed0, y_fixed0) || 
				OverlapTest(x_mobile, y_mobile, x_fixed1, y_fixed1) ||
				OverlapTest(x_mobile, y_mobile, x_fixed2, y_fixed2) ||
				OverlapTest(x_mobile, y_mobile, x_fixed3, y_fixed3);
}

void Game::ComposeFrame()
{
	DrawBox(x_fixed0, y_fixed0, 0, 255, 0);
	DrawBox(x_fixed1, y_fixed1, 0, 255, 0);
	DrawBox(x_fixed2, y_fixed2, 0, 255, 0);
	DrawBox(x_fixed3, y_fixed3, 0, 255, 0);

	if ( colliding )
	{
		DrawBox(x_mobile, y_mobile, 255, 0, 0);
	} 
	else
	{
		DrawBox(x_mobile, y_mobile, 255, 255, 255);
	}
}

void Game::DrawBox(int x, int y, int r, int g, int b)
{
	gfx.PutPixel(-5 + x, -5 + y, r, g, b);
	gfx.PutPixel(-4 + x, -5 + y, r, g, b);
	gfx.PutPixel(-3 + x, -5 + y, r, g, b);
	gfx.PutPixel(3 + x, -5 + y, r, g, b);
	gfx.PutPixel(4 + x, -5 + y, r, g, b);
	gfx.PutPixel(5 + x, -5 + y, r, g, b);

	gfx.PutPixel(-5 + x, -5 + y, r, g, b);
	gfx.PutPixel(-5 + x, -4 + y, r, g, b);
	gfx.PutPixel(-5 + x, -3 + y, r, g, b);
	gfx.PutPixel(5 + x, -5 + y, r, g, b);
	gfx.PutPixel(5 + x, -4 + y, r, g, b);
	gfx.PutPixel(5 + x, -3 + y, r, g, b);

	gfx.PutPixel(-5 + x, 5 + y, r, g, b);
	gfx.PutPixel(-4 + x, 5 + y, r, g, b);
	gfx.PutPixel(-3 + x, 5 + y, r, g, b);
	gfx.PutPixel(3 + x, 5 + y, r, g, b);
	gfx.PutPixel(4 + x, 5 + y, r, g, b);
	gfx.PutPixel(5 + x, 5 + y, r, g, b);

	gfx.PutPixel(-5 + x, 3 + y, r, g, b);
	gfx.PutPixel(-5 + x, 4 + y, r, g, b);
	gfx.PutPixel(-5 + x, 5 + y, r, g, b);
	gfx.PutPixel(5 + x, 3 + y, r, g, b);
	gfx.PutPixel(5 + x, 4 + y, r, g, b);
	gfx.PutPixel(5 + x, 5 + y, r, g, b);
}

bool Game::OverlapTest(int box0x, int box0y, int box1x, int box1y)
{
	const int left_mobile = box0x - 5;
	const int right_mobile = box0x + 5;
	const int top_mobile = box0y - 5;
	const int bottom_mobile = box0y + 5;

	const int left_fixed = box1x - 5;
	const int right_fixed = box1x + 5;
	const int top_fixed = box1y - 5;
	const int bottom_fixed = box1y + 5;
	
	return	left_mobile <= right_fixed && 
			right_mobile >= left_fixed &&
			top_mobile <= bottom_fixed && 
			bottom_mobile >= top_fixed;
}

int Game::ClampScreenX(int x)
{
	const int left = x - 5;
	const int right = x + 5;

	if (right >= gfx.ScreenWidth)
	{
		return gfx.ScreenWidth - 6;
	}
	else if (left <= 0)
	{
		return 6;
	}
	else
	{
		return x;
	}
}

int Game::ClampScreenY(int y)
{
	const int top = y - 5;
	const int bottom = y + 5;

	if (bottom >= gfx.ScreenHeight)
	{
		return gfx.ScreenHeight - 6;
	} 
	else if (top <= 0)
	{
		y = 6;
	}
	else
	{
		return y;
	}
}