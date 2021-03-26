# Table des matières

 1. [La centrale pour détecteurs](#la-centrale-pour-detecteurs)


## La centrale pour détecteurs

Après avoir acheté des détecteurs bons marché (au nombre de 8, nous pêchons en couple), j'ai voulu trouver une centrale qui va avec, mais impossible d'en trouver.

Pourtant le principe est simple, on remonte un signal du détecteur à une centrale au moyen d'un émetteur HF et la centrale reste en écoute permanente. Mais non, des kits à 120€ pour l'entrée de gamme à plus de 600€ pour le haut de gamme, bien sûr x2 puisqu'il m'en faut 8.

C'est pourquoi j'ai conçu ma propre centrale **universelle** (enfin presque, voir le tableau de compatibilité).


## Le principe

La majorité des détecteurs, même bons marché, possède une prise Jack mono en 2.5mm pour y brancher un écureuil (ou swinger) lumineux, qui recevra une tension en cas de détection, pour le faire s'allumer.

Tout le système se base sur ce principe.

Le concept est donc un boîtier qui vient se brancher au niveau de la prise jack sous le détecteur, et une centrale que le pêcheur garde sur lui. 

Dans le boîtier sous le détecteur (que nous appellerons émetteur), on retrouve un Arduino Nano, une batterie, un bouton on/off et un émetteur 2.4GHz.

Dans la centrale (le récepteur), on retrouve un Arduino Nano, une pile 9V (une batterie peut aussi fonctionner, mais je détaillerai plus loin pourquoi j'ai choisi une pile), un afficheur 7 segments, un buzzer piezzo et un récepteur 2.4GHz.


## Construire le projet chez vous

:warning: **ATTENTION** :warning:

Ce projet est fourni en l'état, je fais des mises à jour dessus au fur et à mesure que je trouve des évolutions à faire, il n'est bien entendu pas garanti au niveau d'un produit commercial. Vous utilisez ce système en connaissance de cause.

Le projet n'est probablement rentable que pour mon besoin spécifique de 8 détecteurs sur une seule centrale, en effet sans compter le plastique pour l'imprimante, il y en a pour environ 90€ de composants en tout genre.

### Pré-requis

 - [Arduino IDE](https://www.arduino.cc/en/software/)
 - Un fer à souder et de l'étain
 - Une imprimante 3D et du filament PETG (ou ABS si vous en avez)
 - Des piles 9V pour la centrale
 - [Un chargeur de batteries Lipo](https://www.amazon.fr/gp/product/B074MQ8WF2/ref=ppx_yo_dt_b_asin_title_o06_s01?ie=UTF8&psc=1)
 - Des vis et écrous taille M3 d'environ 11mm de long (j'ai pris [ça](https://www.amazon.fr/gp/product/B01GNVU13K/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1) et [ça](https://www.amazon.fr/gp/product/B01GNW2PK6/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1))

### La liste de courses

*Disclaimer: je n'ai aucun partenariat pour les composants ci-dessous, achetez-les où vous voulez, ou même une alternative si vous le souhaitez, je n'y gagne rien.*

 - [Controlleur ATMega 328P](https://www.amazon.fr/gp/product/B072LPHG92/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1) des arduinos moins chers, même fonctionnement, mêmes performances.
 - [Des câbles dupont femelle-femelle](https://www.amazon.fr/gp/product/B01GI3X1XK/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) pour les montages.
 - [Des boutons on/off](https://www.amazon.fr/gp/product/B076GXD7XN/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) pour les émetteurs et la centrale, prenez ceux que vous voulez, j'ai pris ceux-ci.
 - [Minimum un module NRF24L01+PA+LNA](https://www.amazon.fr/gp/product/B07B3RLLGK/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1) pour la centrale.
 - [Des batteries Lipo](https://www.amazon.fr/gp/product/B07CYMYMS9/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1) pour les émetteurs.
 - [Un buzzer Piezzo](https://www.amazon.fr/gp/product/B07ZGMV61H/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1) pour réveiller le pêcheur.
 - [Des connecteurs micro JST 1.25](https://www.amazon.fr/gp/product/B07VYR7J49/ref=ppx_yo_dt_b_asin_title_o06_s01?ie=UTF8&psc=1) pour connecter les batteries.
 - [Des modules NRF25L01](https://www.amazon.fr/gp/product/B075CZM8LF/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) pour les émetteurs.
