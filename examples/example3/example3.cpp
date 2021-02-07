#include <iostream>

#include "kitepp/kitews.hpp"

void onConnect(kitepp::kiteWS* ws) {

    ws->subscribe({ 408065 });
    ws->setMode("quote", { 408065 });

    std::cout << "connected..\n";
};

// unsigned int tickCount = 0;
void onTicks(kitepp::kiteWS* ws, const std::vector<kitepp::tick>& ticks) {

    std::cout << "onTicks called\n";

    // tickCount++;
    for (const auto& i : ticks) {

        std::cout << "instrument token: " << i.instrumentToken << " last price: " << i.lastPrice << "\n";
    };

    // if (tickCount >= 100) { ws->stop(); };
};

void onOrderUpdate(kitepp::kiteWS* ws, const kitepp::postback& postback) {

    std::cout << "trading symbol: " << postback.tradingSymbol << " status: " << postback.status
              << " filled quantity: " << postback.filledQuantity << "\n";
};

void onMessage(kitepp::kiteWS* ws, const std::string& message) { std::cout << "Received message: " << message << "\n"; }

void onError(kitepp::kiteWS* ws, int code, const std::string& message) {

    std::cout << "Error! Code: " << code << " message: " << message << "\n";
};

void onWSError(kitepp::kiteWS* ws) { std::cout << "Couldn't connect..\n"; };

void onTryReconnect(kitepp::kiteWS* ws, unsigned int attemptCount) {

    std::cout << "Trying to reconnect.. Attempt " << attemptCount << "\n";
};

void onReconnectFail(kitepp::kiteWS* ws) { std::cout << "Failed to reconnect!\n"; }

void onClose(kitepp::kiteWS* ws, int code, const std::string& message) {
    std::cout << "onClose: Closed the connection.. code: " << code << " message: " << message << "\n";
}

int main(int argc, char const* argv[]) {

    kitepp::kiteWS kWS("a9gg2394xe9sqmjc", 5000, true, 5);

    kWS.setAccessToken("3mxGoAL82rTFfD3vjAR6oVbE2z8qK8y8");
    kWS.onConnect = onConnect;
    kWS.onTicks = onTicks;
    kWS.onOrderUpdate = onOrderUpdate;
    kWS.onMessage = onMessage;
    kWS.onError = onError;
    kWS.onWSError = onWSError;
    kWS.onTryReconnect = onTryReconnect;
    kWS.onReconnectFail = onReconnectFail;
    kWS.onClose = onClose;

    kWS.connect();

    kWS.run();

    kWS.stop();

    //!

    /*uWS::Hub hub;
    uWS::Group<uWS::CLIENT>* hubGroup;
    std::unique_ptr<uS::Async> hubTrigger;

    hubGroup = hub.createGroup<uWS::CLIENT>();

    hubGroup->onConnection([](uWS::WebSocket<uWS::CLIENT>* ws, uWS::HttpRequest req) {
        std::cout << "connect, sending HELLO" << std::endl;
        std::string msg = "HELLO";
        ws->send(msg.data(), msg.size(), uWS::OpCode::TEXT);
    });

    hubGroup->onMessage([](uWS::WebSocket<uWS::CLIENT>* ws, char* message, size_t length, uWS::OpCode opCode) {
        std::cout << "Got reply: " << std::string(message, length) << std::endl;
        ws->terminate();
    });

    hubGroup->onDisconnection([](uWS::WebSocket<uWS::CLIENT>* ws, int code, char* message, size_t length) {
        std::cout << "Disconnect." << std::endl;
    });

    hub.connect("wss://echo.websocket.org", nullptr, {}, 5000, hubGroup);

    hub.run();*/

    //!

    // return 0;
};
