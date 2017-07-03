// Programme pour le declenchement de la funny action.

// Renomer le moteur pour la funny action en "funny".


/* 
Ce programme est une tache de fond qui tourne et qui s'active au bout de 90,5s. 
Elle etteint les moteurs pour avancer (motorA et motorB) puis active le moteur pour la funny action.
Ensuite, elle éteint la brique. 

Compatible Ev3 et NXT.
*/


task funnyAction()
{
	int t=90500; // Le temps en secondes.
	wait1Msec(t);
	motor[motorA]=0;
	motor[motorB]=0;
	
	motor[funny] = -100;
	wait1Msec(1000);
	motor[funny] = 0;
	powerOff();

}
