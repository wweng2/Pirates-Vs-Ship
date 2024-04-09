/*
File: Pirate.cpp
Project: CMSC 202 Project 2 , Fall 2020
Date: 10/3/2020
Name: Wei zhang weng
Section: 10
Emil: wweng2@umbc.edu

This file contains the implemtation for all of the function from the Pirate 
class. The function allow the user to create pirate object with their
name, age, birthplace, and decsription. And function that allow for calulation
of treasure, repairing ships and battling.
*/
#include "Pirate.h"


Pirate::Pirate(){
  m_pirateName = "Charles";// These are the default just the most basic template for a pirate
  SetRating(1);
  m_pirateOrigin = "England";
  m_pirateDesc = " Pirate lackey";
  m_pirateCargo = 0;
  m_pirateDays = 0;
} 

Pirate::Pirate(string name, int rating, string origin, string desc){
  m_pirateName = name;
  SetRating(rating);
  m_pirateOrigin = origin;
  m_pirateDesc = desc;
  m_pirateCargo = 0;
  m_pirateDays = 0;
}
string Pirate::GetName(){
  return m_pirateName;
}

int Pirate::GetRating(){
  return m_pirateRating;
}

void Pirate::SetRating(int rating){
  if (rating > 0 && rating <= 100){// To prevent a 0 or negative rating to occur, and if it does the rating will be 1, the lowest amount
    m_pirateRating = rating;
  }
  else{
    m_pirateRating = 1;
  }
}

string Pirate::GetOrigin(){
  return m_pirateOrigin;
}

string Pirate::GetDesc(){
  return m_pirateDesc;
}

void Pirate::SetCurShip(Ship curShip){
  m_curShip = curShip;
}

void Pirate::CalcTreasure(Ship enemyShip){

  double treasureDivider = 3.0;// This is for value to get the average by dividing by it
  double treasure = ( double (enemyShip.m_cannon) +  double (enemyShip.m_toughness) + double (enemyShip.m_speed)) / treasureDivider;// Used decimal to make sure the average is accurate
  cout<<"Congrats you looted "<< treasure<<" cargo from your enemy"<<endl;
  m_pirateCargo += treasure;
}

void Pirate::Battle(Pirate enemyPirate, Ship enemyShip){
  int selfCannon;
  int enemyCannon;
  int hit = 0;
  
  if (m_curShip.m_curToughness > 0){// This make sure that only when the ship has at least 1 toughness to fight, and not have werid 0 toughness ships
    while(enemyShip.m_curToughness > 0 &&  m_curShip.m_curToughness > 0){// The and , make sure that the second either the enemy ship or own ship has o or less toughness it will stop
      for (selfCannon = 0; selfCannon < m_curShip.m_cannon ; selfCannon++){// This will fire based on how many cannons a ship haves
	if ( (rand() % 100 + 1) <= GetRating()){// It will only hit if the rand genrates a number between 1 and 100 that is less then or eqaul to rating for it to hit
	  hit += 1;
	}
      }
      cout<<GetName()<<" fires "<< m_curShip.m_cannon<< " cannons!"<<endl;
      cout << hit<< " shots hit!"<<endl;
      enemyShip.m_curToughness -= hit;
      hit = 0;// This refesh hit , so it can be used by enmeyShip
      
      if (enemyShip.m_curToughness > 0){// This prevent the enmy ship from fire cannons when they are already destroy
	for (enemyCannon = 0; enemyCannon < enemyShip.m_cannon ; enemyCannon++){
	  if ( (rand() % 100 + 1) <= enemyPirate.GetRating()){// Same thing as curShip but for enemy ship and based on the enemy pirates rating
	    hit += 1;
	  }
	}
	cout<<enemyPirate.GetName()<<" fires "<< enemyShip.m_cannon<< " cannons!"<<endl;
	cout << hit<< " shots hit!"<<endl;
	m_curShip.m_curToughness -= hit;
	hit = 0;
      }
    }
    if (m_curShip.m_curToughness < 1){// When the user lose this will display a message and make sure the cargo is decrease by have
      m_curShip.m_curToughness = 0;
      m_pirateCargo -= (m_pirateCargo /2);
      cout<<"The enemy pirate has looted "<<(m_pirateCargo/2)<<" from you."<<endl;
    }
    else if (enemyShip.m_curToughness < 1){
      cout<<"You win!"<<endl;
      CalcTreasure(enemyShip);
    }
    m_pirateDays += 1;
  }
  
  else if( m_curShip.m_curToughness < 1){
    cout<< "Your ship is too damage to battle , please repair it first before trying to battle other pirates."<<endl;

    m_pirateDays += 1;
  }
  
}
void Pirate::RepairShip(){
  int damage = m_curShip.m_toughness - m_curShip.m_curToughness;
  m_pirateDays += damage;// This will increase days by how much damge was cause to to the ship
  m_curShip.m_curToughness = m_curShip.m_toughness;
  cout<<"it takes "<< damage<<" days to repair your "<<m_curShip.m_type<<"."<<endl;
}

void Pirate::Flee(Pirate enemyPirate, Ship enemyShip){
  if(enemyShip.m_speed > m_curShip.m_speed){// This will make the user go into battle and add 1 to pirate day for the atempt
    cout<< "Prepare for battle "<<enemyPirate.GetName()<<" has catch your ship."<<endl;
    Battle(enemyPirate,enemyShip);
    m_pirateDays += 1;
  }
  else if (enemyShip.m_speed < m_curShip.m_speed || enemyShip.m_speed == m_curShip.m_speed ){
    cout<<"You narrowly flee from "<<enemyPirate.GetName()<<endl;
  }
  
}

void Pirate::DisplayScore(){
   cout<<"Name: "<< GetName()<<endl;
  cout<<"Rating: "<<GetRating()<<endl;
  cout<<"Country of Origin: "<<GetOrigin()<<endl;
  cout<<"Description: "<<GetDesc()<<endl;
  cout<<"Days Sailing: "<<m_pirateDays<<endl;
  
  if (m_pirateCargo == 0 && m_pirateDays == 0){// This is make sure no 0/0 happen if someone wnat to check score on day 0, it will just diplay 0 in that case
    cout<<"Cargo Per Day: "<< 0<<endl;

  }
  else{
    cout<<"Cargo Per Day: "<<  double (m_pirateCargo) / double( m_pirateDays)<<endl;
  }
  
  cout<<"Ship Type: "<<m_curShip.m_type<<endl;
  cout<<"Ship Cannons: "<<m_curShip.m_cannon<<endl;
  cout<<"Ship Current Toughness: "<<m_curShip.m_curToughness<<endl;
  cout<<"Ship Max Toughness: "<<m_curShip.m_toughness<<endl;
  cout<<"Ship Speed: "<< m_curShip.m_speed<<endl;
}
