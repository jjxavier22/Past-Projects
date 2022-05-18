//Jiss Xavier
//916427256

#define RAPIDJSON_HAS_STDSTRING 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "AccountService.h"
#include "ClientError.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

AccountService::AccountService() : HttpService("/users") {
    
}

void AccountService::get(HTTPRequest *request, HTTPResponse *response) {
    
    //Initialize the inputs from the user
    WwwFormEncodedDict userAttributes = WwwFormEncodedDict(request->formEncodedBody());
    Document jsonDoc;
    Document::AllocatorType& newDoc = jsonDoc.GetAllocator();

    //authenticate the user
    User * authenticatedUser = getAuthenticatedUser(request);

    //check whether the userID passed matches the userID on record for the specified authToken
    if(m_db->auth_tokens.at(request->getAuthToken())->user_id != request->getPathComponents()[1]){
        throw ClientError::unauthorized();
    }
    
    //set the return objects
    Value o;
    o.SetObject();
    o.AddMember("email", authenticatedUser->email, newDoc);
    o.AddMember("balance", authenticatedUser->balance, newDoc);


    jsonDoc.Swap(o);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    //set the response type and body (code from Discord + Piazza)
    response->setContentType("application/json");
    response->setBody(buffer.GetString() + string("\n"));
    response->setStatus(201); 
}



void AccountService::put(HTTPRequest *request, HTTPResponse *response) {
    
    //Initialize the inputs from the user
    WwwFormEncodedDict userAttributes = WwwFormEncodedDict(request->formEncodedBody());
    Document jsonDoc;
    Document::AllocatorType& newDoc = jsonDoc.GetAllocator();

    //authenticate the User
    User * authenticatedUser = getAuthenticatedUser(request);

    //check whether an empty email was passed in
    if(userAttributes.get("email") == ""){
        throw ClientError::unauthorized();
    }

    //checks if userID stored in the server corresponds to authToken passed in
    if(m_db->auth_tokens.at(request->getAuthToken())->user_id != request->getPathComponents()[1]){
        throw ClientError::unauthorized();
    }
    
    //update the email associated with the user
    authenticatedUser->email = userAttributes.get("email");
    
    //set the return objects
    Value o;
    o.SetObject();
    o.AddMember("email", authenticatedUser->email, newDoc);
    o.AddMember("balance", authenticatedUser->balance, newDoc);
    
    jsonDoc.Swap(o);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    //set the response type and body (code from Discord + Piazza)
    response->setContentType("application/json");
    response->setBody(buffer.GetString() + string("\n"));

    //signal success
    response->setStatus(200); 
}
