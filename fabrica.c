#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NULLSERIAL "NNUULLLL"
#define SER_LEN 21
#define ERR_FOPEN "Error: could not open file."
#define ERR_CORPT "Error: File is corrupted."
#define ERR_ARGS "Error: Invalid argument."
#define ERR_MEM "Error: Couldn't allocate memory."
#define WARN_NO_PRODUCTION_INIT "Warning: No production done initiated yet."
#define ERR_NO_FILES "Error: No files were specified"


typedef enum{FALSE,TRUE}boolean;

typedef enum{GASOLEO,GASOLINA,HIBRIDO,ELETRICO} Fuel;

typedef enum{VERMELHO,VERDE,AZUL,AMARELO,PRETO,BRANCO,CINZENTO} Color;

typedef enum{PorAvaliar,Produzido,NaoPossivelProduzir} Status;


typedef struct motor{
    char serial_number[SER_LEN];
    int power;
    Fuel fuel;
    struct motor* next;
}Motor;
typedef struct motor_list{
    struct motor* head;
    struct motor* tail;
}Motors;
Motor* new_Motor();
Motors* new_Motor_List();
void insert_Motor(Motors* motors, Motor* motor);


typedef struct chassi{
    char serial_number[SER_LEN];
    Color color;
    char model[127];
    struct chassi* next;
}Chassi;
typedef struct chassi_list{
    struct chassi* head;
    struct chassi* tail;
}Chassis;
Chassi* new_Chassi(char* serial, char* color, char* model);
Chassis* new_Chassi_List();
void insert_Chassi(Chassis* chassis, Chassi* chassi);


typedef struct wheel{
    char serial_number[SER_LEN];
    int diameter;
    int width;
    Color color;
    struct wheel* next; 
}Wheel;
typedef struct wheel_list{
    struct wheel* head;
    struct wheel* tail;
}Wheels;
Wheel* new_Wheel();
Wheels* new_Wheel_List();
void insert_Wheel(Wheels* wheels, Wheel* wheel);


typedef struct tire{
    char serial_number[SER_LEN];
    int diameter;
    int width;
    int height;
    struct tire* next;
}Tire;
typedef struct tire_list{
    struct tire* head;
    struct tire* tail;
}Tires;
Tire* new_Tire();
Tires* new_Tire_List();
void insert_Tire(Tires* tires, Tire* tire);


typedef struct request{
    char serial_number[21];
    char motor_type[50];
    char chassi_type[50];
    char wheel_type[50];
    char tire_type[50];
    Status status;
    struct request* next;
}Request;
typedef struct requests{
    Request* head;
    Request* tail;
}Requests;
Request* new_Request(char* serial, char* motor, char* chassi, char* jnate, char* tire);
Requests* new_Request_List();
void insert_Requests(Requests* requests, Request* request);


void start_production(Motors* motors, Chassis* chassis, Wheels* wheels, Tires* tires, Requests* all_requests);
void show_current_inventory(Motors* motors, Chassis* chassis, Wheels* wheels, Tires* tires);
void write_updated_files(char* inventory_file, char* requests_file, Motors* motors, Chassis* chassis,Wheels* wheels,Tires* tires, Requests* requests);
void read_inventory_file(char* file, Motors* motors, Chassis* chassis, Wheels* wheels,Tires* tires);
void read_requests_file(char* file_name, Requests* requests);


void get_Motor(Motors* motors, char* motor_serial);
void get_Chassi(Chassis* chassis, char* chassi_serial);
void get_Wheel(Wheels* wheels, char* wheel_serial);
void get_Tire(Tires* tires, char* tire_serial);


void list_Motors(Motors* motors);
void list_Chassis(Chassis* chassis);
void list_Wheels(Wheels* wheels);
void list_Tires(Tires* tires);
void list_Requests(Requests* requests, int option);
/* list_Requests options:
    0 - todos_pedidos
    1 - pedidos_satisfeitos
    2 - pedidos_insatisfeitos
**/


void write_inventory_file(char* file_name, Motors* motors, Chassis* chassis,Wheels* wheels,Tires* tires);
void write_Requests_file(char* file_name, Requests* requests, int option);
/* writet_Requests_file options:
    1 - pedidos_satisfeitos
    2 - pedidos_insatisfeitos
**/


char* check_Motor(Motors* motors, char* motor_type);
char* check_Chassi(Chassis* chassis, char* chassi_type);
char* check_Wheel(Wheels* wheels, char* wheel_type);
char* check_Tire(Tires* tires, char* tire_type);

boolean str_Is_Equals(char* str1, char* str2);
char* itoa(int value, int base);
char* fuel_to_string(Fuel fuel);
char* color_to_string(Color color);

