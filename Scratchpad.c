// File: Scratchpad.c
#include "raylib.h"

#define FONT_FILE "ModeFont.png"

const int FONT_SIZE = 16;
const int CHARS_PER_ROW = 40;
const int CHARS_PER_COL = 30;
const int W_WIDTH = CHARS_PER_ROW * FONT_SIZE;
const int W_HEIGHT = CHARS_PER_COL * FONT_SIZE;
const Vector2 FONT_VEC = {FONT_SIZE, FONT_SIZE};

typedef struct
{
  Vector2 pos;
  int x_idx;
  int y_idx;
}
cursor_t;


void move_up(cursor_t * cursor)
{
  cursor->pos.y -= FONT_SIZE;
  cursor->y_idx -= 1;
  if (cursor->pos.y < 0.0)
  {
    cursor->pos.y = (W_HEIGHT / FONT_SIZE - 1) * FONT_SIZE;
    cursor->y_idx = CHARS_PER_COL - 1;
  }
}


void move_down(cursor_t * cursor)
{
  cursor->pos.y += FONT_SIZE;
  cursor->y_idx += 1;
  if (cursor->pos.y + FONT_SIZE > W_HEIGHT)
  {
    cursor->pos.y = 0.0;
    cursor->y_idx = 0;
  }
}


void move_left(cursor_t * cursor)
{
  cursor->pos.x -= FONT_SIZE;
  cursor->x_idx -= 1;
  if (cursor->pos.x < 0.0)
  {
    cursor->pos.x = (W_WIDTH / FONT_SIZE - 1) * FONT_SIZE;
    cursor->x_idx = CHARS_PER_ROW - 1;
    move_up(cursor);
  }
}


void move_right(cursor_t * cursor)
{
  cursor->pos.x += FONT_SIZE;
  cursor->x_idx += 1;
  if (cursor->pos.x + FONT_SIZE > W_WIDTH)
  {
    cursor->pos.x = 0.0;
    cursor->x_idx = 0;
    move_down(cursor);
  }
}


int main()
{
  const int T_FPS = 30;
  const int TAB_SIZE = 2;
  const int CURSOR_WIDTH = 1;
  const Vector2 CURSOR_VEC = {CURSOR_WIDTH, FONT_SIZE};

  cursor_t cursor =
  {
    .pos = {0.0, 0.0},
    .x_idx = 0,
    .y_idx = 0
  };

  char written_text[CHARS_PER_COL][CHARS_PER_ROW + 2];
  for (int i = 0; i < CHARS_PER_COL; i++)
  {
    for (int j = 0; j < CHARS_PER_ROW; j++) written_text[i][j] = ' ';
    written_text[i][CHARS_PER_ROW] = '\n';
    written_text[i][CHARS_PER_ROW + 1] = '\0';
  }

  InitWindow(W_WIDTH, W_HEIGHT, "Scratchpad");
  SetTargetFPS(T_FPS);

  Texture2D font = LoadTexture(FONT_FILE);

  while (!WindowShouldClose())
  {
    if (IsKeyPressed(KEY_UP)) move_up(&cursor);
    if (IsKeyPressed(KEY_DOWN)) move_down(&cursor);
    if (IsKeyPressed(KEY_LEFT)) move_left(&cursor);
    if (IsKeyPressed(KEY_RIGHT)) move_right(&cursor);

    while (1)
    {
      char key = (char) GetCharPressed();
      if (key == 0) break;
      written_text[cursor.y_idx][cursor.x_idx] = key;
      move_right(&cursor);
    }

    if (IsKeyPressed(KEY_TAB))
    {
      for (int i = 0; i < TAB_SIZE; i++)
      {
        written_text[cursor.y_idx][cursor.x_idx] = ' ';
        move_right(&cursor);
      }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
      cursor.pos.x = 0.0;
      cursor.x_idx = 0;
      move_down(&cursor);
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
      move_left(&cursor);
      written_text[cursor.y_idx][cursor.x_idx] = ' ';
    }

    BeginDrawing();
    ClearBackground(BLACK);
    Vector2 draw_pos = {0.0, 0.0};
    Rectangle source = {0.0, 0.0, FONT_SIZE, FONT_SIZE};

    for (int i = 0; i < CHARS_PER_COL; i++)
    {
      for (int j = 0; j < CHARS_PER_ROW; j++)
      {
        int index = written_text[i][j] - 32;
        source.x = (index % 8) * FONT_SIZE;
        source.y = (index / 8) * FONT_SIZE;
        DrawTextureRec(font, source, draw_pos, WHITE);
        draw_pos.x += FONT_SIZE;
      }
      draw_pos.x = 0;
      draw_pos.y += FONT_SIZE;
    }

    DrawRectangleV(cursor.pos, CURSOR_VEC, WHITE);
    EndDrawing();
  }

  UnloadTexture(font);
  CloseWindow();
  return 0;
}
