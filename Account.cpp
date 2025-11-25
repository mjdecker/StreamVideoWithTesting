/*
  Account.cpp

  Definition file for Account class
*/

#include "Account.hpp"
#include "Video.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// constructor
Account::Account(const std::string& name)
    : account_name(name)
{ }

// account name
std::string Account::name() const {

    return account_name;
}

// add a stream to this account
void Account::addStream(const Stream& stream) {

    streams.push_back(stream);
}

// account streaming report
std::string Account::report() const {

    // returned string
    std::ostringstream output;

    // customer name
    output << "Stream Report for Account: " << name() << '\n';

    // list streams
    output << "Streams:" << '\n';
    int totalStreams = 0;
    int totalOriginals = 0;
    int totalHours = 0;
    int totalMinutes = 0;
    for (std::vector<Stream>::const_iterator it = streams.begin(); it != streams.end(); ++it) {

        // stream title
        output << '\t' << it->video().title();

        // current total hours and minutes
        totalHours += it->video().hours() * it->viewings();
        totalMinutes += it->video().Minutes() * it->viewings();

        // stream counts and originals
        int streamCount = 0;
        int originals = 0;
        switch (it->video().type()) {

            // for movies, the stream count is the number of hours, with a minimum of 1
            case Video::MOVIE:
                streamCount += it->viewings() * (it->video().hours() ? it->video().hours() : 1);
                break;

            // for TV shows, the stream count is just the number of streams
            case Video::TVSHOW:
                streamCount += it->viewings();
                break;

            // for TV shows, the stream count is just the number of streams
            case Video::ORIGINAL:
                originals += it->viewings();
                streamCount += it->viewings();
                break;
        }

        // stream counts for this video
        std::ostringstream out_str_stream;
        output << '\t' << streamCount << '\n';

        totalStreams += streamCount;
        totalOriginals += originals;
    }
    output << '\n';

    // total stream counts
    output << "Total Stream Events: " << totalStreams << '\n';

    // total non-original stream counts
    output << "Non-Original Stream Events: " << (totalStreams - totalOriginals) << '\n';

    // total time
    int time = totalHours + totalMinutes / 60;
    output << "Total Time: " << time << ':';
    time = totalMinutes % 60;
    output << time << '\n';

    return output.str();
}

// account data in CSV
std::string Account::data() const {

    // returned string
    std::ostringstream output;

    // customer name
    std::string name = this->name();

    // list of streams
    for (std::vector<Stream>::const_iterator it = streams.begin(); it != streams.end(); ++it) {

        // customer name
        output << name << ',';

        // stream type
        switch (it->video().type()) {

            // movies
            case Video::MOVIE:
                output << "MOVIE";
                break;

            // tv
            case Video::TVSHOW:
                output << "TVSHOW";
                break;

            // original
            case Video::ORIGINAL:
                output << "ORIGINAL";
                break;
        }       

        // stream title
        output << ',' << it->video().title();

        // stream hours and minutes
        output << ',' << (it->video().hours() * it->viewings());
        output << ',' << (it->video().Minutes() * it->viewings());

        // stream counts
        output << ',';
        switch (it->video().type()) {

            // for movies, the stream count is the number of hours, with a minimum of 1
            case Video::MOVIE:
                if (it->video().hours()) {
                    output << (it->viewings() * it->video().hours());
                } else {
                    output << it->viewings();
                }
                break;

            // all others are just the number of occurrences
            default:
                output << it->viewings();
                break;
        }

        output << '\n';
    }

    return output.str();
}
