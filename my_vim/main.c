#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TRUE 1

char *readfile(const char *name_file);
int splitString(char ***split_text, char *string, char separator);
void addTextInWin(WINDOW *win, int line, char *text);
int muve_cursor(WINDOW *win, int dx, int dy);
int changeText(char **string, int pos, char new_char);
int saveInFile(char *namefile, char **text, int count_line);
void updateWin(WINDOW *win, char **text, int count, int start_line);

void sig_winch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
  resizeterm(size.ws_row, size.ws_col);
}

int main(int argc, char ** argv) {
  int this_x = 0, this_y = 0;
  int size_win_x, size_win_y;
  char **line_text = NULL;
  char *namefile = NULL;
  int line_term = 0;
  int line = 0;

  WINDOW *mainwin;
  mainwin = initscr();
  signal(SIGWINCH, sig_winch);
  idlok (mainwin, TRUE);
  keypad (mainwin, TRUE);
  scrollok(mainwin, TRUE);

  size_win_y = getmaxy(mainwin);
  size_win_x = getmaxx(mainwin);

  if (argc == 2) {
    char *text = NULL;
    text = readfile(argv[1]);
    if (text != NULL) {
      namefile = argv[1];
      line = splitString(&line_text, text, '\n');
      free(text);
      updateWin(mainwin, line_text, line, 0);
    }
  } else {
    line = 1;
    line_text = malloc(sizeof(char*) * line);
    line_text[line - 1] = malloc(sizeof(char));
    line_text[line - 1][0] = '\0';
  }

  move(0, 0);
  refresh();

  while (TRUE) {
    int press_key = wgetch(mainwin);
    int exit = 0;
      switch (press_key) {
        case KEY_UP: {
          this_y--;
          line_term--;
          if (this_y < 0) {
            this_y++;
            line_term++;
          } else if (muve_cursor(mainwin, 0, -1)) {
            line_term = 0;
            addTextInWin(mainwin, line_term, line_text[this_y]);
            wmove(mainwin, line_term, this_x);
          }
          break;
        }
        case KEY_DOWN: {
          this_y++;
          line_term++;
          if (this_y > (line - 1)) {
            this_y--;
            line_term--;
          } else if (muve_cursor(mainwin, 0, 1)) {
            line_term = size_win_y - 1;
            addTextInWin(mainwin, line_term, line_text[this_y]);
            wmove(mainwin, line_term, this_x);
          }
          break;
        }
        case KEY_LEFT:{
          this_x--;
          muve_cursor(mainwin, -1, 0);
          break;
        }
        case KEY_RIGHT: {
          this_x++;
          muve_cursor(mainwin, 1, 0);
          break;
        }
        case KEY_F(1): {
          if(namefile) {
            saveInFile(namefile, line_text, line);
          } else {
            char namefile[20];
            wscrl(mainwin, 2);
            wmove(mainwin, size_win_y - 2, 0);
            wprintw(mainwin ,"Enter name file:");
            wmove(mainwin, size_win_y - 1, 0);
            wgetnstr(mainwin, namefile, 20);
            saveInFile(namefile, line_text, line);
          }
          goto finally;
        }
        case KEY_F(2): {
          goto finally;
        }
        case '\n': {
          this_y++;
          this_x = 0;
          line_term++;
          if (this_y > (line - 1)) {
            line++;
            line_text = realloc(line_text, sizeof(char*) * line);
            line_text[line - 1] = malloc(sizeof(char*));
            line_text[line - 1][0] = '\0';
          }
          if (muve_cursor(mainwin, 0, 1)) {
            line_term = size_win_y - 1;
            addTextInWin(mainwin, line_term, line_text[this_y]);
            wmove(mainwin, line_term, this_x);
          }
          break;
        }
        default: {
          if (press_key > 0 && press_key < 255) {
            changeText(&(line_text[this_y]), this_x, press_key);
            this_x++;
          }
          wmove(mainwin, line_term, this_x);
          break;
        }
      }

    refresh();
  }
finally:

  for (int i = 0; i < line; i++) {
    free(line_text[i]);
  }
  free(line_text);

  endwin();
  exit(EXIT_SUCCESS);
}

