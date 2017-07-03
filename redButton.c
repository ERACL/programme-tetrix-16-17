
// Programme pour la gestion du bouton rouge d'arret d'urgence.
// Compatible Ev3 et NXT.

// A inclure au debut du task main :
/*
starttask(redButton);
while(start == 0)
	wait1Msec(10);
*/



// start = 0 : on n'a pas encore commence
// start = 1 : le jeu est en cours.
// start = 2 : desactive le bouton d'arre d'urgence (il faudra quand meme apuyer dessus pour demarrer le robot)
char start=0;

task redButton()
{
	start=0;
	// Appui sur le bouton.
	while(SensorValue(touchSensor)==0)
		wait1Msec(10);
	while(SensorValue(touchSensor)==1)
		wait1Msec(10);

	start = 1;
	wait1Msec(500); // Evite le rebond du bouton qui peut fausser le comportement du bouton

	while(1)
	{
		if(SensorValue(touchSensor) == 1)
		{
			// Extinction de toutes les taches lors de l'appui sur le bouton en cours de jeu.
			stopAllTasks();
			motor[motorA]=0;
			motor[motorB]=0;
			wait1Msec(100);
		}
		else if(start == 2)
			return;
		wait1Msec(10);
	}

}
