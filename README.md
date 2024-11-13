# References

<details>
    <summary>ncurses</summary>
    <p>https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/init.html</p>
</details>

<details>
    <summary>curl</summary>
    <p>https://everything.curl.dev/libcurl</p>
    <p>https://curl.se/libcurl/c/libcurl-tutorial.html</p>
</details>

<details>
    <summary>jansson</summary>
    <p>https://jansson.readthedocs.io/en/stable/apiref.html</p>
</details>

<details>
    <summary>c</summary>
    <p>https://man7.org/linux/man-pages/man3/atexit.3.html</p>
</details>


# Commands

These were executed on Ubuntu `24.04.1` LTS:

```shell
$ pkg-config --libs ncurses libcurl jansson
```

# Requirements

To build from source:

- libncurses.so.6
- libtinfo.so.6
- libcurl.so.4
- libjansson.so.4
- libc.so.6
