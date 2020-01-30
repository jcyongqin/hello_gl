//
// Created by wangyongqin01 on 2020/1/30.
//

#pragma once
#include <string>

namespace image {
class Texture {

public:
    explicit Texture(std::string_view path, int width, int height, int channels);

};
}

