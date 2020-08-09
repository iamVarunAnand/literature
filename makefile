TARGET_EXEC ?= run.out

INC_DIR ?= ./include
SRC_DIR ?= ./src
BUILD_DIR ?= ./build

SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))

INC_FLAG_PARAMS ?= .
CXX ?= g++
CXXFLAGS ?= -Wall -g -I $(INC_FLAG_PARAMS)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/player.hpp $(INC_DIR)/dealer.hpp $(INC_DIR)/messages.hpp $(INC_DIR)/constants.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/player.o: $(SRC_DIR)/player.cpp $(INC_DIR)/player.hpp $(INC_DIR)/brain.hpp $(INC_DIR)/set.hpp $(INC_DIR)/messages.hpp \
		  $(INC_DIR)/card.hpp $(INC_DIR)/dtypes.hpp $(INC_DIR)/constants.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/player.cpp -o $(BUILD_DIR)/player.o

$(BUILD_DIR)/dealer.o: $(INC_DIR)/dealer.hpp $(INC_DIR)/card.hpp $(INC_DIR)/dtypes.hpp $(INC_DIR)/constants.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/dealer.cpp -o $(BUILD_DIR)/dealer.o

$(BUILD_DIR)/brain.o: $(SRC_DIR)/brain.cpp $(INC_DIR)/brain.hpp $(INC_DIR)/set.hpp $(INC_DIR)/card.hpp $(INC_DIR)/constants.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/brain.cpp -o $(BUILD_DIR)/brain.o

$(BUILD_DIR)/set.o: $(SRC_DIR)/set.cpp $(INC_DIR)/set.hpp $(INC_DIR)/card.hpp $(INC_DIR)/renderer.hpp $(INC_DIR)/dtypes.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/set.cpp -o $(BUILD_DIR)/set.o

$(BUILD_DIR)/messages.o: $(SRC_DIR)/messages.cpp $(INC_DIR)/messages.hpp $(INC_DIR)/card.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/messages.cpp -o $(BUILD_DIR)/messages.o

$(BUILD_DIR)/card.o: $(SRC_DIR)/card.cpp $(INC_DIR)/card.hpp $(INC_DIR)/renderer.hpp $(INC_DIR)/dtypes.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/card.cpp -o $(BUILD_DIR)/card.o

$(BUILD_DIR)/renderer.o: $(SRC_DIR)/renderer.cpp $(INC_DIR)/renderer.hpp $(INC_DIR)/dtypes.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/renderer.cpp -o $(BUILD_DIR)/renderer.o

clean:
	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/$(TARGET_EXEC)