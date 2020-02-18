#include<iostream>
using namespace std;

class Recta{
	private:
		double A, B, C;
	public:
		Recta(double coef_x, double coef_y, double coef_indep){
			A = coef_x;
			B = coef_y;
			C = coef_indep;
		}
		void SetCoeficientes(double coef_x, double coef_y, double coef_indep){
			A = coef_x;
			B = coef_y;
			C = coef_indep;		
		}
		double CoeficienteX(){
			return A;
		}
		double CoeficienteY(){
			return B;
		}
		double CoeficienteIndepen(){
			return C;
		}
		double Ordenada(double x){
			double ordenada = (-C - x*A)/B;
			return ordenada;
		}
		double Abcisa(double y){
			double abcisa = (-C - y*B)/A;
			return abcisa;
		}
		double Pendiente(){
			double pendiente = -A/B ;
			return pendiente;
		}
		bool ParametrosCorrectos(double coef_x, double coef_y){
			bool son_correctos = false;
			if(coef_x != 0 || coef_y != 0){
				son_correctos = true;
			}
			return son_correctos;
		}
};

int main(){
	double x_recta1, y_recta1, indepen_recta1;
	double x_recta2, y_recta2, indepen_recta2;
	double x, y;
	double pendiente_recta1, pendiente_recta2;
	double ordenada_de_x, abcisa_de_y;
	bool parametros_correctos1, parametros_correctos2;
	
	cout << "Introduzca los coeficientes de la primera recta (del tipo Ax + By + C = 0):  \n";
   	cin >> x_recta1;
   	cin >> y_recta1;
   	cin >> indepen_recta1;
   	
   	cout << "\nIntroduzca los coeficientes de la segunda recta (del tipo Ax + By + C = 0):  \n";
   	cin >> x_recta2;
   	cin >> y_recta2;
   	cin >> indepen_recta2;
   	
   	cout << "\nIntroduzca el valor de abscisa: \n";
   	cin >> x;
   	cout << "\nIntroduzca el valor de ordenada: \n";
   	cin >> y;

	Recta recta1(x_recta1, y_recta1, indepen_recta1);
	Recta recta2(x_recta2, y_recta2, indepen_recta2);
	
	parametros_correctos1 = recta1.ParametrosCorrectos(x_recta1,y_recta1);
	parametros_correctos2 = recta2.ParametrosCorrectos(x_recta2,y_recta2);
	
	if(parametros_correctos1)
		cout << "\n\tLos parametros de la recta 1 son correctos.";
	else
		cout << "\n\tLos parametros de la recta 1 NO son correctos.(A=B=0)";

	if(parametros_correctos2)
		cout << "\n\tLos parametros de la recta 2 son correctos.";
	else
		cout << "\n\tLos parametros de la recta 3 NO son correctos.(A=B=0)";	
/*	
	recta1.SetCoeficientes(x_recta1, y_recta1, indepen_recta1);
	recta2.SetCoeficientes(x_recta2, y_recta2, indepen_recta2);
*/	
	pendiente_recta1 = recta1.Pendiente();
	pendiente_recta2 = recta2.Pendiente();
	
	ordenada_de_x = recta1.Ordenada(x);
	abcisa_de_y = recta1.Abcisa(y); 

	cout << "\n\n\tLa pendiente de la recta 1 es: " << pendiente_recta1 << endl;
	cout << "\n\tLa pendiente de la recta 2 es: " << pendiente_recta2 << endl;
	cout << "\n\tLa ordenada de la recta 1 en " << x << " es " << ordenada_de_x << endl;
	cout << "\n\tLa abcisa de la recta 1 en " << y << " es " << abcisa_de_y << endl;
}
   
   
