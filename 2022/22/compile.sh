# Compile sol.cpp into 'sol' using options to make easier finding bugs

g++ sol.cpp -o sol -Wall -Wextra -fsanitize=undefined -fsanitize=address
