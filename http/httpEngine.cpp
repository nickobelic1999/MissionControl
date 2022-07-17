//
// Created by nickobelic1999 on 7/17/22.
//

#include "httpEngine.hpp"

using namespace MissionControl_HTTP;

constexpr const char* httpEngine::Method2String(Method& method) throw()
{
    switch(method)
    {
        case Method::Get:
            return "GET";
        case Method::Head:
            return "HEAD";
        case Method::Post:
            return "POST";
        case Method::Put:
            return "PUT";
        case Method::Delete:
            return "DELETE";
        default:
            std::cerr << "ABORT: Unable to determine http method, fatal error!" << std::endl;
            std::terminate();
    }

    return NULL;
}

httpEngine::httpEngine()
{}

httpEngine::~httpEngine()
{}