int main(int argc, char* argv[]){
    
    Motors* motors = new_Motor_List();
    Chassis* chassis = new_Chassi_List();
    Wheels* wheels = new_Wheel_List();
    Tires* tires = new_Tire_List();
    Requests* all_requests = new_Request_List();


    boolean production_started = FALSE;
    boolean inventory_file_specified = FALSE;
    boolean requests_file_specified = FALSE;

    char inventory_file[50];
    char requests_file[50];
    char input[200];
        
    if(argc > 2){
        puts("");
        printf("%s\n",ERR_ARGS);
    }   
    if(argv[1] != NULL && argc <= 2){
        strcpy(inventory_file,argv[1]);
        strcpy(requests_file,inventory_file);
        
        read_inventory_file(inventory_file, motors, chassis, wheels, tires);
        inventory_file_specified = TRUE;

        read_requests_file(requests_file, all_requests);
        requests_file_specified = TRUE;
    }
    while (1){        
        printf("**********Autolusofona***********\n");
        printf("1. Iniciar producao\n");
        printf("2. Mostrar inventario atual\n");
        printf("3. Mostrar pedidos satisfeitos\n");
        printf("4. Mostrar pedidos insatisfeitos\n");
        printf("5. Escrever ficheiros atualizados\n");
        printf("6. Ler ficheiro de inventario\n");
        printf("7. Ler ficheiro de pedidos\n");
        printf("8. Sair\n");
        printf("*********************************\n");

        strcpy(input,"");
        scanf("%s", input);
        
        switch (atoi(input)){
            case 1:
                if (inventory_file_specified == FALSE || requests_file_specified == FALSE){
                    printf("%s\n",ERR_NO_FILES);
                    break;
                }
                else{
                    start_production(motors,chassis,wheels,tires,all_requests);
                    production_started = TRUE;
                    break;
                }
            
            case 2:
                if (inventory_file_specified == FALSE){
                    printf("%s\n",ERR_NO_FILES);
                    break;
                }
                else{
                    show_current_inventory(motors,chassis,wheels,tires);
                    break;
                }

            case 3:
                if(production_started == FALSE){
                    puts("");
                    printf("%s\n",WARN_NO_PRODUCTION_INIT);
                }
                list_Requests(all_requests,1);
                break;

            case 4:
                if(production_started == FALSE){
                    puts("");
                    printf("%s\n",WARN_NO_PRODUCTION_INIT);
                }
                list_Requests(all_requests,2);
                break;

            case 5:
                if (inventory_file_specified == FALSE || requests_file_specified == FALSE){
                    printf("%s\n",ERR_NO_FILES);
                    break;
                }
                else{
                    write_updated_files(inventory_file,requests_file,motors,chassis,wheels,tires,all_requests);
                    break;
                }

            case 6:
                printf("Introduza o nome do ficheiro de inventario: ");
                scanf("%s", inventory_file);
                read_inventory_file(inventory_file, motors, chassis, wheels, tires);
                puts("");
                if(motors->head == NULL && chassis->head == NULL 
                && wheels->head == NULL && tires->head == NULL){
                    inventory_file_specified = FALSE;
                }
                else{
                    inventory_file_specified = TRUE;
                }
                break;

            case 7:
                printf("Introduza o nome do ficheiro de pedidos: ");
                scanf("%s", requests_file);
                read_requests_file(requests_file, all_requests);
                puts("");  
                if(all_requests->head == NULL){
                    requests_file_specified = FALSE;
                }
                else{
                    requests_file_specified = TRUE;
                }  
                break;

            case 8:
                return 0;

            
            default:
                puts("");
                printf("%s\n",ERR_ARGS);
                break;
        }

    }
    return 0;
}


void read_inventory_file(char* file_name, Motors* motors, Chassis* chassis,Wheels* wheels,Tires* tires){
    char inventory_file[50];
    strcpy(inventory_file,file_name);
    
    strtok(inventory_file,"\n");
    strcat(inventory_file,".inventario");
    
    char line[60];
    FILE* file;
    file = fopen(inventory_file, "r");
    
    if (file) {
        while (fscanf(file, "%s", line) != EOF){
            char* line_parts[10];
            int position = 0;
            line_parts[position] = strtok(line,",");
            while(line_parts[position] != NULL){
                line_parts[++position] = strtok(NULL,",");
            }
            if(str_Is_Equals(line_parts[0],"Motor")){
                Motor* motor = new_Motor(line_parts[1],line_parts[2],line_parts[3]);
                insert_Motor(motors,motor);
            }
            else if(str_Is_Equals(line_parts[0],"Chassis")){
                Chassi* chassi = new_Chassi(line_parts[1],line_parts[2],line_parts[3]);
                insert_Chassi(chassis,chassi);
            }
            else if(str_Is_Equals(line_parts[0],"Jantes")){
                Wheel* wheel = new_Wheel(line_parts[1],line_parts[2],line_parts[3],line_parts[4]);
                insert_Wheel(wheels,wheel);
            }
            else if(str_Is_Equals(line_parts[0],"Pneus")){
                Tire* tire = new_Tire(line_parts[1],line_parts[2],line_parts[3],line_parts[4]);
                insert_Tire(tires,tire);
            }
        }
        fclose(file);
    }else{
        puts("");
        printf("%s",ERR_FOPEN);
    }
 
}
void read_requests_file(char* file_name, Requests* requests){
    char request_file[50];
    strcpy(request_file,file_name);

    strtok(request_file, "\n");
    strcat(request_file,".pedidos");

    char line[100];
    FILE * file;
    file = fopen(request_file, "r");
    
    if (file) {
        while (fscanf(file, "%s", line) != EOF){
            char* line_parts[10];
            int position = 0;
            line_parts[position] = strtok(line,";");

            while(line_parts[position] != NULL){
                line_parts[++position] = strtok(NULL,";");
            }

            Request* request = new_Request(line_parts[0],line_parts[1],line_parts[2],line_parts[3],line_parts[4]);
            request->status = PorAvaliar;
            insert_Requests(requests,request);
            
        }
        fclose(file);
    }else{
        puts("");
        printf("%s\n",ERR_FOPEN);
    }
}


