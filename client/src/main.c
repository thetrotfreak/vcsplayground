#include <stdlib.h>

#include "curl/curl.h"
#include "ncurses.h"
size_t write_callback(char *buffer, size_t size, size_t nmemb, void *userdata)
{
  /*
   * TODO
   * Write the chunks into a malloc area
   * Resize the area here since write_callback will be invoked n times by curl unless done
   * This will involve realloc and memcpy operations
   * Finally, once done, display it into the stdscr via ncurses
   */
  WINDOW *win = (WINDOW *)userdata;
  wprintw(win, buffer);
  return size * nmemb;
}
void this_endwin(void)
{
  /*
   * Register this_endwin() to be called just before normal termination.
   * Since atexit() takes a function pointer that returns void and
   * accepts void, we wrap endwin() here.
   */
  endwin();
}

void this_curl_global_cleanup(void) { curl_global_cleanup(); }

int main()
{
  /* rare for initscr() to fail, but it's better to be safe than sorry */
  WINDOW *win = initscr();
  if (win == NULL)
  {
    exit(EXIT_SUCCESS);
  }

  /*
   * This is MT-Unsafe.
   * We call curl_global_init() only once in the lifetime of our program.
   * This is necessary to initialize underlying data structures before
   * we can use libcurl.
   *
   * CURL_GLOBAL_ALL is a <long> flag paramter that does the recommended
   * defaults.
   */
  curl_global_init(CURL_GLOBAL_ALL);

  /*
   * Register cleanup(s).
   * Cleaning up ncurses via endwin() is a must
   * so as to not leave the shell in a weird state.
   */
  int ret = atexit(this_endwin);
  if (ret != 0)
  {
    exit(EXIT_FAILURE);
  }
  ret = atexit(this_curl_global_cleanup);
  if (ret != 0)
  {
    exit(EXIT_FAILURE);
  }

  /*
   * Start libcurl operations.
   * We will use the curl_easy_x family which are synchronous operations.
   */
  CURL *curl = curl_easy_init();
  if (curl)
  {
    CURLcode res =
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/");
    res = curl_easy_perform(curl);

    if (res == CURLE_OK)
    {
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&win);
    }
  }

  /* do some simple stuff with ncurses */
  printw("%p", win);

  /* draw buffer onto stdscr */
  refresh();
  getch();

  exit(EXIT_SUCCESS);
}
