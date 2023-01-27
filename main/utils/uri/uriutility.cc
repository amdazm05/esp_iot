#include "uriutility.hpp"

extern bool seperate_token_from_uri(char * uri, std::vector<std::string> &tokenArray)
{
    char * reqToken = strtok(uri,"?");
    reqToken = strtok(NULL,"&");
    while(reqToken!=NULL)
    {
        tokenArray.push_back(std::string(reqToken));
        std::cout<<reqToken<<std::endl;
        reqToken = strtok(NULL,"&");
    }
    return tokenArray.size()>0 ? true:false;
}

extern Token seperate_value_key(char * token )
{
    Token TokenObj = {};
    char * reqToken = strtok(token,"=");
    if(reqToken)
    {
        TokenObj.key = std::string(reqToken);
        reqToken = strtok(NULL,"");
        if(reqToken)
        {
            TokenObj.value = std::string(reqToken);
        }
    }
    return TokenObj;
}

extern bool split_token_key_value_serialise(std::vector<std::string>& Tokens,std::vector<Token>& SerialisedToken)
{
    if(Tokens.size()>0)
        for(int i=0;i<Tokens.size();i++)
        {
            SerialisedToken.emplace_back(seperate_value_key(Tokens[i].data()));
        }
    return SerialisedToken.size()>0 ? true:false;
}