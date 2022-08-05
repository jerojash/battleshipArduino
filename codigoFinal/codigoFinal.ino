#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

byte f[4]={10,9,8,7};
byte c[4]={6,5,4,3};
char keys[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
Keypad teclado = Keypad(makeKeymap(keys),f,c,4,4);
char tecla=' ';
int tmenu=0;
int barcosA[4][10];
int barcosB[4][10];
int tirosA[4][10];
int tirosB[4][10];
int llenado=0;

void setup() {
  Serial.begin(9600);

  lcd.setBacklight(HIGH);
  lcd.init();
  lcd.begin(16,2);

}

void loop() {
  
  menu();

}


void llenarMatriz(int tipo){
  limpiarMatriz(tipo);
  
  String mensaje= " ";
  int coordenada[2];
  int cont =0;
  int matriz[4][10];
  for(int i=0; i<=3; i++){//Limpio la matriz temporal, todas las casillas en 0
      for(int j=0; j<=9; j++){
        matriz[i][j]=0;
      } 
    }
  while (cont<10){
    lcd.setCursor(0,0);
    lcd.print("Ingresa Coordena");
    if (tipo==1){
        
        mensaje = "da de barco: ";
        lcd.setCursor(0,1);
        lcd.print(mensaje);  
    }else{
        mensaje = "da de misil: ";
        lcd.setCursor(0,1);
        lcd.print(mensaje); 
    }
  
    tecla = '1';
    //Valido si la tecla de la primera coordenada de barco es A,B,C o D
    while(tecla != 'A'&&tecla != 'B'&&tecla != 'C'&&tecla != 'D')
    {
       tecla = teclado.getKey(); //Obtengo el primer caracter del teclado
    }
    switch(tecla){
      case 'A': coordenada[0]=0;
              break;
      case 'B': coordenada[0]=1;
              break;
      case 'C': coordenada[0]=2;
              break;
      case 'D': coordenada[0]=3;
              break;
    }
    mensaje += (String)tecla +"x";
    lcd.setCursor(0,1);
    lcd.print(mensaje);
    tecla = 'A';
    //Valido si la tecla de la segunda coordenada de barco es 1,2,3,4,5,6,7,8 o 9
    while(tecla != '1'&&tecla != '2'&&tecla != '3'&&tecla != '4'&&tecla != '5'&&tecla != '6'&&tecla != '7'&&tecla != '8'&&tecla != '9'&&tecla != '0')
    {
       tecla = teclado.getKey(); //Obtengo el primer caracter del teclado
    } 
    coordenada[1]=atoi(&tecla);
    mensaje += (String)tecla;
    lcd.setCursor(0,1);
    lcd.print(mensaje);
    if(matriz[coordenada[0]][coordenada[1]]!=1){//Quiere decir que en esa casilla no hay un barco
      cont++;
      matriz[coordenada[0]][coordenada[1]]=1;
      if (tipo==1){
        barcosA[coordenada[0]][coordenada[1]]=1;
      }else{
        tirosA[coordenada[0]][coordenada[1]]=1;
      }
       
    }else{
      limpiarLed();
      lcd.setCursor(0,0);
      lcd.print("ERROR BARCO");
      lcd.setCursor(0,1);
      lcd.print("YA INGRESADO");
      delay(2400);
      limpiarLed();
      lcd.setCursor(0,0);
      lcd.print("INTENTE DE");
      lcd.setCursor(0,1);
      lcd.print("NUEVO");
    }
    delay(1500);
    limpiarLed();  
  }
  lcd.setCursor(0,0);
  lcd.print("SE INGRESARON");
  if (tipo==1){
    lcd.setCursor(0,1);
    lcd.print("LOS 10 BARCOS");    
  }else{
    lcd.setCursor(0,1);
    lcd.print("LOS 10 DISPAROS");    
  }

  delay(1400);
  
}

void limpiarMatriz(int tipo){
  if(tipo==1){
    for(int i=0; i<=3; i++){
      for(int j=0; j<=9; j++){
        barcosA[i][j]=0;
      } 
    }
  }else{
    for(int i=0; i<=3; i++){
      for(int j=0; j<=9; j++){
        tirosA[i][j]=0;
      }
    } 
  }
}

void menu(){
  while(tmenu==0){
      lcd.setCursor(0,0);
      lcd.print("1.- Comenzar");
      lcd.setCursor(0,1);
      lcd.print("2.- Salir");
    
      tecla = teclado.getKey();
      switch (tecla){
        case '1':limpiarLed();
              delay(500);
              limpiarMatriz(1);
              limpiarMatriz(0);
              llenado=0;
              tmenu = 1;
              menuJuego();
              break;
        case '2': limpiarLed();
              exit;
              break;
        
      }
  }
      
    
  
  
}

void menuJuego(){
  while(tmenu>0){
    while(tmenu == 1){
        lcd.setCursor(0,0);
        lcd.print("1.IngresarBarcos");
        lcd.setCursor(0,1);
        lcd.print("2.Disparar C.Mas");
        tecla = teclado.getKey();
        switch (tecla){
          case '1':limpiarLed();
                delay(500);
                llenarMatriz(1);
                break;
          case '2': limpiarLed();
                delay(500);
                llenarMatriz(0);    
                break;
          case 'C': limpiarLed();
                delay(500);
                tmenu=2;
                break;
        }
    }

    while(tmenu==2){
      lcd.setCursor(0,0);
      lcd.print("3.Ver Barcos");
      lcd.setCursor(0,1);
      lcd.print("B.Volver   C.Mas");
      tecla = teclado.getKey();
      switch (tecla){
        case 'B':limpiarLed();
              tmenu=1;
              break;
        case '3': limpiarLed();
                  delay(500);
                  imprimirBarcosA();
              break;
        case 'C': limpiarLed();
                delay(500);
                tmenu=3;
              break;
      }
    }

    while(tmenu==3){
      lcd.setCursor(0,0);
      lcd.print("4.Ver Disparos");
      lcd.setCursor(0,1);
      lcd.print("B.Volver   C.Mas");
      tecla = teclado.getKey();
      switch (tecla){
        case 'B':limpiarLed();
              tmenu=2;
              break;
        case '4': limpiarLed();
                  delay(500);
                  imprimirTirosA();
              break;
        case 'C': limpiarLed();
                delay(500);
                tmenu=4;
              break;
      }
    }
    
    while(tmenu==4){
      lcd.setCursor(0,0);
      lcd.print("5.Jugar");
      lcd.setCursor(0,1);
      lcd.print("B.Volver   C.Mas");
      tecla = teclado.getKey();
      switch (tecla){
        case '5':limpiarLed();
              delay(500);
              //jugar();
              break;
        case 'B': limpiarLed();
              delay(500);
              tmenu=3;
              break;
        case 'C': limpiarLed();
                delay(500);
                tmenu=5;
                break;
      }
    }
    while(tmenu==5){
      lcd.setCursor(0,0);
      lcd.print("6.Ver puntaje");
      lcd.setCursor(0,1);
      lcd.print("B.Volver   C.Mas");
      tecla = teclado.getKey();
      switch (tecla){
        case '6':limpiarLed();
              delay(500);
              
              break;
        case 'B': limpiarLed();
              delay(500);
              tmenu=4;
              break;
        case 'C': limpiarLed();
              delay(500);
              tmenu=6;
              break;
      }
    }
    while(tmenu==6){
      lcd.setCursor(0,0);
      lcd.print("7.Salir");
      lcd.setCursor(0,1);
      lcd.print("B.Volver");
      tecla = teclado.getKey();
      switch (tecla){
        case '7':limpiarLed();
              delay(500);
              tmenu=0;
              break;
        case 'B': limpiarLed();
              delay(500);
              tmenu=5;
              break;
      }
    }  
  }
    
      
  
  
}

void imprimirBarcosA(){
  
  int cont=0;
  int fila = 0;
  while(fila<4){
      cont = 0;
      lcd.setCursor(0,1); //Algoritmo para llenar la fila de abajo del lcd
      lcd.print('[');
      while(cont<10){ //Algoritmo para imprimir las filas de abajo
        if (barcosA[fila][cont]==1){
          lcd.setCursor(cont+1,1);
          lcd.print('X');
        }else{
          lcd.setCursor(cont+1,1);
          lcd.print('o');
        }
        cont++;
      }
      lcd.setCursor(11,1);
      lcd.print(']');
      cont=0;
      if (fila != 0){
          lcd.setCursor(0,0); //Algoritmo para llenar la fila de arriba del lcd
          lcd.print('[');
          while(cont<10){ //Algoritmo para imprimir las filas de abajo
            if (barcosA[fila-1][cont]==1){
              lcd.setCursor(cont+1,0);
              lcd.print('X');
            }else{
              lcd.setCursor(cont+1,0);
              lcd.print('o');
            }
            cont++;
          }
          lcd.setCursor(11,0);
          lcd.print(']');
      }
          
      delay(2000);
      fila++;
    limpiarLed();
  }
}

void imprimirTirosA(){
  
  int cont=0;
  int fila = 0;
  while(fila<4){
      cont = 0;
      lcd.setCursor(0,1); //Algoritmo para llenar la fila de abajo del lcd
      lcd.print('[');
      while(cont<10){ //Algoritmo para imprimir las filas de abajo
        if (tirosA[fila][cont]==1){
          lcd.setCursor(cont+1,1);
          lcd.print('X');
        }else{
          lcd.setCursor(cont+1,1);
          lcd.print('o');
        }
        cont++;
      }
      lcd.setCursor(11,1);
      lcd.print(']');
      cont=0;
      if (fila != 0){
          lcd.setCursor(0,0); //Algoritmo para llenar la fila de arriba del lcd
          lcd.print('[');
          while(cont<10){ //Algoritmo para imprimir las filas de abajo
            if (tirosA[fila-1][cont]==1){
              lcd.setCursor(cont+1,0);
              lcd.print('X');
            }else{
              lcd.setCursor(cont+1,0);
              lcd.print('o');
            }
            cont++;
          }
          lcd.setCursor(11,0);
          lcd.print(']');
      }
          
      delay(2000);
      fila++;
    limpiarLed();
  }
}

void limpiarLed(){
  //Codigo para limpiar el lcd
  lcd.setCursor(0,0);
  lcd.print("                 ");
  lcd.setCursor(0,1);
  lcd.print("                 ");
}




/*
//ALGORITMO: ENVIA 1, CUANDO RECIBE UN CARACTER VALIDO, POR EL PUERTO SERIAL


// C++ code
//

char flag = '0';
char letra = ' ';
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int cont=0;
  
  while(cont<20){
    letra = ' ';
    flag = '0';
    while (flag == '0') {
      letra = Serial.read();
        if (letra=='1'||letra=='2'||letra=='3'||letra=='4'||letra=='5'||letra=='6'||letra=='7'||letra=='8'||letra=='9'||letra=='0'||letra=='A'||letra=='B'||letra=='C'||letra=='D'){
          flag='1';
            Serial.println(flag);
        }
    }
    cont++;
  }
}

*/
