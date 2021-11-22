PROG_NAME = 42sh_unit_tests

CC ?= clang
COMPILER = $(CC) -c
LINKER = $(CC)

SRCS_ROOT = srcs
INCL_ROOT = includes
OBJS_ROOT = objs

TARGET_OBJS_ROOT = ../objs
TARGET_INCL_ROOT = ../includes
TARGET_OBJS = $(filter-out %main.o, $(filter %.o, $(shell find $(TARGET_OBJS_ROOT) -type f)))

SRCS_DIRS = $(shell find $(SRCS_ROOT) -type d)
OBJS_DIRS = $(patsubst $(SRCS_ROOT)%, $(OBJS_ROOT)%, $(SRCS_DIRS))
SRCS = $(filter %.c,$(shell find $(SRCS_ROOT) -type f))
OBJS = $(patsubst $(SRCS_ROOT)/%.c, $(OBJS_ROOT)/%.o, $(SRCS))

CUNIT_VER ?= $(shell pwd)/CUnit-2.1-3
CUNIT_SRC_ARCHIVE ?= $(CUNIT_VER).tar.bz2
CUNIT_LOCAL_DIR ?= $(CUNIT_VER)/installdir
CUNIT_STATIC_LIB ?= $(CUNIT_LOCAL_DIR)/lib/libcunit.a
CUNIT_INCLUDE_ROOT ?= $(CUNIT_LOCAL_DIR)/include

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -I$(CUNIT_INCLUDE_ROOT)\
	-I$(LIBFT_DIR)/includes -I$(INCL_ROOT) -I$(TARGET_INCL_ROOT)
LFLAGS = -lncurses
MAKE_OPTS = --no-print-directory


all: $(CUNIT_STATIC_LIB)
	@echo "BUILDING TESTS:"
	@$(MAKE) $(PROG_NAME) $(MAKE_OPTS)
	@echo "RUNNING TESTS:"
	@./$(PROG_NAME)

$(CUNIT_STATIC_LIB):
	@echo "BUILDING CUNIT:"
	tar -xf $(CUNIT_SRC_ARCHIVE)
	cd $(CUNIT_VER) && mv configure.in configure.ac
	cd $(CUNIT_VER) && aclocal
	cd $(CUNIT_VER) && autoreconf -i
	cd $(CUNIT_VER) && ./configure --prefix $(CUNIT_LOCAL_DIR)
	make -C $(CUNIT_VER)
	make install -C $(CUNIT_VER)


$(PROG_NAME): $(OBJS_DIRS) $(OBJS) $(LIBFT)
	@echo "LINK   " $@
	@$(LINKER) -o $@ $(OBJS) $(CUNIT_STATIC_LIB) $(TARGET_OBJS) $(LIBFT) $(LFLAGS)

$(OBJS_DIRS):
	@mkdir -p $@

$(OBJS_ROOT)/%.o: $(SRCS_ROOT)/%.c
	@echo "COMPILE" $(patsubst $(SRCS_ROOT)/%.c,%,$^)
	@$(COMPILER) -o $@ $(CFLAGS) -I$(dir $(patsubst $(SRCS_ROOT)%,$(INCL_ROOT)%,$<)) $<

clean:
	@rm -fr $(OBJS_ROOT)

fclean: clean
	@rm -f $(PROG_NAME)

re: fclean all
