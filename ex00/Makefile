NAME = btc
SOURCES = $(wildcard ./src/*.cpp)
CC = @c++
CFLAGS = -Wall -Wextra -Werror -g -std=c++98 -pedantic 
#-fsanitize=address,undefined

all: $(NAME)
$(NAME): $(SOURCES)
	$(CC) $(CFLAGS) $(^) -o $(@)

clean:
	@rm -f $(wildcard ./src/*.o)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re