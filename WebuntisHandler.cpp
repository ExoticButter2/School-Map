#include "WebuntisHandler.h"
#include <ArduinoJson.h>
#include <time.h>
#include <TimeHandler.h>
#include <Arduino.h>
#include <Secrets.h>

bool ConnectClientToUntis()
{
    client.setCACert(certificate);

    unsigned long start = millis();

    if (!client.connect(untisURL, 443))
    {
        char errorBuffer[256] = {};
        client.lastError(errorBuffer, sizeof(errorBuffer));

        Serial.printf("Failed after %lu ms\n", millis() - start);
        Serial.printf("Error: %s\n", errorBuffer);

        Serial.println("Failed to connect to Untis");
        return false;
    }
    else
    {
        Serial.printf("Successfully connected to Untis after: %lu ms\n", millis() - start);
        
        return true;
    }
}

bool AuthenticateUntis(String user, String password)
{
    if (!httpClient.begin(client, jsonRPCURL))
    {
        Serial.printf("Failed to connect to authentication using URL: %s", jsonRPCURL.c_str());
        return false;
    }
    else
    {
        Serial.println("Successfully connected to authentication");

        httpClient.addHeader("Content-Type", "application/json");
        JsonDocument authenticationBody;

        authenticationBody["id"] = "request";
        authenticationBody["method"] = "authenticate";
        authenticationBody["params"]["user"] = user;
        authenticationBody["params"]["password"] = password;
        authenticationBody["params"]["client"] = "ESP32S3-SchoolMap";
        authenticationBody["jsonrpc"] = "2.0";

        String requestBody;
        serializeJson(authenticationBody, requestBody);

        int httpResponseCode = httpClient.POST(requestBody);

        if (httpResponseCode > 0)
        {
            Serial.printf("HTTP Response: %d", httpResponseCode);
            String response = httpClient.getString();
            JsonDocument responseJson;

            deserializeJson(responseJson, response);

            sessionID = responseJson["result"]["sessionId"].as<String>();
            personType = responseJson["result"]["personType"];
            personID = responseJson["result"]["personId"];

            authenticatedUser = true;

            Serial.printf("Session ID: %s", sessionID.c_str());
            Serial.printf("Person Type: %s", String(personType).c_str());
            Serial.printf("Person ID: %s", String(personID).c_str());
        }
        else
        {
            Serial.printf("Failed to send http response: %s", httpClient.errorToString(httpResponseCode).c_str());
        }

        httpClient.end();
        return true;
    }
}

void LogoutUntis()
{
    if (!IsUserAuthenticated())
        return;

    if (!httpClient.begin(client, jsonRPCURL))
    {
        Serial.println("Failed to connect to authentication");
    }
    else
    {
        httpClient.addHeader("Cookie", "JSESSIONID=" + sessionID);
        httpClient.addHeader("Content-Type", "application/json");

        JsonDocument logoutBody;

        logoutBody["id"] = "request";
        logoutBody["method"] = "logout";
        logoutBody["params"] = JsonObject();
        logoutBody["jsonrpc"] = "2.0";

        String requestBody;

        serializeJson(logoutBody, requestBody);

        int httpResponseCode = httpClient.POST(requestBody);

        if (httpResponseCode > 0)
        {
            Serial.printf("HTTP Response: %d", httpResponseCode);
            sessionID = "";
            authenticatedUser = false;
            Serial.printf("Successfully logged out");
        }
        else
        {
            Serial.printf("Failed to send http response: %s", httpClient.errorToString(httpResponseCode).c_str());
        }
    }
}

String GetTimeTableToday()
{
    String timetable;

    if (!IsUserAuthenticated())
        return timetable;

    struct tm timeInfo;
    
    if (!SetTimeInfo(&timeInfo))
        return timetable;

    if (!httpClient.begin(client, jsonRPCURL))
    {
        Serial.println("Failed to connect to authentication");
    }
    else
    {
        char dateBuffer[9];

        snprintf(dateBuffer, 
            sizeof(dateBuffer), 
            "%04d%02d%02d", 
            timeInfo.tm_year + 1900, 
            timeInfo.tm_mon + 1, 
            timeInfo.tm_mday + 2 //remove addition after testing
        );

        String date = String(dateBuffer);
    
        Serial.printf("Current date: %s\n", date.c_str());

        httpClient.addHeader("Content-Type", "application/json");
        httpClient.addHeader("Cookie", "JSESSIONID=" + sessionID);

        JsonDocument requestBody;

        requestBody["id"] = "2";
        requestBody["method"] = "getTimetable";

        JsonObject options = requestBody["params"]["options"].to<JsonObject>();

        options["id"] = String(time(nullptr));
        options["element"]["id"] = personID;
        options["element"]["type"] = personType;
        options["element"]["keyType"] = "id";
        options["startDate"] = date.toInt();
        options["endDate"] = date.toInt();
        requestBody["jsonrpc"] = "2.0";

        String requestString;
        serializeJson(requestBody, requestString);

        int httpResponseCode = httpClient.POST(requestString);

        if (httpResponseCode > 0)
        {
            String responseString = httpClient.getString();
            JsonDocument responseJson;

            timetable = responseString;

            deserializeJson(responseJson, responseString);

            if (!HandleAuthenticationError(responseJson))
            {
                timetable = GetTimeTableToday();
                return timetable;
            }

            String prettyTimeTable;

            serializeJsonPretty(responseJson, prettyTimeTable);
            Serial.println(prettyTimeTable);
        }
        else
        {
            Serial.printf("Failed to send http response: %s", httpClient.errorToString(httpResponseCode).c_str());
        }
    }

    httpClient.end();
    return timetable;
}

bool IsUserAuthenticated()
{
    if (!authenticatedUser)
    {
        Serial.println("User not authenticated");
    }

    return authenticatedUser;
}

// true if authenticated, false if not
bool HandleAuthenticationError(JsonDocument jsonToCheck) // cookies can expire
{
    if (jsonToCheck["error"]["code"] == -8998) // not authenticated
    {
        AuthenticateUntis(Webuntis_User, Webuntis_Password);
        return false;
    }

    return true;
}

// void CheckForLimitError(JsonDocument jsonToCheck) only if actually needed (not sure if jsonrpc has rate limit)
// {

// }