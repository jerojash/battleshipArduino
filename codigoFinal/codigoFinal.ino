#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

byte f[4]={10,9,8,7};
byte c[4]={6,5,4,3};
char keys[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
Keypad teclado = Keypad(makeKeymap(keys),f,c,4,4);
//Copiar desde aca abajo 
boolean barcosLlenos = false;
boolean tirosLlenos = false;
char tecla=' ';
int tmenu=0;
int barcosA[4][10];
int barcosB[4][10];
int tirosA[4][10];
int tirosB[4][10];
//int llenado=0;
int targetA=0;
int targetB=0;
int scoreA=0;
int scoreB=0;
int cantPartidas = 0;

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
              barcosLlenos = false;
              tirosLlenos = false;
              scoreA=0;
              scoreB=0;
              //llenado=0;
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
                barcosLlenos = true;
                break;
          case '2': limpiarLed();
                delay(500);
                llenarMatriz(0);
                tirosLlenos = true;    
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
              jugar();
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
  if(scoreA==2){
    limpiarLed();
    lcd.setCursor(0,0);
    lcd.print("HAS GANADO");
    lcd.setCursor(0,1);
    lcd.print("FELICIDADES");
    delay(2600);
  }
  if(scoreB==2){
    limpiarLed();
    lcd.setCursor(0,0);
    lcd.print("F HAS PERDIDO :(");
    lcd.setCursor(0,1);
    lcd.print("SUERTE LA PROX");
    delay(2600);
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

void jugar(){
  limpiarLed();
  lcd.setCursor(0,0);
  lcd.print("Recibiendo datos");
  lcd.setCursor(0,1);
  lcd.print("de Jugador B");
  targetA=0;
  targetB=0;
  if(!barcosLlenos||!tirosLlenos){
    lcd.setCursor(0,0);
    lcd.print("Asegurate de");
    lcd.setCursor(0,1);
    lcd.print("llenar todas");
    delay(2500);
    limpiarLed();
    lcd.setCursor(0,0);
    lcd.print("las matrices");
    delay(2500);
    limpiarLed();
  }else{
    int x=0;
    int y=0;
    int cont=0;
    int cant=0;
    char letra = ' ';
    while (cant<10){ //Ciclo para recibir los barcos de Python
      letra = Serial.read();
      if (letra=='1'||letra=='2'||letra=='3'||letra=='4'||letra=='5'||letra=='6'||letra=='7'||letra=='8'||letra=='9'||letra=='0'){
        if (cont==0){
          Serial.println("Recibo coordenada y");
          y=atoi(&letra);
          cont++;
        }else{ //Ya recibi la segunda coordenada, puedo aumentar el contador de coordenadas recibidas
          x=atoi(&letra);
          Serial.println("Recibo coordenada x");
          cont++;
          cant++;
        }
        if(cont==2){
          cont=0;
          barcosB[x][y]=1;
          Serial.println("Comparo si di al target");
          if(barcosB[x][y]==tirosA[x][y]){ //Signiica que yo le di al jugador de python
            targetA++; 
            Serial.println("Di al target");
            Serial.println(targetA);
          }
        }
      }
    }
    
    cant = 0;
    cont = 0;
    letra = ' ';
    while (cant<10){ //Ciclo para recibir los disparos de python
      letra = Serial.read();
      if (letra=='1'||letra=='2'||letra=='3'||letra=='4'||letra=='5'||letra=='6'||letra=='7'||letra=='8'||letra=='9'||letra=='0'){
        if (cont==0){
          Serial.println("Recibo coordenada y");
          y=atoi(&letra);
          cont++;
        }else{ //Ya recibi la segunda coordenada, puedo aumentar el contador de coordenadas recibidas
          x=atoi(&letra);
          Serial.println("Recibo coordenada x");
          cont++;
          cant++;
        }
        if(cont==2){
          cont=0;
          tirosB[x][y]=1;
          Serial.println("Comparo si dio al target");
          if(tirosB[x][y]==barcosA[x][y]){ //Signiica que el jugador python me dio a mi
            targetB++; 
            Serial.println("Dio al target");
            Serial.println(targetB);
          }
        }
      }
    }
      Serial.println((String)targetB+(String)targetA);
      limpiarLed(); //Muestro los resultados
      lcd.setCursor(0,0);
      lcd.print("Enviando ");
      lcd.setCursor(0,1);
      lcd.print("resultados");
      delay(2600);
      limpiarLed();
      lcd.setCursor(0,0);
      lcd.print("a");
      lcd.setCursor(0,1);
      lcd.print("Jugador B");
      delay(2600);
      limpiarLed();
    
    if (targetB>targetA){ //Comparaciones para saber quien gana la partida jugada
      lcd.setCursor(0,0);
      lcd.print("La partida");
      lcd.setCursor(0,1);
      lcd.print("la gano:");
      delay(2600);
      limpiarLed();
      lcd.setCursor(0,0);
      lcd.print("Mr Python");
      lcd.setCursor(0,1);
      lcd.print("Jugador B");
      delay(2600);
      scoreB++;
    }else if(targetB<targetA){
      lcd.setCursor(0,0);
      lcd.print("La partida");
      lcd.setCursor(0,1);
      lcd.print("la gano:");
      delay(2600);
      limpiarLed();
      lcd.setCursor(0,0);
      lcd.print("Mr Arduino");
      lcd.setCursor(0,1);
      lcd.print("Jugador A");
      delay(2600);
      scoreA++;
    }else if (targetA=targetB){
      limpiarLed();
      lcd.setCursor(0,0);
      lcd.print("La partida fue");
      lcd.setCursor(0,1);
      lcd.print("un empate");
      delay(2600);
    }
    limpiarLed();
    lcd.setCursor(0,0);
    lcd.print("MostrandoPuntaje");
    lcd.setCursor(0,1);
    lcd.print("de la partida");
    delay(3500);
    limpiarLed();
    lcd.setCursor(0,0);
    targetA=targetA*100;
    targetB=targetB*100;
    lcd.print("Jugador A: "+(String)targetA);
    lcd.setCursor(0,1);
    lcd.print("Jugador B: "+(String)targetB);
    delay(2600);
  }
  limpiarLed();
  limpiarMatriz(1); //Limpio las matrices y los targets para la proxima partida
  limpiarMatriz(0);
  barcosLlenos = false;
  tirosLlenos = false;
  if(scoreA==2||scoreB==2) tmenu =0; //Ya alguno de los dos gana una partida, me salgo del menu del juego
}
