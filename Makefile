NAME		= 	philosophers
FLAGS		= 	-Wall -Wextra -Werror -g -pthread 
RM			= 	rm -f
GREEN		= 	\033[0;32m
RESET		= 	\033[0m
CC	=	gcc $(FLAGS)
RM	=	rm -f				



SOURCES	=	./main.c \


 


OBJETS	=	$(SOURCES:.c=.o)			


all		: $(NAME)
	@echo -e "$(GREEN)\nCompilation philosophers over\n"

$(NAME): $(OBJETS)
	@echo "Création de l'executable $(NAME)"
	@$(CC) $(FLAGS)-o $@ $^

%.o: %.c
	@echo "Génération de $@"
	$(CC) $(FLAGS) -o $@ -c $< 



clean	:
	@echo "Suppression des .o de $(NAME)"
	@$(RM) $(OBJETS)
	@echo "\n$(GREEN)Tout les .o ont bien été effacé$(RESET)"


fclean	:	clean
	@echo "Suppression de $(NAME)"
	@$(RM) $(NAME)
	@echo "Suppression de a.out au cas ou"
	@$(RM) a.out
	@echo "\n$(GREEN)Tout les fichiers ont bien été effacés$(RESET)\n"

re		:	fclean all

.PHONY: all clean fclean re
