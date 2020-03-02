#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <iterator>


std::unique_ptr< std::vector<std::string> > loadFromFile(std::string filename){

    // Allocate memory for a buffer_ptr
    std::unique_ptr< std::vector<std::string> > buffer_ptr = std::make_unique< std::vector<std::string> >();

    // Load file
    std::ifstream file(filename);
    assert(file);

    std::copy(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(), std::back_inserter(*buffer_ptr));

    return buffer_ptr;
}
