#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){ 
    char rotoare[5][27] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ",    //Rotor 1       
                 "AJDKSIRUXBLHWTMCQGZNPYFVOE",    //Rotor 2
                 "BDFHJLCPRTXVZNYEIWGAKMUSQO",    //Rotor 3
                 "ESOVPZJAYQUIRHXLNFTGKDCMWB",    //Rotor 4                 //retine valorile rotoarelor in pozitia default 
                 "VZBRGITYUPSDNHLXAWMJQOFECK"};   //Rotor 5                 //cu setarea inelului (A/default) (R1-R2-R3-R4-R5)            
  
     
    char reflector[3][27] = {"EJMZALYXVBWFCRQUONTSPIKHGD",    //Reflector A
                 "YRUHQSLDPXNGOKMIEBFZCWVJAT",    //Reflector B             //retine valorile reflectoarelor (A/B/C)                      
                 "FVPJIAOYEDRZXWGCTKUQSBNMHL"};   //Reflector C
    
    char iesire[1024];        //retine literele in forma criptata
    char intrare[1024];       //retine literele in forma criptata

    char notch[5][2] = {"X",    //Notch rotor 1
              "S",    //Notch rotor 2
              "M",    //Notch rotor 3                 //retine valorile pt fiecare rotor cand 
              "Q",    //Notch rotor 4                 //sa invarta urmator-ul rotor (R1-R2-R3-R4-R5)
              "K"};   //Notch rotor 5
             
    
    char plugboard[27]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};    //Plugboard in pozitia default
    int plgset;                       //retine valorile plugboard-ului (pt setarea AB pur si simplu interschimba aceste 2 valori)   
    printf("    ##########\n");
    printf("   #          #\n");
    printf("  @   ENIGMA   @\n");               //text cool si cateva instructiuni
    printf("   #          #\n");
    printf("    ##########\n");
    printf("   *Instructiuni:-Baga setarile \n");
    printf("                 -Bagi literele pentru a fi criptate\n");
    printf("                 -Literele criptare deja vor fi afisate toate pe ecran\n");
    printf("                 -Apasa tasta 0 pentru a oprii criptarea\n");

    printf("\n\n *Apasa ENTER* \n");
    getchar();          //asteapta tasta enter sa fie apasata
    system("cls");    //elibereaza ecran ul dupa ce ai apasat enter
    printf("  @@@@@@@@@@\n");
    printf(" @          @\n");
    printf("#   Setari   #\n");           //alt text cool
    printf(" @          @\n");
    printf("  @@@@@@@@@@\n");
    printf("\n\n  * Aveti setari custom pentru plugboard? (Daca NU dati 0 altfel dati nr. lor) *\n");
    scanf("%d",&plgset);          //citeste cate setari ai pt plugboard
    if(plgset==0)                           //dc e 0 nu schimba nimic si trece mai departe
      printf("!!! * Ati ales setari DEFAULT pentru PLUGBOARD (%s)*\n",plugboard);
    else {  int i;        //dc foloseste plugboard -ul intra pe acest 'if'
        char a, b, aux; 
        printf("Dati caracterele\n");
        for(i = 0; i < plgset; i++)
        {
          printf("* %d - Dati caracterele\n",i);        //plugboard ul pur si simplu interschimba cate 2 caractere intre ele
          scanf(" %c %c",&a, &b);  
          if(a > 96 && a < 123){
            a = a - 32;
          }
          if(b > 96 && b < 123){
            b = b - 32;
          }
          printf("%c - %c\n", a, b);
          aux = plugboard[a-65];
          plugboard[a-65] = plugboard[b-65];
          plugboard[b-65] = aux;
        }
      printf("@ - Noul tau plugboard arata asa: %s\n",plugboard);       //afiseaza plugboard-ul dupa interschimbari
      }
    
    int r1, r2, r3;
    char rflct;
    printf("\n\n* Dati ce reflector vreti sa folositi(A / B / C)\n");      //te intreaba ce reflector vrei sa folosesti
    scanf(" %c", &rflct);                                                   //si il citeste
    if(rflct > 96 && rflct < 123)
      rflct = rflct - 32;
    printf("Ati ales reflectorul %c\n",rflct);
    rflct = rflct - 65;                     //scand pt 65 pt ca de exemplu reflector-ul A(65 in ascii) se afla pe pozitia 0
                                        //a matricii


    printf("\n\n* Dati ce rotoare vreti sa folositi in ordinea dorita (I II III IV V) *\n\n");
    printf("* Dati primul rotor\n");
    scanf("%d", &r1);
    printf("* Dati al doilea rotor\n");                     //Iti spune sa dai rotoarele de la stanga la dreapta
    scanf("%d", &r2);                                        //si le citeste
    printf("* Dati al treilea rotor\n");
    scanf("%d", &r3);
  //  scanf("%d%d%d",&r1,&r2,&r3);
    printf("Ati ales %d %d %d\n",r1,r2,r3);
    r1--;
    r2--;                 //scand -1 pt ca de ex rotor-ul 1 se afla pe pozitia 0 in matrice
    r3--;
    
    printf("\n\n@ Dati setarile inelelor: @\n\n");
    char inel;
    int rotr1 = 0, rotr2 = 0,rotr3 = 0, i;
    
    printf("*Dati setarea inelului rotorului numarul 1\n");         //setarile inelului 'rotesc' matricea invers
    scanf(" %c", &inel);                                      
    if(inel > 96 && inel < 123)
      inel = inel - 32;                    // daca introduc litera mica o convertesc automat in litera mare
    if(inel != 'A')         //daca setarile sunt AAA nu se invarte nimic
    {
      for(i = 0; i < inel-65; i++)          //invartesc in functie de litera respectiva -A (ex pt Z invartesc de 25 ori Z(90)-A(65)=25)
      {
        char aux = rotoare[r1][25];
        memmove(rotoare[r1] + 1, rotoare[r1] + 0, 25);        //pt rotire am folosit memmove pt ca e mult mai usor
        rotoare[r1][0] = aux;
        rotr1--;          //rotr1 arata de cate ori sa invartit rotorul
      }
      if(rotr1 < 0)
        rotr1 = 25 + rotr1;   //pt ca un program nu poate accesa matricea cu '-' transform intr-o pozitie care poate fi citita
    }

    printf("*Dati setarea inelului rotorului numarul 2\n");
    scanf(" %c", &inel);
    if(inel > 96 && inel < 123)
      inel = inel - 32;
    if(inel != 'A')
    {
      for(i = 0; i < inel-65; i++)
      {
        char aux = rotoare[r2][25];
        memmove(rotoare[r2] + 1, rotoare[r2] + 0, 25);                  //identic ca la rotr 1
        rotoare[r2][0] = aux;
        rotr2--;
      }
      if(rotr2 < 0)
        rotr2 = 25 + rotr2;
    }

    printf("*Dati setarea inelului rotorului numarul 3\n");
    scanf(" %c",&inel);
    if(inel > 96 && inel < 123)
      inel = inel - 32;
    if(inel != 'A')
    {
      for(i = 0; i < inel-65; i++)
      {
        char aux = rotoare[r3][25];
        memmove(rotoare[r3] + 1, rotoare[r3] + 0, 25);                  //identic ca la rotr 1
        rotoare[r3][0] = aux;
        rotr3--;
      }
      if(rotr3 < 0)
        rotr3 = 25 + rotr3;
    }

    printf("\n\n   * Dati pozitia de inceput a fiecarui rotor *\n");
    char pozrtr;
    printf("Pozitie rotor 1:\n");             //pozitia rotor-ului roteste rotor-ul in fata
    scanf(" %c", &pozrtr);                     
    if(pozrtr > 96 && pozrtr < 123)               
      pozrtr = pozrtr-32;               // daca introduc litera mica o convertesc automat in litera mare
    if(pozrtr != 'A')       //daca setarile sunt AAA nu se invarte nimic
      for(i = 0; i < pozrtr-65; i++)          //invartesc in functie de litera respectiva -A (ex pt Z invartesc de 25 ori Z(90)-A(65)=25)
      {
        char aux = rotoare[r1][0];
        memmove(rotoare[r1]+0 ,rotoare[r1]+1, 25);      //foloses memmove la fel ca la setarile inelului
        rotoare[r1][25] = aux;  //r1 este pozitia in matricea de rotoare a primului rotor
        rotr1++;  //cand se invarte dau ++ pt a marii index ul pt numarul de invartiri
        if(rotr1 == 26)       //daca am rotit de 26 de ori inseamna ca rotor-ul a revenit la pozitia initiala 
          rotr1 = 0;            
      }
    

    printf("Pozitie rotor 2:\n");
    scanf(" %c",&pozrtr);
    if(pozrtr > 96 && pozrtr < 123)
    pozrtr = pozrtr-32;
    if(pozrtr != 'A')
      for(i = 0; i < pozrtr-65; i++)
      {
        char aux = rotoare[r2][0];
        memmove(rotoare[r2]+0, rotoare[r2]+1, 25);          //identic ca rotor-ul 1
        rotoare[r2][25] = aux;
        rotr2++;
        if(rotr2 == 26)
        rotr2 = 0;
      }


      printf("Pozitie rotor 3:\n");
    scanf(" %c",&pozrtr);
    if(pozrtr > 96 && pozrtr < 123)
      pozrtr = pozrtr-32;
    if(pozrtr != 'A')
      for(i = 0; i < pozrtr-65; i++)
      {
        char aux = rotoare[r3][0];
        memmove(rotoare[r3]+0, rotoare[r3]+1, 25);          //identic ca rotor-ul 1
        rotoare[r3][25] = aux;
        rotr3++;
        if(rotr3 == 26)
        rotr3 = 0;
      }

    printf("\n\n *Apasa ENTER* \n");
    getchar();
    system("cls");
    char litera = 50;

    while(litera != '0'){
      printf("     #######################\n");
      printf("   #                        #\n");
      printf("  @   DECRIPTARE / CRIPTARE  @\n");
      printf("   #                        #\n");
      printf("    ########################\n\n");
      printf("***Pozitie rotoare: %c %c %c\n\n", rotoare[r1][0], rotoare[r2][0], rotoare[r3][0]);  //debugging


      printf("*@ Mesaj introdus: %s\n\n", intrare);      //arata literele deja introduse
      printf("*# Mesaj criptat:  %s\n", iesire);         //arata literele deja criptate

      printf("\n\n\n *Da o litere pentru a fii criptata sau APASA 0 pentru a oprii programul*\n");
      scanf("%c ", &litera);       //da o litera
      
      if(litera == '0')          //daca am dat comanda de sf prog dau break;
        break;
      if(litera > 96 && litera < 123)     //dc este litera mica o convertesc automat in litera mare
        litera = litera-32;
      intrare[strlen(intrare)] = litera;      //pun litera in sir-ul 'intrare'
      intrare[strlen(intrare)+1] = '\0';      //pune '\0' la sfarsitul acestui sir altfel cand afisez sirul arata prostii

      
      
     if(rotoare[r2][0] == notch[r2][0])     //dc rotor-ul 2(mijloc) ajunge in pozitia notch invarte rotor-ul unu(stanga)
             {
              char aux = rotoare[r1][0];
              memmove(rotoare[r1]+0, rotoare[r1]+1, 25);    
              rotoare[r1][25] = aux;
              rotr1++;
              if(rotr1 == 26)
              rotr1 = 0;

              aux = rotoare[r2][0];
              memmove(rotoare[r2]+0, rotoare[r2]+1, 25);    //se invarte si pe el becouse enigma are double stepping   
             rotoare[r2][25] = aux;
             rotr2++;
              if(rotr2 == 26)
              rotr2 = 0;
             }
      if(rotoare[r3][0] == notch[r3][0])
        {char aux = rotoare[r2][0];
        memmove(rotoare[r2]+0, rotoare[r2]+1, 25);   //dc rotor-ul 3(dreapta/fast rotor) ajunge in pozitia notch 
        rotoare[r2][25] = aux;                       //invarte rotor-ul 2(mijloc)
        rotr2++;
        if(rotr2 == 26)
        rotr2 = 0;
        }
      char aux = rotoare[r3][0];
      memmove(rotoare[r3]+0, rotoare[r3]+1, 25);    //rotor-ul 3(dreapta) se invarte de fiecare data cand apas o tasta
      rotoare[r3][25] = aux;
      rotr3++;
      if(rotr3 == 26)
        rotr3 = 0;
         
      litera = plugboard[litera-65];        //Trece prin pluboard

      litera = rotoare[r3][litera-65];    //Trece prin rotor 3

      if(litera - 65 - rotr3 >= 0)
      litera = rotoare[r2][litera - 65 - rotr3];    //Trece prin rotor 2
      else litera = rotoare[r2][litera - rotr3 + 26 - 65];

      if(litera - 65 - rotr2 >= 0)
      litera = rotoare[r1][litera - 65 - rotr2];    //Trece prin rotor 1              //!!!!!Astea le explic in persoana pt ca
      else litera = rotoare[r1][litera - rotr2 + 26 - 65];                                    //este prea greu in text

      if(litera - 65 - rotr1 >= 0)
      litera = reflector[rflct][litera - 65 - rotr1];   //Trece prin reflector
      else litera = reflector[rflct][litera - rotr1 + 26 - 65];
                           //Acum inapoi din reflector
      
      aux = 0;                            
      for(i = 0; i < 26; i++)
        if(rotoare[r1][i] == litera + rotr1)
        {
          litera = 'A' + i;
          aux = 1;
          break;   
        }                   //Trece prin rotor 1
       if(aux == 0 && litera+rotr1 > 90)
          for(i = 0; i < 26; i++)
            if(rotoare[r1][i] == litera+rotr1-26)
              {
                litera = 'A' + i;
                 break;
               }

      aux = 0;
      for(i = 0; i < 26; i++)
        if(rotoare[r2][i] == litera+rotr2)
          {
            litera = 'A' + i;
            aux = 1;
            break; 
          }
          if(aux == 0 && litera+rotr2>90)
            for(i = 0; i < 26; i++)
              if(rotoare[r2][i] == litera+rotr2-26)         //Trece prin rotor 2
                {
                  litera = 'A' + i;
                  break;
                 }
      
      aux = 0;
      for(i = 0; i < 26; i++)
        if(rotoare[r3][i] == litera+rotr3)
          {
            litera = 'A' + i;
            aux = 1;
            break; 
          }
         
         if(aux == 0 && litera+rotr3>90){
          for(i = 0; i < 26; i++)
          if(rotoare[r3][i] == litera+rotr3-26)     //Trece prin rotor 3
          {litera = 'A' + i;
          break;
        }
      }
          
      litera = plugboard[litera-65];      //Trece prin plugboard
    
      iesire[strlen(iesire)] = litera;      //pune litera la sf sir-ului 'litera'
      iesire[strlen(iesire)+1] = '\0';      //pune '\0' la sfarsitul acestui sir altfel cand afisez sirul arata prostii
      system("cls");
     }
   system("cls");     //elibereaza ecran-ul
   printf("    ********************\n");
   printf("    *  Made by Mircea  *\n");      //text cool
   printf("    ********************\n");

   return 0;
}