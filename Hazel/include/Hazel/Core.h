//
// Created by dingrui on 25-6-22.
//

#pragma once

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)