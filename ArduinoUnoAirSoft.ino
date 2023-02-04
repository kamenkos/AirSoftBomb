#include "LedControl.h"

LedControl lc = LedControl(12, 13, 10, 1);
int esp = 0;
int esp2 = false;
boolean prefiks = false;
boolean pocetak = false;
boolean kraj = false;
boolean proveri = false;
boolean primio = false;
unsigned long sifre[256] = {10016807,22475252,12650091,94943668,74108942,30211277,21027545,27850894,28777939,37237731,23564449,45438177,84484511,84243042,34807988,67522515,11282343,26531729,23378849,63542613,96544312,44833185,14817723,28097179,27129580,61570945,27493101,64280293,93351825,75795351,74899118,26807844,33613518,21929268,60723827,84877640,18580994,14379167,68236602,74558829,90511972,50010695,31901410,97819353,59125500,76091746,16425243,19894112,55640200,47186367,36035019,45921164,70616713,60357950,61515676,97571493,64788135,47702217,72509551,50060904,62727743,13454678,38728561,65118031,58797824,80806864,41540983,24847410,65308250,78374934,95260309,24938990,65028641,82408034,67623877,17389825,50739085,27554537,25339443,44001687,77724134,99220096,44075629,48446517,74546537,11934210,61030122,37810421,86319474,28194319,60782193,37821130,43799513,32246894,19406766,26731586,84936725,17130357,48354444,92053153,83851513,24844908,86783877,32955832,70111140,67619371,23153196,80982397,77722306,90477915,81621631,86946248,30959758,32844196,91853649,18266318,83098145,16880404,14827985,20090415,25400262,59673563,16441594,89688017,67716395,94325984,44119135,75204535,38471010,61910969,24797963,60285380,62842085,33179868,28530776,32633830,93185706,56824715,10973685,25859921,17248604,81724853,34314751,58153060,51631639,77819799,44555643,53110692,11437341,69077017,16497983,93936120,10649098,78975323,65583461,11345238,12112292,58556775,84948919,24586145,92236128,43129517,36045822,86476774,70935238,56329115,25896230,44987847,64712388,81140543,21725229,21915415,27941365,88318741,72607845,74559598,13436556,30145162,71808641,87764957,40597393,81307227,37195291,30755561,59399262,22242390,29413512,71894906,97140628,58682440,32028155,16531980,39335749,55699934,13161643,12663545,73046064,18796026,53454689,71024171,49575260,77977311,59878841,79590418,38087712,91301821,84113003,34740045,52122671,89119406,78489566,92410567,54975835,47121227,76729682,16830228,19533827,87273393,72822778,51000625,22737356,57401880,14978006,60002777,12062784,69997450,93829889,34689347,78540560,88456322,69468892,31300581,98120106,38918987,77113765,64639812,22851412,67828025,58030200,35222781,13015701,54303465,24016866,32267525,74170971,14233507,85586699,69863111,13963264,73602345,11277844,11887638,50760826,41940014,65428658,97054858};
int cifre[8] = {0,0,0,0,0,0,0,0};
int sifra1 = 0;
int sifra2 = 0;
unsigned long sifra = 0;

int pin = 7;
int broj[50];
int indeks1;
int indeks2;
int ki = 0;
double dec=0;
int t = 0;
int brCif = 0;

boolean index = false;
boolean esp1 = false;
int esp0 = 0;

int sifreInd[10] = {0,0,0,0,0,0,0,0,0,0};   

int brIspravnih = 0;

int x = 0;
int i = 0;
int j = 0;
int ind = 0;
int br = 0;
int pom = 0;

boolean imamoBr = false;

struct Sifra {
  int ind = 0;
  boolean ispravna = false;
  int br = 0;
};

struct Sifra Sifre[15]; 

void(* resetFunc) (void) = 0; 

void sortiraj(int *niz, int n)
{
  int pom;
  for(int i = 0; i < n; i ++)
    for(int j = 0; j < n; j++)
      if(niz[j]<niz[j+1])
      {
        pom = niz[j];
        niz[j] = niz[j+1];
        niz[j+1] = pom;
      }  
}

long powint(int factor, unsigned int exponent)
{
    long product = 1;
    while (exponent--)
       product *= factor;
    return product;
}

