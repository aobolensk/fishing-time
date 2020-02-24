#ifndef INCLUDE_ARGPARSER_H_
#define INCLUDE_ARGPARSER_H_
#include <QCommandLineParser>

class ArgParser {
private:
    QCommandLineParser qParser;
    QCommandLineOption errorOption,
                       resetOption;
public:
    ArgParser();
    int process();
    ~ArgParser() = default;
};

#endif // INCLUDE_ARGPARSER_H_
