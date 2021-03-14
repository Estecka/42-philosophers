#!/bin/zsh

philo=./philo_two

while ! grep <out.log "died" >/dev/null;
do; \
	$philo 4 410 200 200 5 >out.log 2>&1; \
	grep <out.log "died\|fulfilled"; \
done;
