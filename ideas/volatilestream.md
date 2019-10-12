C streams as volatile buffers: volatilestreams
====

what
----
volatile stream = `stdio FILE*` stream as a temporary dynamically allocated (and deallocated) memory buffer.

why
----
Because it is convenient sometimes to see a dynamic temporary buffer as a `FILE *`.

* `fmemopen(3)` uses a fixed size buffer
* `open_memfile(3)` "opens a stream for writing to a memory buffer". Posix specifies that it is for output only

`volstream_open` opens a dynamically allocated, variable sized, R/W stream.

how
----
Just open the file as follows:
```C
FILE *f = volstream_open();
```
and then use any f- stdio function on it: `fwrite`, `fseek`, `fread`, `fprintf`....

The buffer will be automatically freed at:
```C
fclose(f);
```

where
----
Examples of usage:
`https://github.com/virtualsquare/vuos/blob/master/vufs/vufs_getdents.c`,
`https://github.com/virtualsquare/vuos/blob/master/vufuse/vufuseop.c`.
(fill in a buffer to virtualize `getdents(2)`).

references:
----
https://github.com/rd235/libvolatilestream
