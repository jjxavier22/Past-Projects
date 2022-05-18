//Jiss Xavier
//916427256

#include <iostream>

#include <stdlib.h>
#include <stdio.h>

#include "HttpService.h"
#include "ClientError.h"

using namespace std;

HttpService::HttpService(string pathPrefix) {
  this->m_pathPrefix = pathPrefix;
}

User *HttpService::getAuthenticatedUser(HTTPRequest *request)  {
  // TODO: implement this function

  //first check if authToken is specified by user
  if(request->getAuthToken() == ""){
    throw ClientError::unauthorized();
  }
  
  //loop through authToken,User* map looking for matches
  for(auto const& authorizationToken: m_db->auth_tokens){
    if(request->getAuthToken() == authorizationToken.first){
      //if match is found take store the User* value from the map
      User* authorizedUser = authorizationToken.second;
      return authorizedUser;
    }
    else{
      continue;
    }
  }

  //no matches found in the authToken,User* map
  throw ClientError::unauthorized();

}

string HttpService::pathPrefix() {
  return m_pathPrefix;
}

void HttpService::head(HTTPRequest *request, HTTPResponse *response) {
  cout << "HEAD " << request->getPath() << endl;
  throw ClientError::methodNotAllowed();
}

void HttpService::get(HTTPRequest *request, HTTPResponse *response) {
  cout << "GET " << request->getPath() << endl;
  throw ClientError::methodNotAllowed();
}

void HttpService::put(HTTPRequest *request, HTTPResponse *response) {
  cout << "PUT " << request->getPath() << endl;
  throw ClientError::methodNotAllowed();
}

void HttpService::post(HTTPRequest *request, HTTPResponse *response) {
  cout << "POST " << request->getPath() << endl;
  throw ClientError::methodNotAllowed();
}

void HttpService::del(HTTPRequest *request, HTTPResponse *response) {
  cout << "DELETE " << request->getPath() << endl;
  throw ClientError::methodNotAllowed();
}

