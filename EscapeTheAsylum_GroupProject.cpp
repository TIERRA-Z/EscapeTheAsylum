//===============================================================================================
//ESCAPE THE ASYLUM
//Group Project (Text-Based Adventure Game)
//Saint Leo University
//Programming in C+/C++ (COM-207-CA01)
//November 17, 2021
//Tierra Doughty, Sebastien Midence Alvarado, Jesus Correacanaveral, and Sandeepreddy Jilkapalli
//===============================================================================================

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <string>


using namespace std;

//===================================================================
//Global Variables- Constant variables that will be used for the size
// of the game map. 1 is the min and 10 is the max for x & y.
//===================================================================
const int MINX=1;
const int MINY=1;
const int MAXX=10;
const int MAXY=10;

//integer used for exiting the game.
const int exitCode=-1;

//Main commands for the game that players can input.
enum command {NORTH, SOUTH, EAST, WEST, GET, SWING,EXIT};

//====================================================================
//int variables for the player, creatures, and object positions along with
//	the time cycle.
//====================================================================
int playerX, playerY;
int demonX, demonY;
int confederatesoldierX,confederatesoldierY;
int zombieX, zombieY;
int batX, batY;
int timeCycle;

//bool variables
const bool helpMenu=true;
bool holdBat;
bool endGame;

//===================================================================
//Random Generators(int randomInteger and int intialPositions)- Used
//	for the player, item, and creature positions.
//===================================================================
int randomInteger (int min, int max){
	int range =(max-min);
	int difference=(rand()%(range+1));
	return (min+difference);
}

int intialPositions(int min, int max,int A, int B){
	int retVal=randomInteger(min,max);
	if((max-min)>2){
		while((retVal==A) || (retVal==B)){
			retVal=randomInteger(min,max);
		}
	}
	return retVal;
}

//===================================================================
//void SetUp()-Print title card, summary, and set the beginning positions 
//	of the player, demon, zombie, and confederate soldier, and sword.
//	Also contains the random generator for these positions.
//===================================================================
void SetUp(){
	
cout <<"                                                                                                          -----"<<endl;
cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
cout <<"                                                                                                          -----"<<endl;
cout <<" EEEE 	 SS    CCC     A     PPPP    EEEE      (                )"<<endl;
cout <<" E      S  S  C       A A    P   P   E         | \             / |"<<endl;
cout <<" E      S     C      A   A   P   P   E         |  \           /  |"<<endl;
cout <<" EEEE    S    C      AAAAA   PPPP    EEEE      |   \ -'''''. /   |"<<endl;
cout <<" E        S   C      A   A   P       E         \    .        ,-. /"<<endl;
cout <<" E         S  C      A   A   P       E         '  --,   , --    ("<<endl;
cout <<" E      S  S  C      A   A   P       E          \/.-.   .-. .__,)"<<endl;
cout <<" EEEE    SS    CCC   A   A   P       EEEE       (.   .| .  . (  /"<<endl;
cout <<"                                               >  0. | : 0 .  /"<<endl;
cout <<" TTTTT  H  H   EEEE                            ( ..'|  '..'   '"<<endl;
cout << "   T    H  H   E                               \   \|/       '"<<endl;
cout << "   T    H  H   E                               /    -        '"<<endl;
cout << "   T    HHHH   EEEE                            /'---------'  '   ' "<<endl;
cout << "   T    H  H   E                      '--'\/)  |  \/    \/  '    /|\ "<<endl;
cout << "   T    H  H   E                      \____/ ' \            '    /|\ "<<endl;
cout << "   T    H  H   E                        \  \  \  ,,,,,,,,,' /    /_|_\ "<<endl;
cout << "   T    H  H   EEEE                     \  \  /           \     )"<<endl;
cout << "                                       \  \/              \   ("<<endl;
cout << "   A      SS  Y   Y  L    U  U   M     M  \   /               \   ( "<<endl;
cout << "  A A    S  S  Y Y   L    U  U   M M M M  \  /                 \  {"<<endl;
cout << " A   A   S      Y    L    U  U   M  M  M   \/                   \  }"<<endl;
cout <<" AAAAA    S     Y    L    U  U   M     M    /              (      \ }"<<endl;
cout <<" A   A     S    Y    L    U  U   M     M    |              |       |{"<<endl;
cout <<" A   A      S   Y    L    U  U   M     M    |              |        | } "<<endl;
cout <<" A   A   S  S   Y    L    U  U   M     M    |             /        |  }"<<endl;
cout <<" A   A    SS    Y    LLLL  UU    M     M    |______________________|_}"<<endl;
cout<<endl<<"Created by: Tierra Doughty, Sebastien Midence Alvarado, Jesus Correacanaveral, and Sandeepreddy Jilkapalli."<<endl;
cout<<"-----"<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"-----"<<endl;
cout<<endl;

cout<<">You wake up as a patient in a haunted asylum for unknown reasons."<<endl
<<endl<<">According to a hospital bracelet, you are patient #1010."<<endl<<endl<<">Try to escape the asylum without getting caught by the Demon, Zombie, or Confederate Soldier."<<endl
<<endl<<">If you get caught, you die. Find and swing the bat to defend yourself. Good luck...you're going to need it."<<endl<<endl;
cout<<"-----                                                                                                      -----"<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"-----                                                                                                      -----"<<endl;
cout<<endl;

srand(time(NULL));
	playerX=randomInteger(MINX, MAXX);
	playerY=randomInteger(MINY, MAXY);
	zombieX=intialPositions(MINX, MAXX, playerX, playerX);	
	zombieY=intialPositions(MINY, MAXY, playerY, playerY);
	demonX=intialPositions(MINX, MAXX, playerX, playerX);
	demonY=intialPositions(MINY, MAXY, playerY, playerY);
	confederatesoldierX=intialPositions(MINX, MAXX, playerX, playerX);
	confederatesoldierY=intialPositions(MINY, MAXY, playerY, playerY);
	batX=intialPositions(MINX, MAXX, playerX, playerX);
	batY=intialPositions(MINY, MAXY, playerY, playerY);
	
	timeCycle=0;
	holdBat=false;
	endGame=false;	
	
}

