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
#include <sstream>

#include "TransferService.h"
#include "ClientError.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

TransferService::TransferService() : HttpService("/transfers") { }


void TransferService::post(HTTPRequest *request, HTTPResponse *response) {

    //Initialize the inputs from the user
    WwwFormEncodedDict userAttributes = WwwFormEncodedDict(request->formEncodedBody());
    Document jsonDoc;
    Document::AllocatorType& newDoc = jsonDoc.GetAllocator();

    //Initalize Transfer Object
    Transfer *transfer = new Transfer();

    //check to see if the receiver is found in the database
    if(m_db->users.find(userAttributes.get("to")) != m_db->users.end()){
    }
    else{
        throw ClientError::unauthorized();
    }

    //check to see if the user has sufficent balance to make the transfer
    if(m_db->auth_tokens.at(request->getAuthToken())->balance < stoi(userAttributes.get("amount"))){
        throw ClientError::unauthorized();
    }

    //Authenticate the User
    getAuthenticatedUser(request);

    //fill the Transfer Object with appropriate values
    string authToken = request->getAuthToken();
    transfer->from = m_db->auth_tokens[authToken];
    transfer->to = m_db->users[userAttributes.get("to")];
    transfer->amount = stoi(userAttributes.get("amount"));

    //update User balance and append the successfull transfer in the database
    m_db->auth_tokens[authToken]->balance -= transfer->amount;
    m_db->users[userAttributes.get("to")]->balance += transfer->amount;
    m_db->transfers.push_back(transfer);
    int senderBalance = m_db->auth_tokens[authToken]->balance;

    Value o;
    o.SetObject();
    o.AddMember("balance", senderBalance, newDoc);

    //create an Array for the transfers (api_server.md)
    Value array;
    array.SetArray();
    
    // add an object to our array (api_server.md)
    for(unsigned int i=0; i<= (m_db->transfers.size() - 1); i++){
        Value to;
        to.SetObject();
        to.AddMember("from", m_db->transfers[i]->from->username, newDoc);
        to.AddMember("to", m_db->transfers[i]->to->username, newDoc);
        to.AddMember("amount", m_db->transfers[i]->amount, newDoc);
        array.PushBack(to, newDoc);

    }

    // and add the array to our return object (api_server.md)
    o.AddMember("transfers", array, newDoc);

    // now some rapidjson boilerplate for converting the JSON object to a string (api_server.md)
    jsonDoc.Swap(o);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    // set the return object
    response->setContentType("application/json");
    response->setBody(buffer.GetString() + string("\n"));

}
