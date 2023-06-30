# Projet Server IRC 42

Ce projet est un serveur IRC basique qui permet aux utilisateurs de communiquer en temps réel via Internet en utilisant le protocole Internet Relay Chat (IRC).

## Description d'un serveur IRC

Un serveur IRC (Internet Relay Chat) est un système de communication en temps réel qui permet aux utilisateurs de discuter via Internet. Imaginez-le comme une salle de discussion virtuelle où les utilisateurs peuvent se connecter et échanger des messages texte avec d'autres personnes. Voici quelques exemples d'applications connues qui utilisent le protocole IRC :

- **irssi**: Un client IRC en ligne de commande pour les utilisateurs avancés.
- **mIRC**: Un client IRC populaire pour Windows avec une interface conviviale.
- **HexChat**: Un client IRC multiplateforme qui prend en charge de nombreuses fonctionnalités avancées.

## Description technique du protocole IRC

Le protocole IRC est basé sur un modèle client-serveur. Lorsqu'un client se connecte à un serveur IRC, il envoie des requêtes et reçoit des réponses du serveur. Voici comment fonctionne l'envoi et la réception des requêtes :

1. **Connexion au serveur**: Le client se connecte au serveur IRC en utilisant un port spécifique (par exemple, le port 2222).

2. **Identification**: Le client envoie une commande d'identification, généralement avec un nom d'utilisateur (nick) et éventuellement un mot de passe.

3. **Rejoindre un canal**: Le client peut rejoindre un canal de discussion en envoyant une commande pour spécifier le canal cible.

4. **Envoi de messages**: Le client envoie des messages au serveur ou à d'autres utilisateurs en utilisant la commande appropriée. Les messages peuvent être envoyés publiquement dans un canal ou en privé à un utilisateur spécifique.

5. **Réception de messages**: Le client reçoit les messages du serveur ou des autres utilisateurs et les affiche dans son interface.

6. **Déconnexion**: Lorsque le client souhaite se déconnecter, il envoie une commande de déconnexion au serveur.

## Fonctionnalités et Commandes

Le serveur IRC basique offre plusieurs fonctionnalités permettant aux utilisateurs de communiquer efficacement. Voici les principales commandes et leur utilisation :

- **NICK**: Permet à l'utilisateur de choisir un pseudonyme (nick) qui le représentera dans le canal de discussion. Exemple : `/NICK MonPseudo`

- **USER**: Cette commande est utilisée pour spécifier l'identité de l'utilisateur au serveur. Elle inclut généralement des informations telles que le nom réel et l'hôte. Exemple : `/USER MonNom 0 * :MonNom`

- **PASS**: Si le serveur requiert une authentification, la commande PASS est utilisée pour spécifier le mot de passe associé à l'utilisateur. Exemple : `/PASS MonMotDePasse`

- **JOIN**: Cette commande permet à l'utilisateur de rejoindre un canal de discussion spécifique. Exemple : `/JOIN #NomDuCanal`

- **TOPIC**: Utilisée par un utilisateur ayant des privilèges de modérateur, cette commande permet de définir ou de changer le sujet (topic) du canal de discussion. Exemple : `/TOPIC #NomDuCanal NouveauSujet`

- **MSG**: Permet à l'utilisateur d'envoyer un message à un autre utilisateur spécifique ou à un canal de discussion. Exemple : `/MSG UtilisateurDestinataire Salut !`

- **OPER**: Cette commande est utilisée pour demander des privilèges d'opérateur (op) à l'administrateur du serveur. Exemple : `/OPER MonNomDePasseOp`

- **KICK**: Utilisée par un utilisateur ayant des privilèges d'opérateur, cette commande permet de renvoyer un utilisateur spécifié du canal de discussion. Exemple : `/KICK #NomDuCanal UtilisateurARenvoyer Raison du Renvoi`

- **INVITE**: Utilisée par un utilisateur ayant des privilèges d'opérateur, cette commande permet d'inviter un autre utilisateur à rejoindre un canal de discussion spécifique. Exemple : `/INVITE UtilisateurInvité #NomDuCanal`

- **MODE**: Cette commande est utilisée pour modifier les modes d'un canal de discussion. Par exemple, +/-i permet de restreindre ou d'autoriser l'accès au canal, +/-t permet de verrouiller ou de déverrouiller le sujet aux operators, +/-k permet de définir ou de supprimer un mot de passe pour le canal, +/-l permet de limiter ou d'enlever la limite du nombre d'utilisateurs dans le canal, et +/-o permet d'accorder ou de retirer les privilèges d'opérateur à un utilisateur spécifié. Exemple : `/MODE #NomDuCanal +o UtilisateurOp`

- **QUIT**: Utilisée pour se déconnecter du serveur IRC.

## Guide de démarrage rapide

Voici comment lancer le programme :

1. Assurez-vous d'avoir les dépendances nécessaires installées sur votre machine (`make`).

2. Clonez le dépôt du projet sur votre ordinateur.

3. Naviguez jusqu'au répertoire du projet dans votre terminal.

4. Exécutez la commande `make` pour compiler et `./ircserv Port Password` pour lancer le serveur IRC.

5. Une fois le serveur IRC démarré, vous pouvez utiliser un client IRC (ce server a été developpé avec `irssi` en client référence) pour vous y connecter en spécifiant l'adresse du serveur et le port approprié.

6. Suivez les instructions de votre client IRC pour choisir un pseudonyme (nick), rejoindre des canaux de discussion et commencer à communiquer avec d'autres utilisateurs.

Voilà, vous êtes prêt à utiliser votre serveur IRC!
