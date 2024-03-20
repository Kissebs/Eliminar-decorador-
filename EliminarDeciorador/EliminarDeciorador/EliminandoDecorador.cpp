#include <iostream>
#include <sstream>

using namespace std;


class DecoratorX {
private:
	int x;
	string cedula;
	DecoratorX* decorador;//Enlace hacia otro decorador
public:
	DecoratorX(int, string, DecoratorX*);
	virtual ~DecoratorX();
	void setProDec(DecoratorX*);//Para setear el proximo
	DecoratorX* getProDec();//Retorna el decorador siguiente
	int getX();
	string getCedula();
	string toString();


};

DecoratorX::DecoratorX(int n, string ced, DecoratorX* deco):x(n),cedula(ced),decorador(deco)
{

}

DecoratorX::~DecoratorX()
{
}

void DecoratorX::setProDec(DecoratorX* deco)
{
	decorador = deco;
}

DecoratorX* DecoratorX::getProDec()
{
	return decorador;
}

int DecoratorX::getX()
{
	return x;
}

string DecoratorX::getCedula()
{
	return cedula;
}

string DecoratorX::toString()
{
	stringstream s;
	if (decorador != NULL) {

		s << "[OB]=" << x << "," << cedula << "]-------->";
		s << this->getProDec()->toString();//proceso recursivo
	}else {
		s << "[OB= " << x <<"," << cedula << "]----FIN---";
	}
	

	return s.str();
}



int main() {
	char letra;
	int valor;

	DecoratorX* ppio = NULL;
	DecoratorX* pAct= NULL;
	DecoratorX* borrar = NULL;

	cout << "Eliminar Decorator" << endl;

	DecoratorX* k = new DecoratorX(1,"1111",NULL);
	DecoratorX* k2 = new DecoratorX(2,"2222",NULL);
	DecoratorX* k3 = new DecoratorX(3,"3333",NULL);
	DecoratorX* k4 = new DecoratorX(4,"4444",NULL);
	
	cout << "Conectar lo decoradores (Ingredientes)" << endl;
	k4->setProDec(k3);
	k3->setProDec(k2);
	k3->setProDec(k);


	cout<<k4->toString();

	cout << "Eliminando Decorator" << endl;
	cout << "Cual objeto desea borrar" << endl;
	cout << "Por numero o por cedula.......n/c" << endl;

	cin >> letra;
	if (letra == 'n'||letra== 'N') {
		cout << "Escriba el numero que tiene el objeto a borrar: ";
		cin >> valor;
		ppio = k4;
		pAct = k4;
		if (pAct != NULL) {//Aqui se garantiza de que por lo menos hay uno
			if (pAct->getX() == valor) {//Lo encontre y es el primero
				borrar = pAct;
				ppio = pAct->getProDec();
				pAct = ppio;
				delete borrar;
			}
			else {// II Segunda Etapa

				while (pAct->getProDec() != NULL && pAct->getProDec()->getX()!=valor) {
					pAct = pAct->getProDec();//Aqui lo paso al proximo
					
				}
				if (pAct->getProDec() == NULL) {
					cout << "Este objeto tipo decorador concreto con valor " << valor << " no existe" << endl;

				}if (pAct->getProDec()->getX() == valor) {

					borrar = pAct->getProDec();
					pAct->setProDec(borrar->getProDec());//desvio el enlace al prox
					delete borrar;

				}
			
			
			}

		}
		/*else {
			cout << "No existe una lista de decoradores concretos" << endl;
		}*/

	}
	else if(letra == 'c'||letra== 'C') {
	//Tarea moral
	
	}

	cout << k4->toString();


	system("pause");
	return 0;
}