#!/bin/bash

norminette=~/.norminette/norminette.rb

${norminette} *.[ch];
${norminette} minilibft/*.[ch]