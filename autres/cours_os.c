/*open_bsd : OS qui choisit de refuser toutes les requetes presentant un pb de sécurité : ex, si toute mémoire allouée alors on refuse l'alloc..
vmm virtual memory manager (grosso merdo garbage collector version OS)

gestion mémoire moderne : paginée, segmentée et virtuelle :
mémoire allouée par pages
segmentée en pages de 1ko
virtuelles d'adresses : mmu memory management unit
valgrind -> C prog qui réécrit malloc pour vérifier les pb de mémoires et conserve une trace (utiliser via gdb & clang-analyser)
strace => trace appels systèmes

never use vfork : use fork. cf man fork
exec : cf exec_readme.txt
UTILISEZ EXECVE : environnements

Selon l'OS l'ordre des segments mémoire peut changer, sous GNU/Linux c'est : /!\ ceci est la mémoire virtuelle /!\
Kernel
?
Stack
.mms m (librairies dynamiques : .so sous GLinux) 
Heap
?
.bss
.data
.text (code)
?

Un processus a : un espace mémoire (plusieurs des segments ci dessus, a minima .text) et des registres
les parties de l'espace mémoire qui sont conservées dans le fichier (l'image mémoire sur le disque) sont .bss .data et .text, plus qq autres

exec de lancement de prog par bash :
./a.out
>vérification que la commande est valide etc...
>bash se fork
>l'enfant exec le programme d'entrée
software/hardware interface David Patterson John L. Hennessy

mémoire physique :
gestion interuption
?
Périphériques
?
process0
process1
?
kernel data /!\ le kernel n'est jamais fixe sur la mémoire physique, pour éviter les attaques...
kernel code


"code as data" => données <=> code : pas faux grace a la mémoire virtuelle

thread = fils d'execution ; au moins un thread par processeur (plus sur certains intel)
from man clone : One use of clone() is to implement threads: multiple flows of control in a program that run concurrently in a shared address space.
Hackernews pour veille techno
use mmap (cf man mmap)

pipe (cf man pipe) = C equivalent to bash |
pipe (and the Ginux-specific pipe2) is a syscall
pipe's man is extremely instructive and provides a great use example
exo : recode pipe !
deadlock = boucle infinie ou un programme essaie d'accéder à une ressource en cours d'écriture à l'infini

edit shared_counter et rajouter un lock cf man pthread_mutex_lock

différents algos de scheduling :
    simple af : fifo (premier arrivé dans la queue, premier exécuté)
    basé sur le scoring : score évolue au fil de l'exécution du programme (syscall = bonus de score car laisse mains libres etc...) plus le score d'un process est élevé, plus on lui laisse l'acces au proc

note : l'os aussi est sujet au scheduling, puisque sur les machines modernes, il n'y a pas de proc dédié à l'OS !

NOTE : stdbool.h pour type bool !!!
*/
