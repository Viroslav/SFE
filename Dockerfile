FROM ubuntu:22.04

WORKDIR /

RUN mkdir /data/
RUN mkdir /app

COPY * /app/


RUN apt-get update
RUN apt update -y
RUN apt install vim -y

RUN chmod +x /app/prereqs.sh
RUN chmod +x /app/compile.sh

RUN ./app/prereqs.sh
RUN ./app/compile.sh

#ENTRYPOINT ["bash"]
RUN apt update
RUN apt install git build-essential -y

ENTRYPOINT ["bash"]