Motors* new_Motor_List(){
    Motors* motors = (Motors*) calloc(1,sizeof(Motors));
    if(motors == NULL){
        puts("");
        printf("%s\n",ERR_MEM);
    }
    motors->head = NULL;
    motors->tail = NULL;
    return motors;
}
Motor* new_Motor(char* serial, char* power, char* fuel){
    Motor* motor = (Motor*) calloc(1,sizeof(Motor));
    
    if(motor == NULL){
        printf("%s\n",ERR_MEM);
    }

    strcpy(motor->serial_number,serial);

    int cilindrada = (atoi(power));
    motor->power = cilindrada; 

    if(str_Is_Equals(fuel,"Gasoleo")){
        motor->fuel = GASOLEO;
    }
    else if(str_Is_Equals(fuel,"Gasolina")){
        motor->fuel = GASOLINA;
    }
    else if(str_Is_Equals(fuel,"Hibrido")){
        motor->fuel = HIBRIDO;
    }
    else if(str_Is_Equals(fuel,"Eletrico")){
        motor->fuel = ELETRICO;
    }
    
    motor->next = NULL;

    return motor;
}
void insert_Motor(Motors* motors, Motor* motor){
    if(motors->head == NULL){
        motors->head = motor;
        motors->tail = motor;
    }
    else{
        motors->tail->next = motor;
        motors->tail = motor;
    }
}


Chassis* new_Chassi_List(){

    Chassis* chassis = (Chassis*) calloc(1,sizeof(Chassis));
    if(chassis == NULL){
        puts("");
        printf("%s\n",ERR_MEM);
    }
    chassis->head = NULL;
    chassis->tail = NULL;
    return chassis;
}
Chassi* new_Chassi(char* serial, char* color, char* model){
    Chassi* chassi = (Chassi*) calloc(1,sizeof(Chassi));

    if(chassi == NULL){
        puts("");
        printf("%s\n",ERR_MEM);
    }
    strcpy(chassi->serial_number,serial);

    if(str_Is_Equals(color,"Vermelho")){
        chassi->color = VERMELHO;
    }
    else if(str_Is_Equals(color,"Verde")){
        chassi->color = VERDE;
    }
    else if(str_Is_Equals(color,"Azul")){
        chassi->color = AZUL;
    }
    else if(str_Is_Equals(color,"Amarelo")){
        chassi->color = AMARELO;
    }
    else if(str_Is_Equals(color,"Branco")){
        chassi->color = BRANCO;
    }
    else if(str_Is_Equals(color,"Cinzento")){
        chassi->color = CINZENTO;
    }
    else if(str_Is_Equals(color,"Preto")){
        chassi->color = PRETO;
    }

    strcpy(chassi->model,model);

    chassi->next =NULL;
    
    return chassi;
}
void insert_Chassi(Chassis* chassis, Chassi* chassi){
    if(chassis->head == NULL){
        chassis->head = chassi;
        chassis->tail = chassi;
    }
    else{
        chassis->tail->next = chassi;
        chassis->tail = chassi;
    }
}


Wheels* new_Wheel_List(){
    Wheels* wheels = (Wheels*) calloc(1,sizeof(Wheels));
   
    if(wheels == NULL){
        printf("%s\n",ERR_MEM);
        puts("");
    }
    wheels->head = NULL;
    wheels->tail = NULL;
    return wheels;
}
Wheel* new_Wheel(char* serial, char* diameter, char* width, char* color){
    Wheel* wheel = (Wheel*) calloc(1,sizeof(Wheel));
    
    if(wheel == NULL){
        puts("");
        printf("%s\n",ERR_MEM);
    }
    strcpy(wheel->serial_number,serial);
    
    int diameterActual = (atoi(diameter));
    wheel->diameter = diameterActual;

    int widthActual = (atoi(width));
    wheel->width = widthActual;

    if(str_Is_Equals(color,"Vermelho")){
        wheel->color = VERMELHO;
    }
    else if(str_Is_Equals(color,"Verde")){
        wheel->color = VERDE;
    }
    else if(str_Is_Equals(color,"Azul")){
        wheel->color = AZUL;
    }
    else if(str_Is_Equals(color,"Amarelo")){
        wheel->color = AMARELO;
    }
    else if(str_Is_Equals(color,"Branco")){
        wheel->color = BRANCO;
    }
    else if(str_Is_Equals(color,"Cinzento")){
        wheel->color = CINZENTO;
    }
    else if(str_Is_Equals(color,"Preto")){
        wheel->color = PRETO;
    }

    wheel->next =NULL;
    
    return wheel;
}
void insert_Wheel(Wheels* wheels, Wheel* wheel){
    if(wheels->head == NULL){
        wheels->head = wheel;
        wheels->tail = wheel;
    }
    else{
        wheels->tail->next = wheel;
        wheels->tail = wheel;
    }
}


