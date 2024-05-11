namespace easel::util {
    std::string Slurp(std::ifstream& in) {
        std::ostringstream sstr;
        sstr << in.rdbuf();
        return sstr.str();
    }

    std::string SlurpPath(std::string path) {
        auto stream = std::ifstream(path);
        return Slurp(stream);
    }
}