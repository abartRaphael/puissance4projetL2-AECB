# puissance4projetL2-AEC

Membres:

- ABART Raphaël

- El Ghoumari Soumia

- Coupé Xavier

- Brindeau Thomas

Cadre:


	Projet de L2 informatique de Le mans Université
	janvier 2023 --> mars 2023


Concept:
	Ce jeu est un puissance 4 qui contient 2 types de pièces spéciales en plus :
		1- Les pièces bloquantes
		2- Les pièces creuses

		Deux modes de jeu :
			1- Mode "Classique" --> Sans pièces spéciales
			2- Mode "Creux" --> Avec pièces spéciales

		Principales règles :
			Les différents cas :
    		• une pièce creuse est en bas:
					Si une pièce creuse arrive : La case se remplit
					Si une pièce pleine arrive : La case se remplit
					Si une pièce bloquante arrive : La pièce reste au dessus de la pièce creuse
    		• Si une pièce pleine est en bas:
					Si une pièce creuse arrive : La case se remplit
					Si une pièce pleine arrive : La pièce reste au dessus de la pièce pleine
					Si une pièce bloquante arrive : La pièce reste au dessus de la pièce pleine
    		• Si une pièce bloquante est en bas:
					Si une pièce creuse arrive : La pièce reste au dessus de la pièce bloquante
					Si une pièce pleine arrive : La pièce reste au dessus de la pièce bloquante
					Si une pièce bloquante arrive : La pièce reste au dessus de la pièce bloquante


Il existe trois versions du projet :
	V0 : Code existant du jeu en version Classique
	V1 : Version SDL de la V0
	V2 : Version du jeu en mode "Creux"


Contrôles:
	Le jeu se joue uniquement à la souris. Dans le mode Classique, les trois boutons de la souris permettent de placer des pièces. Et, dans le mode Creux, le clic gauche est pour jouer une pièce pleine, le clic droit pour jouer une pièce creuse, et le clic sur la molette de la souris pour jouer une pièce bloquante. 