Tires* new_Tire_List(){
   
    Tires* tires = (Tires*) calloc(1,sizeof(Tires));
    
    if(tires == NULL){
        printf("%s\n",ERR_MEM);
    }
    tires->head = NULL;
    tires->tail = NULL;
    return tires;
}
Tire* new_Tire(char* serial, char* diameter, char* width, char* height){
    Tire* tire = (Tire*) calloc(1,sizeof(Tire));
    if(tire == NULL){
        puts("");
        printf("%s\n",ERR_MEM);
    }
    strcpy(tire->serial_number,serial);

    int diameterActual = (atoi(diameter));
    tire->diameter = diameterActual;

    int widthActual = (atoi(width));
    tire->width = widthActual;

    int heightActual = (atoi(height));
    tire->height = heightActual;
    
    tire->next =NULL;

    return tire;
}
void insert_Tire(Tires* tires, Tire* tire){
    if(tires->head == NULL){
        tires->head = tire;
        tires->tail = tire;
    }
    else{
        tires->tail->next = tire;
        tires->tail = tire;
    }
}


Request* new_Request(char* serial, char* motor, char* chassi, char* wheel, char* tire){
    
    Request* request = (Request*)calloc(1,sizeof(Request));
    
    if(request == NULL){
        puts("");
        printf("%s\n",ERR_MEM);
    }
    strcpy(request->serial_number,serial);
    strcpy(request->motor_type,motor);
    strcpy(request->chassi_type,chassi);
    strcpy(request->wheel_type,wheel);
    strcpy(request->tire_type,tire);
    request->next = NULL;
    return request;
}
Requests* new_Request_List(){
    Requests* requests = (Requests*)calloc(1,sizeof(Request));
   
    if(requests == NULL){
        puts("");
        printf("%s\n",ERR_MEM);
    }
    requests->head = NULL;
    requests->tail = NULL;
    return requests;
}
void insert_Requests(Requests* requests, Request* request){
    if(requests->head == NULL){
        requests->head = request;
        requests->tail = request;
    }
    else{
        requests->tail->next = request;
        requests->tail = request;
    }
}


void start_production(Motors* motors, Chassis* chassis, Wheels* wheels, Tires* tires, Requests* all_requests){
    
    if(all_requests->head != NULL){
        //c_p <=> CURRENT_PEDIDO
        Request* c_p = all_requests->head;        
        while(1){   

            char* motor_serial = check_Motor(motors,c_p->motor_type);
            char* chassi_serial = check_Chassi(chassis,c_p->chassi_type);
            char* wheel_serial = check_Wheel(wheels,c_p->wheel_type);
            char* tire_serial = check_Tire(tires,c_p->tire_type);


            if(str_Is_Equals(motor_serial,NULLSERIAL) == FALSE && str_Is_Equals(chassi_serial,NULLSERIAL) == FALSE 
            && str_Is_Equals(wheel_serial,NULLSERIAL) == FALSE && str_Is_Equals(tire_serial,NULLSERIAL) == FALSE){
                
                get_Motor(motors,motor_serial);
                get_Chassi(chassis,chassi_serial);
                get_Wheel(wheels,wheel_serial);
                get_Tire(tires,tire_serial);
                c_p->status = Produzido;

            }else{
                c_p->status = NaoPossivelProduzir;
            }
            
            if(c_p->next != NULL){
                c_p = c_p->next;
            }else{
                break;
            }
        }
    }
}
void show_current_inventory(Motors* motors, Chassis* chassis, Wheels* wheels, Tires* tires){
    list_Motors(motors);
    list_Chassis(chassis);
    list_Wheels(wheels);
    list_Tires(tires);
}
void write_updated_files(char* inventory_file, char* requests_file, Motors* motors, Chassis* chassis,Wheels* wheels,Tires* tires, Requests* requests){

    char inventory_file_out[50];
    char file_produzidos_out[50];
    char file_nao_produzidos_out[50];

    strcpy(inventory_file_out,inventory_file);
    strcpy(file_produzidos_out,requests_file);
    strcpy(file_nao_produzidos_out,requests_file);

    strtok(inventory_file_out,"\n");
    strtok(file_produzidos_out,"\n");
    strtok(file_nao_produzidos_out,"\n");
    
    strcat(inventory_file_out,"_out");
    strcat(file_produzidos_out,"_out");
    strcat(file_nao_produzidos_out,"_out");

    strcat(inventory_file_out,".inventario");
    strcat(file_produzidos_out,".produzidos");
    strcat(file_nao_produzidos_out,".naoproduzidos");
    
    write_inventory_file(inventory_file_out,motors,chassis,wheels,tires);    
    write_Requests_file(file_produzidos_out,requests,1);
    write_Requests_file(file_nao_produzidos_out,requests,2);

}


