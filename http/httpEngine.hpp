//
// Created by nickobelic1999 on 7/17/22.
//

#pragma once

#include <iostream>

#include <arpa/inet.h>

#include <curlpp/Easy.hpp>
#include <curlpp/Multi.hpp>
#include <curlpp/Options.hpp>


namespace MissionControl_HTTP
{

    enum class Method { Get, Head, Post, Put, Delete };

    class httpEngine
    {
    public:

        constexpr const char* MethodToString(Method& method) throw();

        httpEngine();
        ~httpEngine();
    private:

    };

} // MissionControl_HTTP

