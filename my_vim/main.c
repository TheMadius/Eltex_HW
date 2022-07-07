#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

void sig_winch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
  resizeterm(size.ws_row, size.ws_col);
}

int main () {
  WINDOW * wnd;
  
  initscr();
  signal(SIGWINCH, sig_winch);

  endwin();
  exit(EXIT_SUCCESS);
}