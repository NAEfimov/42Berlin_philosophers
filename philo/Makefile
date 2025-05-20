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
	arg_check.c		

# OBJS_DIR	:= 
OBJS		:= $(SRCS:%.c=%.o)
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

RM			= rm -f
MAKEFLAGS	+= --no-print-directory

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

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)
fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all