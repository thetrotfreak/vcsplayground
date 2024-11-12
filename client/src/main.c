#include <stdlib.h>

#include "curl/curl.h"
#include "jansson.h"
#include "ncurses.h"

void post(CURL *curl, WINDOW *win);

size_t write_callback(char *buffer, size_t size, size_t nmemb, void *userdata) {
  /*
   * TODO
   * Write the chunks into a malloc area.
   * Resize the area here since write_callback will be invoked n times by curl
   * unless done.
   * This will involve realloc and memcpy operations.
   * Finally, once done, display it into the stdscr via ncurses.
   */
  WINDOW *win = (WINDOW *)userdata;

  if (win == NULL) {
    return size * nmemb;
  }

  /* do some simple stuff with ncurses */
  wprintw(win, "HTTP Response: %s\n", buffer);

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
    free(win);
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
  CURLcode res;
  if (curl) {
    res = curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/");
    res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)win);
    res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    res = curl_easy_perform(curl);

    long status_code;
    res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

    printw("HTTP Get: %ld\n", status_code);
  }

  // perform a HTTP Post
  post(curl, win);

  // wait for user input before exiting
  getch();

  exit(EXIT_SUCCESS);
}

void post(CURL *curl, WINDOW *win) {
  if (win == NULL || curl == NULL) {
    return;
  }

  CURLcode res;
  struct curl_slist *slist = NULL;
  // struct curl_slist *temp = NULL;

  /*
   * Passing NULL as the first argument creates a new curl_slist.
   * We want to perform a HTTP POST with a JSON request body.
   */
  slist = curl_slist_append(slist, "Content-Type: application/json");

  if (slist == NULL) {
    // a NULL pointer returned by curl_slist_append() implies failure
    curl_slist_free_all(slist);
    return;
  }

  /*
   * We assign it to temp first to avoid
   * overwriting an exisiting non-empty list on failure.
   */
  // slist = temp;
  json_t *post_data = json_object();
  json_t *username = json_string("foo@example.com\0");
  json_t *password = json_string("foo@123\0");

  if (post_data == NULL || username == NULL || password == NULL) {
    return;
  }

  if (json_object_set(post_data, "username\0", username) != 0 ||
      json_object_set(post_data, "password\0", password) != 0) {
    return;
  }

  char *json_data = json_dumps((const json_t *)post_data, 0);

  if (json_data == NULL) {
    return;
  }

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
  curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/post");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

  res = curl_easy_perform(curl);
  long status_code;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

  if (res == CURLE_OK) {
    wprintw(win, "HTTP Post: %ld\n", status_code);
    wrefresh(win);
  }

  /*
   * Clean up the HTTP Header list,
   * the options set on the CURL* handle, and
   * the heap data used by json_dumps()
   */
  free(json_data);
  curl_slist_free_all(slist);
  curl_easy_cleanup(curl);
}
