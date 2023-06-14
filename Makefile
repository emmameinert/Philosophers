NAME = philo

SRC = main input utils parsing init routine time output life_status

HEADER = philo.h

CC = cc 
#-fsanitize=thread -g

CFLAGS = -Wall -Wextra -Werror -I $(HEADER)

FILES = $(addsuffix .c, $(SRC))

OBJECTS = $(addsuffix .o, $(SRC))

all: $(NAME)

$(NAME): $(OBJECTS)
				$(CC) $(CFLAGS) $(FILES) -o $@

clean:
			rm -f $(OBJECTS)
	
fclean: clean	
			rm -f $(NAME)

re: fclean all 