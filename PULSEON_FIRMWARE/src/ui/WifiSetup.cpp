#include "WifiSetup.h"

#include <DNSServer.h>
#include <Preferences.h>
#include <WebServer.h>
#include <WiFi.h>

#if __has_include("wifi_secrets.h")
#include "wifi_secrets.h"
#endif

namespace
{
constexpr const char* PREFS_NS = "pulseon_wifi";
constexpr const char* AP_NAME = "PULSEON-Setup";
constexpr const char* AP_PASS = "pulseon1";
constexpr uint8_t MAX_SAVED = 5;
constexpr uint8_t MAX_CAND = 6;

struct Cred
{
    char ssid[33];
    char pass[64];
};

Cred saved[MAX_SAVED];
uint8_t savedCount = 0;
Cred cand[MAX_CAND];
uint8_t candCount = 0;
uint8_t candIdx = 0;

DNSServer* dns = nullptr;
WebServer* server = nullptr;
bool savedFlag = false;

void loadSaved()
{
    savedCount = 0;
    Preferences prefs;
    if (!prefs.begin(PREFS_NS, true))
    {
        return;
    }
    const uint8_t n = prefs.getUChar("n", 0);
    for (uint8_t i = 0; i < n && i < MAX_SAVED; ++i)
    {
        char ks[8];
        char kp[8];
        snprintf(ks, sizeof(ks), "s%u", static_cast<unsigned>(i));
        snprintf(kp, sizeof(kp), "p%u", static_cast<unsigned>(i));
        String s = prefs.getString(ks, "");
        String p = prefs.getString(kp, "");
        if (s.length() == 0)
        {
            continue;
        }
        strlcpy(saved[savedCount].ssid, s.c_str(), sizeof(saved[0].ssid));
        strlcpy(saved[savedCount].pass, p.c_str(), sizeof(saved[0].pass));
        ++savedCount;
    }
    prefs.end();
}

void storeSaved()
{
    Preferences prefs;
    if (!prefs.begin(PREFS_NS, false))
    {
        return;
    }
    prefs.putUChar("n", savedCount);
    for (uint8_t i = 0; i < savedCount; ++i)
    {
        char ks[8];
        char kp[8];
        snprintf(ks, sizeof(ks), "s%u", static_cast<unsigned>(i));
        snprintf(kp, sizeof(kp), "p%u", static_cast<unsigned>(i));
        prefs.putString(ks, saved[i].ssid);
        prefs.putString(kp, saved[i].pass);
    }
    prefs.end();
}

void addNetwork(const String& ssid, const String& pass)
{
    loadSaved();

    // Drop an older entry with the same name, then put the new one first.
    uint8_t kept = 0;
    for (uint8_t i = 0; i < savedCount; ++i)
    {
        if (ssid != saved[i].ssid)
        {
            if (kept != i)
            {
                saved[kept] = saved[i];
            }
            ++kept;
        }
    }
    savedCount = kept;
    if (savedCount >= MAX_SAVED)
    {
        savedCount = MAX_SAVED - 1;
    }
    for (int i = savedCount; i > 0; --i)
    {
        saved[i] = saved[i - 1];
    }
    strlcpy(saved[0].ssid, ssid.c_str(), sizeof(saved[0].ssid));
    strlcpy(saved[0].pass, pass.c_str(), sizeof(saved[0].pass));
    ++savedCount;
    storeSaved();
}

String esc(const String& in)
{
    String out;
    for (size_t i = 0; i < in.length(); ++i)
    {
        const char c = in[i];
        if (c == '&') out += "&amp;";
        else if (c == '<') out += "&lt;";
        else if (c == '>') out += "&gt;";
        else if (c == '"') out += "&quot;";
        else out += c;
    }
    return out;
}

void handleRoot()
{
    String page =
        "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width,initial-scale=1'>"
        "<title>PULSEON Wi-Fi</title><style>body{font-family:sans-serif;background:#111;color:#eee;padding:20px}"
        "input,button{width:100%;padding:12px;margin:8px 0;font-size:16px;border-radius:8px;border:0}"
        "button{background:#ff5d6c;color:#fff}</style></head><body><h2>PULSEON Wi-Fi</h2>"
        "<p>Pick or type your network (2.4 GHz only).</p>"
        "<form method='POST' action='/save'>"
        "<input name='ssid' list='nets' placeholder='Network name' maxlength='32' required>"
        "<datalist id='nets'>";

    const int found = WiFi.scanComplete();
    for (int i = 0; i < found && i < 20; ++i)
    {
        page += "<option value=\"" + esc(WiFi.SSID(i)) + "\">";
    }
    page +=
        "</datalist>"
        "<input name='pass' type='password' placeholder='Password' maxlength='63'>"
        "<button type='submit'>Save and connect</button></form></body></html>";
    server->send(200, "text/html", page);
}

void handleSave()
{
    const String ssid = server->arg("ssid");
    const String pass = server->arg("pass");
    if (ssid.length() == 0)
    {
        server->send(400, "text/plain", "Network name is required.");
        return;
    }
    addNetwork(ssid, pass);
    Serial.printf("[WIFI] saved network \"%s\"\n", ssid.c_str());
    server->send(200, "text/html",
                 "<html><body style='font-family:sans-serif;padding:20px'>"
                 "<h2>Saved</h2><p>The watch is joining the network now. "
                 "You can close this page.</p></body></html>");
    savedFlag = true;
}

void handleRedirect()
{
    server->sendHeader("Location", "http://192.168.4.1/", true);
    server->send(302, "text/plain", "");
}

void beginCandidate()
{
    if (candIdx >= candCount)
    {
        return;
    }
    Serial.printf("[WIFI] trying \"%s\" (%u of %u)\n", cand[candIdx].ssid,
                  static_cast<unsigned>(candIdx + 1), static_cast<unsigned>(candCount));
    WiFi.begin(cand[candIdx].ssid, cand[candIdx].pass);
}
} // namespace

