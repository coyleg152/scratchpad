// File: Scratchpad.c
#include "raylib.h"

#define FONT_FILE "ModeFont.png"

const int W_WIDTH = 640;
const int W_HEIGHT = 480;
const int FONT_SIZE = 16;
const Vector2 FONT_VEC = {FONT_SIZE, FONT_SIZE};


void draw_char(char key, Vector2 position, Texture2D * font)
{
  int index = key - 32;
  Rectangle source =
  {
    (index % 8) * FONT_SIZE,
    (index / 8) * FONT_SIZE,
    FONT_SIZE,
    FONT_SIZE
  };
  DrawRectangleV(position, FONT_VEC, BLACK);
  DrawTextureRec(*font, source, position, WHITE);
}


Vector2 move_up(Vector2 position)
{
  position.y -= FONT_SIZE;
  if (position.y < 0) position.y = (W_HEIGHT / FONT_SIZE - 1) * FONT_SIZE;
  return position;
}


Vector2 move_down(Vector2 position)
{
  position.y += FONT_SIZE;
  if (position.y + FONT_SIZE > W_HEIGHT) position.y = 0;
  return position;
}


Vector2 move_left(Vector2 position)
{
  position.x -= FONT_SIZE;
  if (position.x < 0)
  {
    position.x = (W_WIDTH / FONT_SIZE - 1) * FONT_SIZE;
    position = move_up(position);
  }
  return position;
}


Vector2 move_right(Vector2 position)
{
  position.x += FONT_SIZE;
  if (position.x + FONT_SIZE > W_WIDTH)
  {
    position.x = 0;
    position = move_down(position);
  }
  return position;
}


int main()
{
  const int T_FPS = 60;
  const int TAB_SIZE = 2;
  const int CURSOR_WIDTH = 1;

  Vector2 position = {0.0, 0.0};
  const Vector2 CURSOR_VEC = {CURSOR_WIDTH, FONT_SIZE};

  InitWindow(W_WIDTH, W_HEIGHT, "Scratchpad");
  SetTargetFPS(T_FPS);

  Texture2D font = LoadTexture(FONT_FILE);
  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();

  while (!WindowShouldClose())
  {
    BeginDrawing();
    DrawRectangleV(position, CURSOR_VEC, BLACK);

    if (IsKeyPressed(KEY_UP)) position = move_up(position);
    if (IsKeyPressed(KEY_DOWN)) position = move_down(position);
    if (IsKeyPressed(KEY_LEFT)) position = move_left(position);
    if (IsKeyPressed(KEY_RIGHT)) position = move_right(position);

    while (1)
    {
      char key = (char) GetCharPressed();
      if (key == 0) break;
      draw_char(key, position, &font);
      position = move_right(position);
    }

    if (IsKeyPressed(KEY_TAB))
    {
      for (int i = 0; i < TAB_SIZE; i++)
      {
        draw_char(' ', position, &font);
        position = move_right(position);
      }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
      position.x = 0;
      position = move_down(position);
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
      position = move_left(position);
      DrawRectangleV(position, FONT_VEC, BLACK);
    }

    DrawRectangleV(position, CURSOR_VEC, WHITE);
    EndDrawing();
  }

  UnloadTexture(font);
  CloseWindow();
  return 0;
}
