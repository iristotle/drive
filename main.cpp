#include "car.h"

int main(){
	char rfile[] = "rect.txt";
	char cfile[] = "commands.txt";
	Car* c = new Car(rfile,cfile);
	c->drive();
	delete c;
	return 0;
}