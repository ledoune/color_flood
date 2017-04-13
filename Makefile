CC		= gcc

RM		= rm -rf

CFLAGS		= -Wall -Wextra -ansi -pedantic -std=c11
LIB		=

MODULES 	= game  # sdl
SRC_DIR 	= $(addprefix src/,$(MODULES))
BUILD_DIR 	= $(addprefix build/,$(MODULES))

SRC		= $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ		= $(patsubst src/%.c,build/%.o,$(SRC))

NAME		= color_flood

VPATH 		= %.c $(SRC_DIR)

define make-goal
$1/%.o: %.c
	$(CC) -c $$< -o $$@
endef

.PHONY: all checkdirs clean fclean

all: checkdirs $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LIB)

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal, $(bdir))))
