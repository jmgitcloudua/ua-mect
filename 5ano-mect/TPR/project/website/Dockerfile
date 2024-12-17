# Use an official Ngnix runtime as a parent image
FROM nginx:1.15.8-alpine

# Set the working directory to /app
WORKDIR /app

# Copy your application files into the Nginx container's default webroot directory
COPY ./app /usr/share/nginx/html

# Make port 80 available to the world outside this container
EXPOSE 80