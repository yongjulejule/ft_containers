CXX						= c++

ifdef DEBUG
	CXXFLAGS = --std=c++98 -g3 -fsanitize=address
else ifdef LEAKS
	CXXFLAGS = --std=c++98 -g
else ifdef TEST
	CXXFLAGS = -g --std=c++98  #-fsanitize=address
else
	CXXFLAGS	= --std=c++98 -Wall -Wextra -Werror
endif

ifdef TEST
	NAME			=		mine.out
else
	NAME			=		containers #Name of program
endif

INC_DIR		= ./include/

SRCS_DIR	= ./src/

TEST_DIR	= ./tests/

SRCS			= $(addprefix $(SRCS_DIR), \
						__tree.cpp \
				)

ifdef TEST
	SRCS += $(addprefix $(TEST_DIR), $(TEST).cpp)
else
	SRCS += $(addprefix $(SRCS_DIR), main.cpp)
endif

OBJS			= ${SRCS:%.cpp=%.o}

OBJ_FILES	= $(OBJS)

COMPILE_MSG = @echo $(BOLD)$(L_PUPLE) 📣 ${NAME} Compiled 🥳$(RESET)

######################### Color #########################
GREEN="\033[32m"
L_GREEN="\033[1;32m"
RED="\033[31m"
L_RED="\033[1;31m"
RESET="\033[0m"
BOLD="\033[1m"
L_PUPLE="\033[1;35m"
L_CYAN="\033[1;96m"
UP = "\033[A"
CUT = "\033[K"

########################## Rule ##########################

.PHONY		:	all
all				:	 $(OBJS) $(NAME)

$(NAME)		: 	$(OBJS)
							@$(CXX) $(CXXFLAGS) $(OBJS) -I$(INC_DIR) -o $@ 
							@echo  $(L_CYAN) 🔗 Linking [$(notdir $^)] to [$@] $(RESET)
							$(COMPILE_MSG)


%.o			: 	%.cpp
				@$(CXX) $(CXXFLAGS) -I$(INC_DIR)  -c $< -o $@
				@echo $(BOLD)$(L_GREEN) Compiling with $(CXXFLAGS) -I$(INC_DIR) ...$(RESET)
				@echo $(GREEN) [$(notdir $^)] to [$(notdir $@)] $(RESET)

.PHONY			:	clean
clean			:
					@rm -f $(OBJS)
					@echo $(L_RED) Remove🧹 OBJ files in $(NAME) 👋 $(RESET)


.PHONY			:	fclean
fclean			:	clean
					@rm -f $(NAME)
					@echo $(RED) Remove🧹 $(NAME) 📣 $(RESET)

.PHONY			:	re
re				:	fclean all

.PHONY			:	debug
debug			: 
					@make DEBUG=1
					@echo $(RED)$(BOLD) It\'s DEBUG TIME🤪$(RESET)

.PHONY			:	leaks
leaks			:
					@make LEAKS=1
					@echo $(RED)$(BOLD) Is there Leaks?🚰$(RESET)
