#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     touchSensor,    sensorTouch)
#pragma config(Sensor, S3,     SonarArriere,   sensorSONAR)
#pragma config(Sensor, S4,     SonarAvant,     sensorSONAR)
#pragma config(Motor,  motorA,          pince,         tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          verrin,        tmotorNXT, openLoop, reversed, encoder)
#pragma config(Motor,  motorC,          funny,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorA,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorB,        tmotorMatrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "redButton.c"
#include "mouvement_droit_new.c"
#include "funny_action.c"
//#include "point_turn.c"

/*
Tous les temps sont exprimes en ms.
Toutes les distances sont exprimees en mm.
Convention moteurs :
 - motorA = moteur droit
 - motorB = moteur gauche
*/


/*
A faire pour la suite : ne jamais modifier les valeurs de nMotorEncoder[], sauf a l'initialisation.
*/


/*
--------------------------------------------------------------------------------------------------
---------------------------- PROGRAMME DU ROBOT TETRIX COTE JAUNE --------------------------------
------ PROGRAMME 1 : IL PREND LES CYLINDRES DE LA TOUR ET LES PLACE DANS LA ZONE DE DEPART -------
--------------------------------------------------------------------------------------------------
*/




task rentre_verrinT()
{
	motor[verrin]=100;
	wait1Msec(5000);
	motor[verrin]=0;
}

void rentre_verrin()
{
	motor[verrin]=100;
	wait1Msec(5000);
	motor[verrin]=0;
}

task sort_verrinT()
{
	motor[verrin]=-100;
	wait1Msec(5000);
	motor[verrin]=0;
}



void turnLeftDeg_safe(float angle)
{
	float angle_safe = 0;
	char done = 0;
	float sum = 0.0;
	while(done == 0 && angle - sum > 0)
	{
		turnLeftDeg(angle-sum, &angle_safe, &done);
		sum += angle_safe;
		if(done == 0)
			wait1Msec(150);
	}
}

void turnRightDeg_safe(float angle)
{
	float angle_safe = 0;
	char done = 0;
	float sum = 0.0;
	while(done == 0 && angle - sum > 0)
	{
		turnRightDeg(angle-sum, &angle_safe, &done);
		sum += angle_safe;
		if(done == 0)
			wait1Msec(150);
	}
}


/*
void prend_cylindre()
{
	wait1Msec(100);
	avance_nulle(1300);
	wait1Msec(200);

	// On a attrape un cylindre

	recule_nulle(100);
	//wait1Msec(200);
	//recule_nulle(100);
	wait1Msec(200);
	turnLeftDeg(170, 20);
	wait1Msec(100);
}

void depose_cylindre(int trigo)
{
	if(trigo == 1)
		startTask(tourne_pince_gaucheT);
	else
		startTask(tourne_pince_droitT);
	wait1Msec(1000);
//	avance_nulle(70);
	sort_verrin();
	startTask(rentre_verrinT);
	wait1Msec(200);

//	recule_nulle(70);
	wait1Msec(100);

}

void se_place_depose(int distance)
{
	wait1Msec(100);
	avance_nulle(distance);
	wait1Msec(200);
	turnRightDeg(160, 20);
	wait1Msec(100);
}

void se_place_cylindre(int distance)
{
	recule_nulle(50);
	wait1Msec(100);
	turnRightDeg(175, 20);
	wait1Msec(100);
	avance_nulle(distance-45);
	wait1Msec(100);
	turnLeftDeg(190, 20);
	wait1Msec(100);
}
*/
/*
task position()
{
	float vmax=0;
	float vm=0;
	clearTimer(T1);
	float timeT=0.0;
	while(true)
	{
		// Affichage des parametre
		vm=(nMotorEncoder[motorA]-old_A)/10.0*2.0*PI*rayon/360.0;
		if(vm>vmax)
			vmax=vm;
		if(vmax > 1.4545*0.95 && timeT==0.0)
			timeT=time1(T1);

		//nxtDisplayTextLine(3, "motor1 = %f", nMotorEncoder[motorA]);
		//nxtDisplayTextLine(1, "timeT = %f", timeT);
		nxtDisplayTextLine(3, "motor1 = %f", vmax);
		nxtDisplayTextLine(4, "motor2 = %f", nMotorEncoder[motorB]);
		nxtDisplayTextLine(5, "d = %f", nMotorEncoder[motorA]*(float)(PI*rayon)/(float)360);
		old_A=nMotorEncoder[motorA];
		old_B=nMotorEncoder[motorB];
		// fin de la boucle, on evite de saturer le processeur.
		wait1Msec(10);
	}
}
*/

