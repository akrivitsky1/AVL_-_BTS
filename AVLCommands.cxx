#include <iostream>
#include <fstream>
#include "json.hpp"
#include "AVL.h"

using json = nlohmann::json;

int main(int argc, char** argv){
     if (argc != 2) { //if not equal to 2, means wrong input given
        std::cerr << "Usage incorrect. Enter in a json file" << std::endl;
        return 1; //end code
    }
    std::ifstream file(argv[1]); //creates a file with json file input
    // Parse the JSON file
    json input; //creates json object
    file >> input; //reads file into json object
    file.close(); 
    AVLTree sample;

    json::iterator it;
    for(it = input.begin(); it != input.end(); it++){
        if(it.key() == "metadata"){
            continue;
        }
        json op = it.value();
        if(op["operation"] == "Insert"){
            int key = op["key"];
            sample.insert(key);
        } else{
            std::cerr << "Invalid operation: " << op["operation"] << std::endl; //operation given is invalid
            return 1;
        }
    }

    json output = sample.toJSON(); 
    std::cout << output.dump(2) << std::endl; //print to screen
}