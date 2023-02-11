// Copyright 2021 Nikita Pushkin

#include "functions.hpp"
#include <header.hpp>

std::mutex mx;

void print(const std::string& hash, int random) {
    /* std::cmatch result;
     std::regex regular("([\\w]{60})(['0']+)");
     std::regex_match(hash.c_str(), result, regular);
     //  if (std::regex_match(hash.c_str(), result, regular)) {*/

//  mx.lock();
//  BOOST_LOG_TRIVIAL(trace) << std::hex << random << "\twith hash:\t" << hash
//                           << "\n";
//  mx.unlock();
    std::string str=  hash.substr(60, 4);
    if (str == "0000") {

        BOOST_LOG_TRIVIAL(info)
                << random << "\twith hash:\t" << hash << "\n";
        //   auto sinkFile=bl::add_file_log(
        //            bl::keywords::file_name = "file_%5N.log",
        //            bl::keywords::rotation_size = 5 * 1024 * 1024,
        //            bl::keywords::format = "[TimeStamp]: hash");
        //   bl::add_common_attributes();
    }
}

void sha_calculation() {

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6
            (0,std::numeric_limits<int>::max());

    int random = dist6(rng);

    const std::vector<unsigned char> data_vector{
            static_cast<unsigned char>(random)};  // вектор

    std::string hash = picosha2::hash256_hex_string(data_vector);
    mx.lock();

    std::string str=  hash.substr(60, 4);
    //if (str == "1c6e") {

    BOOST_LOG_TRIVIAL(trace)
            << random << "\twith hash:\t" << hash << "\n";
    //   auto sinkFile=bl::add_file_log(
    //            bl::keywords::file_name = "file_%5N.log",
    //            bl::keywords::rotation_size = 5 * 1024 * 1024,
    //            bl::keywords::format = "[TimeStamp]: hash");
    //   bl::add_common_attributes();
//  }

    mx.unlock();
}