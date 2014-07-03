Treuil-Handi
========

Interface de commande de treuil automatisé pour utilisation par des personnes handicapées moteurs.
Le but de ce projet est d'avoir une interface de commande de treuil.
Fonctionalitées :
	utilisation de capteur AS5048B et d'aimants sur le manche de controle et le treuil.
	mémorisation de la position min et max du treuil.
	calibration du manche de controle
	2 modes de fonctionnements :
		- proportionelle au manche
		- impulsionelle avec rampe d'accélération plafonnée

Partie physique :
- un joystick de commande magnétique (adapté au milieux humide/marin)
- une carte de controle avec microcontroleur (de type arduino mega / uno / micro)
- une carte de controle puissance (1er version avec signal PPM pour utilisation de variateur de modélisme).
- détéction de la position du treuil par encodeur magnétique multitours et aimant sur l'axe
- le treuil n'est pas inclus dans ce projet.

Partie logique :
Le schéma synaptique de fonctionement du treuil est au format opendocument (open/libre-office) dans le répository.

![](https://raw.githubusercontent.com/crazytiti/Treuil-Handi/master/images/schema-0.2.jpg)

Schéma synoptique globale

![](https://raw.githubusercontent.com/crazytiti/Treuil-Handi/master/images/schema_global.png)

Proto de développement

![](https://raw.githubusercontent.com/crazytiti/Treuil-Handi/master/images/proto/proto.jpg)