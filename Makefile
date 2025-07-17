NAME	:= miniRT
NAME_BONUS	:= miniRT_bonus
CC		:= cc
CFLAGS	:= -g -Wextra -Wall -Werror
LIBMLX	:= ./library/MLX42
LIBFT	:= ./library/libft
# SUPPRESSION_FILE := suppress_mlx_error.sup

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -lreadline -ldl -lglfw -pthread -lm
SRCS_DIR := sources/mandatory/
SRCS	:= $(addprefix $(SRCS_DIR), closest_hit.c error.c free.c handle_param.c init.c \
				intersect_cylinder_aux.c intersect_cylinder_calc.c intersect_cylinder.c \
				intersect_plane.c intersect_sphere.c light_shadow.c light.c main.c math.c parse_elements.c \
				parse_objects_add.c parse_objects_utils.c parse_objects.c parse_param.c parse_param2.c parse.c ray_direction.c \
				ray_generator.c utils.c utils2.c validate_elements.c)
SRCS_BONUS := sources/bonus/
SRCS_BONUS :=$(addprefix $(SRCS_BONUS), bump_map_utils.c bump_map_uv.c bump_map_vectors.c bump_map.c checkerboard.c closest_hit.c error.c free.c handle_param.c init.c \
				intersect_cone_aux.c intersect_cone_aux2.c intersect_cone_calc.c intersect_cone.c \
				intersect_cylinder_aux.c intersect_cylinder_aux2.c intersect_cylinder_calc.c intersect_cylinder.c \
				intersect_plane.c intersect_sphere_calc.c intersect_sphere.c light_bonus.c light_shadow.c main.c math.c parse_elements.c \
				parse_objects_add.c parse_objects_utils.c parse_objects.c parse_param.c parse_param2.c parse.c ray_direction.c ray_generator.c \
				utils.c utils2.c \
				validate_elements.c)
DIR_OBJ	:= .objs
DIR_OBJ_BONUS := .objs_bonus
OBJS		:= $(SRCS:$(SRCS_DIR)%.c=$(DIR_OBJ)/%.o)
OBJS_BONUS	:= $(SRCS_BONUS:src/bonus/%.c=$(DIR_OBJ_BONUS)/%.o)

# valgrind:
# 	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPPRESSION_FILE) ./$(NAME)

# valgrind_bonus:
# 	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPPRESSION_FILE) ./$(NAME_BONUS)

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

$(DIR_OBJ)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(DIR_OBJ_BONUS)/%.o: $(SRCS_BONUS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

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