//===================================================================
//bool found_____()-When the player is in the same location as the 
//	item or creatures.
//===================================================================

//foundDemon()-player and demon coordinates are equal.
bool foundDemon(){
	return((playerX==demonX)&&(playerY==demonY));
	
}

//foundZombie()-player and zombie coordinates are equal.
bool foundZombie(){
	return((playerX==zombieX)&&(playerY==zombieY));
	
}

//foundConfederateSoldier()-player and confederate soldier coordinates are equal.
bool foundConfederateSoldier(){
	return((playerX==confederatesoldierX)&&(playerY==confederatesoldierY));
	
}

//===================================================================
//bool demonAttacks()-return absolute value of the player coordinates
// minus the demon coordinates.
//===================================================================
bool demonAttacks(){
	return(((abs(playerX-demonX))+(abs(playerY-demonY)))<2) && (!foundDemon());
}

//===================================================================
//bool zombieAttacks()-return absolute value of the player coordinates
// minus the demon coordinates.
//===================================================================
bool zombieAttacks(){
	return(((abs(playerX-zombieX))+(abs(playerY-zombieY)))<2) && (!foundZombie());
}

//===================================================================
//bool confederateSoldierAttacks()-return absolute value of the player
// coordinates minus the demon coordinates.
//===================================================================
bool confederateSoldierAttacks(){
	return(((abs(playerX-confederatesoldierX))+(abs(playerY-confederatesoldierY)))<2) && (!foundConfederateSoldier());
}

//===================================================================
//bool foundBat()-player and bat coordinates are equal.
//===================================================================
bool foundBat(){
	return ((playerX==batX)&&(playerY==batY)&&!(holdBat));
}


//===================================================================
//bool isValidMovement(int X, int Y, int Move)-Defines valid movements
//	based on user input of the commands.
//===================================================================
bool isValidMovement (int X, int Y, int Move) {
	bool RetVal=true;
	if((Move==NORTH)&& (Y>=MAXY))RetVal=false;
	if((Move==SOUTH)&& (Y<=MINY)) RetVal=false;
	if((Move==EAST) && (X>=MAXX)) RetVal=false;
	if((Move==WEST) && (X<=MINX)) RetVal=false;
	if((Move==GET) && (!foundBat())) RetVal=false;
	if((Move==SWING)&& (!holdBat)) RetVal=false;
return RetVal;

}

//===================================================================
//string makeUpperCase(string convertText)-When the user inputs the 
//	command words,the text is converted to uppercase so both lower
//	and upper case is accepted.
//===================================================================
string makeUpperCase(string convertText){
	string RetVal="";
	string letter;
	int i;
	for (int i=0;i<convertText.length();i++){
		if(convertText[i]!= ' '&& convertText[i]!= ' /t'){
			letter=toupper(convertText[i]);
			RetVal=RetVal.append(letter);
		}
	}
	return RetVal;
}