task main()
{
	nMotorEncoder[motorA]=0;
	nMotorEncoder[motorB]=0;
	nMotorEncoder[pince]=0;

	//rayon = 46.3;
	rayon = 25.1;
	matrix_or_tetrix=2;
	//offset_motor=16; // Pour passer la bascule avec une matrix.
	offset_motor=15;
	// Gestion des obstacle, savoir si on les prend en compte ou non. 1 pour les prendre en compte, 0 sinon.
	obstacle = 1;
	entraxe = 190;
	start=0;

	//startTask(position);
	startTask(rentre_verrinT);

	startTask(redButton);
	start=0;

	while(start == 0)
		wait1Msec(10);

	startTask(funnyAction);


	saturation_dpuiss_avant = 100;
	saturation_dpuiss_arriere = 100;

	float dist;
	float angle;
	char done;
	char obs;

	//wait1Msec(7000);
	//avance_nulle(900);
	//wait1Msec(200);
	//recule_nulle(300);

	//tourne_pince_gauche();
	//motor[motorD] = 15;
	//wait1Msec(1300);
	//motor[motorD] = 0;

	//wait1Msec(40000);

	//rayon /=2;
	//avance_nulle(666);
	//avance_poly(666-2, 20, 350, 0.6);

// Passage de la bascule

	// Attendre que le petit robot parte.

	wait1Msec(4000);

	obstacle = 0;
	recule_nulle(100, &dist, &done, &obs, 700);
	wait1Msec(200);

	obstacle = 1;

	//wait1Msec(4000);
	avance_nulle_anyway(680, &dist, &done, &obs);
	wait1Msec(1000);
/*
	nxtDisplayTextLine(2, "dist : %f", dist);
	nxtDisplayTextLine(3, "done : %d", done);
	nxtDisplayTextLine(4, "obs : %d", obs);
	*/
	//wait1Msec(20000);


	// On se recalibre sur la bascule pour savoir ou on est.
	obstacle = 0;
	recule_nulle(90, &dist, &done, &obs, 1200);
	wait1Msec(100);
	obstacle = 1;
	avance_nulle(170, &dist, &done, &obs, 1000);
	wait1Msec(100);
	turnLeftDeg(180, &angle, &done);
	wait1Msec(100);

	//recule_nulle(200, &dist, &done, &obs, 1000);
	recule_nulle(200, &dist, &done, &obs, 1000);
	// On est cale contre le mur
	/*
	obstacle = 0;
	recule_nulle(20, &dist, &done, &obs, 1000);
	obstacle = 1;
	*/


	// Prise du cylindre, on parcourt un rectangle
	wait1Msec(300);
	obstacle = 1;
	avance_nulle_anyway(330, &dist, &done, &obs);
	wait1Msec(100);
	turnRightDeg_safe(180);
	wait1Msec(100);
	avance_nulle_anyway(145, &dist, &done, &obs);
	//obstacle = 0;
	wait1Msec(100);
	turnRightDeg_safe(145);
	wait1Msec(100);
	obstacle = 0;
	avance_nulle_anyway(600, &dist, &done, &obs, 1500, 27);
	obstacle = 1;
	// Cylindre pris.
	wait1Msec(200);
	obstacle = 1;
	recule_nulle_anyway(200, &dist, &done, &obs, 2500, 13);
	obstacle = 0;
	// Cylindre sorti de la fusee.


	startTask(sort_verrinT);
	wait1Msec(10);

	// On tourne de maniere securisee
	turnRightDeg_safe(90);
	//nxtDisplayTextLine(3, "angle = %f", angle);
	//nxtDisplayTextLine(4, "done = %d", done);

	wait1Msec(100);
	avance_nulle(140, &dist, &done, &obs);
	// Depose le cylindre dans la base.
	// On attend que le verrin sorte.
	wait1Msec(1000);
	obstacle = 1;
	recule_nulle_anyway(40, &dist, &done, &obs);


	wait1Msec(3000);
	stopTask(sort_verrinT);
	wait1Msec(10);
	startTask(rentre_verrinT);
	wait1Msec(4000);
	obstacle = 1;
	recule_nulle_anyway(130, &dist, &done, &obs);
	for(int i = 0; i < 2; i++)
	{
		obstacle = 0;
		wait1Msec(300);
		turnLeftDeg_safe(85);
		wait1Msec(1000);

		// A retirer pour l'homologation

		// De nouveau mis en place pour prendres des cylindres dans la fusee.

		obstacle = 0;
		avance_nulle(600, &dist, &done, &obs, 1000, 25);
		// Cylindre pris.
		wait1Msec(200);
		obstacle = 1;
		recule_nulle_anyway(150, &dist, &done, &obs, 2500, 13);
		obstacle = 0;
		// Cylindre sorti de la fusee.

		startTask(sort_verrinT);

		// On tourne de maniere securisee
		turnRightDeg_safe(85);

		avance_nulle(110, &dist, &done, &obs);
		wait1Msec(3000);
		stopTask(sort_verrinT);
		wait1Msec(10);
		startTask(rentre_verrinT);
		wait1Msec(4000);
		//rentre_verrin();
		obstacle = 1;
		recule_nulle_anyway(120, &dist, &done, &obs);
		obstacle = 0;
		wait1Msec(100);
		/*
		// On est en face
		// On tourne de maniere securisee
		done = 0;
		angle = 0;
		while(done == 0)
		{
			turnLeftDeg(90-angle, &angle, &done);
			if(done == 0)
				wait1Msec(150);
		}
		//turnLeftDeg(90, &angle, &done);
		wait1Msec(200);
		*/
	}
	/*
	recule_nulle_anyway(110, &dist, &done, &obs);

	turnLeftDeg_safe(180);

	obstacle = 1;
	avance_nulle_anyway(240, &dist, &done, &obs, 2500, 13);
	obstacle = 0;
	turnRightDeg_safe(310);
	obstacle = 1;
	avance_nulle_anyway(350, &dist, &done, &obs, 1000, 25);
	*/

	turnLeftDeg_safe(90);
	wait1Msec(100);
	recule_nulle_anyway(65, &dist, &done, &obs);
	turnLeftDeg_safe(50);
	obstacle = 1;
	avance_nulle_anyway(225, &dist, &done, &obs, 0, 13);
	obstacle = 0;
	turnRightDeg_safe(90);
	wait1Msec(100);
	turnRightDeg_safe(90);
	wait1Msec(100);
	turnRightDeg_safe(70);
	wait1Msec(100);
	avance_nulle_anyway(50, &dist, &done, &obs);
	wait1Msec(100);
	avance_nulle_anyway(30, &dist, &done, &obs);
	wait1Msec(100);

	/*
	done = 0;
	angle = 0;
	while(done == 0)
	{
		turnRightDeg(90-angle, &angle, &done);
		if(done == 0)
			wait1Msec(150);
	}
	avance_nulle(200, &dist, &done, &obs, 1000, 25);
	wait1Msec(50000);
	/*
	// On attent 2 secondes
	wait1Msec(500);

	// On eteint les moteurs
	motor[motorA] = 0;
	motor[motorB] = 0;
	wait1Msec(1000);
	avance_nulle(150);
	wait1Msec(200);
	turnLeftDeg(180, 20);
	wait1Msec(100);
	motor[motorA] = -20;
	motor[motorB] = -20;
	wait1Msec(1000);
	motor[motorA]=0;
	motor[motorB]=0;

	wait1Msec(300);
	//startTask(init_pince);
	avance_nulle(850);
	wait1Msec(200);
	turnLeftDeg(90, 20);
	wait1Msec(200);
	avance_nulle(500);
	wait1Msec(200);
	turnLeftDeg(80, 20);
	wait1Msec(100);
	//avance_nulle(800);
	//wait1Msec(200);

	// On est en face de la tour et on veut prendre un cylindre

	//Verrin deja rentre.
	//rentre_verrin();

	// On est devant la tour.
	// Avec le cylindre deja.
	prend_cylindre();

	startTask(tourne_pince_GaucheT);
	//wait1Msec(10000);
	wait1Msec(100);
	//recule_nulle(200);
	se_place_depose(400);


	depose_cylindre(1);

	se_place_cylindre(450);

	// On est de nouveau place devant les cylindres de la tour.

	place_pince();
	wait1Msec(1500);

	prend_cylindre();

	se_place_depose(250);

	depose_cylindre(0);
/*
*/


	wait1Msec(90000);
}
