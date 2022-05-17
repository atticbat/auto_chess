# -*- MakeFile -*-

VPATH	=	src
SDIR 	=	src/
NAME	=	auto_chess
FUNCTS	=	main.cpp sprite.cpp menu.cpp database.cpp get_next_line.cpp \
			get_next_line_utils.cpp ft_itoa.cpp settings.cpp
OBJS	=	$(FUNCTS:.cpp=.o)
SPATH	=	$(addprefix $(SDIR),$(OBJS))

BREW	=	$(shell brew --prefix)
CC		=	g++
CFLAGS	= 	-std=c++0x -O3
IFLAGS	=	-I $(BREW)/include
LFLAGS	=	-L $(BREW)/lib -lraylib -lcurl
RM 		=	/bin/rm -f

all: $(NAME)

$(NAME): $(SPATH)
	$(CC) $^ $(CFLAGS) -o $@ $(LFLAGS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $(IFLAGS) $^ -o $@

clean:
	$(RM) $(SPATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
