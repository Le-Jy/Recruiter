#pragma once

#include <string>

template <typename T>
class Singleton
{
public:
    static T& instance();
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
};

class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;

public:
    void open_log_file(const std::string& file);
    void write_to_log_file();
    void close_log_file();

private:
    Logger() = default;
};
#include "singleton.hxx"
