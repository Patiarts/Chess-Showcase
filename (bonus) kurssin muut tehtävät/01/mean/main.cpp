#include <iostream>
#include <vector>

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


double mean(const string& input)  // Don't change the function definition!
{
    // TODO: Write mean function code here.
    // Must throw invalid_argument and domain_error on applicaple errors

    vector<string> num_strings = split(input, ' ', true);
    double sum = 0;
    unsigned int count = num_strings.size();
    if(count == 0){
        throw domain_error("No numbers");
    }
    for(unsigned int i = 0; i < count; i++){
        sum += stod(num_strings[i]);
    }
    return sum/count;
}


// Don't remove! Needed for tests.
#ifndef MEAN_TEST
// Don't remove! Needed for tests.
// Main function
int main()
{
    // TODO: Write main function code here
    //       (including try-catch block to catch the thrown exceptions)

    cout << "Enter numbers: ";
    string input = "";
    getline(cin, input);
    try{
        double result = mean(input);
        cout << "Mean: " << result << endl;
    }
    catch(domain_error &ex1){
        cout << "domain_error: " << ex1.what() << endl;
    }
    catch(invalid_argument &ex2){
        cout << "invalid_argument: " << ex2.what() << endl;
    }
    return EXIT_SUCCESS;
}
// Don't remove! Needed for tests.
#endif // MEAN_TEST
// Don't remove! Needed for tests.
