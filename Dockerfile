FROM ubuntu:latest as builder
USER root
WORKDIR /build
COPY . .
RUN apt update -y && apt install -y git libthai-dev libc6-dev build-essential && \
	cd /build && \
	make all


FROM bitnami/postgres
USER root
RUN mkdir -p /opt/bitnami/postgresql/lib /opt/bitnami/postgresql/share/extension 
COPY --from=builder thai_parser/thai_parser.so /opt/bitnami/postgresql/lib/
COPY --from=builder thai_parser/thai_parser.control /opt/bitnami/postgresql/share/extension/
COPY --from=builder thai_parser/sql/thai_parser--1.0.sql /opt/bitnami/postgresql/share/extension/
COPY --from=builder thai_parser/sql/thai_parser--unpackaged--1.0.sql /opt/bitnami/postgresql/share/extension/
RUN chmod 755 /opt/bitnami/postgresql/lib/thai_parser.so && \
    chmod 644 -R /opt/bitnami/postgresql/share/extension/

USER 1001


