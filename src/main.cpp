
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <tgbot/tgbot.h>
#include <stdio.h>
#include <iostream>


int main() {
    const char* env_token = std::getenv("TOKEN");
    if(!env_token) {
        std::cerr << "Token not found" << "\n";
    }
    std::string token(env_token);
    TgBot::Bot bot(token);
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        std::cout << "User wrote:" << message->text << "\n";
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

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
