#include "shape.hh"
#include "circle.hh"
#include "rectangle.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

// Splits the given string into several strings, by using the given delimiter
// as a separator.
// Returns the splitted string as a vector such that each string part is an
// element of the vector.
// User can specify if empty parts will be ignored or not.
vector<string> split(const string& str, const char delimiter,
                     bool ignore_empty = false)
{
    vector<string> result;
    string tmp = str;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// Goes through the given vector of Shapes and prints each element
// (by calling their print functions).
void print_shapes(vector<shared_ptr<Shape>> shapes)
{
    for(size_t i = 0; i < shapes.size(); i++){
        shapes[i]->print(i+1);
        std::cout << endl;
    }
}

int main()
{
    cout << "Enter file name: ";
    string file_name = "";
    getline(cin, file_name);
    ifstream file(file_name);
    if(not file)
    {
        cout << "File not found" << endl;
        return EXIT_FAILURE;
    }
    string line = "";

    vector<shared_ptr<Shape>> shapes;

    // Goes through the input file line by line and splits each line.
    // Based on the content of each line, creates either a Circle
    // or a Rectangle, and pushes the shape to the vector shapes.
    while(getline(file, line))
    {
        std::vector<std::string> line_parts = split(line, ' ', true);
        int part_count = line_parts.size();
        if(part_count < 2 || part_count > 3){
            continue;
        }

        char color_code = line_parts[0][0];
        if(COLOR_CODES.find(color_code) == COLOR_CODES.end()){
            continue;
        }

        double dim1 = -1;
        double dim2 = -1;
        std::shared_ptr<Shape> new_shape = nullptr;
        try{
            dim1 = std::stod(line_parts[1]);
            if(part_count == 2){
                new_shape = std::make_shared<Circle>(Circle(color_code, dim1));
            }
            else{
                dim2 = std::stod(line_parts[2]);
                new_shape = std::make_shared<Rectangle>(Rectangle(color_code, dim1, dim2));
            }
        }
        catch(std::invalid_argument& problem){
            std::cout << problem.what() << std::endl;
            continue;
        }
        catch(std::out_of_range& problem){
            std::cout << problem.what() << std::endl;
            continue;
        }

        shapes.push_back(new_shape);

    }

    std::cout << std::endl;
    print_shapes(shapes);
    return 0;
}
