//
// Created by nickobelic1999 on 7/24/22.
//

#pragma once

#include <string>
#include <set>
#include <map>
#include <list>

namespace MissionControl_Utils
{

    class Utils
    {
    public:

        static std::string ToLower(std::string str);

        Utils();
        ~Utils();
    private:


    }; //Utils

    /**
    * Multimap represents dictionary of keys and their multiple values.
    */
    class Multimap {
    private:
        std::map<std::string, std::set<std::string>> map_;
        std::map<std::string, std::set<std::string>> keys_;

    public:

        Multimap() {}

        Multimap(const Multimap& headers) { this->AddAll(headers); }

        void Add(std::string key, std::string value);

        void AddAll(const Multimap& headers);

        std::list<std::string> ToHttpHeaders();

        std::string ToQueryString();

        operator bool() const { return !map_.empty(); }

        bool Contains(std::string_view key);

        std::list<std::string> Get(std::string_view key);

        std::string GetFront(std::string_view key);

        std::list<std::string> Keys();

        void GetCanonicalHeaders(std::string& signed_headers,
                                 std::string& canonical_headers);

        std::string GetCanonicalQueryString();
    };  // Multimap

}


