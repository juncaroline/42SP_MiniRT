NAME	:= miniRT
NAME_BONUS	:= miniRT_bonus
CC		:= cc
CFLAGS	:= -g -Wextra -Wall -Werror
LIBMLX	:= ./library/MLX42
LIBFT	:= ./library/libft
# SUPPRESSION_FILE := suppress_mlx_error.sup

# SCENE_DIR := scenes/basic/
# SCENES := $(wildcard $(SCENE_DIR)*.rt)

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -lreadline -ldl -lglfw -pthread -lm
SRCS_DIR := sources/mandatory/
SRCS	:= $(addprefix $(SRCS_DIR), init/handle_param.c init/init.c init/main.c init/validate_elements.c \
				intersection/closest_hit.c intersection/intersect_cylinder_aux.c \
				intersection/intersect_cylinder_calc.c intersection/intersect_cylinder.c intersection/intersect_plane.c \
				intersection/intersect_quadratic.c intersection/intersect_sphere.c \
				ray/ray_direction.c ray/ray_generator.c \
				utils/error.c utils/free.c utils/math.c utils/utils.c utils/utils2.c \
				light_shadow.c light.c parse_elements.c \
				parse_objects_add.c parse_objects_utils.c parse_objects.c parse_param.c parse_param2.c parse.c)
SRCS_BONUS := sources/bonus/
SRCS_BONUS :=$(addprefix $(SRCS_BONUS), bump/bump_map_bonus.c bump/bump_map_generic_bonus.c bump/bump_map_utils_bonus.c \
				bump/bump_map_uv_bonus.c bump/bump_map_uv_calc_bonus.c bump/bump_map_vectors_bonus.c  \
				checkerboard/checkerboard_bonus.c checkerboard/checkerboard_calc_bonus.c checkerboard/checkerboard_map_bonus.c \
				init/handle_param_bonus.c init/init_bonus.c init/main.c init/validate_elements.c \
				intersection/closest_hit_bonus.c intersection/intersect_cone_aux_bonus.c intersection/intersect_cone_aux2_bonus.c \
				intersection/intersect_cone_bonus.c intersection/intersect_cone_calc_bonus.c \
				intersection/intersect_cylinder_aux_bonus.c intersection/intersect_cylinder_aux2_bonus.c \
				intersection/intersect_cylinder_bonus.c intersection/intersect_cylinder_calc_bonus.c \
				intersection/intersect_plane_bonus.c intersection/intersect_quadratic_bonus.c \
				intersection/intersect_sphere_bonus.c intersection/intersect_sphere_calc_bonus.c \
				ray/ray_direction_bonus.c ray/ray_generator_bonus.c \
				utils/error_bonus.c utils/free_bonus.c utils/math_bonus.c utils/utils_bonus.c utils/utils2_bonus.c \
				light_bonus.c light_shadow.c main.c  parse_elements.c \
				parse_objects_add.c parse_objects_utils.c parse_objects.c parse_param.c parse_param2.c parse.c)
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

# val:
# 	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPPRESSION_FILE) ./$(NAME) $$scene;

# val_bonus:
# 	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPPRESSION_FILE) ./$(NAME_BONUS) $$scene;

.PHONY: all clean fclean re bonus libmlx libft