//
// Created by nickobelic1999 on 7/25/22.
//

#pragma once

#include "../toolbox/utils.hpp"

namespace MissionControl_S3
{

    MissionControl_Utils::Multimap GetCommonListObjectsQueryParams(std::string& delimiter,
                                                    std::string& encoding_type,
                                                    unsigned int max_keys,
                                                    std::string& prefix);

    class BaseClient
    {
    public:

    protected:

    private:

    };

}
