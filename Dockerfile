FROM alpine:latest

RUN apk update && apk add g++ git

#RUN git clone https://github.com/ptrsh/pahpsd.git

WORKDIR /pahpsd

COPY lab.cpp .

RUN g++ -fopenmp lab.cpp -o lab

CMD ["./lab"]