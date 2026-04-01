#include<raylib.h>

enum SCREEN_STATE
{
	MOVER;
	PINTAR;
};

SCREEN_STATE estado;

int main()
{

	InitWindow(1024, 720, "State");

	estado = mover;

	while(!WindowShouldClose())
	{
		BeginDrawing();

		EndDrawing();
	}


	CloseWindow();
	return 0;
}
