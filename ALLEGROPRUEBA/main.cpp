#include <allegro.h>
#include <iostream>
#include <random>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <climits>
#include <bits/stdc++.h>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <locale.h>

BITMAP *buffer;
BITMAP *L0,*L1,*L2,*L3,*L4,*L5,*L6,*L7,*L8,*L9,*L10,*L11,*L12,*L13,*L14,*L15,*L16,*L17,*L18,*L19,*L20,*L21,*L22;
BITMAP *mapaAqp;
BITMAP *banner;
BITMAP *R1,*R2,*R3,*R4,*R5,*R6,*R7,*R8,*R9,*R10,*R11,*R12;
using namespace std;
struct Lugar {
	string name;
	int tiempo,precio;
	struct Lugar *sig;
};
typedef struct Lugar *LugarI;
struct Dest{
	string Inicio,Final;
	int tiempo;
	float Km;
	struct Dest *sig;
};
typedef struct Dest *DestI;
struct Ruta {
	string Lugar;
	int tiempo,precio;
	struct Ruta *sig;
};
typedef struct Ruta *RutaI;
struct Minimal{
	string lugar;
	int tiempo,precio;
	struct Minimal *sig;
};
typedef struct Minimal *MiniI;
struct AArista {
	int time;
	float km;
	struct AArista *sig;
};
typedef struct AArista *AARI;
struct Lista{
  string name;
  struct Lista *next;
};
typedef struct Lista *ListaI;
struct Tiempo{
  int timme;
  struct Tiempo *next;
};
typedef struct Tiempo *TiempoI;
struct RestauranteLugar{
	string Inicio;
	string final;
	int tiempo;
	float km;
	struct RestauranteLugar *sig;
};
typedef struct RestauranteLugar *RL;
struct LugarRestaurante{
	string Inicio;
	string final;
	int tiempo;
	float km;
	struct LugarRestaurante *sig;
};
typedef struct LugarRestaurante *LR;
struct RUTAFINAL {
	string place;
	int tiempo;
	int precio;
	struct RUTAFINAL *sig;
};
typedef struct RUTAFINAL *RF;
struct ViajeFinal {
	int tiempo;
	float km;
	struct ViajeFinal *sig;
};
typedef struct ViajeFinal *VF;
struct Fusion{
    string place;
    int tiempoL,tiempoV;
    int precio;
    float km;
    struct Fusion *sig;
};
typedef struct Fusion *FRV;

FRV CrearFusion(string lugar,int tiempoA, int tiempoB, int precios, float kms){
    FRV nuevoMini = new(struct Fusion);
	nuevoMini->place = lugar;
	nuevoMini->tiempoL = tiempoA;
	nuevoMini->tiempoV = tiempoB;
	nuevoMini->precio = precios;
	nuevoMini->km = kms;
	nuevoMini->sig=NULL;
	return nuevoMini;
}
void InsertarFusion(FRV &ListaFusion,string lugar,int tiempoA, int tiempoB, int precios, float kms){
	if(ListaFusion==NULL){
		ListaFusion=CrearFusion(lugar,tiempoA,tiempoB,precios,kms);
	}
	else{
		InsertarFusion(ListaFusion->sig,lugar,tiempoA,tiempoB,precios,kms);
	}
}
void MostrarFusion(FRV ListaFusion){
	if(ListaFusion!=NULL){
		cout<<ListaFusion->place<<" -- "<<ListaFusion->tiempoL<<" minutos "<<" -- S/."<<ListaFusion->precio<<endl;
		cout<<ListaFusion->tiempoV<<" minutos "<<" -- "<<ListaFusion->km<<" km "<<endl;
		MostrarFusion(ListaFusion->sig);
	}
}

RF CrearRF(string Lugar,int tiempo, int precio) {
	RF nuevoMini = new(struct RUTAFINAL);
	nuevoMini->place = Lugar;
	nuevoMini->tiempo = tiempo;
	nuevoMini->precio = precio;
	nuevoMini->sig=NULL;
	return nuevoMini;
}
void InsertarRF(RF &ListaMinimal,string lugar, int tiempo, int precio){
	if(ListaMinimal==NULL){
		ListaMinimal=CrearRF(lugar,tiempo,precio);
	}
	else{
		InsertarRF(ListaMinimal->sig,lugar,tiempo,precio);
	}
}
void MostrarRF(RF ListaMinimal){
	if(ListaMinimal!=NULL){
		cout<<ListaMinimal->place<<" -- "<<ListaMinimal->tiempo<<" minutos "<<" -- S/."<<ListaMinimal->precio<<endl;
		MostrarRF(ListaMinimal->sig);
	}
}


VF CrearVF(int time,float km) {
	VF nuevoLugar = new(struct ViajeFinal);
	nuevoLugar->tiempo = time;
	nuevoLugar->km = km;
	nuevoLugar->sig=NULL;
	return nuevoLugar;
}
void LlenarVF(VF &ListaAristas,int time,float km) {
	if(ListaAristas==NULL){
		ListaAristas=CrearVF(time,km);
	}
	else {
		LlenarVF(ListaAristas->sig,time,km);
	}
}
void MostrarVF(VF ListaAristas) {
	if(ListaAristas!=NULL) {
		cout<<ListaAristas->tiempo<<" minutos. - "<<ListaAristas->km<<" km."<<endl;
		MostrarVF(ListaAristas->sig);
	}
}

RL CrearRL(string Ini,string End,int time, float Kms) {
	RL nuevoDestino =new(struct RestauranteLugar);
	nuevoDestino->Inicio = Ini;
	nuevoDestino->final = End;
	nuevoDestino->tiempo = time;
	nuevoDestino->km = Kms;
	nuevoDestino->sig=NULL;
	return nuevoDestino;
}
void LlenarRL(RL &ListaDestinos,string Ini,string End,int time, float Kms) {
	if(ListaDestinos==NULL){
		ListaDestinos=CrearRL(Ini,End,time,Kms);
	}
	else {
		LlenarRL(ListaDestinos->sig,Ini,End,time,Kms);
	}
}
void InsertarRL(RL &ListaDestino){
	string A2[12]={"Restaurant Campestre Los Andenes de Chilina","Chicha de Gastón Acurio","Picanteria Pata'ccala","Restaurant Campestre SONCCO KILLA","El Chopito","Tradición Arequipeña","Restaurant Las Palmeras","Costanera AQP","Místico Restaurante típico campestre","Restaurant Campestre Delf","Restaurante Los Rosales","La Guardiana de Characato"};
	string A1[23]={"Plaza de Armas","Museo Santuarios Andinos - MUSA","Monasterio de Santa Catalina","Mundo Alpaca","Mirador de Yanahuara","Mirador de Carmen Alto","Incalpaca","Palacio Goyeneche","Mansion del Fundador","Molino de Sabandia","Casona Tristán del pozo","Casa Museo Mario Vargas Llosa","Templo La Compañía de Jesús Arequipa","Ruta del Sillar","Museo CASA MORAL","Museo de Arte virreinal Santa Teresa","Chapi chico","Mirador de Sachaca","Parque Selva Alegre","Tingo","Mirador Natural de Kasapatac","Plaza de Characato","Basílica Catedral de Arequipa"};
	long int   B[12][23]={{24,24,11,9,11,10,16,14,33,40,18,15,23,42,19,16,12,22,8,24,28,45,23},
						{13,13,0,7,10,15,11,10,30,33,8,13,11,43,9,5,11,19,11,20,25,38,12},
						{32,27,14,12,11,5,19,16,35,44,22,18,26,28,24,19,14,25,11,27,30,46,26},
						{28,28,19,19,15,17,11,18,24,36,29,20,27,23,28,26,21,13,18,16,19,39,28},
						{29,29,23,23,23,29,14,21,10,21,28,19,29,40,30,24,25,11,28,8,5,24,30},
						{18,18,14,16,21,23,15,15,15,20,15,11,17,42,14,7,9,12,11,10,14,19,11},
						{12,13,8,9,12,15,14,11,19,19,8,12,12,34,9,6,7,17,9,15,18,22,11},
						{12,12,6,5,9,10,10,8,18,22,6,11,11,31,7,4,2,16,5,15,18,25,11},
						{20,20,15,15,19,22,21,20,22,18,15,18,17,40,16,14,13,23,16,21,23,21,17},
						{20,20,17,18,21,25,16,12,4,16,16,14,17,36,17,15,18,15,18,12,9,19,17},
						{14,14,6,8,5,7,9,15,22,26,10,9,10,28,11,9,10,15,7,15,18,29,11},
						{26,26,24,25,27,31,23,23,18,5,23,21,23,41,23,21,23,25,24,23,22,2,23}
						};
	float C[12][23]={{5.3,5.4,4.5,4,4.3,4.8,7,5.5,14.8,15.7,5,6.7,5.2,14.4,5.2,4.8,5,10.1,3.5,10.2,12.2,17.8,5.3},
						{1.3,1.3,0,1.2,2.3,4.6,1.2,1.8,12,10.2,1,2.6,1.2,13.1,1.2,0.8,2.6,7.2,1.4,7.6,9.2,12,1.3},
						{13.4,7.5,6.6,6.1,4.6,2.3,8.9,6.3,15.6,17.6,7.1,7.4,7.3,11,7.3,8.1,6.8,10.6,5.7,10.9,12.9,18.1,7.4},
						{6.1,6.1,6,6.8,4.4,6,4,5.3,11.3,14,7.8,6.2,6,7.9,7.1,9,7.5,6,6.4,7.1,9.4,15.8,7.5},
						{6.1,6.1,6.8,6.9,8.5,10.3,6,6,6,8.2,6.6,5.1,6.3,15.9,6.9,6.5,7.7,4.1,7.6,3.1,2,10,6.2},
						{3,3,3.7,3.9,5.6,8.5,5.6,3.9,6.9,7.6,3.2,2.7,2.9,16,3.4,3.1,4.5,6.9,4.1,6,6.6,9.4,2.9},
						{3.2,3.3,3.1,3.3,4.5,7.2,6.4,4,10.4,7.3,3,4.4,3.1,21.1,3.3,2.5,2.5,9.2,3.2,8.2,10.2,9.2,3.1},
						{2.3,2.3,2.2,2.3,3.8,4.9,4.9,3.9,10.7,10,2.1,5.4,2.2,14.5,2.3,1.6,0.9,8.4,2.1,8.7,10.3,11.8,2.2},
						{7.2,7.2,6.7,6.8,7.9,10.3,9.3,9.3,11.7,7.9,6.6,8,6.7,24.1,6.8,6.1,5.3,12.3,6.7,11.3,10.9,9.7,6.7},
						{7.6,7.6,8.7,9.3,9.6,11.9,8.7,5.4,2.3,6.9,8.2,6.7,7.5,21.2,8.5,8.1,9.9,6.2,9.2,5.2,3.8,8.7,7.6},
						{3.7,3.7,2.4,3.5,1.4,2.7,4.3,7.9,12.1,13.2,3.5,4,3.6,12.3,3.7,3.3,4.2,7.3,3.1,7.5,9.4,15.1,3.6},
						{10.8,10.8,10.8,11.4,12.1,14.4,12.3,11.7,9.7,1.9,10.5,10.4,10.7,25.3,11.2,10.2,10.9,13.6,11.3,12.6,10.2,0.6,10.7}
						};
	for(int i=0;i<12;i++){
		for(int j=0;j<23;j++){
			LlenarRL(ListaDestino,A2[i],A1[j],B[i][j],C[i][j]);
		}
	}
}
void MostrarRL(RL ListaDestino){
	if(ListaDestino!=NULL) {
		cout<<ListaDestino->Inicio<<" -- "<<ListaDestino->tiempo<<"minutos "<<" -- "<<ListaDestino->km<<"KM -- "<<ListaDestino->final<<endl;
		MostrarRL(ListaDestino->sig);
	}
}

