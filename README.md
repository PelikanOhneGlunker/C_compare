# Build
gcc server.c -o server

# parxis
gcc $pname.c -o $pname

# Info
## Memory handling
  malloc()  → reserve only
  calloc()  → reserve + zero
  realloc() → resize, preserving old data, possibly moving it

