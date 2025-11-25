/*
  StreamingActivity.cpp

  Basic operations of a streaming service
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Video.hpp"
#include "Stream.hpp"
#include "Account.hpp"

int main(int argc, char* argv[]) {

    // verify options
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << '\n';
        return 1;
    }

    // Load videos from data file
    std::vector<Video> videos;
    std::ifstream invideo(argv[1]);
    if (!invideo) {
        std::cerr << argv[0] << ": Unable to open input file " << argv[1] << '\n';
        return 1;
    }

    std::string line;
    while (getline(invideo, line)) {
        std::istringstream sline(line);

        // video type
        std::string str;
        std::getline(sline, str, ',');
        int type;
        if (str == "MOVIE")
            type = Video::MOVIE;
        else if (str == "TVSHOW")
            type = Video::TVSHOW;
        else if (str == "ORIGINAL")
            type = Video::ORIGINAL;
        // ignore any unkown types
        else
            continue;

        // video title
        std::string title;
        std::getline(sline, title, ',');

        // video hours
        std::getline(sline, str, ',');
        std::stringstream strhours(str);
        int hours;
        strhours >> hours;

        // video minutes
        std::getline(sline, str, ',');
        std::stringstream strminutes(str);
        int minutes;
        strminutes >> minutes;

        // video episodes
        std::getline(sline, str, ',');
        std::stringstream strepisodes(str);
        int episodes;
        strepisodes >> episodes;

        // create our new video for this input line
        videos.push_back(Video(title, type, hours, minutes, episodes));
    }
    invideo.close();

    // Account
    Account customer("Fred");

    // Some streams of these movies
    Stream s1(videos[0], 3);
    Stream s2(videos[1], 1);
    Stream s3(videos[2], 2);

    customer.addStream(s1);
    customer.addStream(s2);
    customer.addStream(s3);

    // Output account streaming report
    std::cout << customer.report() << '\n';

    // Output account data report
    std::cout << customer.data() << '\n';

    return 0;
}
