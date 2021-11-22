# 42sh
[![Build Status](https://travis-ci.org/42shpimanmls/42sh.svg?branch=master)](https://travis-ci.org/42shpimanmls/42sh) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/e64c37954bc84549bf555381defa6fdc)](https://www.codacy.com/app/pilespin/42sh)

FEATURES
---

- [x] Édition de ligne
	- [x] Éditer la ligne à l’endroit où se trouve le curseur.
	- [x] Déplacer le curseur vers la gauche et vers la droite.
	- [x] Les flèches du haut et du bas pour naviguer dans l’historique.
	- [x] Couper, copier et/ou coller tout ou partie d’une ligne. `ctrl+K` `ctrl+B` `ctrl+P`
	- [x] Se déplacer par "mot" vers la gauche et vers la droite. `ctrl+LEFT` `ctrl+RIGHT`
	- [x] Aller directement au début et à la fin d’une ligne. `home` `end`
	- [x] Écrire ET éditer une commande sur plusieurs lignes.
	- [x] Saut d’une ligne à l’autre. `ctrl+UP` `ctrl+DOWN`
	- [x] Retour à la ligne partie parenthésée de la commande non refermée.
	- [x] ctrl+D et ctrl+C dans l’édition de la ligne.
	- [x] Gérer complètement les quotes et doubles quotes, (hors expansions).

- [ ] Builtins
	- [x] cd [-L|-P] [directory]
	- [x] echo [string...]
	- [x] exit [n]
	- [x] env [-i] [name=value]... [utility [argument...]]
	- [x] setenv
	- [x] unsetenv
	- [x] unset [-fv] name...
	- [x] export [-p] name[=word]...
	- [ ] history

- [x] Exécution
	- [x] Exécution de commandes avec leurs paramètres et gestion du PATH.
	- [x] Gestion des erreurs et de la valeur de retour des commandes.
	- [x] Les redirection suivantes : ">", ">>", "<".
	- [x] Les pipes “|”.
	- [x] Les opérateurs logiques "&&" et "||".
	- [x] Les back quotes "‘".
	- [x] Le séparateur ";".

- [x] Shell
	- [x] Les variables locales.
	- [x] Les inhibiteurs """ (double quote), "’" (simple quote) et "\" (backslash).

- [x] Signaux 
	- [x] ctrl+D
	- [x] ctrl+C

- [ ] Bonus
	- [ ] Le heredoc "<<".
	- [x] Complétion dynamique.
	- [ ] Le Job control, job, fg et bg, et l’operateur "&".
	- [ ] Les aggrégations de descripteurs de fichiers 2>&- etc.
	- [ ] Rechercher dans l’historique avec ctrl+R.

- [x] Structure
	- [x] init
	- [x] edit input
	- [x] break input
	- [x] parse input
	- [x] word expansion
	- [x] redirection
	- [x] execution
	- [x] wait