//===================================================================
//void describeDemon()-Outlines the actions pertaining to the Demon
//	, Confederate Soldier, and Zombie including dialogue if the player
//	is near its location, attacks,and if the player has a bat or not to attack it.
//===================================================================
void describeDemon() {

if(foundDemon()||foundZombie()||foundConfederateSoldier()){
	 cout<<endl<<"One of the creatures is standing right in front of you, patient #1010... "<<endl;
}

	if (helpMenu) {
		cout<<"|Player ("<<playerX<<", "<<playerY<<")";
		cout<<" |Zombie ("<<zombieX<<", "<<zombieY<<")";
		cout<<" |Demon ("<<demonX<<", "<<demonY<<")";
		cout<<" |Confederate Soldier ("<<confederatesoldierX<<", "<<confederatesoldierY<<")";
		cout<<" |Bat ("<<batX<<", "<<batY<<") "<<" |Exit"<<endl<<endl;
	}
	
	cout<<"You are currently at location ("<<playerX<<","<<playerY<<") in the haunted asylum. "<<endl;
	
if (demonAttacks()||zombieAttacks()||confederateSoldierAttacks()) 
	cout<<endl<<"You can hear an ominous whisper of spells, a faint moaning for brainzzz, and boot stomping coming from the asylum wings and rooms."<<endl<<endl;
    if (holdBat) {
        cout<<endl<<"You have a bat, it's probably a good idea to swing it."<<endl;
    } else {
        if (foundDemon()||foundZombie()||foundConfederateSoldier()) {
            cout<<"There is a bat on the floor... ";
        }
    }
    
//Dialogue for random coordinates on the map.
if(((playerX==5)&& (playerY==5)) ||((playerX==2)&& (playerY==3))||((playerX==7)&& (playerY==4))||((playerX==9)&& (playerY==1))){
	cout<<endl<<"An alarm breaks the silence: patient #1010, admitted for *%^$%&$%#%  has escaped his room."<<endl;
	cout<<endl<<"Red lights flash on and off. You really messed up patient #1010."<<endl;
}

if(((playerX==10)&& (playerY==10)||(playerX==1)&& (playerY==1)||(playerX==1)&& (playerY==10))){
	cout<<endl<<"You are at a corner of the asylum. You spot a camera with a blinking red light. Strike a pose!"<<endl<<endl;
}

if((playerX==1)&& (playerY==3)){
	cout<<endl<<"Down the north wing, you see another patient who appears to be in a trance:"<<endl; 
	cout<<endl<<"'Reality is an illusion, the earth is a hologram', he yells. Interesting..."<<endl;
}

if(((playerX==6)&& (playerY==8))||((playerX==6)&& (playerY==2))){
	cout<<endl<<"You get a shiver down your spine. You stop to think about how you were admitted into this asylum and reevaluate your life choices..."<<endl;
}

if((playerX==8)&& (playerY==7)){
	cout<<endl<<"You hear multiple voices coming from every direction:%$#%&%%$##@.."<<endl;
}

if(((playerX==4)&& (playerY==9))||((playerX==3)&& (playerY==4))){
	cout<<endl<<"Suddenly, you start levitating off the ground. The demon is probably nearby somewhere."<<endl;
}

if(((playerX==7)&& (playerY==5))||((playerX==2)&& (playerY==9))){
	cout<<endl<<"You should be scared. Very scared."<<endl;
}

if(((playerX==1)&& (playerY==10))){
	cout<<"You find your shredded medical record in the south wing. It reads:"<<endl<<endl;
	cout<<"^-----^-----^^^^^----^"<<endl;
	cout<<"| patient #1010       |"<<endl;
	cout<<"|                     |"<<endl;
	cout<<"|s:Male dob:6/17/19XX |"<<endl;
	cout<<"|                     |"<<endl;
	cout<<"|Reason:CLAIMED TO DO |"<<endl;
	cout<<"|*REDACTED*           |"<<endl;
	cout<<"|Status:Very Dangerous|"<<endl;
	cout<<"|_____________________|"<<endl;
	
}

if((playerX==1)&& (playerY==5)){
	cout<<endl<<"This is your room. You left it in rough condition."<<endl; 
	cout<<endl<<"There is a broken mirror, an unconcious guard, and a nice landscape painting. Don't threaten me with a good time."<<endl;
}

	if(isValidMovement(playerX,playerY,NORTH)){
}
	cout<<endl<<">You can go to the NORTH wing. "<<endl;

	if(isValidMovement(playerX,playerY,SOUTH)){
		cout<<endl<<">You can go to the SOUTH wing. "<<endl;
		
	}
	if(isValidMovement(playerX,playerY,EAST)){
		cout<<endl<<">You can go to the EAST wing. "<<endl;
	}
	 
	if(isValidMovement(playerX,playerY,WEST)){
		cout<<endl<<">You can go to the WEST wing. "<<endl<<endl;
cout<<"-----                                                                                                      -----"<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"-----                                                                                                      -----"<<endl;
cout<<endl;
	}

}

