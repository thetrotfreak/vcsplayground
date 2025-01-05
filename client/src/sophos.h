/*
 * This C header defines necessary struct and enum
 * required as a HTTP Form Data of the MIME Type
 * application/x-www-form-urlencoded
 * which is used for the Internet Access Login Portal.
 */

#ifdef SOPHOS_H
#undef SOPHOS_H
#endif

#ifndef SOPHOS_H
#define SOPHOS_H

/*
 * These enumerations were derived from the
 * bundled JavaScript for the Internet Access Login
 * Page.
 *
 * The actual source defines more enumerations,
 * each for a different mode of User state;
 * but, is not necessary in our case.
 */
enum sophos_mode { LOGIN = 191, LOGOUT = 193 };

/*
 * These enumerations were derived from the
 * bundled JavaScript for the Internet Access Login
 * Page.
 *
 * The actual source defines more enumerations,
 * each for a different platform, possibly User-Agent;
 * but, is not necessary in our case.
 */
enum sophos_product_type { WEB = 0 };

struct sophos_form_data {
  char *username;
  char *password;
  enum sophos_mode mode;
  enum sophos_product_type producttype;
};

#endif // SOPHOS_H
