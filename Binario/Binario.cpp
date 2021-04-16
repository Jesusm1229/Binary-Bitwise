//JESUS MEDINA C.I:24225319 Asignación 2: ARCHIVO BINARIO

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using std::cout;
using std::string;
using std::ifstream;
using std::ios;
using std::endl;


struct CabeceraImagen
{
	int ancho;
	int alto;
	char sustitutoDelCero;
	char sustitutoDelUno;
	int cantidadDeBytes;

	CabeceraImagen() {
		ancho = alto = cantidadDeBytes = 0;
		sustitutoDelCero = sustitutoDelUno = '\0';
	}

	~CabeceraImagen(){}
};


void cabecera(struct CabeceraImagen cb) {

		system("CLS");
		cout << "Ancho | Alto | Sustituto del Cero | Sustituto del Uno | Cantidad de Bytes a graficar\n"<<cb.ancho<<" "<< cb.alto<<" "<< cb.sustitutoDelCero<<" "<< cb.sustitutoDelUno<<" "<< cb.cantidadDeBytes<<endl;
	
}
	
bool comprbStruct(struct CabeceraImagen cb){
	bool flag = false;
	flag = ((cb.alto * cb.ancho) != (cb.cantidadDeBytes * 8) || ((cb.cantidadDeBytes || cb.ancho || cb.alto) < 0) || cb.ancho > 80);
	return flag;
}

void crearFigura(string nombreArchivo, struct CabeceraImagen cb){

	ifstream archivo(nombreArchivo, ios::binary | ios::in);	
	int salto = 0;
	long desplazamiento = (long) sizeof(CabeceraImagen);		
	
	cabecera(cb); 
	if (comprbStruct(cb)) { std::cerr << "\nError en tamano asignado\n"; return; }

	cout << "\nFIGURA RESULTANTE\n" << endl;
	for (int i = 0 , k = i+(desplazamiento); i < cb.cantidadDeBytes; i++, k++)
	{	
		char byte;
		archivo.seekg(k);
		archivo.get(byte);

		int bit;
		for (int i = 7; i >= 0; i--)
		{
			bit = ((byte >> i) & 1);  //BITWISE Por la derecha
			(bit == 0) ? (cout << cb.sustitutoDelCero) : (cout << cb.sustitutoDelUno);
			salto++;
			if (salto == cb.ancho) { cout << endl; salto = 0; }

		}
	}
}




int main()
{ 
	struct CabeceraImagen cb;
	string nombreArchivo;
	ifstream archivo;

	
	cout << "Ingrese nombre Archivo junto con extension (.dat, .bin , etc)"<<endl;
	std::cin>>nombreArchivo;
	
	archivo.open(nombreArchivo, ios::binary);
	if (!archivo) { cout << "Error al leer archivo";	
					system("pause"); 
					return 1; }
	try {
		archivo.read(reinterpret_cast<char*>(&cb), sizeof(CabeceraImagen));	
		crearFigura(nombreArchivo,cb);	
	}
	catch (... ) {
		cout << "Excepción imprevista" << endl;
	}
		
	
	system("pause");

	return 0; 
}
