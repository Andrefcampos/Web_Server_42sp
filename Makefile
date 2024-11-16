#-----------------------------------------------------------------------------------------
# Static library
NAME		:= webServ

#-----------------------------------------------------------------------------------------
# Compiler and flags
CFLAGS		:= -Wall -Werror -Wextra -std=c++98 -g3
CPP			:= c++
O_FLAGS		:= -c

#-----------------------------------------------------------------------------------------
# Command to clean up files
CMD_CLEAN	:= rm -Rf

#-----------------------------------------------------------------------------------------
# DIRECTORY
DIR_MAIN 			:= src/
DIR_INCLUDE			:= include/
DIR_UTILS			:= src/utils/
DIR_SERVER			:= src/Server/
DIR_SOCKET			:= src/Server/Socket/
DIR_RESPONSE		:= src/Server/Response/
DIR_WEBSERVER		:= src/WebServer/
DIR_PARSEREQUEST	:= src/ParseRequest/
DIR_REQUEST			:= src/ParseRequest/Request/
DIR_BODY			:= src/ParseRequest/Request/Body/
DIR_HEADERS			:= src/ParseRequest/Request/Headers/
DIR_RLINE			:= src/ParseRequest/Request/RequestLine/


#-----------------------------------------------------------------------------------------
# Header file
INCLUDE			:= -I $(DIR_SERVER) -I $(DIR_SOCKET)\
					-I $(DIR_RESPONSE) -I $(DIR_WEBSERVER)\
					-I $(DIR_UTILS) -I $(DIR_PARSEREQUEST)\
					-I $(DIR_REQUEST) -I $(DIR_BODY)\
					-I $(DIR_HEADERS) -I $(DIR_RLINE)\

#-----------------------------------------------------------------------------------------
# Source files
FILE_MAIN				:= main.cpp
FILE_SERVER				:= Server.cpp
FILE_SOCKET				:= Socket.cpp
FILE_RESPONSE			:= Response.cpp
FILE_WEBSERVER			:= WebServer.cpp
FILE_PARSEREQUEST		:= ParseRequest.cpp


FILE_REQUEST			:= Request.cpp
FILE_BODY				:= Body.cpp
FILE_HEADERS			:= Headers.cpp
FILE_RLINE				:= RequestLine.cpp




#-----------------------------------------------------------------------------------------
# Source files
SRC_FILES	:= $(addprefix $(DIR_MAIN), $(FILE_MAIN))\
				$(addprefix $(DIR_SERVER), $(FILE_SERVER))\
				$(addprefix $(DIR_SOCKET), $(FILE_SOCKET))\
				$(addprefix $(DIR_RESPONSE), $(FILE_RESPONSE))\
				$(addprefix $(DIR_WEBSERVER), $(FILE_WEBSERVER))\
				$(addprefix $(DIR_PARSEREQUEST), $(FILE_PARSEREQUEST))\
				$(addprefix $(DIR_REQUEST), $(FILE_REQUEST))\
				$(addprefix $(DIR_BODY), $(FILE_BODY))\
				$(addprefix $(DIR_HEADERS), $(FILE_HEADERS))\
				$(addprefix $(DIR_RLINE), $(FILE_RLINE))\

#-----------------------------------------------------------------------------------------
# Directory for object files
OBJS		:= ./objs
O_FILE		:= $(SRC_FILES:%.cpp=$(OBJS)/%.o)

#-----------------------------------------------------------------------------------------
# Default rule to create the static library
all: $(NAME)

#-----------------------------------------------------------------------------------------
# Rule to create the static library
$(NAME): $(O_FILE)
	@$(CPP) $(O_FILE) -o $(NAME)

#-----------------------------------------------------------------------------------------
# Rule to compile source files into object files
$(OBJS)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CPP) $(O_FLAGS) $(INCLUDE) $(CFLAGS) $< -o $@

#-----------------------------------------------------------------------------------------
# Rule to clean
clean:
	@$(CMD_CLEAN) $(OBJS)

fclean: clean
	@$(CMD_CLEAN) $(NAME)

re: fclean all

run:
	./$(NAME)

re_run: re
	./$(NAME)

debug: re
	./$(NAME) "DEBUG"

valgrind:
	valgrind ./$(NAME)

.PHONY: all clean fclean re