LR CrearLR(string Ini,string End,int time, float Kms) {
	LR nuevoDestino =new(struct LugarRestaurante);
	nuevoDestino->Inicio = Ini;
	nuevoDestino->final = End;
	nuevoDestino->tiempo = time;
	nuevoDestino->km = Kms;
	nuevoDestino->sig=NULL;
	return nuevoDestino;
}
void LlenarLR(LR &ListaDestinos,string Ini,string End,int time, float Kms) {
	if(ListaDestinos==NULL){
		ListaDestinos=CrearLR(Ini,End,time,Kms);
	}
	else {
		LlenarLR(ListaDestinos->sig,Ini,End,time,Kms);
	}
}
void InsertarLR(LR &ListaDestino){
	string A1[12]={"Restaurant Campestre Los Andenes de Chilina","Chicha de Gastón Acurio","Picanteria Pata'ccala","Restaurant Campestre SONCCO KILLA","El Chopito","Tradición Arequipeña","Restaurant Las Palmeras","Costanera AQP","Místico Restaurante típico campestre","Restaurant Campestre Delf","Restaurante Los Rosales","La Guardiana de Characato"};
	string A2[23]={"Plaza de Armas","Museo Santuarios Andinos - MUSA","Monasterio de Santa Catalina","Mundo Alpaca","Mirador de Yanahuara","Mirador de Carmen Alto","Incalpaca","Palacio Goyeneche","Mansion del Fundador","Molino de Sabandia","Casona Tristán del pozo","Casa Museo Mario Vargas Llosa","Templo La Compañía de Jesús Arequipa","Ruta del Sillar","Museo CASA MORAL","Museo de Arte virreinal Santa Teresa","Chapi chico","Mirador de Sachaca","Parque Selva Alegre","Tingo","Mirador Natural de Kasapatac","Plaza de Characato","Basílica Catedral de Arequipa"};
	long int   B[23][12]={{13,4,12,12,11,8,9,8,16,14,7,22},
					{13,4,12,12,11,8,9,8,16,14,7,22},
					{10,0,11,11,12,9,7,6,15,14,5,23},
					{9,2,10,10,11,9,8,7,16,15,4,23},
					{9,5,8,9,13,11,14,9,19,17,4,25},
					{9,9,4,13,17,15,14,10,20,21,6,29},
					{14,6,13,9,9,11,12,11,19,14,9,21},
					{13,4,12,12,9,6,7,6,14,12,7,20},
					{27,17,26,21,10,13,17,18,22,4,22,19},
					{29,21,29,25,17,14,17,20,18,14,24,4},
					{12,3,12,11,11,9,9,7,17,14,6,22},
					{14,5,13,12,7,7,8,10,15,13,8,19},
					{13,5,12,12,11,8,9,7,15,14,7,22},
					{32,26,24,17,26,27,29,31,37,31,27,38},
					{11,2,11,10,10,8,8,7,15,13,5,21},
					{10,3,12,11,12,7,6,5,13,14,6,20},
					{11,7,12,15,14,8,6,3,12,16,9,21},
					{20,12,19,13,10,13,16,16,23,14,15,24},
					{7,4,9,11,13,9,8,6,15,16,6,22},
					{21,12,21,15,8,13,13,14,20,11,15,23},
					{23,14,23,17,5,13,15,16,22,8,17,22},
					{32,24,32,28,20,17,20,22,21,17,27,2},
					{13,4,12,11,10,8,8,7,15,13,6,21}
					};
	float C[23][12]={{6,1.6,6.1,5.5,5.6,3.4,3.8,2.9,7.3,7.4,2.6,11},
					{6,1.6,6.1,5.5,5.6,3.4,3.8,2.9,7.3,7.4,2.6,11},
					{4.4,0,5.6,5,6.5,3.3,3.3,2,6.8,7.7,1.8,11},
					{4.3,0.7,5.6,5,6.8,5.5,3.6,2.6,7.3,9,1.8,13.1},
					{4.3,1.8,4.4,4.5,7.5,6.1,6.6,4.6,9,9.7,1.3,13.9},
					{5,3.9,2.2,6,9.6,8.2,7.4,5.4,9.7,11.8,2.7,14.7},
					{6.8,2.8,6.6,4.9,5.2,6.9,6.2,5.2,10.3,8.2,4.4,12.4},
					{6.1,1.5,6.9,5.8,5.3,2.8,3.4,2.5,7,7.1,3.1,10.6},
					{14.6,10.1,15.4,14.6,6,7.4,10.2,10.2,11.7,2.3,12,9.7},
					{13.5,10.1,15,16,8.3,6.6,7.8,9.2,7.9,6.9,11.3,1.9},
					{5.4,0.9,6.2,5.6,6.5,3.7,4.1,3.2,8.4,7.8,2.5,11.3},
					{6.8,2.3,7.6,7.1,4.5,4,5,6,9.1,8.1,3.9,11.2},
					{6.1,1.8,6.2,5.7,5.7,3.3,3.9,3,7.4,7.6,2.8,11.1},
					{14.2,12.6,10.6,8.3,17.1,18.8,19.6,20.5,23.7,20.1,13.2,24.3},
					{5.2,0.6,6,5.4,6.3,3.5,3.9,3,7.4,7.5,2.3,11},
					{4.4,1.1,6.2,5.6,6.6,3,3,1.7,6.5,7.6,2.4,10.3},
					{5.2,3,6.7,7.3,7.8,4.1,2.4,1,5.9,9.5,4.4,10.5},
					{9.7,5.7,9.5,6.4,4.3,8,8.5,8.3,12.6,6.2,7.3,13.5},
					{3.5,1.4,5.6,5.7,7.5,4,3.5,2.5,7.1,9.7,2.5,11.3},
					{10.5,6,11.3,7.6,3.4,6.9,7.4,7.2,11.5,5.3,7.6,12.4},
					{12.2,7.7,13.1,11.8,2.1,6.5,9.1,9,13.3,3.8,9.3,10.3},
					{15.3,11.9,16.9,17.8,10.1,8.4,9.7,11.1,9.7,8.7,13.1,0.6},
					{5.9,1.6,6.1,5.5,5.6,3.4,3.7,2.9,7.3,7.4,2.6,10.9}
					};
	for(int i=0;i<23;i++){
		for(int j=0;j<12;j++){
			LlenarLR(ListaDestino,A2[i],A1[j],B[i][j],C[i][j]);
		}
	}
}
void MostrarLR(LR ListaDestino){
	if(ListaDestino!=NULL) {
		cout<<ListaDestino->Inicio<<" -- "<<ListaDestino->tiempo<<"minutos "<<" -- "<<ListaDestino->km<<"KM -- "<<ListaDestino->final<<endl;
		MostrarLR(ListaDestino->sig);
	}
}

TiempoI CrearTempo(int time) {
	TiempoI nuevoLugar = new(struct Tiempo);
	nuevoLugar->timme = time;
	nuevoLugar->next= NULL;
	return nuevoLugar;
}
void LlenarTempo(TiempoI &Tiempos,int tempo){
	if(Tiempos==NULL){
		Tiempos=CrearTempo(tempo);
	}
	else {
		LlenarTempo(Tiempos->next,tempo);
	}
}

void MostrarTempo(TiempoI Tiempos) {
	if(Tiempos!=NULL) {
		cout<<Tiempos->timme<<endl;
		MostrarTempo(Tiempos->next);
	}
}

int Posicion(TiempoI &Tiempos,int min, int alf) {
	if(Tiempos->timme==min) {
		return alf;
	}
	else {
		alf++;
		Posicion(Tiempos->next,min,alf);
	}
}

ListaI CrearLista(string nombre) {
	ListaI nuevoLugar = new(struct Lista);
	nuevoLugar->name = nombre;
	nuevoLugar->next= NULL;
	return nuevoLugar;
}
void LlenarLista(ListaI &Lista,string nombre){
	if(Lista==NULL){
		Lista=CrearLista(nombre);
	}
	else {
		LlenarLista(Lista->next,nombre);
	}
}
void MostrarLista(ListaI Lista) {
	if(Lista!=NULL) {
		cout<<Lista->name<<endl;
		MostrarLista(Lista->next);
	}
}
void permute(string a, int l, int r,ListaI &Lista,int b){
   string Inicio="0";
   int Final=b+1;
   string Finalstr = to_string(Final);
    if (l == r){
      Inicio.append(a);
      Inicio.append(Finalstr);
      a=Inicio;
      LlenarLista(Lista,a);
      }
    else{
        for (int i = l; i <= r; i++){
            swap(a[l], a[i]);
            permute(a, l+1, r,Lista,b);
            swap(a[l], a[i]);
        }
    }
}