void list_Motors(Motors* motors){
    if(motors->head != NULL){
        //c_m <=> CURRENT_MOTOR
        Motor* c_m = motors->head;
        while(1){
            char output[200];
            strcpy(output,"Motor");
            strcat(output,",");
            strcat(output,c_m->serial_number);
            strcat(output,",");
            strcat(output,itoa(c_m->power,10));
            strcat(output,",");
            strcat(output,fuel_to_string(c_m->fuel));

            puts(output);

            if(c_m->next != NULL){
                c_m = c_m->next;
            }else{
                break;
            }
        } 
    }
}
void list_Chassis(Chassis* chassis){
    if(chassis->head != NULL){
       //c_c <=> CURRENT CHASSI 
       Chassi* c_c = chassis->head;
       while(1){
            char output[200];
            strcpy(output,"Chassis");
            strcat(output,",");
            strcat(output,c_c->serial_number);
            strcat(output,",");
            strcat(output,color_to_string(c_c->color));
            strcat(output,",");
            strcat(output,c_c->model);

            puts(output);
            
            if(c_c->next != NULL){
                c_c = c_c->next;
            }else{
                break;
            }
       } 
    }
}
void list_Wheels(Wheels* wheels){
    if(wheels->head != NULL){
        //c_j <=> CURRENT_JANTE
        Wheel* c_j = wheels->head;
        while(1){
            char output[200];
            strcpy(output,"Jantes");
            strcat(output,",");
            strcat(output,c_j->serial_number);
            strcat(output,",");
            strcat(output,itoa(c_j->diameter,10));
            strcat(output,",");
            strcat(output,itoa(c_j->width,10));
            strcat(output,",");
            strcat(output,color_to_string(c_j->color));

            puts(output);

            if(c_j->next != NULL){
                c_j = c_j->next;
            }else{
                break;
            }
        } 
    }
}
void list_Tires(Tires* tires){
    if(tires->head != NULL){
       //c_p <=> CURRENT_PNEUS
        Tire* c_p = tires->head;
        while(1){
            char output[200];
            strcpy(output,"Pneus");
            strcat(output,",");
            strcat(output,c_p->serial_number);
            strcat(output,",");
            strcat(output,itoa(c_p->diameter,10));
            strcat(output,",");
            strcat(output,itoa(c_p->width,10));
            strcat(output,",");
            strcat(output,itoa(c_p->height,10));

            puts(output);

            if(c_p->next != NULL){
                c_p = c_p->next;
            }else{
                break;
            }
       } 
    }
}
void list_Requests(Requests* requests, int option){
    if(requests->head != NULL){
        if(option == 0){
            Request* current_request = requests->head;
            while(1){
                char output[200];
                strcpy(output,current_request->serial_number);
                strcat(output,";");
                strcat(output,current_request->motor_type);
                strcat(output,";");
                strcat(output,current_request->chassi_type);
                strcat(output,";");
                strcat(output,current_request->wheel_type);
                strcat(output,";");
                strcat(output,current_request->tire_type);

                puts(output);
                
                if(current_request->next != NULL){
                    current_request = current_request->next;
                }else{
                    break;
                }
            }
        }
        else if(option == 1){
            boolean first = TRUE;
            Request* current_request = requests->head;
            while(1){
                if(current_request->status == Produzido){
                    if(first == FALSE){
                        printf("\n");
                    }
                    first = FALSE;
                    char output[200];
                    strcpy(output,current_request->serial_number);
                    strcat(output,";");
                    strcat(output,current_request->motor_type);
                    strcat(output,";");
                    strcat(output,current_request->chassi_type);
                    strcat(output,";");
                    strcat(output,current_request->wheel_type);
                    strcat(output,";");
                    strcat(output,current_request->tire_type);

                    //puts(output);
                    printf("%s",output);
                }
                if(current_request->next != NULL){
                    current_request = current_request->next;
                }else{
                    break;
                }
            }
        }
        else if(option == 2){
            boolean first = TRUE;
            Request* current_request = requests->head;
            while(1){
                if(current_request->status == NaoPossivelProduzir){
                    if(first == FALSE){
                        printf("\n");
                    }
                    first = FALSE;
                    char output[200];
                    strcpy(output,current_request->serial_number);
                    strcat(output,";");
                    strcat(output,current_request->motor_type);
                    strcat(output,";");
                    strcat(output,current_request->chassi_type);
                    strcat(output,";");
                    strcat(output,current_request->wheel_type);
                    strcat(output,";");
                    strcat(output,current_request->tire_type);

                    printf("%s",output);
                    //puts(output);
                }
                if(current_request->next != NULL){
                    current_request = current_request->next;
                }else{
                    break;
                }
            }

        }  
    }
    puts("");
}


