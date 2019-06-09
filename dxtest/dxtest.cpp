#include "DxLib.h"
#include <math.h>

#define PI 3.141592654f

int Key[256];

int gpUpdateKey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}

	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	
	
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);



	int Handle[3];
	Handle[0] = LoadGraph("image/mychar.png");
	Handle[1] = LoadGraph("image/charkick.png");
	Handle[2] = LoadGraph("image/my_back.png");
	int id=0;
	int x = 70;
	int y = 400;
	int Count = 60;
	int fb=0;
	int jud =0;
	while (gpUpdateKey() == 0) {
		

		ProcessMessage();
		ClearDrawScreen();
		DrawRotaGraph(x, y +( sin(PI * 2 / 120 * Count) * 200), 1.0, 0.0, Handle[id], TRUE);
		
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
		else if (ProcessMessage() != 0) {
			break;
		}

		if (Key[KEY_INPUT_RIGHT] >= 1) {
			
			if(x<571)x+=3;
			id = 0;
			fb = 0;
		}

		if (Key[KEY_INPUT_LEFT] >= 1) {
			if(x>69)x-=3;
			id = 2;
			fb = 2;
		}

		if (Key[KEY_INPUT_UP] >= 1&&jud==0) {
			jud = 60;
			
		}
		if (jud != 0&&Count<121) {
			jud--;
			Count++;
		}
		if (jud == 0) {
			Count = 60;
			id = fb;
		}
		if (Key[KEY_INPUT_K] >= 1)id = 1;

		
		
	
		ScreenFlip();
	}
	DxLib_End();

	return 0;
}