#include <stdlib.h>

#include "curl/curl.h"
#include "ncurses.h"

size_t write_callback(char *buffer, size_t size, size_t nmemb, void *userdata) {
  /*
   * TODO
   * Write the chunks into a malloc area
   * Resize the area here since write_callback will be invoked n times by curl
   * unless done This will involve realloc and memcpy operations Finally, once
   * done, display it into the stdscr via ncurses
   */
  WINDOW *win = (WINDOW *)userdata;

  if (win == NULL) {
    return size * nmemb;
  }

  /* do some simple stuff with ncurses */
  wprintw(win, "%s", buffer);

  /* draw buffer onto stdscr */
  wrefresh(win);

  return size * nmemb;
}

void this_endwin(void) {
  /*
   * Register this_endwin() to be called just before normal termination.
   * Since atexit() takes a function pointer that returns void and
   * accepts void, we wrap endwin() here.
   */
  endwin();
}

void this_curl_global_cleanup(void) { curl_global_cleanup(); }

int main() {
  /* rare for initscr() to fail, but it's better to be safe than sorry */
  WINDOW *win = initscr();
  if (win == NULL) {
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
  int ret = atexit(this_curl_global_cleanup);
  if (ret != 0) {
    exit(EXIT_FAILURE);
  }

  // atexit() executes in reverse oreder of registration
  ret = atexit(this_endwin);
  if (ret != 0) {
    exit(EXIT_FAILURE);
  }

  /*
   * Start libcurl operations.
   * We will use the curl_easy_x family which are synchronous operations.
   */
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode res =
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/");
    res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)win);
    res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    res = curl_easy_perform(curl);

    // HTTP status code >= 4XX will be treated as error
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    long status_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

    mvprintw(1, 0, "res %d", res);
    mvprintw(2, 0, "status_code %ld", status_code);
  }

  // wait for user input before exiting
  getch();

  exit(EXIT_SUCCESS);
}
