#include <iostream>
#include <fstream>
#include <string>
#include <regex>

/* Created by: Lucas Saito, 12 Apr 2021
 *
 * This simple program uses fstream to read the textfile,
 * extract the author's name using regex, and then prints
 * the poem.
 *
 */

class PoemReader {
public:
    typedef std::ifstream input;
    std::string author;
private:
    std::string file_path_;
    input inFile_;
    input GetInput() {
        input tempInput = input(file_path_);
        return tempInput;
    }
    std::string GetAuthor() {
        input tempInput = GetInput();
        std::string line;
        getline(tempInput, line);
        tempInput.close();

        // Regex to find the author's name
        std::regex regexp("(?:by )(.+)");
        std::smatch m;
        std::regex_search(line, m, regexp);

        // Case when regex finds no matches
        if (m.empty() || m.size() == 1) {
            return "No author found";
        } else {
            return m[1];
        }
    }
public:
    PoemReader() = default;
    ~PoemReader() = default;
    explicit PoemReader(const std::string& path)
    : file_path_(path){
        inFile_ = input(path.c_str());
        if (inFile_.fail()) {
            throw (std::runtime_error("Error opening the file, verify if the filepath is correct."));
        }
        inFile_.close();
        author = GetAuthor();
    };

    void read() {
        inFile_ = GetInput();
        std::string line;
        while (getline(inFile_, line)) {
            std::cout << line << std::endl;
        }
        inFile_.close();
    };
};

int main() {
    std::string path = "../IOReadWrite/poem.txt";
    PoemReader poem_reader(path);
    std::cout << "A poem by: " << poem_reader.author << std::endl;
    poem_reader.read();

    return 0;
}
