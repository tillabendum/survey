#ifndef GUARD_MAIN
#define GUARD_MAIN

#include <string>

class Record{

typedef enum {LITERAL, HEX, DEC, BIN, NIHIL} record_type_t;

  public:
    record_type_t       type;
    std::string         literal;
    int                 num_digits;


};


#endif
