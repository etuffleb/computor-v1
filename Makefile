NAME			=	computorv1

SRCDIR			=	src
OBJDIR			=	obj
INCDIR			=	lib

SRCNAM			=	main.cpp ParsableString.cpp ParserError.cpp Polynomial.cpp PolyPrinter.cpp CV1Math.cpp
INCNAM			=	computorv1.h ParsableString.h ParserError.h Polynomial.h PolyPrinter.h CV1Math.h

CC				=	g++
CFLAGS			=	-g -Wall -Wextra -I$(INCDIR) -std=c++11

SRC					=	$(SRCNAM:%=$(SRCDIR)/%)
INC					=	$(INCNAM:%=$(INCDIR)/%)
OBJ					=	$(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean fclean re

all:
	@$(MAKE) $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@$(MAKE) all