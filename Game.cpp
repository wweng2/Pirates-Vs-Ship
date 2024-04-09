/*
File: Game.cpp
Project: CMSC 202 Project 2 , Fall 2020
Name: Weizhang weng
Email: wweng2@umbc.edu
Section: 10
Date: 10/5/2020
File Descitpion: This file contains all the implemtation of functions from the Game.h header file which allows the, the class
                  to set up a ga,e any ustilze two arrays fro pirate and ship in order to make a game.
*/
#include "Game.h"

Game::Game(){
  GameTitle();
  LoadShips();// Help fill the m_ships array with ship
  LoadPirates();// This does it for the m_allPirates
}

void Game::LoadShips(){

  int i = 0;
  string type;
  string cannon ;// Its string becuase getline only accept string
  string toughness;// Becuse Getline only accept string 
  string speed;// its becuase getline only accept string
  string desc;
  ifstream myfile(PROJ2_SHIPS);
  
  if (myfile.is_open()){// While the file is open each line will be divede into peice by  useing the getline wiht comma and store into spearate varible to create a stop object
    while(getline(myfile,type,',')){// This will keep run until these is no more string to do getline
	  getline(myfile,cannon,',');
	  getline(myfile,toughness,',');
	  getline(myfile,speed,',');
	  getline(myfile,desc);// No demliter to let everything else be store in descipriton and to prevent /n from casuing any problem

	  Ship ship(type,stoi(cannon),stoi(toughness),stoi(speed),desc);// The dtoi turns the three varible into int so the ship contrustor will accept it
	  m_ships[i] = ship;// This will for every ship object add it the array , incremtly by 1 to prevent ship overriding eachother
	  i +=1;
	  
	}
	}

   else {
      cout<<"Unable to open file: please try again."<<endl;
    }
      myfile.close();
      cout<<i<<" ships loaded."<<endl;
}

void Game::LoadPirates(){
  int i = 0;
  string name;
  string rating;// Getline only accpet string so this is for it
  string origin;
  string desc;
  ifstream myfile(PROJ2_PIRATES);

  if (myfile.is_open()){// Each line will be broken up by the demilter of comma and be store in separate varible to use 
    while(getline(myfile,name,',')){
          getline(myfile,rating,',');
          getline(myfile,origin,',');
          getline(myfile,desc);// This is to prevent that /n will show up in name for the next line so it will all be include in this varible

          Pirate pirate(name,stoi(rating),origin,desc);// The stoi turn rating back to int so it can be use in the overloaded function
          m_allPirates[i] = pirate;// This will add the pirate object into the array incrmetly by 1 until every pirate is in
          i +=1;

        }
        }

   else {
      cout<<"Unable to open file: please try again."<<endl;
    }
      myfile.close();
      cout<< i << " pirates loaded."<<endl;

}

void Game::StartGame(){
  int userInput = 0;
  int PirateNum = rand() % 352 + 1;// This is use to generate a random number out of the 352 , to choose a pirate
  int ShipNum = rand() % 15 + 1;// This is use to generate a reandom number out of 15 to choose a ship
  m_myPirate = m_allPirates[PirateNum];
  Ship myShip = m_ships[ShipNum];// This is so i can use it's type and other info since seting curship makes it private
  m_myPirate.SetCurShip(myShip);

  cout<<"Congratulation! "<<m_myPirate.GetName()<<" is now ready to plunder!"<<endl;
  cout<<m_myPirate.GetName()<<" is aboard a "<<myShip.m_type<<"."<<endl;

  while (userInput != 4){// While the user don't want to  choose retire which is 4
    userInput = MainMenu();// The choose will be displyed in main menu and the choice will be returned and used here

    if (userInput == 1){
      SearchTreasure();// Invokes the search treasure function and allow the user to descide if they want to fight or flee agasint a random pirate and ship
     }
     else if (userInput == 2){
       m_myPirate.RepairShip();// This will repair the ship but also increase days by how many damage the ship has
     }
     else if (userInput == 3){
       cout<<"********************************"<<endl;// This is just to make the screen for score look good
       m_myPirate.DisplayScore();
       cout<<"********************************"<<endl;
     }
     else if (userInput < 1 || userInput > 4){// When the user enter some other that 1 - 4
       cout<<"You have enter an invalid input please try again."<<endl;
     }
   }

   cout<<"********************************"<<endl;
   m_myPirate.DisplayScore();// This is the victory or end game screen for the game, display the score and have a farewell
   cout<<"********************************"<<endl;
   cout<< m_myPirate.GetName()<<" sails off into retirement!"<<endl;
   cout<<"Thanks for playing Pirates!"<<endl;
  
}

int Game::MainMenu(){
  int userChoice;
  cout<< "What would you like you to do"<<endl;
  cout<<"1. Search for Treasure"<<endl;
  cout<<"2. Repair Ship"<<endl;
  cout<<"3. See Score"<<endl;
  cout<<"4. Retire"<<endl;

  cin >> userChoice;
  return userChoice;
}

void Game::SearchTreasure(){
  int choice = 0;
  int EnemyPirateNum = rand() % 352 + 1;// Randomly choose a number out of 352 that repsent priates
  int EnemyShipNum = rand() % 15 + 1;// Randomly choose a number out 

  Pirate EnemyPirate = m_allPirates[EnemyPirateNum];//random pirate from the number chosen, out of 352 choices
  Ship EnemyShip = m_ships[EnemyShipNum];//Random ship chosen from the number out of 15 choices

  cout<<"You scan the hoirzon for prospective targets . . ."<<endl;
  cout<<"Off in the distance , you see "<<EnemyPirate.GetName()<<" on a "<<EnemyShip.m_type <<"!"<<endl;
  cout<<"What would you like to do?"<<endl;
  cout<<"1. Attack "<< EnemyPirate.GetName()<<endl;
  cout<<"2. Attempt to Flee from "<<EnemyPirate.GetName()<<endl;
  
  while( choice > 2 || choice < 1){// This is just for input validation make sure that the choice will be 1 or 2
    cin >> choice;
    cout<<"You have enter the wrong number please choose 1 or 2."<<endl;
    cout<<endl;
    cout<<"1. Attack "<< EnemyPirate.GetName()<<endl;// This is repated to let the user know what 1 and 2 represent and not jus tbe choose 1 or 2
    cout<<"2. Attempt to Flee from "<<EnemyPirate.GetName()<<endl;

  }

  if (choice == 1){
      m_myPirate.Battle(EnemyPirate,EnemyShip);
    }
  else if (choice == 2){
      m_myPirate.Flee(EnemyPirate,EnemyShip);
    }

   
}




