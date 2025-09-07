//
// Created by Master0914 on 07.09.2025.
//

#ifndef INC_3DENGINE_DEBUG_H
#define INC_3DENGINE_DEBUG_H

#endif //INC_3DENGINE_DEBUG_H

#pragma once
#include <iostream>

#ifdef DEBUG_MODE
#define DEBUG_PRINT(x) do { std::cout << x << std::endl; } while(0)
#else
#define DEBUG_PRINT(x) do {} while(0)
#endif