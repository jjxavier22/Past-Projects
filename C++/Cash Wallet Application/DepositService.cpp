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

#include "DepositService.h"
#include "Database.h"
#include "ClientError.h"
#include "HTTPClientResponse.h"
#include "HttpClient.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

DepositService::DepositService() : HttpService("/deposits") { }

void DepositService::post(HTTPRequest *request, HTTPResponse *response) {

    //Initialize the inputs from the user
    WwwFormEncodedDict userAttributes = WwwFormEncodedDict(request->formEncodedBody());
    Document jsonDoc;
    Document::AllocatorType& newDoc = jsonDoc.GetAllocator();

    //Initalize Deposit Object
    Deposit *deposit = new Deposit();

    //Check that the amount specified is not negative
    if(stoi(userAttributes.get("amount")) <= 50){
        throw ClientError::badRequest();
    }
    //Check that the stripe_token is provided
    if(userAttributes.get("stripe_token") == ""){
        throw ClientError::unauthorized();
    }
    //Authenticate the User
    getAuthenticatedUser(request);


    //Prof King's code (stripe.md)
    WwwFormEncodedDict body;
    body.set("amount", userAttributes.get("amount"));
    body.set("currency", "usd");
    body.set("source", userAttributes.get("stripe_token"));
    string encoded_body = body.encode();

    //Prof King's code "from the gunrock server to Stripe" (stripe.md)
    HttpClient client("api.stripe.com", 443, true);
    client.set_basic_auth(m_db->stripe_secret_key, "");
    HTTPClientResponse *client_response = client.post("/v1/charges", encoded_body);

    //check if we get a valid Client Response (HTTPClientResponse.h)
    if(client_response->success()){
        
    }
    else{
        throw ClientError::badRequest();
    }

    // This method converts the HTTP body into a rapidjson document (stripe.md)
    Document *d = client_response->jsonBody();
    string chargeID = (*d)["id"].GetString();
    delete d;

    //fill the Deposit Object with appropriate values
    deposit->stripe_charge_id = chargeID;
    deposit->amount = stoi(userAttributes.get("amount"));
    string authToken = request->getAuthToken();
    deposit->to = m_db->auth_tokens[authToken];

    //update User balance and append the successfull deposit in the database
    m_db->auth_tokens[authToken]->balance += deposit->amount;
    m_db->deposits.push_back(deposit);
    int userBalance = m_db->auth_tokens[authToken]->balance;

    Value o;
    o.SetObject();
    o.AddMember("balance", userBalance, newDoc);

    //create an Array for the deposits (api_server.md)
    Value array;
    array.SetArray();

    // add an object to our array (api_server.md)
    for(unsigned int i=0; i<= (m_db->deposits.size() - 1); i++){
        Value to;
        to.SetObject();
        to.AddMember("to", m_db->deposits[i]->to->username, newDoc);
        to.AddMember("amount", m_db->deposits[i]->amount, newDoc);
        to.AddMember("stripe_charge_id", m_db->deposits[i]->stripe_charge_id, newDoc);
        array.PushBack(to, newDoc);

    }

    // and add the array to our return object (api_server.md)
    o.AddMember("deposits", array, newDoc);

    // now some rapidjson boilerplate for converting the JSON object to a string (api_server.md)
    jsonDoc.Swap(o);
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    // set the return object
    response->setContentType("application/json");
    response->setBody(buffer.GetString() + string("\n"));

}
