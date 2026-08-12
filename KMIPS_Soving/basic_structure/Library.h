//
//  Error_code.h
//  KMIPS_Soving
//
//  Created by Godric Tan on 2025/5/29.
//

#ifndef LIBRARY_H
#define LIBRARY_H

typedef enum {
    success,
    underflow,
    overflow
} Error_code;

struct Posting {
    int vec_id;
    float value;
    
    Posting(int id, float val) : vec_id(id), value(val) {}
};

struct Query{
    int term_id;
    float value;
    
    Query(int id, float val) : term_id(id), value(val) {}
};

#endif
