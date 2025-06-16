NAME	:= minirt
NAME_BONUS	:= minirt_bonus
CC		:= cc
CFLAGS	:= -g -Wextra -Wall -Werror
LIBMLX	:= ./library/MLX42
LIBFT	:= ./library/libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -lreadline -ldl -lglfw -pthread -lm
SRCS_DIR := src/mandatory/
SRCS	:= $(addprefix $(SRCS_DIR), error.c init.c parse.c main.c utils.c free.c)
SRCS_BONUS := src/bonus/
SRCS_BONUS :=$(addprefix $(SRCS_BONUS), )
DIR_OBJ	:= .objs
DIR_OBJ_BONUS := .objs_bonus
OBJS		:= $(SRCS:$(SRCS_DIR)%.c=$(DIR_OBJ)/%.o)
OBJS_BONUS	:= $(SRCS_BONUS:src/bonus/%.c=$(DIR_OBJ_BONUS)/%.o)

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

$(DIR_OBJ)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(DIR_OBJ_BONUS)/%.o: $(SRCS_BONUS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)

bonus: libmlx libft $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)
	
clean:
	@make -C $(LIBFT) clean
	@rm -rf $(DIR_OBJ) $(DIR_OBJ_BONUS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re bonus libmlx libft