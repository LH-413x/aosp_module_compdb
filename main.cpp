#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if(argc!=2){
        std::cout << "usage: compile_commands relative_path" << std::endl;
        return 0;
    }
    std::string target(argv[1]);
    std::ifstream inFile;
    inFile.open("/Users/haoliu/all-android/aosp/android-master/out/development/ide/compdb/compile_commands.json"); //open the input file

    std::stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    std::string content = strStream.str(); //str holds the content of the file

    std::size_t found_left=0;
    std::size_t found_right=0;

    std::size_t found_file=0;
    std::string left("{");
    std::string right("}");
    std::string file("\"file\": \"");
    std::string output("[");
    while(true){
        found_left=content.find(left,found_left+1);
        found_right=content.find(right,found_right+1);
        found_file=content.find(file,found_file+1);
        if(found_left==std::string::npos||found_right==std::string::npos){
            //std::cout << "find end" << std::endl;
            break;
        }
        if(!strncmp(&content[found_file+file.size()],target.data(),target.size())){
            std::string sub=content.substr(found_left,found_right-found_left+1);
            //std::cout << sub<< std::endl;
            output+=sub+",\n";
        }
    }
    output+="]";
    std::ofstream out_file("compile_commands.json");
    out_file << output;
}