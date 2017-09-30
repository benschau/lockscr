#ifndef PASSHANDLER_H
#define PASSHANDLer_H

#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <vector>

typedef struct {
    char c;
    u_int16_t x, y; 
} passwdch;

class passHandler {
    std::vector<passwdch> input;
    uid_t uid;
    struct passwd* passwd; 

    public:                                                                                                                                      
        passHandler();
        
        void passInit();
        
        bool passValidate();
};

#endif
