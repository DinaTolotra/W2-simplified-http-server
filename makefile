CC = gcc
AR = ar -rcs
W = -Wextra -Wall -Werror
F = -g

lib = -lio

includedir = include
sourcedir = source
builddir = build
libdir = build

LOG = echo -n "[MAKE] "; echo

launch: $(builddir)/server
	@$(LOG) "LAUNCHING 'server' PROGRAM"
	@./$(builddir)/server

$(builddir)/server: build $(builddir)/libio.a main.c
	@$(LOG) "COMPILING 'server' PROGRAM"
	@$(CC) $(W) $(F) -o $@ main.c -L$(libdir) $(lib) -I$(includedir)

$(builddir)/libio.a: $(builddir) $(sourcedir)/io.c
	@$(LOG) "COMPILING 'libio' STATIC LIB"
	@$(CC) $(W) $(F) -o $(builddir)/io.o -c $(sourcedir)/io.c -I$(includedir)
	@$(AR) $(builddir)/libio.a $(builddir)/io.o
	@rm $(builddir)/io.o

$(builddir):
	@$(LOG) "CREATING 'build' dir"
	@mkdir -p $(builddir)

clean:
	@$(LOG) "REMOVING 'build' dir"
	@rm -r $(builddir)
