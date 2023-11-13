NAME = philo

SRC = main ./src/input ./src/utils ./src/parsing ./src/init ./src/routine ./src/time ./src/output ./src/life_status

HEADER = ./header/philo.h

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
