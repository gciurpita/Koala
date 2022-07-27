/*
    wifi_setup_connect - takes over setup functions for wifi by:
        1. attempts connecting to wifi using ssid and password from cfg file
        2. goes into access point mode if fails after five tries
        3. access mode starts server with web page where user enters loca
            ssid and password
        4. new ssid and password as used to connect Koala to local network
        */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include <string.h>

#include "vars.h"
#include "cfg.h"
#include "koala.h"

#include "wifiSetup.h"

using namespace std;

// will use this block of code if we need to construct larger web input page and want to automate
// the process
#if 0

enum CfgId_e : byte {
    C_NONE,

    C_VER  = 1,

    C_NAME,
    C_SSID,
    C_PASS,
};

// -------------------------------------
// stored (configurable) variable description
enum { V_NONE, V_STR };

struct CfgVar_s {
    CfgId_e     id;
    void       *p;
    byte        nByte;
    byte        type;
    const char *desc;
};

// -------------------------------------
//  stored variables

CfgVar_s cfgVarTbl [] = {
    { C_NAME, (void*)   name,       MAX_CHAR,       V_STR,  "name" },

    { C_SSID, (void*)   ssid,       MAX_CHAR,       V_STR,  "ssid"},
    { C_PASS, (void*)   pass,       MAX_CHAR,       V_STR,  "pass" },


    { C_NONE, NULL,               0,              V_NONE, NULL     },
};
#endif

// these are standard values that should not need to be changed
IPAddress gateway(10, 0, 0, 1);

IPAddress subnet(255, 255, 0, 0);

AsyncWebServer server(80);
WiFiClient wifiClient;

#define print2(x, y) (Serial.print(x), Serial.println(y))

// apCode is html to get ssid and password for local network
// hard coded as we know the parameters needed

String apCode()
{
    String pageCode;
    String workingStr;
    String ssidStr, passStr, thIPStr, hostStr;
    workingStr = apIPString;
    ssidStr = ssid;
    //    ssidStr = "'" + ssidStr + "'"; // converting to string

    passStr = pass;
    //    passStr = "'" + passStr + "'"; // converting to string

    // Note that we need the user to input a local IP address.  Could use 191.168.1.251 as a default, but
    // some networks use 10.0.0.251; .251 is a guess at an IP seldom used on a local network
    thIPStr = thIPString;
    hostStr = host;

    pageCode = "<!DOCTYPE html> <html>";
    pageCode += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    pageCode += "<link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>";

    pageCode += "<head><title>Local Wifi Parameters</title> </head> <body>";
    pageCode += "<div> <h2 align='Center'> Local Wifi Parameters</h2> </div>";
    pageCode += "<div><table id='table1' ; cellspacing='5px' cellpadding='5%' ; align='center'>";
    //    pageCode += "<form id='form1' name='form1' method='GET' action='http://" + workingStr + "/rdparams'>";
    pageCode += "<form id='form1' name='form1' method='GET' onsubmit=\"event.preventDefault();>\"";

    pageCode += "<tr>  <td align='right'> WiFI network name (SSID): </td>";
    pageCode += "<td><input align='right' type='text' name='ssid' form='form1' value='" + ssidStr + "'></td></tr>";

    pageCode += "<tr>  <td align='right'> WiFI password: </td>";
    pageCode += "<td><input align='right' type='text' name='pass' form='form1' value='" + passStr + "'></td></tr>";

    pageCode += "<tr>  <td align='right'> IP address for Throttle: </td>";
    pageCode += "<td><input align='right' type='text' name='thIPStr' form='form1' value='" + thIPStr + "'></td></tr>";

    pageCode += "<tr> <td colspan='2'> Recommend 10.0.0.251 or 192.168.1.251 for Throttle IP to stay clear of other IP addresses <td><tr>";

    pageCode += "<tr>  <td align='right'> IP address for JMRI host: </td>";
    pageCode += "<td><input align='right' type='text' name='hostStr' form='form1' value='" + hostStr + "'></td></tr>";

    //    pageCode += "<tr> <td><input type='submit'  value='Submit'> </td></tr>";
    pageCode += "<tr> <td> <input type='button' onclick='submitFunc()' formaction= action='http://" + workingStr + "/rdparams' value='Submit'></td></tr>";
    pageCode += "</form></table></div>";
    pageCode += "<script>function submitFunc() {";
    pageCode += "document.getElementById('form1').submit();}";
    pageCode += "</script>";
    pageCode += "</body> </html>";
    return pageCode;
}
void wifiReconnect()
{
}

