FROM alpine:3.9
LABEL maintainer="Mark Daams <mjtdaams@gmail.com>"

# Get package manager
RUN apk update && apk upgrade

# Add bash and set the look of the command prompt
RUN apk add bash
ENV PS1 "\u@\h:\w > "

# Install the C++compiler
RUN apk add --no-cache g++

# Create a folder for our application
WORKDIR /var/www/app



CMD tail -f /dev/null