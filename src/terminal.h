class Terminal {
public:
    Terminal(std::string input) {
        _input = input;
    }
    std::string showResult(){
        std::vector<std::string> v;
        std::string result;
        v = splitInput(_input, ')');
        // for(auto x: v){
        //     std::cout<< x << std::endl;
        // }
        return result;
    }
private:
    std::string _input;
    
    std::vector<std::string> splitInput(std::string & input, char delimiter){
        std::vector<std::string> v;
        std::string str;
        std::istringstream iss(input);
        while (std::getline(iss, str, delimiter)){
            v.push_back(str);
        }
        return v;
    }
};