void write_inventory_file(char* inventory_file, Motors* motors, Chassis* chassis,Wheels* wheels,Tires* tires){
    if(motors->head != NULL){
        FILE* file = fopen(inventory_file,"w");
        if(file){
            if(motors->head != NULL){
                //c_m <=> CURRENT_MOTOR
                Motor* c_m = motors->head;
                while(1){
                    char output[200];
                    strcpy(output,"Motor");
                    strcat(output,",");
                    strcat(output,c_m->serial_number);
                    strcat(output,",");
                    strcat(output,itoa(c_m->power,10));
                    strcat(output,",");
                    strcat(output,fuel_to_string(c_m->fuel));

                    fprintf(file,"%s\n",output);

                    if(c_m->next != NULL){
                        c_m = c_m->next;
                    }else{
                        break;
                    }
                } 
            }
            if(chassis->head != NULL){    
                //c_c <=> CURRENT CHASSI 
                Chassi* c_c = chassis->head;
                while(1){
                    char output[200];
                    strcpy(output,"Chassis");
                    strcat(output,",");
                    strcat(output,c_c->serial_number);
                    strcat(output,",");
                    strcat(output,color_to_string(c_c->color));
                    strcat(output,",");
                    strcat(output,c_c->model);

                    fprintf(file,"%s\n",output);
                    
                    if(c_c->next != NULL){
                        c_c = c_c->next;
                    }else{
                        break;
                    }
                } 
            }
            if(wheels->head != NULL){    
                //c_j <=> CURRENT_JANTE
                Wheel* c_j = wheels->head;
                while(1){
                    char output[200];
                    strcpy(output,"Jantes");
                    strcat(output,",");
                    strcat(output,c_j->serial_number);
                    strcat(output,",");
                    strcat(output,itoa(c_j->diameter,10));
                    strcat(output,",");
                    strcat(output,itoa(c_j->width,10));
                    strcat(output,",");
                    strcat(output,color_to_string(c_j->color));

                    fprintf(file,"%s\n",output);

                    if(c_j->next != NULL){
                        c_j = c_j->next;
                    }else{
                        break;
                    }
                }
            }
            if(tires->head != NULL){    
                //c_p <=> CURRENT_PNEU
                Tire* c_p = tires->head;
                while(1){
                    char output[200];
                    strcpy(output,"Pneus");
                    strcat(output,",");
                    strcat(output,c_p->serial_number);
                    strcat(output,",");
                    strcat(output,itoa(c_p->diameter,10));
                    strcat(output,",");
                    strcat(output,itoa(c_p->width,10));
                    strcat(output,",");
                    strcat(output,itoa(c_p->height,10));

                    fprintf(file,"%s\n",output);
                    
                    if(c_p->next != NULL){
                        c_p = c_p->next;
                    }else{
                        break;
                    }
                }
            }
        }
        else{
            puts("");
            printf("%s\n",ERR_FOPEN);
        }
        fclose(file);  
    }
}
void write_Requests_file(char* file_name, Requests* requests, int option){
    if(requests->head != NULL){
        FILE* file = fopen(file_name,"w");
        if(file){
            if(option == 1){
                Request* current_request = requests->head;
                while(1){
                    if(current_request->status == Produzido){
                        char output[200];
                        strcpy(output,current_request->serial_number);
                        strcat(output,";");
                        strcat(output,current_request->motor_type);
                        strcat(output,";");
                        strcat(output,current_request->chassi_type);
                        strcat(output,";");
                        strcat(output,current_request->wheel_type);
                        strcat(output,";");
                        strcat(output,current_request->tire_type);

                        fprintf(file,"%s\n",output);
                        
                    }
                    if(current_request->next != NULL){
                        current_request = current_request->next;
                    }else{
                        break;
                    }
                }
            }
            else if(option == 2){
                Request* current_request = requests->head;
                while(1){
                    if(current_request->status == NaoPossivelProduzir){
                        char output[200];
                        strcpy(output,current_request->serial_number);
                        strcat(output,";");
                        strcat(output,current_request->motor_type);
                        strcat(output,";");
                        strcat(output,current_request->chassi_type);
                        strcat(output,";");
                        strcat(output,current_request->wheel_type);
                        strcat(output,";");
                        strcat(output,current_request->tire_type);

                       fprintf(file,"%s\n",output);
                    }
                    if(current_request->next != NULL){
                        current_request = current_request->next;
                    }else{ 
                        break;
                    }
                }
            } 
            fclose(file); 
        }
        else{
            puts("");
            printf("%s\n",ERR_FOPEN);
        }
    }
}


boolean str_Is_Equals(char* str1, char* str2){
    if(str1 == NULL || str2 == NULL){
        return FALSE;
    }
    if(strcmp(str1,str2) == 0){
        return TRUE;
    }
    return 0;
    
}
char* itoa(int value, int base){
	
	static char buf[32] = {0};
	int i = 30;
	
	for(; value && i ; --i, value /= base){
		buf[i] = "0123456789abcdef"[value % base];
	}
	return &buf[i+1];
}
char* fuel_to_string(Fuel fuel){
    switch(fuel){
        case GASOLEO:
            return "Gasoleo";

        case GASOLINA:
            return "Gasolina";  

        case HIBRIDO:
            return "Hibrido";  

        default:
            return "Eletrico";  
    }
}
char* color_to_string(Color color){
    switch(color){
        case AZUL:
            return "Azul";

        case AMARELO:
            return "Amarelo";  

        case VERDE:
            return "Verde";  

        case VERMELHO:
            return "Vermelho";

        case PRETO:
            return "Preto";  

        case CINZENTO:
            return "Cinzento";  

        default:
            return "Branco";  
    }
}