void wifiConnectBegin()
{
    loadSaved();
    candCount = 0;

    // keep the secrets network first, then the saved ones
#ifdef WIFI_SSID
    strlcpy(cand[candCount].ssid, WIFI_SSID, sizeof(cand[0].ssid));
    strlcpy(cand[candCount].pass, WIFI_PASSWORD, sizeof(cand[0].pass));
    ++candCount;
#endif

    for (uint8_t i = 0; i < savedCount && candCount < MAX_CAND; ++i)
    {
#ifdef WIFI_SSID
        if (strcmp(saved[i].ssid, WIFI_SSID) == 0)
        {
            continue;
        }
#endif
        cand[candCount++] = saved[i];
    }

    candIdx = 0;
    beginCandidate();
}

bool wifiConnectAdvance()
{
    if (candIdx + 1 >= candCount)
    {
        return false;
    }
    ++candIdx;
    WiFi.disconnect();
    beginCandidate();
    return true;
}

void wifiSetupStart()
{
    wifiSetupStop();
    savedFlag = false;

    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(AP_NAME, AP_PASS);
    Serial.printf("[WIFI] setup page open: join \"%s\", go to %s\n", AP_NAME,
                  WiFi.softAPIP().toString().c_str());

    dns = new DNSServer();
    dns->start(53, "*", WiFi.softAPIP());

    server = new WebServer(80);
    server->on("/", HTTP_GET, handleRoot);
    server->on("/save", HTTP_POST, handleSave);
    server->onNotFound(handleRedirect);
    server->begin();

    WiFi.scanNetworks(true);
}

void wifiSetupLoop()
{
    if (dns != nullptr)
    {
        dns->processNextRequest();
    }
    if (server != nullptr)
    {
        server->handleClient();
    }
}

bool wifiSetupSaved()
{
    return savedFlag;
}

void wifiSetupStop()
{
    if (server != nullptr)
    {
        server->stop();
        delete server;
        server = nullptr;
    }
    if (dns != nullptr)
    {
        dns->stop();
        delete dns;
        dns = nullptr;
    }
    WiFi.scanDelete();
    WiFi.softAPdisconnect(true);
    savedFlag = false;
}

const char* wifiSetupHelp()
{
    return "On your phone join Wi-Fi PULSEON-Setup, password pulseon1, then open 192.168.4.1";
}
