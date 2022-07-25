//
// Created by nickobelic1999 on 7/17/22.
//

#pragma once

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

#include <curlpp/Easy.hpp>
#include <curlpp/Multi.hpp>
#include <curlpp/Options.hpp>

#include "../toolbox/utils.hpp"



namespace MissionControl_HTTP
{

    enum class Method { Get, Head, Post, Put, Delete };

    class httpEngineClient
    {
    public:

        constexpr const char* Method2String(Method& method) throw();

        /**
         * Url represents HTTP URL and it's components.
         */
        struct URL
        {
            bool            isHTTPS;
            std::string     host;
            unsigned int    port        = 0;
            std::string     path;
            std::string     query_string;

            operator bool() const { return !host.empty(); }

            std::string String() {
                if (host.empty()) return "";

                std::string url = (isHTTPS ? "https://" : "http://") + host;
                if (port) url += ":" + std::to_string(port);
                if (!path.empty()) {
                    if (path.front() != '/') url += '/';
                    url += path;
                }
                if (!query_string.empty()) url += "?" + query_string;

                return url;
            }

            std::string HostHeaderValue() {
                if (!port) return host;
                return host + ":" + std::to_string(port);
            }

            static URL Parse(std::string value) {
                std::string scheme;
                size_t pos = value.find("://");
                if (pos != std::string::npos) {
                    scheme = value.substr(0, pos);
                    value.erase(0, pos + 3);
                }

                scheme = MissionControl_Utils::Utils::ToLower(scheme);


                if (!scheme.empty() && scheme != "http" && scheme != "https") return URL{};

                bool https = (scheme.empty() || scheme == "https");

                std::string host;
                std::string path;
                std::string query_string;
                pos = value.find("/");
                if (pos != std::string::npos) {
                    host = value.substr(0, pos);
                    value.erase(0, pos + 1);

                    pos = value.find("?");
                    if (pos != std::string::npos) {
                        path = value.substr(0, pos);
                        value.erase(0, pos + 1);
                        query_string = value;
                    } else {
                        path = value;
                    }
                } else {
                    pos = value.find("?");
                    if (pos != std::string::npos) {
                        host = value.substr(0, pos);
                        value.erase(0, pos + 1);
                        query_string = value;
                    } else {
                        host = value;
                    }
                }

                if (host.empty()) return URL{};

                unsigned int port = 0;
                struct sockaddr_in6 dst;
                if (inet_pton(AF_INET6, host.c_str(), &(dst.sin6_addr)) <= 0) {
                    if (host.front() != '[' || host.back() != ']') {
                        std::stringstream ss(host);
                        std::string portstr;
                        while (std::getline(ss, portstr, ':')) {
                        }

                        if (!portstr.empty()) {
                            try {
                                port = std::stoi(portstr);
                                host = host.substr(0, host.rfind(":" + portstr));
                            } catch (std::invalid_argument) {
                                port = 0;
                            }
                        }
                    }
                } else {
                    host = "[" + host + "]";
                }

                if (!https && port == 80) port = 0;
                if (https && port == 443) port = 0;

                return URL{https, host, port, path, query_string};
            }
        };//URL struct

        struct DataFunctionArgs;

        using DataFunction = std::function<bool(DataFunctionArgs)>;

        struct Response;

        struct DataFunctionArgs {
            curlpp::Easy* handle = NULL;
            Response* response = NULL;
            std::string datachunk;
            void* userdata = NULL;
        };  // struct DataFunctionArgs

        struct Request {
            Method method;
            httpEngineClient::URL url;
            MissionControl_Utils::Multimap headers;
            std::string_view body = "";
            DataFunction datafunc = NULL;
            void* userdata = NULL;
            bool debug = false;
            bool ignore_cert_check = false;
            std::string ssl_cert_file;
            std::string key_file;
            std::string cert_file;

            Request(Method method, Url url);
            Response Execute();
            operator bool() const {
                if (method < Method::Get || method > Method::Delete) return false;
                return url;
            }

        private:
            Response execute();
        };  // struct Request

        struct Response {
            std::string error;
            DataFunction datafunc = NULL;
            void* userdata = NULL;
            int status_code = 0;
            MissionControl_Utils::Multimap headers;
            std::string body;

            size_t ResponseCallback(curlpp::Multi* requests, curlpp::Easy* request,
                                    char* buffer, size_t size, size_t length);
            operator bool() const {
                return error.empty() && status_code >= 200 && status_code <= 299;
            }
            error::Error Error() {
                if (!error.empty()) return error::Error(error);
                if (status_code && (status_code < 200 || status_code > 299)) {
                    return error::Error("failed with HTTP status code " +
                                        std::to_string(status_code));
                }
                return error::SUCCESS;
            }

        private:
            std::string response_;
            bool continue100_ = false;
            bool status_code_read_ = false;
            bool headers_read_ = false;

            error::Error ReadStatusCode();
            error::Error ReadHeaders();
        };  // struct Response

        httpEngineClient();
        ~httpEngineClient();

    private:

    };

} // MissionControl_HTTP

