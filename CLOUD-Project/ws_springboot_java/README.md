# Serveur Spring boot

## Build de l'image docker du serveur
Un `Dockerfile` se trouve dans le ce dossier ws_springboot_java. Pour construire l'image docker il suffit donc d'executer la commande suivante : 
```sh
docker build -t springboot .
```
Ensuite il est possible d'executer l'image : 
```sh
docker run --rm -p 8085:8080 springboot
```
Vous pouvez egalement lancer le serveur springboot en meme temps qu'EMQX et NiFi avec le docker-compose.yml situe dans le dossier parent de celui-ci : 
```sh
cd .. # uniquement si vous vous situez dans le dossier ws_springboot_java/
docker compose up # une fois dans le dossier ssie_cloud_project/ (racine de ce depot git)
```

## URL utilisee par NiFi pour envoyer ses donnees au service REST
L'URL utilisee est :
```
http://springboot:8080/ssie/tcs/veh
```
