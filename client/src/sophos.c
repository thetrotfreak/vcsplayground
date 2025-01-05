#include "sophos.s"
#include "curses.h"

/*
 * Serialize a struct sophos_form_data to a string as:
 * "<field>=<value>&<field>=<value>&...".
 *
 * This will be used as a query parameter string.
 */
void struct_dump_str(const *struct sophos_form_data p) {
  if (p == NULL) {
    return;
  }
}

/*
 * Use ncurses to take interactive input for
 * the required form fields, namely
 * username, and
 * password
 *
 * This returns a pointer
 */
struct sophos_form_data *nc_form(WINDOW *win) {
  if (win == NULL) {
    return NULL;
  }
  newwin(win, LINES / 2, COLS / 2);
}
