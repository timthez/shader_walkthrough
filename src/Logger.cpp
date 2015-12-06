//
//  Logger.cpp
//  opengl-series
//
//  Created by Tim Zuercher on 12/5/15.
//
//

#include "Logger.h"

bool Logger::show = true;

void Logger::log(const char * str){
    if(show){
        printf("%s\n",str);
    }
}