# Makefile for Docker tasks

# Variables
DOCKER_COMPOSE = docker-compose
DOCKERFILE_DIR = .  # Replace with the actual path

# Targets
.PHONY: build run start stop down clean

build:
	$(DOCKER_COMPOSE) -f docker-compose.yaml build

run:
	$(DOCKER_COMPOSE) -f docker-compose.yaml up -d

brun:
	$(DOCKER_COMPOSE) -f docker-compose.yaml up --build -d

start:
	$(DOCKER_COMPOSE) -f docker-compose.yaml start

stop:
	$(DOCKER_COMPOSE) -f docker-compose.yaml stop

down:
	$(DOCKER_COMPOSE) -f docker-compose.yaml down

clean: down
	$(DOCKER_COMPOSE) -f docker-compose.yaml down --volumes
	docker rmi website_nginx

# docker rm -f $(docker ps -qa)
# docker rmi -f $(docker images -qa)
