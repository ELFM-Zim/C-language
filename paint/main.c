#include <raylib.h>
#include <stdio.h>

#define WINDOW_SIZE 500

typedef struct PixelPosition
{
	Vector2 position;
	Color color;
} PixelPosition;

typedef struct Quadro
{
	PixelPosition position[WINDOW_SIZE*WINDOW_SIZE];
	int counter;
	Color cor_padrao;
} Quadro;

int main(int argc, char* argv[])
{
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Pincel");
    SetTargetFPS(60);
	
	Quadro quadro;
	quadro.counter = 0;
    quadro.cor_padrao = BLUE;
	Texture2D pincel = LoadTexture("/home/ell/programming/paint/pincel.png");

	Rectangle rec = {0, 0, (float)(pincel.width), pincel.height};

    while(!WindowShouldClose())
    {
		if(IsKeyPressed(KEY_ONE)) quadro.cor_padrao = BLUE;
		if(IsKeyPressed(KEY_TWO)) quadro.cor_padrao = GREEN;
		if(IsKeyPressed(KEY_THREE)) quadro.cor_padrao = PINK;
		if(IsKeyPressed(KEY_FOUR)) quadro.cor_padrao = PURPLE;
		if(IsKeyPressed(KEY_FIVE)) quadro.cor_padrao = GOLD;
		if(IsKeyPressed(KEY_SIX)) quadro.cor_padrao = VIOLET;
		if(IsKeyPressed(KEY_ZERO)) quadro.cor_padrao = RED;	
		quadro.position[quadro.counter].color = quadro.cor_padrao;

			if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && quadro.counter != WINDOW_SIZE*WINDOW_SIZE)
			{
				Vector2 posAUX = GetMousePosition();
				
				Image screencapture = LoadImageFromScreen(); 
				Color pixelcolor = GetImageColor(screencapture, posAUX.x, posAUX.y);
				UnloadImage(screencapture);
								
				if(!ColorIsEqual(pixelcolor, quadro.position[quadro.counter].color))
					
				{
					quadro.position[quadro.counter].position = posAUX;
					quadro.counter++;
				}
		}
		
		
	
		BeginDrawing();
			ClearBackground(RED);	
			DrawTextureRec(pincel, rec, (Vector2){0, 0}, WHITE);	
			DrawText("Pintar", 100, 100, 10, GREEN);	
			for(int i = 0; i < quadro.counter; i++)
			{
				printf("%i\n", i);
				DrawPixelV(quadro.position[i].position, quadro.position[i].color);
			}	
		EndDrawing();

	}
    CloseWindow();
	UnloadTexture(pincel);
    return 0;
}
