#ifndef _URIUTIL
#define _URIUTIL

#include "util.hpp"
#include "uritokenstructures.hpp" 

// Some helper functions to splice URI tokens
extern bool seperate_token_from_uri(char * uri, std::vector<std::string> &tokenArray);
extern bool split_token_key_value(std::vector<std::string> Tokens,std::vector<std::string>& key,std::vector<std::string>& value);
extern bool split_token_key_value_serialise(std::vector<std::string>& Tokens,std::vector<Token>& SerialisedToken);
extern Token seperate_value_key(char * token );

#endif //_URIUTIL