AARI CrearAARI(int time,float km) {
	AARI nuevoLugar = new(struct AArista);
	nuevoLugar->time = time;
	nuevoLugar->km = km;
	nuevoLugar->sig=NULL;
	return nuevoLugar;
}
void LlenarAARI(AARI &ListaAristas,int time,float km) {
	if(ListaAristas==NULL){
		ListaAristas=CrearAARI(time,km);
	}
	else {
		LlenarAARI(ListaAristas->sig,time,km);
	}
}
void MostrarAARI(AARI ListaAristas) {
	if(ListaAristas!=NULL) {
		cout<<ListaAristas->time<<" minutos. - "<<ListaAristas->km<<" km."<<endl;
		MostrarAARI(ListaAristas->sig);
	}
}

LugarI CrearLugar(string nombre,int time,int price) {
	LugarI nuevoLugar = new(struct Lugar);
	nuevoLugar->name = nombre;
	nuevoLugar->tiempo = time;
	nuevoLugar->precio = price;
	nuevoLugar->sig=NULL;
	return nuevoLugar;
}
void LlenarLugares(LugarI &ListaTuristica,string nombre,int time,int price) {
	if(ListaTuristica==NULL){
		ListaTuristica=CrearLugar(nombre,time,price);
	}
	else {
		LlenarLugares(ListaTuristica->sig,nombre,time,price);
	}
}
void MostrarLugares(LugarI ListaTuristica, int contu) {
	if(contu==0){
		contu++;
		MostrarLugares(ListaTuristica->sig,contu);
	}
	else if(contu==22){
		cout<<"--------------------------------------------------------------------------------------------------"<<endl;
	}
	else{
		if(ListaTuristica!=NULL) {
			cout<<contu<<".\t"<<ListaTuristica->name<<" - "<<ListaTuristica->tiempo<<" minutos."<<" - S/."<<ListaTuristica->precio<<endl;
			contu++;
			MostrarLugares(ListaTuristica->sig,contu);
		}
	}
}
void InsertarLugar(LugarI &ListaTuristica) {
	string A[23]={"Plaza de Armas","Museo Santuarios Andinos - MUSA","Monasterio de Santa Catalina","Mundo Alpaca","Mirador de Yanahuara","Mirador de Carmen Alto","Incalpaca","Palacio Goyeneche","Mansion del Fundador","Molino de Sabandia","Casona Tristán del pozo","Casa Museo Mario Vargas Llosa","Templo La Compañía de Jesús Arequipa","Ruta del Sillar","Museo CASA MORAL","Museo de Arte virreinal Santa Teresa","Chapi chico","Mirador de Sachaca","Parque Selva Alegre","Tingo","Mirador Natural de Kasapatac","Plaza de Characato","Basílica Catedral de Arequipa"};
	int B[23]={10,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,20};
	int C[23]={17,20,50,20,20,30,20,20,25,30,20,30,15,30,20,20,15,15,10,15,15,10,18};
	int i=0;
	while(i<23) {
		LlenarLugares(ListaTuristica,A[i],B[i],C[i]);
		i++;
	}
}

DestI CrearDestino(string Ini,string End,int time, float Kms) {
	DestI nuevoDestino =new(struct Dest);
	nuevoDestino->Inicio = Ini;
	nuevoDestino->Final = End;
	nuevoDestino->tiempo = time;
	nuevoDestino->Km = Kms;
	nuevoDestino->sig=NULL;
	return nuevoDestino;
}
void LlenarDestinos(DestI &ListaDestinos,string Ini,string End,int time, float Kms) {
	if(ListaDestinos==NULL){
		ListaDestinos=CrearDestino(Ini,End,time,Kms);
	}
	else {
		LlenarDestinos(ListaDestinos->sig,Ini,End,time,Kms);
	}
}
void InsertarDestino(DestI &ListaDestino){
	string A2[23]={"Plaza de Armas","Museo Santuarios Andinos - MUSA","Monasterio de Santa Catalina","Mundo Alpaca","Mirador de Yanahuara","Mirador de Carmen Alto","Incalpaca","Palacio Goyeneche","Mansion del Fundador","Molino de Sabandia","Casona Tristán del pozo","Casa Museo Mario Vargas Llosa","Templo La Compañía de Jesús Arequipa","Ruta del Sillar","Museo CASA MORAL","Museo de Arte virreinal Santa Teresa","Chapi chico","Mirador de Sachaca","Parque Selva Alegre","Tingo","Mirador Natural de Kasapatac","Plaza de Characato","Basílica Catedral de Arequipa"};
	string A1[23]={"Plaza de Armas","Museo Santuarios Andinos - MUSA","Monasterio de Santa Catalina","Mundo Alpaca","Mirador de Yanahuara","Mirador de Carmen Alto","Incalpaca","Palacio Goyeneche","Mansion del Fundador","Molino de Sabandia","Casona Tristán del pozo","Casa Museo Mario Vargas Llosa","Templo La Compañía de Jesús Arequipa","Ruta del Sillar","Museo CASA MORAL","Museo de Arte virreinal Santa Teresa","Chapi chico","Mirador de Sachaca","Parque Selva Alegre","Tingo","Mirador Natural de Kasapatac","Plaza de Characato","Basílica Catedral de Arequipa"};
	long int   B[23][23]={{0,0,5,6,7,18,7,14,24,32,9,4,8,35,10,8,13,14,9,20,24,37,0},
					{0,0,5,6,7,12,7,14,26,34,9,5,8,35,9,8,13,14,8,19,23,37,0},
					{8,8,0,2,6,13,7,13,25,33,4,6,7,37,4,3,8,14,4,18,22,36,8},
					{11,11,2,0,5,13,10,13,26,34,9,7,10,36,9,7,8,13,3,18,22,38,11},
					{15,15,6,8,0,11,14,16,29,37,11,11,15,34,12,10,11,17,8,21,25,41,15},
					{21,21,12,10,9,0,19,23,40,45,16,17,20,35,16,14,12,23,9,27,33,47,20},
					{15,15,8,9,10,18,0,7,20,32,12,10,14,29,13,11,16,8,12,11,16,35,15},
					{26,23,15,16,17,25,9,0,13,31,19,16,22,34,20,18,23,4,18,4,9,35,23},
					{31,34,22,24,27,34,20,12,0,24,28,22,31,45,29,27,29,15,26,11,8,27,31},
					{36,37,31,34,37,43,32,30,22,0,31,31,36,55,32,29,32,34,34,29,26,7,36},
					{14,14,3,4,7,13,7,13,25,36,0,6,14,35,1,6,11,14,6,15,20,38,15},
					{8,8,6,5,7,13,5,7,14,20,9,0,8,25,9,9,11,10,7,7,10,23,5},
					{0,0,6,5,6,12,6,11,18,24,6,4,0,27,7,6,10,12,7,11,14,25,0},
					{31,31,27,27,27,26,30,25,33,38,31,26,31,0,32,31,32,25,29,26,29,40,31},
					{5,5,3,2,5,11,5,10,17,22,6,3,5,25,0,6,8,11,4,10,13,24,5},
					{4,4,3,3,5,12,3,13,17,20,2,7,3,26,3,0,6,14,3,13,16,22,4},
					{8,8,7,5,9,11,7,15,19,21,6,9,7,30,7,5,0,16,5,15,18,23,7},
					{15,15,13,13,13,20,8,4,12,24,16,12,15,29,16,15,18,0,14,5,9,26,15},
					{6,6,3,2,5,9,6,12,19,22,5,6,6,26,6,4,6,12,0,12,15,24,6},
					{16,16,16,16,18,23,15,14,7,14,16,12,15,34,16,14,17,17,17,0,10,16,15},
					{16,16,14,14,16,22,13,6,7,20,16,12,15,31,17,16,19,9,16,6,0,23,15},
					{24,24,24,24,26,32,23,25,19,6,23,21,23,42,24,21,23,26,24,16,23,0,24},
					{0,0,5,4,5,10,5,10,17,20,5,3,4,26,6,5,9,11,6,10,12,23,0}
					};
	float C[23][23]={{0,0,1.6,2,2,4.4,2.6,5.7,9,10.2,1.4,1.1,1.1,12.6,1.6,2.5,4.3,5.3,2.8,6.4,8.3,12,0},
					{0,0,1.5,2,1.9,4.4,2.6,5.6,9,10.2,1.3,1.1,1.1,12.5,1.6,2.5,4.2,5.3,2.8,6.4,8.2,12,0},
					{1.3,1.3,0,0.2,1.4,3.6,1.2,6.1,11.1,9.4,1,1.4,1.2,12.2,1.2,0.8,2.6,5.8,1,6.9,8.7,11.2,1.2},
					{12.4,2.4,0.5,1.4,3.6,2.3,6.4,11.3,13.1,1.8,2.7,2.3,12.2,2,1.6,2.4,6.1,0.9,7.2,9.2,13.6,2.3},
					{3,3,1.7,3.4,0,2.4,2.9,6.1,11,13.7,2.8,3.3,2.9,11.7,3,2.7,4,5.7,2.9,6.8,8.7,14.3,3},
					{5.4,5.4,4.6,9.1,8.1,0,18.1,22.1,13.7,15,5.1,5.4,5.3,11.9,5.3,5,4.8,8.8,3.7,8.9,10.9,17,5.4},
					{3.2,3.2,2.7,3.2,2.8,4.9,0,3.4,8.3,11.8,3.8,3,3.1,12.1,4,3.6,5.4,3,3.9,4.1,6,13.6,3.1},
					{6.4,6.5,6,6.4,6.1,8.2,3.5,0,5.1,10.6,7.1,4.8,6.3,14,7.3,6.9,8.7,1.1,7.2,0.8,2.8,12.4,6.4},
					{10.8,10.2,10.3,10.8,11.6,13.8,8.5,5.1,0,8.5,11.4,9,10.7,21.5,11.6,10.5,11.5,5.8,11.6,4.7,3,10.3,10.1},
					{9.6,9.6,10.3,10.8,11.7,13.8,11.1,10,8.5,0,9.8,9.3,9.5,23.1,10,9,9.7,12.4,10.1,10.3,9.1,2.5,9.5},
					{1.5,1.5,0.8,1.3,2.1,4.2,2.7,6.1,10.6,11.1,0,1.6,1.4,13.1,0.2,1.7,3.5,5.8,2,5.9,7.9,13.1,1.5},
					{2.7,2.7,2.2,2.7,3.5,5.6,2.4,4.5,8.5,10,2.9,0,2.6,17,3.1,4,4.9,5.2,3.5,3.9,5.8,11.9,2.6},
					{0,0,1.7,2.2,2.1,4.2,2.7,5.7,9.8,10,1.5,1.2,0,12.8,1.7,1.8,3.6,5.4,2.9,5.1,7,11.2,0},
					{12.7,12.7,11.5,12,10.9,11.8,12.5,15.5,21.3,23.1,14,16.6,12.6,0,14.2,14.4,14,15.2,12.9,16.6,18.6,25,12.6},
					{5,1.3,0.6,1,1.9,4,1.2,5.9,10.3,9.3,1.5,1.2,1.2,12.6,0,1.8,3.3,5.6,1.8,5.7,7.6,11.2,1.2},
					{1,1,0.6,1.1,2,4.2,0.8,7.2,9.4,9.1,0.7,3.5,0.9,12.8,0.9,0,2.3,6.8,1,7,8.9,10.9,0.9},
					{2.6,2.6,2.8,2.2,3.7,4.7,2.5,8.7,11.1,9.3,2.5,4.3,2.6,14.4,2.7,2,0,8.3,2,8.7,10.4,11.1,2.6},
					{6.1,6.1,5.6,6.1,5.7,8,3.2,1.1,5.8,12.3,6.3,5.5,6,3.6,6.5,6.6,8.3,0,6.9,1.6,3.5,14.1,6},
					{2,2,1.2,0.6,2.1,3.6,1.9,7.1,11.5,10.1,1.7,3.4,1.9,12.8,1.9,1.5,2.3,6.7,0,6.9,8.8,11.9,1.9},
					{7,7,7.7,8.2,9,11.3,7.8,5.9,3.6,4.4,7.6,6.1,6.9,20.9,7.8,7.5,80.5,6.6,9,0,4.1,7.9,6.9},
					{7.5,7.5,7.7,8.1,8.9,11.2,6.8,2.9,3,9.1,7.7,6.3,7.4,20,7.9,8.5,9.6,3.6,8.9,2.5,0,10.9,7.5},
					{11.3,11.3,11.7,12,12.7,14.9,12.9,13.9,10.3,2.5,11.2,11.2,11.2,26,11.4,10.9,11.6,14.3,11.9,7.9,10.9,0,11.2},
					{0,0,1.5,2,1.9,4.2,2.6,5.6,9.6,9.2,1.3,1.1,1.1,12.7,1.6,1.7,3.4,5.3,2.8,5,6.9,11,0}
					};
	for(int i=0;i<23;i++){
		for(int j=0;j<23;j++){
			LlenarDestinos(ListaDestino,A1[i],A2[j],B[i][j],C[i][j]);
		}
	}
}
void MostrarDestino(DestI ListaDestino){
	if(ListaDestino!=NULL) {
		cout<<ListaDestino->Inicio<<" -- "<<ListaDestino->tiempo<<"minutos "<<" -- "<<ListaDestino->Km<<"KM -- "<<ListaDestino->Final<<endl;
		MostrarDestino(ListaDestino->sig);
	}
}

