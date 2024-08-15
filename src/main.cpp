
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <stdio.h>
#include <iostream>
#include <tgbot/tgbot.h>
#include "handlers/handlers.h"

int main() {
    const char* env_token = std::getenv("TOKEN");
    if(!env_token) {
        std::cerr << "Token not found" << "\n";
    }
    std::string token(env_token);
    TgBot::Bot bot(token);

    echo_handler(bot);

    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
    });

    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username << "\n";
        bot.getApi().deleteWebhook();

        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Long poll started\n";
            longPoll.start();
        }
    } catch (std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
    }

    return 0;
}
