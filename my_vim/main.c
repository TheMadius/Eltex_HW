#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

#define TRUE 1

void mouse_click(void) {
  MEVENT event;
  getmouse(&event);
  move(event.y, event.x);
}

void muve_new_line(WINDOW *win) {
  int x, y, dy = 1;
  getyx(win, y, x);
  wmove(win, y + 1, 0);
}

void muve_cursor(WINDOW *win, int dx, int dy) {
  int x, y;
  getyx(win, y, x);
  move(y + dy, x + dx);
}

void sig_winch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
  resizeterm(size.ws_row, size.ws_col);
  nodelay(stdscr, 1);
  while (wgetch(stdscr) != ERR);
  nodelay(stdscr, 0);
}

void wfileOpen(WINDOW *win, const char *name_file) {
  FILE *file = fopen(name_file, "r+");
  char c;

  while ((c = fgetc(file)) != EOF) {
    addch(c);
  }

  wmove(win, 0, 0);

  wrefresh(win);
  fclose(file);
}

int main(int argc, char ** argv) {
  initscr();
  signal(SIGWINCH, sig_winch);
  keypad(stdscr, 1);
  mousemask(BUTTON1_CLICKED, NULL);

  if (argc == 2) {
    wfileOpen(stdscr, argv[1]);
  }

  refresh();

  while (TRUE) {
      int press_key = wgetch(stdscr);

      switch (press_key) {
      case KEY_MOUSE:
        mouse_click();
        break;
      case KEY_UP:
        muve_cursor(stdscr, 0, -1);
        break;
      case KEY_DOWN:
        muve_cursor(stdscr, 0, 1);
        break;
      case KEY_LEFT:
        muve_cursor(stdscr, -1, 0);
        break;
      case KEY_RIGHT:
        muve_cursor(stdscr, 1, 0);
        break;
      case '\n':
        muve_new_line(stdscr);
        break;
      }
  }
  
  endwin();
  exit(EXIT_SUCCESS);
}
