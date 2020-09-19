
#include"Gun.h"

Gun::Gun(){
}

Gun::Gun(string _type, int _damage, double _priceoo){
  type =  _type;
  damage =  _damage;
  priceoo =  _priceoo;
}

void Gun::set_type(string _type){
     type = _type;
}

void Gun::set_damage(int _damage){
     damage = _damage;
}

void Gun::set_priceoo(double _priceoo){
     priceoo = _priceoo;
}

string Gun::get_type(){
     return type;
}

int Gun::get_damage(){
     return damage;
}

double Gun::get_priceoo(){
     return priceoo;
}

Gun::~Gun(){
}
