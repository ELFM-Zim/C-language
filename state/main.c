#include<raylib.h>
#include<string.h>

enum SCREEN_STATE
{
	MOVER,
	PARAR
};

enum SCREEN_STATE estado;

int main()
{

	InitWindow(1024, 720, "State");
	char state[6];
	estado = MOVER;
	float speed = 0.1;
	Vector2 rec_pos = {100, 100};
	while(!WindowShouldClose())
	{

		if(IsKeyPressed(KEY_ONE)) estado = MOVER;
		if(IsKeyPressed(KEY_TWO)) estado = PARAR;
		if(estado == MOVER)
		{
			
			if(IsKeyDown(KEY_UP)) rec_pos.y -= 1 * speed;
			if(IsKeyDown(KEY_DOWN)) rec_pos.y += 1 * speed;
			if(IsKeyDown(KEY_LEFT)) rec_pos.x -= 1 * speed;
			if(IsKeyDown(KEY_RIGHT)) rec_pos.x += 1 * speed;
			strcpy(state, "Mover");	
		}
		else if(estado == PARAR)
		{
			strcpy(state, "Parar");
		}

		BeginDrawing();
		ClearBackground(PINK);
		DrawText(state, 2, 2, 24, BLACK);
		DrawRectangleV(rec_pos, (Vector2){30,30}, RED);
		EndDrawing();
	}


	CloseWindow();
	return 0;
}
