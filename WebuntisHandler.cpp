#include "WebuntisHandler.h"
#include <ArduinoJson.h>

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
            authenticatedUser = true;
            Serial.printf("Session ID: %s", sessionID.c_str());
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
    if (!authenticatedUser)
    {
        Serial.println("User not authenticated yet");
        return;
    }

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

// JsonDocument GetTimeTable() TO-DO: IMPLEMENT THIS
// {

// }