#pragma once

#include <iostream>
#include "Data.hpp"

Data desBlock(const Data &block, const Data &key);
Data desCfb(const Data &data, const Data &key);