void wifiConn_FixedIP()
{

    WiFi.setHostname(name);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    WiFi.begin(ssid, pass);

    int count = 0;

    while ((WiFi.status() != WL_CONNECTED) && (count < 5))
    {
        delay(1000);
        count++;
        Serial.println("Connecting to WiFi..");
        if (count == 5)
            return;
    }

    if (!WiFi.config(thIP, gateway, subnet))
    {
        Serial.println("Fixed IP Throttle Failed to configure");
    }

    IPAddress ip = WiFi.localIP();
    printf("WiFi Network, Password: %s, %s", ssid, pass);
    print2("Throttle IP Address: ", ip);
    state |= ST_WIFI;

    return;
}

// Come up as access point and start web page to enter local ssid and password
void wifiConn_AP()
{

    WiFi.mode(WIFI_AP);
    WiFi.disconnect();

    Serial.println();
    Serial.println("Configuring access point...");

    WiFi.softAP(apSsid);

    print2("AP running: ", apSsid);

    apIP = WiFi.softAPIP();
    Serial.print("Use this IP address to setup local wifi network: ");
    Serial.println(apIP);
}

void getWifiInfo(int *wifiState)
{
    //    String webCode = apCode();

    server.on("/", HTTP_GET, [wifiState](AsyncWebServerRequest *request)
              { 
                request->send(200, "text/html", apCode()); });

    server.on("/rdparams", HTTP_GET, [wifiState](AsyncWebServerRequest *request)
              {
                if (*wifiState == 1)
                {
                if (request->hasParam("ssid"))
                {
                    AsyncWebParameter *prequest = request->getParam(0);
                    // fill ssid
                    strcpy(ssid, prequest->value().c_str());
                    print2 ("SSID: ", ssid);

                }

                if (request->hasParam("pass"))
                {
                    AsyncWebParameter *prequest = request->getParam(1);
                    // fill password
                    strcpy(pass, prequest->value().c_str());
                    print2 ("password: ", pass);
                }

                if (request->hasParam("thIPStr"))
                {
                    AsyncWebParameter *prequest = request->getParam(2);
                    // fill password
                    strcpy(thIPString, prequest->value().c_str());
                    print2 ("Throttle IP: ", thIPString);
                }
                
                if (request->hasParam("hostStr"))
                {
                    AsyncWebParameter *prequest = request->getParam(3);
                    // fill password
                    strcpy(host, prequest->value().c_str());
                    print2 ("JMRI Host: ", host);
                }
                *wifiState = 2;  //0 = initialization; 1=server started but no submit; 2=data submitted

                }
                else *wifiState = 1;

                request->send(200, "text/html", apCode()); 
                return; });
    server.begin();
    Serial.println("HTTP server started");

    return;
}

void wifiSetup()
{
    int wifiState = 0; // 0 = initialization; 1=server started but no submit; 2=data submitted

    wifiConn_FixedIP();
    while (WiFi.status() != WL_CONNECTED)
    {
        wifiConn_AP();

        // create web code and wait for input
        wifiState = 0;
        getWifiInfo(&wifiState);

        while (wifiState != 2)
        {
            delay(1000);
            print2("wifiState: ", wifiState);
        };

        // at this point we have a local ssid and password, so try fixed IP coneect
        server.end();
        wifiConn_FixedIP();
    }
}