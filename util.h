#pragma once
// http://stackoverflow.com/questions/116038/ddg#116220
namespace easel {
    namespace util {
        std::string Slurp(std::ifstream& in);
        std::string SlurpPath(std::string path);
    }
}