RutaI CrearRuta(string lugar,int tiempo, int precio) {
	RutaI nuevoRuta = new(struct Ruta);
	nuevoRuta->Lugar = lugar;
	nuevoRuta->tiempo = tiempo;
	nuevoRuta->precio = precio;
	nuevoRuta->sig=NULL;
	return nuevoRuta;
}
void InsertarRuta(RutaI &ListaRuta, LugarI &ListaTuristica, int a){
	if(a==0) {
		if(ListaRuta==NULL) {
			ListaRuta=CrearRuta(ListaTuristica->name,ListaTuristica->tiempo,ListaTuristica->precio);
		}
		else{
			InsertarRuta(ListaRuta->sig,ListaTuristica,a);
		}
	}
	else {
		InsertarRuta(ListaRuta,ListaTuristica->sig,(a-1));
	}
}
void InsertarenRuta(RutaI &ListaRuta,string lugar,int tiempo, int precio){
	if(ListaRuta==NULL){
		ListaRuta=CrearRuta(lugar,tiempo,precio);
	}
	else {
		InsertarenRuta(ListaRuta->sig,lugar,tiempo,precio);
	}
}
void MostrarRuta(RutaI ListaRuta) {
	if(ListaRuta!=NULL) {
		cout<<ListaRuta->Lugar<<" -- "<<ListaRuta->tiempo<<"minutos "<<" -- S/."<<ListaRuta->precio<<endl;
		MostrarRuta(ListaRuta->sig);
	}
}

MiniI CrearMinimal(string Lugar,int tiempo, int precio) {
	MiniI nuevoMini = new(struct Minimal);
	nuevoMini->lugar = Lugar;
	nuevoMini->tiempo = tiempo;
	nuevoMini->precio = precio;
	nuevoMini->sig=NULL;
	return nuevoMini;
}
void InsertarMinimal(MiniI &ListaMinimal,string lugar, int tiempo, int precio){
	if(ListaMinimal==NULL){
		ListaMinimal=CrearMinimal(lugar,tiempo,precio);
	}
	else{
		InsertarMinimal(ListaMinimal->sig,lugar,tiempo,precio);
	}
}
void MostrarMinimal(MiniI ListaMinimal){
	if(ListaMinimal!=NULL){
		cout<<ListaMinimal->lugar<<" -- "<<ListaMinimal->tiempo<<" minutos "<<" -- S/."<<ListaMinimal->precio<<endl;
		MostrarMinimal(ListaMinimal->sig);
	}
}

void EliminarUltimo(MiniI lista,MiniI &nuevo){
	string s="Basílica Catedral de Arequipa";
	if(lista->lugar==s){
		lista=NULL;
	}
	else{
		InsertarMinimal(nuevo,lista->lugar,lista->tiempo,lista->precio);
		EliminarUltimo(lista->sig,nuevo);
	}
}

