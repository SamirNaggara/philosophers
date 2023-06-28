NAME		= 	philosophers
FLAGS		= 	-Wall -Wextra -Werror -pthread 
DEBUG_FLAGS =	
RM			= 	rm -f
GREEN		= 	\033[0;32m
BIG		= 	\033[0;1m
RESET		= 	\033[0m
CC	=	gcc $(FLAGS)
RM	=	rm -f
LOG = log.txt	



SOURCES	=	./main.c \
			./create_philosophers.c \
			./dead.c \
			./ft_atoi.c \
			./ft_chartod.c \
			./ft_itoa.c \
			./init.c \
			./life.c \
			./log.c \
			./mutex.c \
			./threads.c \
			./timestamp.c \
			./unlock.c \
			./end.c \
			./verify_args.c \


 


OBJETS	=	$(SOURCES:.c=.o)			


all		: $(NAME)
	@echo "$(GREEN)\nCompilation philosophers over\n$(RESET)"
	@echo "$(BIG)Tu peux maintenant compiler ./philosophers avec les arguments dans l'ordre : \n	number_of_philosophers\n	time_to_die(ms)\n	time_to_eat(ms)\n	time_to_sleep(ms)\n	[number_of_times_each_philosopher_must_eat]\n\nExemple simple : ./philosophers 7 4000 2000 2000 1\n\nLorsque le programme est terminé, les logs sont disponibles dans log.txt$(RESET)"

$(NAME): $(OBJETS)
	@echo "Création de l'executable $(NAME)"
	@$(CC) $(FLAGS) -o $@ $^

%.o: %.c
	@echo "Génération de $@"
	@$(CC) $(FLAGS) -o $@ -c $< 



clean	:
	@echo "Suppression des .o de $(NAME)"
	@$(RM) $(OBJETS)
	@echo "\n$(GREEN)Tout les .o ont bien été effacé$(RESET)"


fclean	:	clean
	@echo "Suppression de $(NAME)"
	@$(RM) $(NAME)
	@echo "Suppression du fichier de log"
	@$(RM) $(LOG)
	@echo "Suppression de a.out au cas ou"
	@$(RM) a.out
	@echo "\n$(GREEN)Tout les fichiers ont bien été effacés$(RESET)\n"

re		:	fclean all

.PHONY: all clean fclean re
