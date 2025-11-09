# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Target executable
TARGET = file_explorer

# Source file
SRC = file_explorer.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Compiling the File Explorer program..."
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	@echo "Build complete. Run './$(TARGET)' to start the program."

run: all
	@echo "Running File Explorer..."
	./$(TARGET)

install: $(TARGET)
	@echo "Installing File Explorer to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Installation complete. You can now run it using 'file_explorer'."

uninstall:
	@echo "Removing File Explorer from /usr/local/bin..."
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstallation complete."

clean:
	@echo "Cleaning up build files..."
	rm -f $(TARGET)
	@echo "Clean complete."


.PHONY: all run install uninstall clean
