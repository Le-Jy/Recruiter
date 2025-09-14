# CODE REVIEW 42SH

## Code review du 23/01/24 : Presentation du module Extansion

-> Pour utiliser le module expansion, appeller init_expansion() au debut du main, et penser à appeller free_expansion() à la fin

-> Pour utiliser les variables speciales, appeller set_special_variables() au debut du main

### Utilisation de l'expansion :

-> Pour utiliser l'expansion, appeller expand_word() dans visit_word. L'expansion renvoie la string approrié dans le cas d'une string, ou la valeur de la variable dans le cas d'une variable de la forme $a

-> Il faut passer en parametre une copie de la string originale, et penser à la free après

-> La valeur de retour de expand_word est importante pour savoir si l'expansion s'est bien passé

### Utilisation des variables spéciales : 

-> Les variables $@ et $1 .... $n ne sont pas initialisées par défault, il faut le faire avant de les utiliser avec add_special_var(struct special_var *v)

-> Les autres variables speciales existent par default

-> Pour modifier une variables spéciale il faut appeller modify_special_var(struct special_var *v)

-> Exemple de code nécessaire pour appeller les fonctions add et modify:

```
char **val = calloc(2, sizeof(char *));
val[0] = calloc(1, 5 * sizeof(char));
val[0] = VALUE TO PUT IN THE VARIABLE;
struct special_var current_var = {.key="NAME OF THE SPECIAL VARIABLE WITHOUT THE $", .value=val};
modify_special_var(&current_var);
free_value(val);
```
### Utilisation des variables classiques :

-> Pour créer et modifier une variables, il faut appeller add_var(char *) en passant en parametre une string de la forme "a=b" -> la value d'un AST_ASSIGNEMENT_WORD

## Code review du 24/01/24 : Code review 2 avec un ACU

-> Penser à enlever les ../ dans les includes 

-> Faire plus de tests (voir même les faires avant de coder)

-> mettre les define dans le Makefile