void get_Motor(Motors* motors, char* motor_serial){  
    if(motors->head != NULL){
        char motor_serial_copy[50];
        strcpy(motor_serial_copy,motor_serial);

        if(str_Is_Equals(motors->head->serial_number,motor_serial_copy) == TRUE){
           Motor* temp = motors->head;
           motors->head = motors->head->next;
           free(temp); 
        }
        else{
            Motor* anterior = motors->head;
            while(1){
                if(str_Is_Equals(anterior->next->serial_number,motor_serial_copy) == TRUE){
                    Motor* temp = anterior->next;
                    anterior->next = temp->next;
                    free(temp);
                    break; 
                }
                if(anterior->next != NULL){
                    anterior = anterior->next;
                }else{
                    break;
                }
            }
        }
    }
}
void get_Chassi(Chassis* chassis, char* chassi_serial){
    if(chassis->head != NULL){
        char chassi_serial_copy[50];
        strcpy(chassi_serial_copy,chassi_serial);

        if(str_Is_Equals(chassis->head->serial_number,chassi_serial_copy) == TRUE){
           Chassi* temp = chassis->head;
           chassis->head = chassis->head->next;
           free(temp); 
        }
        else{
            Chassi* anterior = chassis->head;
            while(1){
                if(str_Is_Equals(anterior->next->serial_number,chassi_serial_copy) == TRUE){
                    Chassi* temp = anterior->next;
                    anterior->next = temp->next;
                    free(temp);
                    break; 
                }
                if(anterior->next != NULL){
                    anterior = anterior->next;
                }else{
                    break;
                }
            }
        } 
    }
}
void get_Wheel(Wheels* wheels, char* wheel_serial){
    if(wheels->head != NULL){
        char wheel_serial_copy[50];
        strcpy(wheel_serial_copy,wheel_serial);

        if(str_Is_Equals(wheels->head->serial_number,wheel_serial_copy) == TRUE){
           Wheel* temp = wheels->head;
           wheels->head = wheels->head->next;
           free(temp); 
        }
        else{
            Wheel* anterior = wheels->head;
            while(1){
                if(str_Is_Equals(anterior->next->serial_number,wheel_serial_copy) == TRUE){
                    Wheel* temp = anterior->next;
                    anterior->next = temp->next;
                    free(temp);
                    break; 
                }
                if(anterior->next != NULL){
                    anterior = anterior->next;
                }else{
                    break;
                }
            }
        }
    }

}
void get_Tire(Tires* tires, char* tire_serial){
    if(tires->head != NULL){
        char tire_serial_copy[50];
        strcpy(tire_serial_copy,tire_serial);

        if(str_Is_Equals(tires->head->serial_number,tire_serial_copy) == TRUE){
           Tire* temp = tires->head;
           tires->head = tires->head->next;
           free(temp); 
        }
        else{
            Tire* anterior = tires->head;
            while(1){
                if(str_Is_Equals(anterior->next->serial_number,tire_serial_copy) == TRUE){
                    Tire* temp = anterior->next;
                    anterior->next = temp->next;
                    free(temp);
                    break; 
                }
                if(anterior->next != NULL){
                    anterior = anterior->next;
                }else{
                    break;
                }
            }
        }
    }

}


