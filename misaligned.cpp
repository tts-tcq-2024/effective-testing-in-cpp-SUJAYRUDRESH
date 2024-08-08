#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

class OutputInterface {
public:
    virtual ~OutputInterface() = default;
    virtual void print(const std::string& message) = 0;
};


class MockOutput : public OutputInterface {
public:
    void print(const std::string& message) override {
        messages.push_back(message);
    }

    const std::vector<std::string>& getMessages() const {
        return messages;
    }

private:
    std::vector<std::string> messages;
};


int printColorMap(OutputInterface& output) {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            output.print(std::to_string(i * 5 + j) + " | " + majorColor[i] + " | " + minorColor[i] + "\n");
        }
    }
    return i * j;
}

//void testColorPairs(const std::vector<std::string>& messages) {}

size_t countOccurrences(const std::string& str, char ch) {
    size_t count = 0;
    for (char c : str) {
        if (c == ch) {
            count++;
        }
    }
    return count;
}

void testAlignment(const std::vector<std::string>& messages) {
    for (const auto& line : messages) {
        // Check for a consistent number of '|' characters (should be exactly 2)
        size_t wireCount = countOccurrences(line, '|');
        assert(wireCount == 2 && "Misalignment: Incorrect number of separators '|' in line");

        // Check alignment: Ensure that there are exactly 3 columns
        size_t firstWire = line.find('|');
        size_t secondWire = line.find('|', firstWire + 1);
        assert(firstWire != std::string::npos && secondWire != std::string::npos && "Misalignment: Missing separators");

        // Ensure proper alignment by checking spaces around separators
        assert(line[firstWire + 1] == ' ' && "Misalignment: Missing space after first separator");
        assert(line[secondWire + 1] == ' ' && "Misalignment: Missing space after second separator");
    }
}




int main() {
    MockOutput mockOutput;
    int result = printColorMap(mockOutput);


    const auto& messages = mockOutput.getMessages();
    testColorPairs(messages);
    testAlignment(messages);
    //testNumericAlignment(messages);
    assert(messages.size() == 25 && "Expected exactly 25 lines of output");

    // Check the first line
    assert(messages[0] == "0 | White | Blue\n" && "First line mismatch");
    
    // Check the middle line (13th line)
    assert(messages[12] == "12 | Black | Green\n" && "Middle line mismatch");
    
    // Check the last line (25th line)
    assert(messages[24] == "24 | Violet | Slate\n" && "Last line mismatch");
    assert(result == 25 && "Expected return value to be 25");
    std::cout << "All is well (maybe!)\n";
    return 0;
}