void setup() {
  pinMode(pin,INPUT_PULLUP);
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop() {

  while(!primio)
  {
     delay(5);
  if(digitalRead(pin) == LOW)
  {
    Serial.println('1');
    if(proveri)
      br++;
    else br = 0;
    if(pocetak)
    {
      broj[ind++] = 1;
      
    }   
  }
  else if(digitalRead(pin) == HIGH)
  {
    Serial.println('0');
    if(!proveri)
      br++;
    
   
    if(pocetak)
    {
      broj[ind++] = 0;
      
    }
  }
    
  if(br == 9)
    proveri = true;
  if(br == 10)
  {
    proveri = false;
    pocetak = true;
    br = 0;
  }
  if(ind == 8)
  {
    
    pocetak = false;
    Serial.println(" ");
    for(int i = 7; i >= 0 ; i--)
      Serial.print(broj[i]);
    Serial.println("Smestio je broj u niz");
    for(int i = 7; i >= 0 ; i--)
    {
      dec+=broj[i]*powint(2,j++);
      Serial.print(dec);Serial.print("+");Serial.print(broj[i]);Serial.print("*");Serial.print("2 na");Serial.println(j-1);
      imamoBr = true;
    }
    j = 0;
    ind = 0;
  }
  if(imamoBr)
  {
    for(int i = 0; i < 15; i++)
    {
      if(Sifre[i].ind == 0)
      {
        Sifre[i].ind = dec;
        Serial.print("Smestili smo ");
        Serial.print(dec);
        Serial.print(" na ");
        Serial.print(i);
        Serial.println(". mesto");
        i = 15;
      }
      else if(Sifre[i].ind == dec)
      {
        Serial.print("Povecali smo brojac ");
        Serial.print(Sifre[i].ind);
        Serial.print(" na ");
        Serial.println(Sifre[i].br);
        Sifre[i].br++;
        if(Sifre[i].br > 3)
        {
          if(!Sifre[i].ispravna)
          {
            Sifre[i].ispravna = true;
            brIspravnih++;
          
          

          if(Sifre[i].ispravna)
            Serial.println("Ispravna");
          else Serial.println("Neispravna");
          Serial.println(brIspravnih);
          }
        }
        i = 15;
      }
    }
    dec = 0;
    imamoBr = false;
  }

  
  if(brIspravnih == 3)
  {
    for(int i = 0; i < 15; i++)
    {
      if(Sifre[i].ispravna && Sifre[i].ind < 4)
        brCif = Sifre[i].ind;
      Serial.println("");
      Serial.println(Sifre[i].ind);
      if(Sifre[i].ispravna && Sifre[i].ind > 3)
      {
        Serial.println("Ispravna");
        if(!index)
        {
          indeks1 = Sifre[i].ind;
          index = true;
        }
        else indeks2 = Sifre[i].ind;
      }
      else Serial.println("Neispravna");
      Serial.println(Sifre[i].br);
      Serial.println("");
    }
    Serial.println("KRAJ---------------------");
    Serial.println(brIspravnih);
    Serial.println(" ");
    Serial.println(indeks1);
    Serial.println(" ");
    Serial.println(indeks2);
    Serial.println(" ");
    Serial.println(sifre[indeks1]);
    Serial.println(" ");
    Serial.println(sifre[indeks2]);
    
    if (indeks1<indeks2)
    {
      pom = indeks1;
      indeks1 = indeks2;
      indeks2 = pom;
    }
    primio = true;
    Serial.println(" ");
Serial.println("kraj--------------------------------");
Serial.println(" ");
Serial.println(brCif);
Serial.println(brCif);
Serial.println(brCif);
     delay(5000);
  }
 
}
if(brCif == 1)
  brCif = 4;
else if(brCif == 2)
  brCif = 6;
else if(brCif == 3) 
  brCif = 8;


if(digitalRead(pin)==HIGH)
    esp0++;
if(esp0>10)
  esp1 = true;
if(esp1 && !esp2)
{
  sifra = sifre[indeks1];
  for(int i = 0; i < 8; i++)
    {
      cifre[i] = sifra%10;
      sifra/=10;
    }
    Serial.println(brCif);
    Serial.println("brCif");
    for(int i = brCif-1; i >= 0; i--)
      lc.setChar(0, t++, cifre[i], false);
    t=0;
    esp0 = 0;
    esp1 = false;
    esp2 = true;
    delay(5000);
}
if(brCif)
if(esp2 && esp1)
{
  sifra = sifre[indeks2];
  for(int i = 0; i < 8; i++)
  {
    cifre[i] = sifra%10;
    sifra/=10;
  }
  for(int i = brCif-1; i >= 0; i--)
    lc.setChar(0, t++, cifre[i], false);
  t=0;
  esp0 = 0;
  delay(5000);
  while(true)
  {
    if(digitalRead(pin)==HIGH)
      esp0++;
    if(esp0>10)
      resetFunc();
  }
}


}
