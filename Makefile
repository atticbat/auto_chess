# -*- MakeFile -*-

VPATH	=	src

NAME	=	auto_chess
FUNCTS	=	main.cpp sprite.cpp menu.cpp ft_itoa.cpp settings.cpp draft.cpp \
			database.cpp game_progression.cpp gui_checkbox.cpp gui_button.cpp \
			gui_slider.cpp gui_scrollbar.cpp gui_dropdown.cpp \
			storyboard_controls.cpp gui_textbox.cpp gui_drag_drop.cpp \
			gui_dynamic_label.cpp user.cpp get_next_line_utils.cpp \
			get_next_line.cpp ft_split.cpp simulation.cpp controls.cpp
OBJS	=	$(addprefix _bin/,$(notdir $(FUNCTS:.cpp=.o)))
BREW	=	$(shell brew --prefix)
CC		=	g++
CFLAGS	= 	-std=c++0x -O3
IFLAGS	=	-I $(BREW)/include
LFLAGS	=	-L $(BREW)/lib -lraylib -lcurl
RM 		=	/bin/rm -f

$(NAME): $(OBJS) 
	$(CC) $^ $(CFLAGS) -o $@ $(LFLAGS)

_bin:
	mkdir _bin

_bin/%.o : %.cpp | _bin
	$(CC) $(CFLAGS) -c -MMD -MP $(IFLAGS) $< -o $@

clean:
	rm -rf _bin

fclean: clean
	$(RM) $(NAME)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(OBJS:.o=.d)