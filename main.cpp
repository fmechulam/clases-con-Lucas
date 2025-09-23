using namespace std;

const int max_titulo = 50;
const int max_mail = 50;
const int max_evaluadores = 3;
const int max_categoria = 5;

struct Trabajo {
    char titulo[max_titulo+1];
    int categoria;
    char correo[max_mail+1];
    int evaluadores[max_evaluadores];
    char resultado[40];
    Trabajo* sig;
}

Trabajo* buscarTrabajoEnLista(Trabajo* cabeza, const char titulo[]) {
    Trabajo* act = cabeza;
    
    while (act != NULL) {
        if (strcmp(act->titulo, titulo) == 0) {
            return act;
        }
        act = act->sig;
    }
    return NULL;
}

void calcularGrupos(const int v12[], int &formales, int &CT, int &autores, bool &tieneCero) {
    tieneCero = false;

    for (int i = 0; i<12, i++) {
        if (v12[i] == 0) {
            tieneCero = true;
        }
    }


    formales    = v12[0] + v12[3] + v12[6] + v12[9];
    CT          = v12[1] + v12[4] + v12[7] + v12[10];
    autores     = v12[2] + v12[5] + v12[8] + v12[11];
}

// 1) Asignar dictamen a un trabajo

void dictamen(Trabajo* categorias[], const int v12[], int idEvaluador, int categoria, const char titulo[]) {

    if (categoria < 1 || categoria > max_categoria) return;

    Trabajo* trabajo = buscarTrabajoEnLista(categorias[categoria-1], titulo);
    if (trabajo == NULL) return; //no encontrado


    int formales, CT, autores;
    bool tieneCero;

    calcularGrupos(v12, formales, CT, autores, tieneCero);

    if(tieneCero) {
        strcpy(trabajo->resultado, "Rechazado");
    } else if (formales > 22 && CT >= 35 && autores >= 17) {
        strcpy(trabajo->resultado, "Aprobado totalmente");
    } else if (formales >20 && CT >= 30 && autores >= 25) {
        strcpy(trabajo->resultado, "Aprobado, requiere modificaciones");
    } else if(formales >17 && CT >= 25 && autores >= 12) {
        strcpy(trabajo->resultado, "No aprobado, reformular");
    } else {
        strcpy(trabajo->resultado, "Rechazado");
    }
}


