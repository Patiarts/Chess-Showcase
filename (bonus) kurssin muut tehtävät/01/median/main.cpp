#include <iostream>
#include <vector>
#include <algorithm>

const std::string VAL_DB_CHARS = "0123456789.-+ ";
const std::string NOT_DB_ERROR = "Not a double";
const std::string NO_INP_ERROR = "No input";

std::vector<std::string> split_str(std::string input, char splitter){
    input.push_back(splitter);
    std::vector<std::string> output = {};
    std::string copy = "";
    int input_len = input.size();

    for(int i = 0; i < input_len; i++){
        if(input[i] != splitter){
            copy.push_back(input[i]);
        }
        else if(!copy.empty()){
            output.push_back(copy);
            copy.clear();
        }
    }

    return output;
}

int main()
{
    std::cout << "Enter numbers: ";
    std::string input = "";
    std::getline(std::cin, input);

    if(input.empty()){
        std::cout << NO_INP_ERROR << std::endl;
        return 1;
    }

    for(size_t i = 0; i < input.size(); i++){
        if(VAL_DB_CHARS.find(input[i]) == std::string::npos){
            std::cout << NOT_DB_ERROR << std::endl;
            return 1;
        }
    }

    std::vector<std::string> num_strs = split_str(input, ' ');
    int num_count = num_strs.size();
    int middle = num_count / 2;
    std::vector<double> nums = {};

    for(int i = 0; i < num_count; i++){
        nums.push_back(stod(num_strs[i]));
    }
    std::sort(nums.begin(), nums.end());

    double m1 = nums.at(middle);
    double m2 = nums.at(num_count - middle -1);
    double median = (m1 + m2)/2.0;

    std::cout << "Median: " << median << std::endl;
}
