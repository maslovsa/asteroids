//
//  Entities.h
//  Asteroids
//
//  Created by MaslovSA (s.maslov@corpwebgames.com) on 01.12.14.
//  Copyright (c) 2014 Drimmi. All rights reserved.
//

#ifndef __Asteroids_Entities_H__
#define __Asteroids_Entities_H__

#include <bitset>

enum KeyState {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_FIRE
};

enum {
    JET_FRONT, JET_BACK
};

typedef std::bitset<2> Jet;
typedef std::bitset<5> Keys;

#define MakePoint(_x, _y) \
    vertex.Position = vec2(_x, _y); \
    body.push_back(vertex);

#endif //__Asteroids_Entities_H__
