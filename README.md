# Spell_Masters

1.Players take turns choosing words from a provided list.
2.Each chosen word cannot be selected again.
3.The next player must choose a word that starts with the last letter of the previously chosen word.
4.If a player picks a word whose last letter doesn't start any remaining words, they win.

to run program:

gcc -c main.c -o main.o
gcc -c utilities.c -o utilities.o
gcc -c pvp.c -o pvp.o
gcc -c pvb.c -o pvb.o
gcc -c botLogic.c -o botLogic.o
gcc main.o utilities.o pvp.o pvb.o botLogic.o -o spell_master
./spell_master


for test 
gcc -c test.c -o test.o
gcc -c utilities.c -o utilities.o
gcc -c botLogic.c -o botLogic.o
gcc test.o utilities.o botLogic.o -o TEST
./TEST

gcc -c test2.c -o test2.o
gcc -c utilities.c -o utilities.o
gcc -c botLogic.c -o botLogic.o
gcc test2.o utilities.o botLogic.o -o TEST
./TEST