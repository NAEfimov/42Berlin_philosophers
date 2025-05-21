NAME        := philo

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# INCS			header file locations
#
# SRCS			source files
#
# OBJS			object files
# DEPS			dependency files
#
# CC			compiler
# CFLAGS		compiler flags
# CPPFLAGS		preprocessor flags
# IFLAGS		Include flags

INCS        := .

SRCS		:=			\
	philo.c				\
	ph_arg_check.c		\
	ph_utils.c			\
	ph_mutex.c			\
	ph_thread.c			\
	ph_philosopher.c

BUILD_DIR	:= .build
OBJS		:= $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -MMD -MP
IFLAGS		:= $(addprefix -I,$(INCS))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM		force remove
# MAKEFLAGS	make flags

RM_FILES	= rm -f
RM_DIR		= rm -fr
MAKEFLAGS	+= --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all		default goal
# $(NAME)	link .o -> library
# %.o		compilation .c -> .o
# clean		remove .o .d
# fclean	remove .o .d + binary
# re		remake default goal

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(IFLAGS) -o $@ $(OBJS)
	$(info CREATED $(NAME))

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(IFLAGS) -c -o $@ $< $(LDLIBS)
	$(info CREATED $@)

$(BUILD_DIR)/%.o: %.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(RM_FILES) $(OBJS) $(DEPS)
	$(RM_DIR) $(BUILD_DIR)
fclean: clean
	$(RM_FILES) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all