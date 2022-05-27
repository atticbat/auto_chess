# -*- MakeFile -*-

VPATH	=	src
SDIR 	=	src/
NAME	=	auto_chess
FUNCTS	=	main.cpp sprite.cpp menu.cpp ft_itoa.cpp settings.cpp draft.cpp \
			database.cpp game_progression.cpp gui_checkbox.cpp gui_button.cpp \
			gui_slider.cpp gui_scrollbar.cpp gui_dropdown.cpp \
			storyboard_controls.cpp gui_textbox.cpp gui_drag_drop.cpp
OBJS	=	$(FUNCTS:.cpp=.o)
SPATH	=	$(addprefix $(SDIR),$(OBJS))
DPATH	=	$(addprefix $(SDIR),$(OBJS:.o=.d))
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
	$(CC) $(CFLAGS) -c -MMD -MP $(IFLAGS) $< -o $@

clean:
	$(RM) $(SPATH)
	$(RM) $(DPATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

-include $(SPATH:.o=.d)