void updateWin(WINDOW *win, char **text, int count, int start_line) {
  int max_x, max_y;
  wclear(win);

  max_y = getmaxy(win);
  max_x = getmaxx(win);

  for(int i = 0; (i < max_y) && (i < count); i++) {
    addTextInWin(win, i, text[start_line + i]);
   }
  wrefresh(win);
}

int saveInFile(char *namefile, char **text, int count_line) {
  int fd;

  fd = open(namefile, O_RDWR | O_TRUNC | O_CREAT, S_IREAD | S_IWRITE);
  for (int i = 0; i < count_line; i++) {
    int size_string = strlen(text[i]);
    write(fd, text[i], size_string);
    if (i != count_line -1) {
      write(fd, "\n", sizeof(char));
    }
  }
}

char *readfile(const char *name_file) {
  int size_file;
  char *buff = NULL;
  int error;
  int fd;

  fd = open(name_file, O_RDWR);
  size_file = lseek(fd, 0, SEEK_END);

  if (size_file < 0) {
    perror("Error");
    return NULL;
  }

  error = lseek(fd, 0, SEEK_SET);
  if (error < 0) {
    perror("Error");
    return NULL;
  }

  buff = malloc(sizeof(*buff) * (size_file + 1));
  error = read(fd, buff, size_file);
  if (error < 0) {
    perror("Error");
    return NULL;
  }
  buff[size_file] = '\0';

  close(fd);
  return buff;
}

int splitString(char ***split_text, char *string, char separator) {
  if (string == NULL) {
    return -1;
  }

  int size = strlen(string);
  int count = 1;
  int len = 1;

  (*split_text) = malloc(sizeof(char *) * count);
  (*split_text)[count - 1] = malloc(sizeof(char) * len);
  (*split_text)[count - 1][len - 1] = '\0';

  for (int i = 0; i < size; i++) {
    if (string[i] == separator) {
      (*split_text)[count - 1][len - 1] = '\0';

      count++;
      (*split_text) = realloc(*split_text, sizeof(char *) * count);

      len = 1;
      (*split_text)[count - 1] = malloc(sizeof(char) * len);
      (*split_text)[count - 1][len - 1] = '\0';

    } else {
      len++;
      (*split_text)[count - 1] = realloc((*split_text)[count - 1], sizeof(char) * len);
      (*split_text)[count - 1][len - 2] = string[i];
    }
  }

  (*split_text) = realloc(*split_text, sizeof(char *) * (count + 1));
  (*split_text)[count] = (char *)NULL;

  return count;
}

void addTextInWin(WINDOW *win, int line, char *text) {
  int x, y;
  int len = strlen(text);

  wmove(win, line, 0);

  for(int i = 0; i < len; ++i) {
    waddch(win, text[i]);
  }

  wrefresh(win);
}

int muve_cursor(WINDOW *win, int dx, int dy) {
  int x, y;
  int new_line = 0;
  int max_x, max_y;

  max_y = getmaxy(win);
  max_x = getmaxx(win);

  getyx(win, y, x);
  x += dx;
  y += dy;

  if (y > (max_y - 1)) {
    wscrl(win, 1);
    new_line = 1;
  } else if (y < 0) {
    wscrl(win, -1);
    new_line = -1;
  } else {
    wmove(win, y, x);
  }

  wrefresh(win);
  return new_line;
}

int changeText(char **string, int pos, char new_char) {
  int size_string = strlen(*string);
  if (pos < size_string) {
    (*string)[pos] = new_char;
  } else {
    *string = realloc(*string, sizeof(**string) * (pos + 2));
    for (int i = size_string; i < pos; i++) {
      (*string)[i] = ' ';
    }
    (*string)[pos] = new_char;
    (*string)[pos + 1] = '\0';

    int size = strlen(*string);
    return size;
  }
}