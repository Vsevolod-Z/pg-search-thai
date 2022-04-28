FROM bitnami/postgresql:13 as builder
USER root
WORKDIR /build
COPY . .
RUN apt update -y && apt install -y git libthai-dev libc6-dev build-essential && \
	cd /build && \
	make all


FROM bitnami/postgresql:13
COPY --from=builder /build/thai_parser/thai_parser.so /opt/bitnami/postgresql/lib/
COPY --from=builder /build/thai_parser/thai_parser.control /opt/bitnami/postgresql/share/extension/
COPY --from=builder /build/thai_parser/sql/thai_parser--1.0.sql /opt/bitnami/postgresql/share/extension/
COPY --from=builder /build/thai_parser/sql/thai_parser--unpackaged--1.0.sql /opt/bitnami/postgresql/share/extension/
