# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 12:18:12 by lguiller          #+#    #+#              #
#    Updated: 2019/10/28 10:48:01 by lguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################
##  VARIABLES   ##
##################

OPE_SYS			= $(shell uname)
NAME			= npuzzle

SRCS1			= main.cpp
SRCS1			+= Coord.class.cpp
SRCS1			+= State.class.cpp
SRCS1			+= test.cpp

SRCS			= $(addprefix $(SRCS_DIR), $(SRCS1))
OBJS			= $(addprefix $(OBJS_DIR), $(SRCS1:$(SUFFIX)=.o))

SUFFIX			= .cpp

SRCS_DIR		= ./srcs/
OBJS_DIR		= ./objs/
INCLUDES_DIR		= ./includes/

INCLUDES		= -I $(INCLUDES_DIR)

HEADER1			= npuzzle.h
HEADER1			+= Coord.class.hpp
HEADER1			+= State.class.hpp
HEADER			= $(addprefix $(INCLUDES_DIR), $(HEADER1))

CFLAGS			= -Wall -Wextra -O2 -g
CC			= clang++

##################
##    COLORS    ##
##################

_BLACK			= "\033[30m"
_RED			= "\033[31m"
_GREEN			= "\033[32m"
_YELLOW			= "\033[33m"
_BLUE			= "\033[34m"
_VIOLET			= "\033[35m"
_CYAN			= "\033[36m"
_WHITE			= "\033[37m"
_END			= "\033[0m"
_CLEAR			= "\033[2K"
_HIDE_CURS		= "\033[?25l"
_SHOW_CURS		= "\033[?25h"
_UP			= "\033[A"
_CUT			= "\033[k"

##################
##   TARGETS    ##
##################

.PHONY: all launch clean fclean re norme title
.SILENT:

all: launch

launch: title
	echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	$(MAKE) $(NAME)
	echo $(_GREEN)"\nDone."$(_END)$(_SHOW_CURS)

$(OBJS_DIR):
	mkdir $@

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(OBJS_DIR)%.o: $(SRCS_DIR)%$(SUFFIX) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf $<

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) -s fclean
	$(MAKE) -s

norme:
	echo "RT-V1"
	norminette $(SRCS) $(HEADER)

title:
	echo $(_RED)
	echo "◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"
	echo
	echo "      ::::    :::         :::::::::  :::    ::: ::::::::: ::::::::: :::        :::::::::: "
	echo "     :+:+:   :+:         :+:    :+: :+:    :+:      :+:       :+:  :+:        :+:         "
	echo "    :+:+:+  +:+         +:+    +:+ +:+    +:+     +:+       +:+   +:+        +:+          "
	echo "   +#+ +:+ +#+ +#++:++ +#++:++#+  +#+    +:+    +#+       +#+    +#+        +#++:++#      "
	echo "  +#+  +#+#+#         +#+        +#+    +#+   +#+       +#+     +#+        +#+            "
	echo " #+#   #+#+#         #+#        #+#    #+#  #+#       #+#      #+#        #+#             "
	echo "###    ####         ###         ########  ######### ######### ########## ##########       "
	echo
	echo "◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"
	printf $(_YELLOW)
	echo "                                                                           2019 © lguiller"
	echo $(_END)