int ContarRuta(RutaI ListaRuta, int contador) {
	if(ListaRuta==NULL){
		return contador;
	}
	else {
		contador++;
		ContarRuta(ListaRuta->sig,contador);
	}

}
FRV Arbol_Minimal(RutaI &ListaRuta, DestI &ListaDestinos){
	ListaI Lista=NULL;
	string str="";
	string straux;
   	MiniI ListaMinimal=NULL;
	RutaI ListaRuta6=ListaRuta;
	RutaI ListaRutaAux;
	RutaI ListaRutaAux2;
	DestI ListaDestinosAux;
	int cantidad=0;
	int src=0;
	string Data;
	stringstream ss;
	int datoG;
	ListaDestinosAux=ListaDestinos;
	ListaRutaAux2=ListaRuta;
	ListaRutaAux=ListaRuta;
	cantidad=ContarRuta(ListaRuta,cantidad);
	int b=cantidad-2;
	int c=b;
	int graph[cantidad][cantidad];
	for (int i=0; i<cantidad; i++) {
		for (int j=0; j<cantidad; j++) {
			while(true) {
				string lugarA=ListaRutaAux->Lugar;
				string lugarB=ListaRutaAux2->Lugar;
				string A=ListaDestinosAux->Inicio;
				string B=ListaDestinosAux->Final;
				if(lugarA==A) {
					if(lugarB==B) {
						datoG = ListaDestinosAux->tiempo;
						break;
					}
					else {
						ListaDestinosAux=ListaDestinosAux->sig;
					}
				}
				else {
					ListaDestinosAux=ListaDestinosAux->sig;
				}
			}
			graph[i][j] = datoG;
			ListaRutaAux2=ListaRutaAux2->sig;
			ListaDestinosAux=ListaDestinos;
		}
		ListaRutaAux=ListaRutaAux->sig;
		ListaRutaAux2=ListaRuta;
		ListaDestinosAux=ListaDestinos;
	}
	float graphkm[cantidad][cantidad];
	float DtoKm;
	DestI ListaDestinosAux10=ListaDestinos;
	RutaI ListaRutaAux20=ListaRuta;
	RutaI ListaRutaAux30=ListaRuta;
	for (int i=0; i<cantidad; i++) {
		for (int j=0; j<cantidad; j++) {
			while(true) {
				string lugarA=ListaRutaAux30->Lugar;
				string lugarB=ListaRutaAux20->Lugar;
				string A=ListaDestinosAux10->Inicio;
				string B=ListaDestinosAux10->Final;
				if(lugarA==A) {
					if(lugarB==B) {
						DtoKm = ListaDestinosAux10->Km;
						break;
					}
					else {
						ListaDestinosAux10=ListaDestinosAux10->sig;
					}
				}
				else {
					ListaDestinosAux10=ListaDestinosAux10->sig;
				}
			}
			graphkm[i][j] = DtoKm;
			ListaRutaAux20=ListaRutaAux20->sig;
			ListaDestinosAux10=ListaDestinos;
		}
		ListaRutaAux30=ListaRutaAux30->sig;
		ListaRutaAux20=ListaRuta;
		ListaDestinosAux10=ListaDestinos;
	}
	/*for (int i=0; i<cantidad; i++) {
		ListaRuta=ListaRutaAux;
		for (int j=0; j<cantidad; j++) {
			cout <<graph[i][j] << " ";
		}
		cout << endl;
	}//Imprime grafo de tiempo*/
	while(b!=0){
		straux = to_string(b);
		str.append(straux);
		b--;
	}
	int n = str.size();
   	permute(str, 0, n-1,Lista,c);
	ListaI ListaAux =Lista;
	TiempoI Tiempos=NULL;
	string Ruta;
	char R1,R2;
	int Ai;
	int Bi;
	int inicial=0;
	int aristaaas=1;
	for(int i=1;i<=(cantidad-2);i++) {
		aristaaas=aristaaas*i;
	}
	for(int inicial=0;inicial<aristaaas;inicial++) {
		int tiemmmm=0;
		if(Lista==NULL){
			break;
		}
		else {
			Ruta=ListaAux->name;
			for(int i=0;i<(cantidad-1);i++) {
				R1=Ruta[i];
				R2=Ruta[i+1];
				Ai=R1 - 48;
				Bi=R2 - 48;
				tiemmmm=tiemmmm+graph[Ai][Bi];
			}
			LlenarTempo(Tiempos,tiemmmm);

			ListaAux=ListaAux->next;
		}
	}
	int Minimo=9999;
	int alf=1,bos=1;
	TiempoI tiemposAUX=Tiempos;
    while(true){
        if(tiemposAUX!=NULL) {
            if(tiemposAUX->timme < Minimo) {
                Minimo=tiemposAUX->timme;
            }
            tiemposAUX=tiemposAUX->next;
        }
        else {
            break;
        }
    }
	alf=Posicion(Tiempos,Minimo,alf);
	ListaI ListaAux5=Lista;
	string Finalizacion;
	for(int i=0;i<aristaaas; i++) {
		if(bos==alf){
			Finalizacion=ListaAux5->name;
			break;
		}
		else{
			bos++;
			ListaAux5=ListaAux5->next;
		}
	}
	int Cant=Finalizacion.size();
	char ejem;
	int Rutilla[Cant];
	for(int i=0;i<Cant; i++) {
		ejem=Finalizacion[i];
		Rutilla[i]=ejem - 48;
	}
	RutaI ListaRutaAux8=ListaRuta6;
	string LugarMini;
	int tiempoMini;
	int precioMini;
	int jko;
	for(int i=0;i<Cant;i++) {
		jko=Rutilla[i];
		ListaRuta6=ListaRutaAux8;
		while(jko>=0){
			if(jko==0){
				LugarMini=ListaRuta6->Lugar;
				tiempoMini=ListaRuta6->tiempo;
				precioMini=ListaRuta6->precio;
				break;

			}
			else {
				ListaRuta6=ListaRuta6->sig;
				jko--;
			}
		}
		InsertarMinimal(ListaMinimal,LugarMini,tiempoMini,precioMini);
	}

	AARI ListaAristas=NULL;
	for(int i=0;i<(Cant-1);i++) {
		int lolo=Rutilla[i];
		int lala=Rutilla[i+1];
		float KMI=graphkm[lolo][lala];
		int tempoAr=graph[lolo][lala];

		LlenarAARI(ListaAristas,tempoAr,KMI);
	}
	cout<<"-------------------------------------------"<<endl;
	//MostrarMinimal(ListaMinimal);
	//MostrarAARI(ListaAristas);

	//Ruta sin Restaurante
	int ContadorLugares=0;
	MiniI AuxCont=ListaMinimal;
	while(true) {
		if(AuxCont==NULL) {
			break;
		}
		else {
			ContadorLugares++;
			AuxCont=AuxCont->sig;
		}
	}
	MiniI AuxComer=ListaMinimal;
	AARI AuxComerRuta=ListaAristas;
	int ContadorViajes=ContadorLugares-1;
	int tiemposTotal=ContadorViajes+ContadorLugares;
	int ContadorLugartoComer=0;
	int ContadorTiempoparaComer=0;
	RF ListaRF=NULL;
	VF ListaVF=NULL;
	for(int i=0;i<tiemposTotal;i++) {
		div_t Par=div(i,2);
		if(Par.rem>0) {
			ContadorTiempoparaComer=ContadorTiempoparaComer+AuxComerRuta->time;
			if(ContadorTiempoparaComer>270) {
				i=tiemposTotal;
			}
			else {
				LlenarVF(ListaVF,AuxComerRuta->time,AuxComerRuta->km);
				AuxComerRuta=AuxComerRuta->sig;
			}
		}
		else {
			ContadorTiempoparaComer=ContadorTiempoparaComer+AuxComer->tiempo;
			ContadorLugartoComer++;
			InsertarRF(ListaRF,AuxComer->lugar,AuxComer->tiempo,AuxComer->precio);
			AuxComer=AuxComer->sig;
			if(ContadorTiempoparaComer>270) {
				i=tiemposTotal;
			}
		}
	}
	FRV ListaFusion=NULL;
	int rayquaza=9907;
	while(rayquaza!=0) {
            if(ContadorTiempoparaComer>270) {
                    if(AuxComer->sig!=NULL) {
                            MiniI LRestantes=NULL;
                            //MostrarRF(ListaRF);
                            //MostrarVF(ListaVF);
                            MiniI LRestantesF=NULL;
                            LRestantesF=AuxComer;
                            MiniI LRestantesFAUX=NULL;
                            LRestantesFAUX=AuxComer;
                            EliminarUltimo(AuxComer,LRestantes);
                            //MostrarMinimal(LRestantes);
                            RL ListaRL=NULL;
                            InsertarRL(ListaRL);
                            LR ListaLR=NULL;
                            InsertarLR(ListaLR);
                            RF Ultimo=ListaRF;
                            int agumon=10;
                            while(agumon!=0) {
                                if(Ultimo->sig==NULL) {
                                    agumon=0;
                                }
                                else {
                                    Ultimo=Ultimo->sig;
                                }
                            }
                            int abc=0;
                            LR ListaLRAux=ListaLR;
                            int matrizLR[12];
                            for (int i=0; i<23; i++) {
                                for (int i=0; i<12; i++) {
                                    string lugarA=ListaLRAux->Inicio;
                                    string A=Ultimo->place;
                                    if(lugarA==A) {
                                        matrizLR[abc] = ListaLRAux-> tiempo;
                                        abc++;
                                    }
                                    ListaLRAux=ListaLRAux->sig;
                                }
                            }
                            int men=matrizLR[0];
                            for(int i=0;i<12;i++){
                                if(men>matrizLR[i]){
                                    men=matrizLR[i];
                                }
                            }
                            LR ListaLRAux2=ListaLR;
                            for (int i=0; i<23; i++) {
                                for (int i=0; i<12; i++) {
                                    string lugarA=ListaLRAux2->Inicio;
                                    string A=Ultimo->place;
                                    if(lugarA==A) {
                                        if(men==ListaLRAux2-> tiempo) {
                                            LlenarVF(ListaVF,ListaLRAux2->tiempo,ListaLRAux2->km);
                                            InsertarRF(ListaRF,ListaLRAux2->final,60,50);
                                        }
                                    }
                                    ListaLRAux2=ListaLRAux2->sig;
                                }
                            }
                            //MostrarRF(ListaRF);
                            //MostrarVF(ListaVF);
                            int ContRestantes=0;
                            MiniI LAUXRestantes=LRestantes;
                            int pqeu=10;
                            while(pqeu!=0) {
                                if(LAUXRestantes==NULL) {
                                    pqeu=0;
                                }
                                else {
                                    ContRestantes++;
                                    LAUXRestantes=LAUXRestantes->sig;
                                }
                            }
                            ListaI Lista2=NULL;
                            int bio=ContRestantes;
                            string str2="";
                            string straux2;
                            while(bio!=0){
                                straux2 = to_string(bio);
                                str2.append(straux2);
                                bio--;
                            }
                            int nio = str2.size();
                            permute(str2, 0, nio-1,Lista2,ContRestantes);
                            //MostrarLista(Lista2);
                            ListaI ListaAux9 =Lista2;
                            TiempoI TiemposR=NULL;
                            int permutaciones=1;
                            for(int i=1;i<=ContRestantes;i++) {
                                permutaciones=permutaciones*i;
                            }
                            RF UltR=ListaRF;
                            int yugioh=10;
                            while(yugioh!=0) {
                                if(UltR->sig==NULL) {
                                    yugioh=0;
                                }
                                else{
                                    UltR=UltR->sig;
                                }
                            }
                            RutaI TramoF=NULL;
                            for (int i=0;i < (ContRestantes+2);i++) {
                                if(i==0) {
                                    InsertarenRuta(TramoF,UltR->place,UltR->tiempo,UltR->precio);
                                }
                                else {
                                    InsertarenRuta(TramoF,LRestantesFAUX->lugar,LRestantesFAUX->tiempo,LRestantesFAUX->precio);
                                    LRestantesFAUX=LRestantesFAUX->sig;
                                }
                            }
                            int RLDATA;
                            int contadora=0;
                            RL ListaRLAux=ListaRL;
                            DestI ListaDestinosAux90=ListaDestinos;
                            RutaI ListaRutaAux29=TramoF;
                            RutaI ListaRutaAux39=TramoF;
                            int MatrizRL[ContRestantes+2][ContRestantes+2];
                            for (int i=0; i<(ContRestantes+2); i++) {
                                for (int j=0; j<(ContRestantes+2); j++) {
                                    if(contadora==0) {
                                        while(true) {
                                            if(j==0) {
                                                    RLDATA = 60;
                                                    break;
                                                }
                                            else{
                                                string lugarA=ListaRutaAux39->Lugar;
                                                string lugarB=ListaRutaAux29->Lugar;
                                                string A=ListaRLAux->Inicio;
                                                string B=ListaRLAux->final;
                                                if(lugarA==A) {
                                                    if(lugarB==B) {
                                                        RLDATA = ListaRLAux->tiempo;
                                                        break;
                                                    }
                                                    else {
                                                        ListaRLAux=ListaRLAux->sig;
                                                    }
                                                }
                                                else {
                                                    ListaRLAux=ListaRLAux->sig;
                                                }
                                            }
                                        }
                                        MatrizRL[i][j] = RLDATA;
                                        ListaRutaAux29=ListaRutaAux29->sig;
                                        ListaRLAux=ListaRL;
                                        }
                                    else {
                                        while(true) {
                                                if(j==0) {
                                                    RLDATA = 60;
                                                    break;
                                                }
                                                else {
                                                    string lugarA=ListaRutaAux39->Lugar;
                                                    string lugarB=ListaRutaAux29->Lugar;
                                                    string A=ListaDestinosAux90->Inicio;
                                                    string B=ListaDestinosAux90->Final;
                                                    if(lugarA==A) {
                                                        if(lugarB==B) {
                                                            RLDATA = ListaDestinosAux90->tiempo;
                                                            break;
                                                        }
                                                        else {
                                                            ListaDestinosAux90=ListaDestinosAux90->sig;
                                                        }
                                                    }
                                                    else {
                                                        ListaDestinosAux90=ListaDestinosAux90->sig;
                                                    }
                                                }
                                            }
                                        MatrizRL[i][j] = RLDATA;
                                        ListaRutaAux29=ListaRutaAux29->sig;
                                        ListaDestinosAux90=ListaDestinos;
                                    }

                                }
                                contadora++;
                                ListaRutaAux39=ListaRutaAux39->sig;
                                ListaRutaAux29=TramoF;
                                ListaDestinosAux90=ListaDestinos;
                            }
                            /*for (int i=0; i<(ContRestantes+2); i++) {
                                for (int j=0; j<(ContRestantes+2); j++) {
                                    cout <<MatrizRL[i][j] << " ";
                                }
                                cout << endl;
                            }*/
                            float MatrizRLKM[ContRestantes+2][ContRestantes+2];
                            float RLDATAKM;
                            int contadorakm=0;
                            RL ListaRLAuxkm=ListaRL;
                            DestI ListaDestinosRL=ListaDestinos;
                            RutaI ListaRutaAuxRL2=TramoF;
                            RutaI ListaRutaAuxRL3=TramoF;
                            for (int i=0; i<(ContRestantes+2); i++) {
                                for (int j=0; j<(ContRestantes+2); j++) {
                                    if(contadorakm==0) {
                                            int jugar=10;
                                        while(jugar!=0) {
                                            if(j==0) {
                                                    RLDATAKM = 60;
                                                    jugar=0;
                                                }
                                            else{
                                                string lugarA=ListaRutaAuxRL3->Lugar;
                                                string lugarB=ListaRutaAuxRL2->Lugar;
                                                string A=ListaRLAuxkm->Inicio;
                                                string B=ListaRLAuxkm->final;
                                                if(lugarA==A) {
                                                    if(lugarB==B) {
                                                        RLDATAKM = ListaRLAuxkm->km;
                                                        jugar=0;
                                                    }
                                                    else {
                                                        ListaRLAuxkm=ListaRLAuxkm->sig;
                                                    }
                                                }
                                                else {
                                                    ListaRLAuxkm=ListaRLAuxkm->sig;
                                                }
                                            }
                                        }
                                        MatrizRLKM[i][j] = RLDATAKM;
                                        ListaRutaAuxRL2=ListaRutaAuxRL2->sig;
                                        ListaRLAuxkm=ListaRL;
                                        }
                                    else {
                                        int kollu=10;
                                        while(kollu!=0) {
                                                if(j==0) {
                                                    RLDATAKM = 60;
                                                    kollu=0;
                                                }
                                                else {
                                                    string lugarA=ListaRutaAuxRL3->Lugar;
                                                    string lugarB=ListaRutaAuxRL2->Lugar;
                                                    string A=ListaDestinosRL->Inicio;
                                                    string B=ListaDestinosRL->Final;
                                                    if(lugarA==A) {
                                                        if(lugarB==B) {
                                                            RLDATAKM = ListaDestinosRL->Km;
                                                            kollu=0;
                                                        }
                                                        else {
                                                            ListaDestinosRL=ListaDestinosRL->sig;
                                                        }
                                                    }
                                                    else {
                                                        ListaDestinosRL=ListaDestinosRL->sig;
                                                    }
                                                }
                                            }
                                        MatrizRLKM[i][j] = RLDATAKM;
                                        ListaRutaAuxRL2=ListaRutaAuxRL2->sig;
                                        ListaDestinosRL=ListaDestinos;
                                    }

                                }
                                contadorakm++;
                                ListaRutaAuxRL3=ListaRutaAuxRL3->sig;
                                ListaRutaAuxRL2=TramoF;
                                ListaDestinosRL=ListaDestinos;
                            }
                            /*for (int i=0; i<(ContRestantes+2); i++) {
                                for (int j=0; j<(ContRestantes+2); j++) {
                                    cout <<MatrizRLKM[i][j] << " ";
                                }
                                cout << endl;
                            }*/
                            char R8,R7;
                            int AiU;
                            int BiU;
                            for(int inicial=0;inicial<permutaciones;inicial++) {
                                int tiemo=0;
                                if(Lista2==NULL){
                                    inicial=permutaciones;
                                }
                                else {
                                    Ruta=ListaAux9->name;
                                    for(int i=0;i<(ContRestantes+1);i++) {
                                        R7=Ruta[i];
                                        R8=Ruta[i+1];

                                        AiU=R7 - 48;
                                        BiU=R8 - 48;

                                        tiemo=tiemo+MatrizRL[AiU][BiU];
                                    }
                                    LlenarTempo(TiemposR,tiemo);
                                    ListaAux9=ListaAux9->next;
                                }
                            }
                            //MostrarTempo(TiemposR);
                            int Minimo2=9999;
                            int alf2=1,bos2=1;
                            TiempoI TiemposRAUX=TiemposR;
                            int abue=10;
                            while(abue!=0){
                                if(TiemposRAUX!=NULL) {
                                    if(TiemposRAUX->timme < Minimo2) {
                                        Minimo2=TiemposRAUX->timme;
                                    }
                                    TiemposRAUX=TiemposRAUX->next;
                                }
                                else {
                                    abue=10;
                                }
                            }
                            alf2=Posicion(TiemposR,Minimo2,alf2);
                            ListaI ListaAux68=Lista2;
                            string Finalizacion2;
                            for(int i=0;i<permutaciones; i++) {
                                if(bos2==alf2){
                                    Finalizacion2=ListaAux68->name;
                                    i=permutaciones;
                                }
                                else{
                                    bos2++;
                                    ListaAux68=ListaAux68->next;
                                }
                            }
                            int Cant2=Finalizacion2.size();
                            char ejem4;
                            int RutillaF[Cant2];
                            for(int i=0;i<Cant2; i++) {
                                ejem4=Finalizacion2[i];
                                RutillaF[i]=ejem4 - 48;
                            }
                            MiniI RestoF=NULL;
                            RutaI ListaF6=TramoF;
                            RutaI ListaF8=ListaF6;
                            string LugarMiniF;
                            int tiempoMiniF;
                            int precioMiniF;
                            int jkoF=0;
                            for(int i=0;i<Cant2;i++) {
                                jkoF=RutillaF[i];
                                ListaF6=ListaF8;
                                while(jkoF>=0){
                                    if(jkoF==0){
                                        LugarMiniF=ListaF6->Lugar;
                                        tiempoMiniF=ListaF6->tiempo;
                                        precioMiniF=ListaF6->precio;
                                        jkoF=-1;

                                    }
                                    else {
                                        ListaF6=ListaF6->sig;
                                        jkoF--;
                                    }
                                }
                                InsertarMinimal(RestoF,LugarMiniF,tiempoMiniF,precioMiniF);
                            }
                            AARI ListaAristasF=NULL;
                            for(int i=0;i<(Cant2-1);i++) {
                                int lolo=RutillaF[i];
                                int lala=RutillaF[i+1];
                                float KMI=MatrizRLKM[lolo][lala];
                                int tempoAr=MatrizRL[lolo][lala];

                                LlenarAARI(ListaAristasF,tempoAr,KMI);
                            }
                            RF RUTAFINALM=NULL;
                            for(int i=0;i<((cantidad+1)-Cant2);i++) {
                                InsertarRF(RUTAFINALM,ListaRF->place,ListaRF->tiempo,ListaRF->precio);
                                ListaRF=ListaRF->sig;
                            }
                            for(int i=0;i<Cant2;i++) {
                                InsertarRF(RUTAFINALM,RestoF->lugar,RestoF->tiempo,RestoF->precio);
                                RestoF=RestoF->sig;
                            }
                            VF VAIJEFINALM=NULL;
                            for(int i=0;i<((cantidad)-Cant2);i++) {
                                LlenarVF(VAIJEFINALM,ListaVF->tiempo,ListaVF->km);
                                ListaVF=ListaVF->sig;
                            }
                            for(int i=0;i<(Cant2-1);i++) {
                                LlenarVF(VAIJEFINALM,ListaAristasF->time,ListaAristasF->km);
                                ListaAristasF=ListaAristasF->sig;
                            }
                            int contadoras=0;
                            int jugo=100;
                            while(jugo!=0){
                                if(contadoras==0){
                                        if(RUTAFINALM==NULL){
                                            jugo=0;
                                        }
                                        else{
                                            string lugark=RUTAFINALM->place;
                                            int tiempok=RUTAFINALM->tiempo;
                                            int preciok=RUTAFINALM->precio;
                                            int tiempob=0;
                                            float kmb=0;
                                            InsertarFusion(ListaFusion,lugark,tiempok,tiempob,preciok,kmb);
                                            RUTAFINALM=RUTAFINALM->sig;
                                            contadoras=1;
                                        }
                                }
                                else{
                                        if(VAIJEFINALM==NULL){
                                            jugo=0;
                                        }
                                        else{
                                            string lugark="vacio";
                                            int tiempok=0;
                                            int preciok=0;
                                            int tiempob=VAIJEFINALM->tiempo;
                                            float kmb=VAIJEFINALM->km;
                                            InsertarFusion(ListaFusion,lugark,tiempok,tiempob,preciok,kmb);
                                            VAIJEFINALM=VAIJEFINALM->sig;
                                            contadoras=0;
                                        }
                                }

                            }
                            rayquaza=0;
                            }

                    else{
                ContadorTiempoparaComer=250;

            }
            }
            else {

                //MostrarMinimal(ListaMinimal);
                RF RUTAFINALM=NULL;
                int usao=10;
                while(usao!=0) {
                    if(ListaMinimal==NULL) {
                        usao=0;
                    }
                    else {
                        InsertarRF(RUTAFINALM,ListaMinimal->lugar,ListaMinimal->tiempo,ListaMinimal->precio);
                        ListaMinimal=ListaMinimal->sig;
                    }
                }
                VF VAIJEFINALM=NULL;
                int guhio=10;
                while(guhio!=0) {
                    if(ListaAristas==NULL) {
                        guhio=0;
                    }
                    else {
                        LlenarVF(VAIJEFINALM,ListaAristas->time,ListaAristas->km);
                        ListaAristas=ListaAristas->sig;
                    }
                }

                MostrarRF(RUTAFINALM);
                //MostrarVF(VAIJEFINALM);

                int contadoras=0;
                int gusion=10;
                while(gusion!=0){
                    if(contadoras==0){
                            if(RUTAFINALM==NULL){
                                gusion=0;
                            }
                            else{
                                string lugark=RUTAFINALM->place;
                                int tiempok=RUTAFINALM->tiempo;
                                int preciok=RUTAFINALM->precio;
                                int tiempob=0;
                                float kmb=0;
                                InsertarFusion(ListaFusion,lugark,tiempok,tiempob,preciok,kmb);
                                RUTAFINALM=RUTAFINALM->sig;
                                contadoras=1;
                            }
                    }
                    else{
                            if(VAIJEFINALM==NULL){
                                gusion=0;
                            }
                            else{
                                string lugark="vacio";
                                int tiempok=0;
                                int preciok=0;
                                int tiempob=VAIJEFINALM->tiempo;
                                float kmb=VAIJEFINALM->km;
                                InsertarFusion(ListaFusion,lugark,tiempok,tiempob,preciok,kmb);
                                VAIJEFINALM=VAIJEFINALM->sig;
                                contadoras=0;
                            }
                    }

                }
                // MostrarFusion(ListaFusion);
                rayquaza=0;
            }
	}
	return ListaFusion;

}
bool todosiguales(vector<int>v,int n,int e){
  	for(int i=0;i<n;i++){
    	if(v[i]==e){
    		return  true;
		}
	}
    return false;
}

