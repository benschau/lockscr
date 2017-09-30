#include "passHandler.h"

passHandler::passHandler() {
    this->uid = getuid();
    this->passwd = getpwuid(this->uid);

       
}

void passHandler::passInit() {

}

bool passHandler::passValidate() {

}

