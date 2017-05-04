CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -ansi -pedantic -std=c11 -O3
LIB		= -lSDL2 -lSDL2_image -lSDL2_ttf -lm

MODULES 	= game sdl 
SRC_DIR 	= $(addprefix src/,$(MODULES))
BUILD_DIR 	= $(addprefix build/,$(MODULES))

SRC		= $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ		= $(patsubst src/%.c,build/%.o,$(SRC))

NAME		= color_flood

VPATH 		= %.c $(SRC_DIR)

define make-goal
$1/%.o: %.c
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

.PHONY: all checkdirs clean fclean

all: checkdirs $(NAME) solver

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LIB)

solver : src/solver/solver.c src/solver/stack.c src/game/game.c src/game/grid.c src/game/rgb.c
	$(CC) $(CFLAGS) $^ -o $@

solver_link: $(OBJ_SLV)
	$(CC) $^ -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME) solver

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal, $(bdir))))