FRV menuPrincipal(){
	int DestinosA,TamanoV;
	int contu=0;
	vector<int> DestinosB;
	string paquete;
	LugarI ListaTuristica=NULL;
	DestI ListaDestinos=NULL;
	RutaI ListaRuta=NULL;
	InsertarDestino(ListaDestinos);
	InsertarLugar(ListaTuristica);
	cout << "********************************Hola, Bienvenido a TheShyni Tour********************************" <<	endl;
	cout << "Somos una empresa dedicada a la guia de diferentes lugares turisticos de Arequipa. Esperamos que lo disfrute." <<endl;
	cout<<"Le mostramos todos los posibles lugares que usted puede visitar: "<<endl;
	cout<<" "<<endl;
	cout<<"Le presentamos nuestros paquetes: \n\t1. Paquete Inicial: \n\t\tIncluye  la parada inicial \"Plaza de Armas\" y como parada final \"Basilica Catedral de Arequipa\"\n\t\tUsted podra escojer 3 lugares adicionales de la lista ofrecida.\"\n\t\t(S./35 + el precio de cada lugar adicionado e Incluye Almuerzo en un Restaurante + Guia Turistica)"<<endl;
	cout<<"\n\t2. Paquete Personalizado: \n\t\tIncluye  la parada inicial \"Plaza de Armas\" y como parada final \"Basilica Catedral de Arequipa\"\n\t\tUsted podra escojer mas de 3 hasta 7 lugares adicionales de la lista ofrecida considerando el tiempo.\n\t\t(S./35 + el precio de cada lugar adicionado e Incluye Almuerzo en un Restaurante + Guia Turistica)"<<endl;
	cout<<"--------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Indique el paquete que desea adquirir: (1/2) ";
	cin>>paquete;
	if(paquete=="1") {
		cout<<"Usted ha elegido el Paquete Inicial."<<endl;
		MostrarLugares(ListaTuristica,contu);
		for(int i=0;i<5;i++) {
			if (i==0) {
				DestinosA=0;
				DestinosB.push_back(DestinosA);
				InsertarRuta(ListaRuta,ListaTuristica,DestinosA);
			}
			else if(i==4){
				DestinosA=22;
				DestinosB.push_back(DestinosA);
				InsertarRuta(ListaRuta,ListaTuristica,DestinosA);
			}
			else {
				cout<<"Ingrese el número del lugar a escoger: ";
				cin >>DestinosA;
				if(DestinosA==22){
					cout<<"No puede escoger Basílica Catedral de Arequipa."<<endl;
					i--;
				}
				else if(0<DestinosA && DestinosA<22){
					TamanoV=DestinosB.size();
					if(todosiguales(DestinosB,TamanoV,DestinosA)) {
						cout<<"Valor Repetido." <<endl;
						i--;
					}
					else {
						DestinosB.push_back(DestinosA);
						InsertarRuta(ListaRuta,ListaTuristica,DestinosA);
					}
				}
				else {
					cout<<"Valor Incorrecto" <<endl;
					i--;
				}
			}
		}
		cout<<endl;
		FRV ListaFusion=Arbol_Minimal(ListaRuta,ListaDestinos);
		return ListaFusion;

	}
	else if(paquete=="2") {
		cout<<"Usted ha elegido el Paquete Personalizado."<<endl;
		MostrarLugares(ListaTuristica,contu);
		int Contadoori=0;
		int Contadora=0;
		while(true) {
			if (Contadoori==0) {
				DestinosA=0;
				DestinosB.push_back(DestinosA);
				InsertarRuta(ListaRuta,ListaTuristica,DestinosA);
				Contadoori++;
			}
			else if(Contadora==7) {
				DestinosA=22;
				DestinosB.push_back(DestinosA);
				InsertarRuta(ListaRuta,ListaTuristica,DestinosA);
				break;
			}
			else {
				cout<<"Ingrese el número del lugar a escoger (Si desea culminar ingrese 50): ";
				cin >>DestinosA;
				if(DestinosA==22){
					cout<<"No puede escoger Basílica Catedral de Arequipa."<<endl;
				}
				else if(DestinosA==50){
					DestinosA=22;
					DestinosB.push_back(DestinosA);
					InsertarRuta(ListaRuta,ListaTuristica,DestinosA);
					break;
				}
				else if(0<DestinosA && DestinosA<22){
					TamanoV=DestinosB.size();
					if(todosiguales(DestinosB,TamanoV,DestinosA)) {
						cout<<"Valor Repetido." <<endl;
					}
					else {
						DestinosB.push_back(DestinosA);
						Contadora++;
						InsertarRuta(ListaRuta,ListaTuristica,DestinosA);
					}
				}
				else {
					cout<<"Valor Incorrecto" <<endl;
				}
			}
		}
		cout<<endl;
		FRV ListaFusion=Arbol_Minimal(ListaRuta,ListaDestinos);
		//MostrarFusion(ListaFusion);
		return ListaFusion;
	}
	else{
		cout<<"El valor ingresado es incorrecto. Ingrese 1 o 2."<<endl;
	}
}


