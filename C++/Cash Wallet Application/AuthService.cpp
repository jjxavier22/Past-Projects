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

#include "AuthService.h"
#include "StringUtils.h"
#include "ClientError.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

AuthService::AuthService() : HttpService("/auth-tokens") {
  
}

//Does not need to be authenticated
void AuthService::post(HTTPRequest *request, HTTPResponse *response) {

    //Initialize the inputs from the user
    WwwFormEncodedDict userAttributes = WwwFormEncodedDict(request->formEncodedBody());
    Document jsonDoc;
    Document::AllocatorType& newDoc = jsonDoc.GetAllocator();

    //ensures user doesn't pass blank username
    if(userAttributes.get("username") == ""){
        response->setStatus(400);
        return;
    }

    //ensures user doesn't pass blank password
    if (userAttributes.get("password") == ""){
        response->setStatus(400);
        return;
    }

    //ensures all entries of the username are lowercase
    for (const auto i : userAttributes.get("username")) {
        if (islower(i)) {
            continue;
        }
        else {
            response->setStatus(400);
            return;
        }
    }

    //if username is found in the database as an existing user
    if(m_db->users.find(userAttributes.get("username")) != m_db->users.end()){
        
        User* curConsumer = m_db->users.at(userAttributes.get("username"));

        //if there is a password match
        if(userAttributes.get("password") == curConsumer->password){
            //retrive the existing ID associated with the user
            string user_id = m_db->users.at(userAttributes.get("username"))->user_id;

            //create a new auth token for the user
            string auth_token = StringUtils::createAuthToken();

            //insert authToken and User pair into the database map
            pair<string, User*> authTokenUserPair(auth_token, curConsumer);
            m_db->auth_tokens.insert(authTokenUserPair);

            //set the return objects
            Value o;
            o.SetObject();
            o.AddMember("auth_token", auth_token, newDoc);
            o.AddMember("user_id", user_id, newDoc);

            jsonDoc.Swap(o);
            StringBuffer buffer;
            PrettyWriter<StringBuffer> writer(buffer);
            jsonDoc.Accept(writer);
            
            //set the response type and body (code from Discord + Piazza)
            response->setContentType("application/json");
            response->setBody(buffer.GetString() + string("\n"));
            return;
        }

        //incorrect password
        else{
            throw ClientError::unauthorized();
        }
    }

    //new user to the database
    else {

        //create new User Object
        User* newUser = new User();
        newUser->username = userAttributes.get("username");
        newUser->password = userAttributes.get("password");
        newUser->balance = 0;
        newUser->email = "";

        //assign new authtoken and userID to the new User and update Database
        string auth_token = StringUtils::createAuthToken();
        string newUserID = StringUtils::createUserId();
        newUser->user_id = newUserID;
        userAttributes.set("user_id", newUserID);
        pair<string, User*> usernameUserPair(userAttributes.get("username"), newUser);
        m_db->users.insert(usernameUserPair);
        pair<string, User*> authTokenUserPair(auth_token, newUser);
        m_db->auth_tokens.insert(authTokenUserPair);

        //set the return objects
        Value o;
        o.SetObject();
        o.AddMember("auth_token", auth_token, newDoc);
        o.AddMember("user_id", newUserID, newDoc);

        jsonDoc.Swap(o);
        StringBuffer buffer;
        PrettyWriter<StringBuffer> writer(buffer);
        jsonDoc.Accept(writer);

        //set the response type and body (code from Discord + Piazza)
        response->setContentType("application/json");
        response->setBody(buffer.GetString() + string("\n"));
        response->setStatus(201);
        
    } 

}

void AuthService::del(HTTPRequest *request, HTTPResponse *response) {

    //ensure User is authenticated
    if(getAuthenticatedUser(request) != NULL){
        //check auth_token User* map for matches and erase if found
        if(m_db->auth_tokens.find(request->getPathComponents()[1]) != m_db->auth_tokens.end()){
            m_db->auth_tokens.erase(request->getPathComponents()[1]);
        }
    }
    //no auth_token found to be deleted
    else{
        throw ClientError::unauthorized();
    }

}