char* check_Motor(Motors* motors, char* motor_type){
    if(motors->head != NULL){
        Motor* current_motor = motors->head;

        char motor_type_copy[50];
        strcpy(motor_type_copy,motor_type);
        
        char* motor_parts[5];
        motor_parts[0] = "";
	    motor_parts[1] = "";

        int position = 0;
        motor_parts[position] = strtok(motor_type_copy,",");
        while(motor_parts[position] != NULL){
            motor_parts[++position] = strtok(NULL,",");
        }

        if(motor_parts[0] == NULL && motor_parts[1] == NULL){
          return current_motor->serial_number; 
        }
        else{
            while(1){
                if(motor_parts[0] != NULL && motor_parts[1] == NULL){
                    if(current_motor->power == atoi(motor_parts[0])){
                       return current_motor->serial_number;
                    }
                }
                else if(motor_parts[0]==NULL && motor_parts[1] != NULL){
                    if(str_Is_Equals(fuel_to_string(current_motor->fuel),motor_parts[1]) == TRUE){
                        return current_motor->serial_number;
                    }
                }
                else if(motor_parts[0]!=NULL && motor_parts[1] != NULL){
                    if(str_Is_Equals(fuel_to_string(current_motor->fuel),motor_parts[1]) == TRUE 
                    && current_motor->power == atoi(motor_parts[0])){
                        return current_motor->serial_number;
                    }
                }
            
                if(current_motor->next != NULL){
                    current_motor = current_motor->next;
                }
                else{
                    break;
                }
            }
        }
    }
    return NULLSERIAL;
}
char* check_Chassi(Chassis* chassis, char* chassi_type){
    if(chassis->head != NULL){

        Chassi* current_chassi = chassis->head;

        char chassi_type_copy[50];
        strcpy(chassi_type_copy,chassi_type);

        char* chassi_parts[5];
        chassi_parts[0] = "";
	    chassi_parts[1] = "";
        int position = 0;
        chassi_parts[position] = strtok(chassi_type_copy,",");
        while(chassi_parts[position] != NULL){
            chassi_parts[++position] = strtok(NULL,",");
        }

        if(chassi_parts[0] == NULL && chassi_parts[1] == NULL){
           return current_chassi->serial_number;
        }
        else{
            while(1){
                if(chassi_parts[0] != NULL && chassi_parts[1] == NULL){
                    if(str_Is_Equals(color_to_string(current_chassi->color),chassi_parts[0]) == TRUE){
                        return current_chassi->serial_number;
                    }
                }
                else if(chassi_parts[0]==NULL && chassi_parts[1] != NULL){
                    if(str_Is_Equals(current_chassi->model,chassi_parts[1]) == TRUE){
                        return current_chassi->serial_number;
                    }
                }
                else if(chassi_parts[0]!=NULL && chassi_parts[1] != NULL){
                    if(str_Is_Equals(color_to_string(current_chassi->color),chassi_parts[0]) == TRUE 
                    && str_Is_Equals(current_chassi->model,chassi_parts[1]) == TRUE){
                        return current_chassi->serial_number;
                    }   
                }
                if(current_chassi->next != NULL){
                    current_chassi = current_chassi->next;
                }
                else{
                    break;
                }
            }
        }
    }
    return NULLSERIAL;
}
char* check_Wheel(Wheels* wheels, char* wheel_type){
    if(wheels->head != NULL){

        Wheel* current_wheel = wheels->head;

        char wheel_type_copy[50];
        strcpy(wheel_type_copy,wheel_type);

        char* wheel_parts[5];
        wheel_parts[0] = "";
	    wheel_parts[1] = "";
        wheel_parts[2] = "";
	    
        int position = 0;
        wheel_parts[position] = strtok(wheel_type_copy,",");
        while(wheel_parts[position] != NULL){
            wheel_parts[++position] = strtok(NULL,",");
        }

        if(wheel_parts[0] == NULL && wheel_parts[1] == NULL && wheel_parts[2] == NULL){
           return current_wheel->serial_number; 
        }
        else{
            while(1){
                if(wheel_parts[0] == NULL && wheel_parts[1] == NULL && wheel_parts[2] != NULL){
                    if(str_Is_Equals(color_to_string(current_wheel->color),wheel_parts[2])){
                        return current_wheel->serial_number; 
                    }
                }
                else if(wheel_parts[0] != NULL && wheel_parts[1] == NULL){
                    if(wheel_parts[2] == NULL){
                        if(current_wheel->diameter == atoi(wheel_parts[0])){
                            return current_wheel->serial_number; 
                        }
                    }
                    else{
                        if(current_wheel->diameter == atoi(wheel_parts[0]) && str_Is_Equals(color_to_string(current_wheel->color),wheel_parts[2])){
                            return current_wheel->serial_number; 
                        }
                    }
                }
                else if(wheel_parts[0]==NULL && wheel_parts[1] != NULL){
                    if(wheel_parts[2] == NULL){
                        if(current_wheel->width == atoi(wheel_parts[1])){
                            return current_wheel->serial_number; 
                        }
                    }
                    else{
                        if(current_wheel->width == atoi(wheel_parts[1]) 
                        && str_Is_Equals(color_to_string(current_wheel->color),wheel_parts[2])){
                            return current_wheel->serial_number; 
                        }
                    }
                }
                else if(wheel_parts[0]!=NULL && wheel_parts[1] != NULL){
                    if(wheel_parts[2] == NULL){
                        if(current_wheel->diameter == atoi(wheel_parts[0]) && current_wheel->width == atoi(wheel_parts[1])){
                            return current_wheel->serial_number; 
                        }
                    }
                    else{
                        if(current_wheel->diameter == atoi(wheel_parts[0]) && current_wheel->width == atoi(wheel_parts[1]) 
                        && str_Is_Equals(color_to_string(current_wheel->color),wheel_parts[2])){
                            return current_wheel->serial_number; 
                        }
                    }    
                }
                
                if(current_wheel->next != NULL){
                    current_wheel = current_wheel->next;
                }else{
                    break;
                }
            }
        }
    }
    return NULLSERIAL;
}
char* check_Tire(Tires* tires, char* tire_type){
    if(tires->head != NULL){

        Tire* current_tire = tires->head;

        char tire_type_copy[50];
        strcpy(tire_type_copy,tire_type);


        char* tire_parts[5];
        tire_parts[0] = "";
	    tire_parts[1] = "";
        tire_parts[2] = "";

        int position = 0;
        tire_parts[position] = strtok(tire_type_copy,",");
        while(tire_parts[position] != NULL){
            tire_parts[++position] = strtok(NULL,",");
        }

        if(tire_parts[0] == NULL && tire_parts[1] == NULL && tire_parts[2] == NULL){
           return current_tire->serial_number; 
        }
        else{
            while(1){
                if(tire_parts[0] == NULL && tire_parts[1] == NULL && tire_parts[2] != NULL){
                    if(current_tire->height == atoi(tire_parts[2])){
                        return current_tire->serial_number;
                    }
                }
                else if(tire_parts[0] != NULL && tire_parts[1] == NULL){
                    if(tire_parts[2] == NULL){
                        if(current_tire->diameter == atoi(tire_parts[0])){
                            return current_tire->serial_number;
                        } 
                    }
                    else{
                        if(current_tire->diameter == atoi(tire_parts[0]) && current_tire->height == atoi(tire_parts[2])){
                            return current_tire->serial_number;
                        }  
                    }
                }
                else if(tire_parts[0]==NULL && tire_parts[1] != NULL){
                    if(tire_parts[2] == NULL){
                        if(current_tire->width == atoi(tire_parts[1])){
                            return current_tire->serial_number;
                        }   
                    }
                    else{
                        if(current_tire->width == atoi(tire_parts[1]) && current_tire->height == atoi(tire_parts[2])){
                            return current_tire->serial_number;
                        }
                        
                    }
                }
                else if(tire_parts[0]!=NULL && tire_parts[1] != NULL){
                    if(tire_parts[2] == NULL){
                        if(current_tire->diameter == atoi(tire_parts[0]) && current_tire->width == atoi(tire_parts[1])){
                            return current_tire->serial_number;
                        }
                    }
                    else{
                        if(current_tire->diameter == atoi(tire_parts[0]) && current_tire->width == atoi(tire_parts[1]) 
                        && current_tire->height == atoi(tire_parts[2])){
                            return current_tire->serial_number;
                        }  
                    }    
                }
                if(current_tire->next != NULL){
                    current_tire = current_tire->next;
                }else{
                    break;
                }
            }
        }
    }
    return NULLSERIAL;
}