void dibujar(RF ListaRF,int a,int b){
                string L00="Plaza de Armas",L01="Museo Santuarios Andinos - MUSA",L02="Monasterio de Santa Catalina",L03="Mundo Alpaca",L04="Mirador de Yanahuara",L05="Mirador de Carmen Alto",L06="Incalpaca";
                string L07="Palacio Goyeneche",L08="Mansion del Fundador",L09="Molino de Sabandia",L010="Casona Tristán del pozo",L011="Casa Museo Mario Vargas Llosa",L012="Templo La Compañía de Jesús Arequipa";
                string L013="Ruta del Sillar",L014="Museo CASA MORAL",L015="Museo de Arte virreinal Santa Teresa",L016="Chapi chico",L017="Mirador de Sachaca",L018="Parque Selva Alegre",L019="Tingo";
                string L020="Mirador Natural de Kasapatac",L021="Plaza de Characato",L022="Basílica Catedral de Arequipa";


                string R01="Restaurant Campestre Los Andenes de Chilina",R02="Chicha de Gastón Acurio",R03="Picanteria Pata'ccala",R04="Restaurant Campestre SONCCO KILLA",R05="El Chopito",R06="Tradición Arequipeña";
                string R07="Restaurant Las Palmeras",R08="Costanera AQP",R09="Místico Restaurante típico campestre",R010="Restaurant Campestre Delf",R011="Restaurante Los Rosales",R012="La Guardiana de Characato";

                if(ListaRF->sig->place==L00){
                        int c=474,d=314+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L01){
                        int c=470,d=321+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L02){
                        int c=479,d=285+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L03){
                        int c=489,d=270+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L04){
                        int c=446,d=240+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L05){
                        int c=478,d=120+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L06){
                        int c=366,d=350+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L07){
                        int c=467,d=322+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L08){
                        int c=347,d=749+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L09){
                        int c=718,d=700+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L010){
                        int c=485,d=307+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L011){
                        int c=452,d=362+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L012){
                        int c=480,d=320+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L013){
                        int c=35,d=51+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L014){
                        int c=471,d=300+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L015){
                        int c=517,d=297+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L016){
                        int c=594,d=261+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L017){
                        int c=285,d=497+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L018){
                        int c=507,d=250+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L019){
                        int c=309,d=530+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L020){
                        int c=325,d=622+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L021){
                        int c=816,d=780+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==L022){
                        int c=478,d=310+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R01){
                        int c=527,d=106+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R02){
                        int c=481,d=296+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R03){
                        int c=453,d=8+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R04){
                        int c=252,d=228+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R05){
                        int c=388,d=552+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R06){
                        int c=544,d=441+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R07){
                        int c=636,d=356+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R08){
                        int c=580,d=281+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R09){
                        int c=817,d=390+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R010){
                        int c=447,d=711+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R011){
                        int c=489,d=206+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
                else if(ListaRF->sig->place==R012){
                        int c=792,d=759+140;
                        for(int i=0;i<1;i++){
                            line(screen,a+i,b+i,c+i,d+i,pallete_color[4]);
                        }
                }
}

int main (){
    setlocale(LC_CTYPE,"Spanish");
    FRV ListaFusion=menuPrincipal();
    RF RutaF=NULL;
    VF ViajeF=NULL;
	//MostrarFusion(ListaFusion);
    int contadoras=0;
    while(true){
        if(contadoras==0){
            if(ListaFusion!=NULL){
                string lugark=ListaFusion->place;
                int tiempok=ListaFusion->tiempoL;
                int preciok=ListaFusion->precio;
                InsertarRF(RutaF,lugark,tiempok,preciok);
                ListaFusion=ListaFusion->sig;
                contadoras=1;}
            else{
                break;
            }
        }
        else{
            if(ListaFusion!=NULL){
                int tiempob=ListaFusion->tiempoV;
                float kmb=ListaFusion->km;
                LlenarVF(ViajeF,tiempob,kmb);
                ListaFusion=ListaFusion->sig;
                contadoras=0;}
            else{
                break;
            }
        }
    }

    //MostrarRF(RutaF);
    //MostrarVF(ViajeF);

    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 1000, 0, 0);
    buffer=create_bitmap(1000,1000);
    mapaAqp=load_bitmap("map.bmp",NULL);
    //Lugares turisticos
    L0=load_bitmap("Plaza_de_Armas.bmp",NULL);
    L1=load_bitmap("Museo_Santuarios_Andinos.bmp",NULL);
    L2=load_bitmap("Monasterio_de_Santa_Catalina.bmp",NULL);
    L3=load_bitmap("Mundo_Alpaca.bmp",NULL);
    L4=load_bitmap("Mirador_de_Yanahuara.bmp",NULL);
    L5=load_bitmap("Mirador_de_Carmen_Alto.bmp",NULL);
    L6=load_bitmap("Incalpaca.bmp",NULL);
    L7=load_bitmap("Palacio_Goyeneche.bmp",NULL);
    L8=load_bitmap("Mansion_del_Fundador.bmp",NULL);
    L9=load_bitmap("Molino_de_Sabandia.bmp",NULL);
    L10=load_bitmap("Casona_Tristan_del_Pozo.bmp",NULL);
    L11=load_bitmap("Casa_Museo_Mario_Vargas_Llosa.bmp",NULL);
    L12=load_bitmap("Templo_la_Compania_de_Jesus.bmp",NULL);
    L13=load_bitmap("Ruta_del_Sillar.bmp",NULL);
    L14=load_bitmap("Museo_CASA_MORAL.bmp",NULL);
    L15=load_bitmap("Museo_de_Arte_Virreinal_Santa_Teresa.bmp",NULL);
    L16=load_bitmap("Chapi_Chico.bmp",NULL);
    L17=load_bitmap("Mirador de Sachaca.bmp",NULL);
    L18=load_bitmap("Parque_Selva_Alegre.bmp",NULL);
    L19=load_bitmap("Tingo.bmp",NULL);
    L20=load_bitmap("Mirador_Natural_de_Kasapatac.bmp",NULL);
    L21=load_bitmap("Plaza_de_Characato.bmp",NULL);
    L22=load_bitmap("Basilica_Catedral_de_Arequipa.bmp",NULL);
    //Restaurantes
    R1=load_bitmap("Restaurante_Campestre_Los_Andenes_de_Chilina.bmp",NULL);
    R2=load_bitmap("Chicha_de_Gaston_Acurio.bmp",NULL);
    R3=load_bitmap("Picanteria_Pataccala.bmp",NULL);
    R4=load_bitmap("Restaurant_Campestre_SONCCO_KILLA.bmp",NULL);
    R5=load_bitmap("El_Chopito.bmp",NULL);
    R6=load_bitmap("Tradicion_Arequipena.bmp",NULL);
    R7=load_bitmap("Restaurant_Las_Palmeras.bmp",NULL);
    R8=load_bitmap("Costanera_AQP.bmp",NULL);
    R9=load_bitmap("Mistico_Restaurante_tipico_campestre.bmp",NULL);
    R10=load_bitmap("Restaurant_Campestre_Delf.bmp",NULL);
    R11=load_bitmap("Restaurante_Los_Rosales.bmp",NULL);
    R12=load_bitmap("La_Guardiana_de_Characato.bmp",NULL);

    banner=load_bitmap("BANNER.bmp",NULL);
    blit(buffer,screen,0,0,0,0,1000,1000);
    blit(mapaAqp,screen,0,0,0,140,1000,860);
    RF ListaRF=RutaF;
    RF Aux=ListaRF;
    int cantidad=0;
    while(true) {
        if(Aux==NULL){
            break;
        }
        else{
            cantidad++;
            Aux=Aux->sig;
        }
    }
    string L00="Plaza de Armas",L01="Museo Santuarios Andinos - MUSA",L02="Monasterio de Santa Catalina",L03="Mundo Alpaca",L04="Mirador de Yanahuara",L05="Mirador de Carmen Alto",L06="Incalpaca";
    string L07="Palacio Goyeneche",L08="Mansion del Fundador",L09="Molino de Sabandia",L010="Casona Tristán del pozo",L011="Casa Museo Mario Vargas Llosa",L012="Templo La Compañía de Jesús Arequipa";
    string L013="Ruta del Sillar",L014="Museo CASA MORAL",L015="Museo de Arte virreinal Santa Teresa",L016="Chapi chico",L017="Mirador de Sachaca",L018="Parque Selva Alegre",L019="Tingo";
    string L020="Mirador Natural de Kasapatac",L021="Plaza de Characato",L022="Basílica Catedral de Arequipa";


    string R01="Restaurant Campestre Los Andenes de Chilina",R02="Chicha de Gastón Acurio",R03="Picanteria Pata'ccala",R04="Restaurant Campestre SONCCO KILLA",R05="El Chopito",R06="Tradición Arequipeña";
    string R07="Restaurant Las Palmeras",R08="Costanera AQP",R09="Místico Restaurante típico campestre",R010="Restaurant Campestre Delf",R011="Restaurante Los Rosales",R012="La Guardiana de Characato";


    int cantidadRF=cantidad;
    int cantidadVF=cantidad-1;
    for(int i=0;i<cantidadRF;i++){
        if(ListaRF->place==L00){
                int a=474,b=314+140;
                blit(L0,screen,0,0,474,314+140,50,25);
                dibujar(ListaRF,a,b);

        }
        else if(ListaRF->place==L01){
                int a=470,b=321+140;
                blit(L1,screen,0,0,470,321+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L02){
            int a=479,b=285+140;
                blit(L2,screen,0,0,479,285+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L03){
                int a=489,b=270+140;
                blit(L3,screen,0,0,489,270+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L04){
            int a=446,b=240+140;
                blit(L4,screen,0,0,446,240+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L05){
                int a=478,b=120+140;
                blit(L5,screen,0,0,478,120+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L06){
                int a=366,b=350+140;
                blit(L6,screen,0,0,366,350+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L07){
                int a=467,b=322+140;
                blit(L7,screen,0,0,467,322+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L08){
                int a=347,b=749+140;
                blit(L8,screen,0,0,347,749+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L09){
                int a=718,b=700+140;
                blit(L9,screen,0,0,718,700+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L010){
                int a=485,b=307+140;
                blit(L10,screen,0,0,485,307+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L011){
                int a=452,b=362+140;
                blit(L11,screen,0,0,452,362+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L012){
                int a=480,b=320+140;
                blit(L12,screen,0,0,480,320+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L013){
                int a=35,b=51+140;
                blit(L13,screen,0,0,35,51+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L014){
                int a=471,b=300+140;
                blit(L14,screen,0,0,471,300+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L015){
                int a=517,b=297+140;
                blit(L15,screen,0,0,517,297+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L016){
                int a=594,b=261+140;
                blit(L16,screen,0,0,594,261+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L017){
                int a=285,b=497+140;
                blit(L17,screen,0,0,285,497+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L018){
                int a=507,b=250+140;
                blit(L18,screen,0,0,507,250+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L019){
                int a=309,b=530+140;
                blit(L19,screen,0,0,309,530+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L020){
                int a=325,b=622+140;
                blit(L20,screen,0,0,325,622+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L021){
                int a=816,b=780+140;
                blit(L21,screen,0,0,816,780+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==L022){
                blit(L22,screen,0,0,478,310+140,50,25);
                break;
        }
        else if(ListaRF->place==R01){
                int a=527,b=106+140;
                blit(R1,screen,0,0,527,106+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R02){
                int a=481,b=296+140;
                blit(R2,screen,0,0,481,296+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R03){
                int a=453,b=8+140;
                blit(R3,screen,0,0,453,8+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R04){
                int a=252,b=228+140;
                blit(R4,screen,0,0,252,228+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R05){
                int a=388,b=552+140;
                blit(R5,screen,0,0,388,552+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R06){
                int a=544,b=441+140;
                blit(R6,screen,0,0,544,441+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R07){
                int a=636,b=356+140;
                blit(R7,screen,0,0,636,356+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R08){
                int a=580,b=281+140;
                blit(R8,screen,0,0,580,281+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R09){
                int a=817,b=390+140;
                blit(R9,screen,0,0,817,390+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R010){
                int a=447,b=711+140;
                blit(R10,screen,0,0,447,711+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R011){
                int a=489,b=206+140;
                blit(R11,screen,0,0,489,206+140,50,25);
                dibujar(ListaRF,a,b);
        }
        else if(ListaRF->place==R012){
                int a=792,b=759+140;
                blit(R12,screen,0,0,792,759+140,50,25);
                dibujar(ListaRF,a,b);
        }
    ListaRF=ListaRF->sig;
    }
    while(!key[KEY_ESC]) {
        blit(banner,screen,0,0,100,10,800,120);
        //al_save_bitmap("guardado.bmp", screen);
        textout(screen, font, "PRESIONE ESC PARA SALIR...", 800,0,palette_color[15]);
    }
    destroy_bitmap(banner);
    destroy_bitmap(mapaAqp);
    destroy_bitmap(buffer);
    destroy_bitmap(L0);
    destroy_bitmap(L1);
    destroy_bitmap(L2);
    destroy_bitmap(L3);
    destroy_bitmap(L4);
    destroy_bitmap(L5);
    destroy_bitmap(L6);
    destroy_bitmap(L7);
    destroy_bitmap(L8);
    destroy_bitmap(L9);
    destroy_bitmap(L10);
    destroy_bitmap(L11);
    destroy_bitmap(L12);
    destroy_bitmap(L13);
    destroy_bitmap(L14);
    destroy_bitmap(L15);
    destroy_bitmap(L16);
    destroy_bitmap(L17);
    destroy_bitmap(L18);
    destroy_bitmap(L19);
    destroy_bitmap(L20);
    destroy_bitmap(L21);
    destroy_bitmap(L22);
    destroy_bitmap(R1);
    destroy_bitmap(R2);
    destroy_bitmap(R3);
    destroy_bitmap(R4);
    destroy_bitmap(R5);
    destroy_bitmap(R6);
    destroy_bitmap(R7);
    destroy_bitmap(R8);
    destroy_bitmap(R9);
    destroy_bitmap(R10);
    destroy_bitmap(R11);
    destroy_bitmap(R12);




    return 0;
}
END_OF_MAIN ()


