FROM alpine:latest

RUN apk update && apk upgrade

RUN apk add g++

RUN apk add git
RUN apk add make
RUN apk add cmake


RUN apk add boost-dev
# RUN apk add sqlite-dev
# RUN apk add postgresql-libs
RUN apk add postgresql-dev

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 8000 8000

ENTRYPOINT ["./my-project-exe"]
