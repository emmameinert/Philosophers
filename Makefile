NAME = philo

SRC = main input utils parsing init routine time output life_status

HEADER = philo.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -I $(HEADER) -o2

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
