#include"IdNotFoundLager.h"

IdNotFoundLager::IdNotFoundLager(const std::string &message) : std::runtime_error(message) {}
