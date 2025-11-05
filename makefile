CC = gcc
W = -Wextra -Wall -Werror
F = -g

includedir = include
sourcedir = source
builddir = build

LOG = echo -n "[MAKE] "; echo

launch: $(builddir)/server
	@$(LOG) "LAUNCHING 'server'"
	@./$(builddir)/server

$(builddir)/server: build main.c
	@$(LOG) "COMPILING 'server'"
	@$(CC) $(W) $(F) -o $@ main.c

@(builddir):
	@$(LOG) "CREATING build dir"
	@mkdir -p $(builddir)

clean:
	@$(LOG) "REMOVING build dir"
	@rm -r $(builddir)
