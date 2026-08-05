# Build stage: compiles the benchmark with the toolchain from the README.
FROM gcc:13-bookworm AS build 
# Debian Bookworm is a Linux distribution.
WORKDIR /app
# Creates the app dir. if it does not exist and positions itself within it.
COPY include/ include/
# Copies the file folder include/ to the app/include dir. of the container.
COPY src/ src/
COPY Makefile .
RUN make

# Runtime stage: ships only the compiled binary, no compiler included.
FROM debian:bookworm-slim
WORKDIR /app
COPY --from=build /app/bin/main ./bin/main
ENTRYPOINT ["./bin/main"]
CMD ["2"]
