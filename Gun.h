
#ifndef GUN_H
#define GUN_H

#include <string>

using namespace std;

class Gun{
    private:
       string type;
       int damage;
       double priceoo;
public:
       Gun();
       Gun(string,int,double);
       void set_type(string);
       void set_damage(int);
       void set_priceoo(double);
       string get_type();
       int get_damage();
       double get_priceoo();
       string toString();
       ~Gun();
};

#endif