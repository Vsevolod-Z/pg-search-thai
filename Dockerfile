FROM postgres:14 as builder
WORKDIR /build
COPY . .
RUN apt update -y && apt install -y git libthai-dev libc6-dev build-essential postgresql-server-dev-14 && \
	cd /build && \
	make all