//===================================================================
//int userInput (bool Phrases)-Controls user input and asks user to enter
//	a valid command listed below..
//===================================================================
int userInput(bool Phrases){
	int RetVal=-2;
	string receiveInput="Start";
	while (RetVal==-2){
		if(Phrases) {
			describeDemon();
			cout<<endl<<"Please input a command: "<<endl;
		}
	cin>> receiveInput;
	receiveInput=makeUpperCase(receiveInput);
	if(Phrases){
	 cout<<endl<<"You've entered: " <<receiveInput<<endl<<endl;
	
	if(receiveInput=="EXIT") RetVal=exitCode;
	if(receiveInput=="NORTH") RetVal=NORTH;
	if(receiveInput=="SOUTH") RetVal=SOUTH;
	if(receiveInput=="EAST") RetVal=EAST;
	if(receiveInput=="WEST") RetVal=WEST;
	if(receiveInput=="GET") RetVal=GET;
	if(receiveInput=="SWING") RetVal=SWING;
	}
	return RetVal;

}
}
		
//===================================================================
//void batSwing()-When player inputs the command swing, it enables 
//	comeback against the Demon, Zombie, and Confederate Soldier.
//===================================================================
void batSwing(){
    if (holdBat) {
        if (demonAttacks()||zombieAttacks()||confederateSoldierAttacks()) {
            cout<<"You have defeated the creature! You exit the asylum's backdoor and run to freedom! Hurrah, enjoy freedom patient #1010!"<<endl<<endl;
            endGame = true;
        } else {
            cout<<"You swing the bat. The bat shakes in your shaky hands."<<endl;
        }
    } else {
        if (demonAttacks()||zombieAttacks()||confederateSoldierAttacks()) {
            cout<<"The creature slowly approaches and uses its ~special attack~. R.I.P. patient #1010."<<endl<<endl;
            endGame = true;
        } else {
            cout<<"You don't have a bat. Better start running."<<endl;
        }
    }
}
	
//===================================================================
//void walking(int compassForDirections)-Function for valid movements
//	and directions.
//===================================================================
void walking(int compassForDirections){
	if(demonAttacks()||zombieAttacks()||confederateSoldierAttacks()&& (compassForDirections!=SWING)) batSwing();
		if(isValidMovement(playerX,playerY,compassForDirections)){
		switch(compassForDirections){
			case NORTH: playerY++; break;
            case SOUTH: playerY--; break;
            case EAST: playerX++; break;
            case WEST: playerX--; break;
            case GET: holdBat = true; break;
            case SWING: batSwing(); break;
            case exitCode: break;
            case EXIT:exitCode;break;
            default: cout<<endl<<"You are toast. Please input a valid command."<<endl<<endl;
        }
    } else {
cout<<"-----                                                                                                      -----"<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"-----                                                                                                      -----"<<endl;
cout<<endl;
        cout<<"Dead End: Cannot move that way."<<endl<<endl;
    }
}

//===================================================================
//Main Program-Runs the setup function to start the game and
// exit game function.
//===================================================================
int main(int argc, char** argv) {
	int UserCommand = -2;
    SetUp();

    while ((UserCommand!=exitCode)) {
        UserCommand = userInput(true);
        walking(UserCommand);

if (endGame){
cout<<"-----                                                                                                      -----"<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"-----                                                                                                      -----"<<endl;
cout<<endl;
            cout<<"Game Over, please type exit---> ";
            cout<<"Thank you for playing, ESCAPE THE ASYLUM!";
            UserCommand = userInput(false);
             return 0;
        }
       
    }    
	
}
//========================================================================
