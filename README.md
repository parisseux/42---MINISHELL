

1. display a prompt -> minishell$
---> with worknig history
2. read input
--> search for executable careful with quotes
3. parsing 
4. link between parsing & command
5. create commands et execute 
6. handle signal
7. pipe - Redirects the output of one command into the input of another
8. redirection input/output t/from files

GIT BRANCH
- pour voir les différentes branch : git branch
- pour créer une nouvelle branch : git branch [nom nouvelle branch]
- pour aller sur une branch : git checkout [nom branch]
j'ai pas encore merge ça fait peur

--------------- Remaques ----------------
quand on change de PATH, l'historique s'affiche plus dans le fichier, jusqu'a ce quon retourne dans le path dans le dossier minishell


Gestion des entrées/sorties:
------------------------------------------------------------------------------------
readline	        Lit une ligne depuis l'entrée standard avec édition
rl_clear_history	Efface l'historique de readline
rl_on_new_line	    Indique à readline qu'on est sur une nouvelle ligne
rl_replace_line	    Remplace la ligne en cours dans readline
rl_redisplay	    Rafraîchit l'affichage de readline
add_history	        Ajoute une ligne à l'historique de readline
printf	            Affiche du texte formaté
write	            Écrit des données dans un descripteur de fichier
open	            Ouvre un fichier ou un périphérique
read	            Lit des données depuis un descripteur de fichier
close	            Ferme un descripteur de fichier
dup, dup2	        Dupliquent un descripteur de fichier

Memoire:
------------------------------------------------------------------------------------
malloc	            Alloue de la mémoire dynamiquement
free	            Libère la mémoire allouée dynamiquement

Processeurs & signaux 
------------------------------------------------------------------------------------
fork	            Crée un nouveau processus (clone du processus parent)
wait, waitpid,      Attendent la fin d'un processus enfant
wait3, wait4	
signal, sigaction	Configurent le traitement des signaux
sigemptyset,        Manipulent les ensembles de signaux
sigaddset	
kill	            Envoie un signal à un processus
exit	            Termine le processus en cours
execve	            Exécute un programme

Gestion des répertoires:
------------------------------------------------------------------------------------
opendir	            Ouvre un flux de répertoire
readdir	            Lit une entrée d'un flux de répertoire
closedir	        Ferme un flux de répertoire
getcwd	            Obtient le répertoire de travail actuel
chdir	            Change le répertoire de travail
access	            Vérifie les permissions d'accès à un fichier
stat, lstat, fstat	Obtiennent des informations sur un fichier
unlink	            Supprime un nom du système de fichiers
pipe	            Crée un tube (pipe) pour la communication inter-processus

Gestion d'erreur:
------------------------------------------------------------------------------------
strerror	        Retourne une chaîne décrivant l'erreur
perror	            Affiche un message d'erreur système

Manipulation de terminal :
------------------------------------------------------------------------------------
isatty	            Vérifie si un descripteur de fichier se réfère à un terminal
ttyname	            Obtient le nom du terminal
ttyslot	            Trouve l'index de l'entrée du terminal actuel
ioctl	            Contrôle un périphérique
getenv	            Obtient une variable d'environnement
tcsetattr,          Configurent les attributs du terminal
tcgetattr	
tgetent, tgetflag,  Fonctions de la base de données terminfo
tgetnum, tgetstr	
tgoto, tputs	    Fonctions pour le positionnement du curseur et l'affichage

echo 
<img width="571" alt="Screenshot 2025-02-07 at 16 07 11" src="https://github.com/user-attachments/assets/e96deb95-d91f-4f38-b3f8-00dfc8b24a04" />
