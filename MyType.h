
#define MNOG 100

typedef struct tagTREUG {
	bool pr;
	float x;
	float y;
	float z;
} TREUG;

typedef struct tagFLOATPOINT{
	float x;
	float y;
} FLOATPOINT;

typedef struct tagPOLYGON {
	bool pr; // Признак заполненности полигона
	bool dv; //  Признак наличия двойственности
	int ma; // Номер материала
	int kv; // Количество вершин
	int xyz[4];// Номера вершин в пространстве
	FLOATPOINT vh[4];//  Координаты на ВМР
} POLYGON;

typedef struct tagBMPINF{
	CString ImFile[2];
	CBitmap ris;
	CPoint n,k,z;
} BMPINF;
typedef int *MASINT;
typedef MASINT *MASMASINT;
typedef struct tagINFOPTIM{
	MASINT *masPolMat;// Двумерный массив списков полигонов для каждого материала.
	int *kPolMat; //  Массив количеств полигонов для каждого материала.
} INFOPTIM;

typedef struct tagREZ{
	MASMASINT *Podgrup;// Трехмерный масси подгруп непересекающихся полигонов по материалам.
	int *kPodgrup;// Одномерный массив количества подгрупп в каждом материале.
	MASINT *kElemPod;// Двумерный массив количества регионов в каждой подгруппе материала.. 
} REZ;

