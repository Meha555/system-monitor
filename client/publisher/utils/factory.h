#pragma once

namespace monitor {

template<typename Product>
class Factory {
public:
    Factory() = default;
    virtual ~Factory() = default;
    virtual Product* create() = 0;
};

}