FROM reo7sp/tgbot-cpp

WORKDIR /usr/src/everyday_bot
COPY . .
RUN cmake .
RUN make -j4
CMD ["./everyday_bot"]