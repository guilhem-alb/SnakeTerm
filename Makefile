CXX = g++
CXXFLAGS = -Wall



EXEC = Snake++

SRC_DIR = src
_SRCS = main.cpp snake_game.cpp snake.cpp board.cpp
SRCS = $(patsubst %, $(SRC_DIR)/%, $(_SRCS))

TARGET_DIR = build
_OBJS = $(_SRCS:.cpp=.o)
OBJS = $(patsubst %, $(TARGET_DIR)/%, $(_OBJS))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(TARGET_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(EXEC) $(TARGET_DIR)