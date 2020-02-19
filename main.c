 #include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct{
char *turn;
int activated; //egale à 1 si la case est activée sinon 0
}caseinfo;


int stat[3][8];         // Définition de l'etat des points.
int role;               // Determine le role du joueur qui va jouer.
int moulin[3][8];       // Determine si un pion forme un moulin ou non.
int next;               // Empeche le joueur suivant de jouer en cas d'une erreur
int i,j;                // Pour les boucles
int counter=0;          // Passe le role au joueur suivant        //
int dest;               // Le mouvement desiré par le joueur
int pleft1=9;           // Les pion qui restent à deposer pour joueur 1
int pleft2=9;           // Les pion qui restent à deposer pour joueur 2
int err=0;              // Detecte les erreurs
int redeaten=0;         // Le nombre des pions supprimer par le joueur 1
int greeneaten=0;       // Le nombre des pions supprimer par le joueur 2
int down[3][8];         // La possibilité de deplacer le pion vers le carré précédent
int up[3][8];           // La possibilité de deplacer le pion vers le carré suivant
int clock[3][8];        // La possibilité de deplacer le pion dans le sens horraire
int counterclock[3][8]; // La possibilité de deplacer le pion dans le sens trigonometrique
int onBoard1=0;         // Le nombre des pions posés sur le tablier pour joueur 1
int onBoard2=0;         // Le nombre des pions posés sur le tablier pour joueur 1
int paralized1=0;       // Le nombre des pions paralysés pour joueur 1
int paralized2=0;       // Le nombre des pions paralysés pour joueur 2
int targetsqr;          // Coordonnes du points de la
int targetpos;          // destination après un mouvement*/
char jumpsqr;
char jumppos;



void possibleMvt()// Determiner les mouvement possibles pour chaque pion posé
{
    for(i=0;i<3;i++){
        for(j=0;j<8;j++){
            if((j<7 && stat[i][j+1]!=1 && stat[i][j+1]!=2)|| (j==7 && stat[i][0]!=1 && stat[i][0]!=2))
                clock[i][j]=1;
            else
                clock[i][j]=0;

            if((j>0 && stat[i][j-1]!=1 && stat[i][j-1]!=2)|| (j==0 && stat[i][7]!=1 && stat[i][7]!=2))
                counterclock[i][j]=1;
            else
                counterclock[i][j]=0;

            if (stat[i+1][j]!=1 && stat[i+1][j]!=2 && j%2==1 && i<2)
                up[i][j]=1;
            else
                up[i][j]=0;

            if (stat[i-1][j]!=1 && stat[i-1][j]!=2 && j%2==1 && i>0)
                down[i][j]=1;
            else
                down[i][j]=0;
        }
    }
}

void retry(){// la fonction de repettion qui initialise tout les cases à 0
for(i=0;i<3;i++){
    for(j=0;j<8;j++){
         stat[i][j]=0;
    }
}
}
void cl(){ //la fonction qui met à jour l'ecran
HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }

int molin(int a, int b ){ //detecter l'existance d'un moulin*
    for(i=0;i<3;i++){
            for(j=0;j<8;j++){
            moulin[i][j]=0;
    }
    }

    for (i =0 ; i<3 ; i++){

        if (stat[i][0]==stat[i][1] && stat[i][1]==stat[i][2] && stat[i][1]==1){
                moulin[i][0]=1;moulin[i][2]=1;moulin[i][1]=1;
        }
        if (stat[i][2]==stat[i][3] && stat[i][3]==stat[i][4] && stat[i][3]==1){
                moulin[i][2]=1 ; moulin[i][4]=1 ; moulin[i][3]=1;
                }
        if (stat[i][4]==stat[i][5] && stat[i][5]==stat[i][6] && stat[i][5]==1){
                moulin[i][4]=1 ; moulin[i][6]=1; moulin[i][5]=1;
                }
        if (stat[i][6]==stat[i][7] && stat[i][7]==stat[i][0] && stat[i][0]==1){
                moulin[i][6]=1 ; moulin[i][7]=1; moulin[i][0]=1;
                }
                }

        if (stat[0][1]==stat[1][1] && stat[1][1]==stat[2][1] && stat[1][1]==1){
            moulin[0][1]=1; moulin[1][1]=1 ; moulin[2][1]=1;

        }
        if (stat[0][3]==stat[1][3] && stat[1][3]==stat[2][3] && stat[1][3]==1){
            moulin[0][3]=1; moulin[1][3]=1 ; moulin[2][3]=1;

        }
        if (stat[0][5]==stat[1][5] && stat[1][5]==stat[2][5] && stat[1][5]==1){
            moulin[0][5]=1; moulin[1][5]=1 ; moulin[2][5]=1;

        }
        if (stat[0][7]==stat[1][7] && stat[1][7]==stat[2][7] && stat[1][7]==1){
            moulin[0][7]=1; moulin[1][7]=1 ; moulin[2][7]=1;
}

            //mou+=1;
            // else???
for (i =0 ; i<3 ; i++){

        if (stat[i][0]==stat[i][1] && stat[i][1]==stat[i][2] && stat[i][1]==2){
                moulin[i][0]=1;moulin[i][2]=1;moulin[i][1]=1;
        }
        if (stat[i][2]==stat[i][3] && stat[i][3]==stat[i][4] && stat[i][3]==2){
                moulin[i][2]=1 ; moulin[i][4]=1 ; moulin[i][3]=1;
                }
        if (stat[i][4]==stat[i][5] && stat[i][5]==stat[i][6] && stat[i][5]==2){
                moulin[i][4]=1 ; moulin[i][6]=1; moulin[i][5]=1;
                }
        if (stat[i][6]==stat[i][7] && stat[i][7]==stat[i][0] && stat[i][0]==2){
                moulin[i][6]=1 ; moulin[i][7]=1; moulin[i][0]=1;
                }
                }

        if (stat[0][1]==stat[1][1] && stat[1][1]==stat[2][1] && stat[1][1]==2){
            moulin[0][1]=1; moulin[1][1]=1 ; moulin[2][1]=1;

        }
        if (stat[0][3]==stat[1][3] && stat[1][3]==stat[2][3] && stat[1][3]==2){
            moulin[0][3]=1; moulin[1][3]=1 ; moulin[2][3]=1;

        }
        if (stat[0][5]==stat[1][5] && stat[1][5]==stat[2][5] && stat[1][5]==2){
            moulin[0][5]=1; moulin[1][5]=1 ; moulin[2][5]=1;

        }
        if (stat[0][7]==stat[1][7] && stat[1][7]==stat[2][7] && stat[1][7]==2){
            moulin[0][7]=1; moulin[1][7]=1 ; moulin[2][7]=1;
}

    return moulin[a][b];
}

caseinfo state(int pos1,int pos2){// changer l'etat des cases suivant l'etat de la matrice stat
    caseinfo util;


    if(stat[pos1-1][pos2-1]==1){
        util.turn="@@";
        util.activated=1;}
    else if (stat[pos1-1][pos2-1]==2){
        util.turn="++";
        util.activated=1;}


    else {
        util.activated=0;
        sprintf(util.turn, "%d", pos1*10+pos2);
    }

    return util;
}



void color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void drawgrid(){
    printf("                        ",stat[0][0]);
    color(15*(1-state(1,1).activated),state(1,1).activated*(stat[0][0]*2));printf("%s",state(1,1).turn);color(15,0);
    printf("_______________________________________");
    color(15*(1-state(1,2).activated),state(1,2).activated*(stat[0][1]*2));printf("%s",state(1,2).turn);color(15,0);
    printf("______________________________________");
    color(15*(1-state(1,3).activated),state(1,3).activated*(stat[0][2]*2));printf("%s\n",state(1,3).turn);color(15,0);
    printf("                        | \\_                                     |                                     _/ |\n");
    printf("                        |  \\_                                    |                                   _/   |\n");
    printf("                        |    \\_                                  |                                 _/     |\n");
    printf("                        |      \\_                                |                               _/       |\n");
    printf("                        |         ");
    color(15*(1-state(2,1).activated),state(2,1).activated*(stat[1][0]*2));printf("%s",state(2,1).turn);color(15,0);
    printf("_____________________________");
    color(15*(1-state(2,2).activated),state(2,2).activated*(stat[1][1]*2));printf("%s",state(2,2).turn);color(15,0);
    printf("____________________________");
    color(15*(1-state(2,3).activated),state(2,3).activated*(stat[1][2]*2));printf("%s",state(2,3).turn);color(15,0);
    printf("         |\n");
    printf("                        |         |                              |                              |         |\n");
    printf("                        |         |                              |                              |         |\n");
    printf("                        |         |                              |                              |         |\n");
    printf("                        |         |                              |                              |         |\n");
    printf("                        |         |         ");
    color(15*(1-state(3,1).activated),state(3,1).activated*(stat[2][0]*2));printf("%s",state(3,1).turn);color(15,0);
    printf("___________________");
    color(15*(1-state(3,2).activated),state(3,2).activated*(stat[2][1]*2));printf("%s",state(3,2).turn);color(15,0);
    printf("__________________");
    color(15*(1-state(3,3).activated),state(3,3).activated*(stat[2][2]*2));printf("%s",state(3,3).turn);color(15,0);
    printf("         |         |                            GREEN: %d left   Score:%d\n",pleft1,redeaten);

    for (i=0 ;i<15 ;i++){
        if (i==7){
            printf("                        ");
            color(15*(1-state(1,8).activated),state(1,8).activated*(stat[0][7]*2));printf("%s",state(1,8).turn );color(15,0);
            printf("________");
            color(15*(1-state(2,8).activated),state(2,8).activated*(stat[1][7]*2));printf("%s", state(2,8).turn );color(15,0);
            printf("_______");
            color(15*(1-state(3,8).activated),state(3,8).activated*(stat[2][7]*2));printf("%s", state(3,8).turn);color(15,0);
            printf("                                         ");
            color(15*(1-state(3,4).activated),state(3,4).activated*(stat[2][3]*2));printf("%s",state(3,4).turn);color(15,0);
            printf("________");
            color(15*(1-state(2,4).activated),state(2,4).activated*(stat[1][3]*2));printf("%s",state(2,4).turn);color(15,0);
            printf("_______");
            color(15*(1-state(1,4).activated),state(1,4).activated*(stat[0][3]*2));printf("%s\n",state(1,4).turn);color(15,0);
            }
            else
                printf("                        |         |         |                                         |         |         |\n");

    }
    printf("                        |         |         ");
    color(15*(1-state(3,7).activated),state(3,7).activated*(stat[2][6]*2));printf("%s",state(3,7).turn);color(15,0);
    printf("___________________");
    color(15*(1-state(3,6).activated),state(3,6).activated*(stat[2][5]*2));printf("%s",state(3,6).turn);color(15,0);
    printf("__________________");
    color(15*(1-state(3,5).activated),state(3,5).activated*(stat[2][4]*2));printf("%s",state(3,5).turn);color(15,0);
    printf("         |         |                            RED: %d left     Score:%d\n",pleft2, greeneaten);
    //printf("                        |         |         %s___________________%s__________________%s         |         |\n",state(3,7).turn,state(3,6).turn,state(3,5).turn);
    printf("                        |         |                              |                              |         |\n");
    printf("                        |         |                              |                              |         |\n");
    printf("                        |         |                              |                              |         |\n");
    printf("                        |         |                              |                              |         |\n");
    printf("                        |         ");
    color(15*(1-state(2,7).activated),state(2,7).activated*(stat[1][6]*2));printf("%s",state(2,7).turn);color(15,0);
    printf("_____________________________");
    color(15*(1-state(2,6).activated),state(2,6).activated*(stat[1][5]*2));printf("%s",state(2,6).turn);color(15,0);
    printf("____________________________");
    color(15*(1-state(2,5).activated),state(2,5).activated*(stat[1][4]*2));printf("%s",state(2,5).turn);color(15,0);
    printf("         |\n");
   // printf("                        |         %s_____________________________%s____________________________%s         |\n",state(2,7).turn,state(2,6).turn,state(2,5).turn);
    printf("                        |        _/                              |                              \\_        |\n");
    printf("                        |      _/                                |                                \\_      |\n");
    printf("                        |    _/                                  |                                  \\_    |\n");
    printf("                        |  _/                                    |                                    \\_  |\n");
    printf("                        ");
    color(15*(1-state(1,7).activated),state(1,7).activated*(stat[0][6]*2));printf("%s",state(1,7).turn);color(15,0);
    printf("_______________________________________");
    color(15*(1-state(1,6).activated),state(1,6).activated*(stat[0][5]*2));printf("%s",state(1,6).turn);color(15,0);
    printf("______________________________________");
    color(15*(1-state(1,5).activated),state(1,5).activated*(stat[0][4]*2));printf("%s\n",state(1,5).turn);color(15,0);
    //printf("                        %s/______________________________________%s_______________________________________%s\n",state(1,7).turn,state(1,6).turn,state(1,5).turn);


  }

void mov(int dest , int s , int p){

int sqr=s-1;
int pos=p-1;

if (dest==3) // UP mouvement
    {
    if (stat[sqr+1][pos]!=1 && stat[sqr+1][pos]!=2 && p%2==0 && sqr<2){

    targetsqr=sqr+1;
    targetpos=pos;
}
else{
    err=1;
    up[sqr][pos]=0;
}
    }
else if (dest==4) // DOWN  mouvement
    {
    if (stat[sqr-1][pos]!=1 && stat[sqr-1][pos]!=2 && p%2==0 && sqr>0){
        targetsqr=sqr-1;
        targetpos=pos;

    }
    else{
        err = 1;
        down[sqr][pos]=0;
    }
}

else if (dest==2) //COUNTERCLOCK MOVEMENT
{
    if ((stat[sqr][pos-1]!=1 && stat[sqr][pos-1]!=2)|| (pos==0 && stat[sqr][7]!=1 && stat[sqr][7]!=2)){
    targetsqr=sqr;
    if (pos!=0)
        targetpos=pos-1;
    else
        targetpos=7;
    }
    else{
        err=1;
        counterclock[sqr][pos]=0;
}
}

else if (dest==1) //CLOCK MOVEMENT
{
    if((stat[sqr][pos+1]!=1 && stat[sqr][pos+1]!=2)|| (pos==7 && stat[sqr][0]!=1 && stat[sqr][0]!=2)){
    clock[sqr][pos]=1;
    targetsqr=sqr;
    if(pos!=7)
        targetpos=pos+1;
    else
        targetpos=0;

    }
    else{
        err=1;
        clock[sqr][pos]=0;
}
}
if (!err){
    if(!role)
            stat[targetsqr][targetpos]=1;

    else
            stat[targetsqr][targetpos]=2;

    stat[s-1][p-1]=0;
    next=1;
    }
cl();
drawgrid();
}

void evaluate(){
    onBoard1=0;
    onBoard2=0;
    paralized1=0;
    paralized2=0;
    for(i=0;i<3;i++){
        for(j=0;j<8;j++){
            if (stat[i][j]==2){
                onBoard2++;
                if(down[i][j]==0 && up[i][j]==0 && clock[i][j]==0 && counterclock[i][j]==0){
                    paralized2++;
                }
            }
            else if (stat[i][j]==1){
                onBoard1++;
                if(down[i][j]==0 && up[i][j]==0 && clock[i][j]==0 && counterclock[i][j]==0){
                    paralized1++;
                }
            }
        }
    }

}


int main()
{
    again:
    srand(time(0));
    int choice;
    int choice2;
    char *choice3;
    int choice4;
    int k=0;
    int input1,input2,input3,input4;
    int moving;
    int win=0;
    role=rand()%2+1;
    int random=0;
    pleft1=9;
    pleft2=9;
    greeneaten=0;
    redeaten=0;

    if (1){
    do{
    go:
    cl();
    color(3,0);printf("\n\n\n\n\t\t _     _  _______  _     _  ______      __   __   ______  _     _  _   _____       __   __    _____   _____   _____   _______  _____ \n\t\t(_)   (_)(_______)(_)   (_)(______)    (__)_(__) (______)(_)   (_)( ) (_____)     (__)_(__)  (_____) (_____) (_____) (_______)(_____) \n\t\t(__)_ (_)   (_)   (__)_ (_)(_)__      (_) (_) (_)(_)__   (__)_ (_)() (_)___      (_) (_) (_)(_)   (_)(_)__(_)(_)__(_)   (_)  (_)___   \n\t\t(_)(_)(_)   (_)   (_)(_)(_)(____)     (_) (_) (_)(____)  (_)(_)(_)     (___)_    (_) (_) (_)(_)   (_)(_____) (_____)    (_)    (___)_ \n\t\t(_)  (__) __(_)__ (_)  (__)(_)____    (_)     (_)(_)____ (_)  (__)     ____(_)   (_)     (_)(_)___(_)( ) ( ) ( ) ( )  __(_)__  ____(_)\n\t\t(_)   (_)(_______)(_)   (_)(______)   (_)     (_)(______)(_)   (_)    (_____)    (_)     (_) (_____) (_)  (_)(_)  (_)(_______)(_____) \n\t\t\t \n\n\n\n\n\n");color(15,0);
    color(3,0);printf("                                    \t\t\t\t  __________________\n                                    \t\t\t\t /                  \\\n                                     \t\t\t\t|| 1-->Start Game  \ ||\n                                    \t\t\t\t \\__________________/\n\n\n\n\n\n");color(15,0);
    color(3,0);printf("                                      \t\t\t\t     __________\n                                      \t\t\t\t    /          \\\n                                      \t\t\t\t   || 2-->Help ||\n                                      \t\t\t\t    \\__________/\n\n\n\n\n\n");color(15,0);
    color(3,0);printf("                                      \t\t\t\t     __________\n                                      \t\t\t\t    /          \\\n                                      \t\t\t\t   || 3-->Exit ||\n                                      \t\t\t\t    \\__________/\n\n\n\n\n\n");color(15,0);
    color(3,0);printf("\n                                      \t\t\t\t     Your choice:");color(15,0);
    scanf("%d",&choice);
    cl();

    switch(choice){
    case 2:for (int i = 0 ; i<10 ; i++){
    printf("\n");

    }
    printf("\t\t\t\t\t _________________________________________________________________________ \n");
    printf("\t\t\t\t\t|The board consists of a grid with twenty-four intersections or points.   |\n");
    printf("\t\t\t\t\t|Each player has nine pieces, coloured green and red. Players try to      |\n");
    printf("\t\t\t\t\t|form 'mills'-three of their own men lined horizontally or vertically-    |\n");
    printf("\t\t\t\t\t|allowing a player to remove an opponent's man from the game.             |\n");
    printf("\t\t\t\t\t|A player wins by reducing the opponent to two pieces (where they         |\n");
    printf("\t\t\t\t\t|could no longer form mills and thus be unable to win), or by leaving     |\n");
    printf("\t\t\t\t\t|them without a legal move.                                               |\n");
    printf("\t\t\t\t\t|The game proceeds in three phases:                                       |\n\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|\t\t\tPlacing pieces                                    |\n");
    printf("\t\t\t\t\t|The game begins with an empty board. The players take turns placing      |\n");
    printf("\t\t\t\t\t| their men one per play on empty points. If a player is able to place    |\n");
    printf("\t\t\t\t\t|three of their pieces on contiguous points in a straight line, vertically|\n");
    printf("\t\t\t\t\t|or horizontally, they have formed a mill and may remove one of their     |\n");
    printf("\t\t\t\t\t|opponent's pieces from the board and the game, with the caveat that      |\n");
    printf("\t\t\t\t\t|a piece in an opponent's mill can only be removed if no other pieces     |\n");
    printf("\t\t\t\t\t|are available. After all men have been placed, phase two begins.         |\n\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|\t\t\tMoving pieces                                     |\n");
    printf("\t\t\t\t\t|Players continue to alternate moves, this time moving a man to an        |\n");
    printf("\t\t\t\t\t|adjacent point. A piece may not \"jump\" another piece. Players continue   |\n");
    printf("\t\t\t\t\t|to try to form mills and remove their opponent's pieces as in phase one. |\n");
    printf("\t\t\t\t\t|_________________________________________________________________________|\n\n\n");
    printf("\n\n\n\t\t\t\t\tPress 0 to return to the menu:");
    scanf("%d",&choice);
    goto go;

    break;
    case 1: //for (int i = 0 ; i<50 ; i++){
    //printf("\n");
    //}
    for (int i = 0 ; i<10 ; i++){
    printf("\n");
    }
    printf("\t\t\t\t\t");color(15,5);printf("1--> vs machine");color(15,0);
    printf("\t\t\t\t\t");color(15,5);printf("2--> vs player\n\n\n\n\n\n\n\n\n\n\n");color(15,0);
    printf("                                      \t\t\t\t     ");color(3,0);printf("Your choice:");color(15,0);
    scanf("%d",&choice2);
    if (choice2==1){
        cl();
        for (int i = 0 ; i<10 ; i++){
            printf("\n");
        }
        printf("\t\t\t\t\t");color(15,2);printf("1--> Easy");color(15,0);
        printf("\t\t\t\t\t\t\t");color(15,1);printf("2--> Medium");color(15,0);printf("\n\n\n\n\n\n\n\n\n\n\n");
        printf("                                      \t\t\t\t     Your choice:");
        scanf("%d",&choice4);
    }



    k=1;
    break;

    case 3:  printf("goodbye\n");break;
    default: printf("try again\n"); break;
    }
    }
    while(choice!=3 &&choice!=2 &&choice!=1);


}



    if (k){

        retry();
        cl();
        drawgrid();
    for (int i = 0 ; i<3 ; i++){
    printf("\n");
    }
    printf("\t\t\t\t\t\t      Player %d plays first\n",(role)%2+1);
    //printf("choose position");
    for (int i = 0 ; i<1 ; i++){
    printf("\n");
    }
    onBoard2=0;
    paralized2=0;


    do{
run:

        moving=(pleft1 == 0  &&  pleft2 == 0);
        next=0;

        err=0;
        if (!(choice2==1 && role==1)){
        if (moving)
            printf("\n\t\t\t\t\t\t         Moving phase:\n\n 1/ Move clockwise\t 2/ Move counter clockwise\t 3/ Move to following square\t 4/ Move to previous square \n\n");
        else
            printf("\n\t\t\t\t\t\t         Placing phase:\n");
        }
        if (role==1 && choice2==1 && (choice4==1 || (moving && choice4==2))){ //cas de vs machine facile relativement à la première phase
            input1=rand()%3+1;
            input2=rand()%8+1;
        }

        else if (role==1 && choice2==1 && choice4==2 && !moving){ //cas de vs machine moyen relativement à la première phase
        random=0;
        for (j=0;j<8;j++){for (i=0;i<3;i++){



        if (j%2==0 && stat[i][j]==2 && stat[i][(j+1)%8]==2 && stat[i][(j+2)%8]==0){
            input1=i+1;
            input2=(j+2)%8+1;
            break;
        }

        else if (j%2==0 && stat[i][(j+1)%8]==2 && stat[i][(j+2)%8]==2 && stat[i][j]==0){
            input1=i+1;
            input2=j+1;
            break;
        }

        else if (j%2==1 && stat[i][(j-1)%8]==2 && stat[i][(j+1)%8]==2 && stat[i][j]==0){
            input1=i+1;
            input2=j+1;
            break;
        }

        else if (j%2==1 && stat[(i+2)%3][j]==2 && stat[(i+1)%3][j]==2 && stat[i][j]==0){
            input1=i+1;
            input2=j+1;
            break;
        }

        else if (j%2==0 && stat[i][j]==1 && stat[i][(j+1)%8]==1 && stat[i][(j+2)%8]==0){
            input1=i+1;
            input2=(j+2)%8+1;
            break;
        }

        else if (j%2==0 && stat[i][(j+1)%8]==1 && stat[i][(j+2)%8]==1 && stat[i][j]==0){
            input1=i+1;
            input2=j+1;
            break;
        }

        else if (j%2==1 && stat[i][(j-1)%8]==1 && stat[i][(j+1)%8]==1 && stat[i][j]==0){
            input1=i+1;
            input2=j+1;
            break;
        }

        else if (j%2==1 && stat[(i+2)%3][j]==1 && stat[(i+1)%3][j]==1 && stat[i][j]==0){
            input1=i+1;
            input2=j+1;
            break;
        }
        else{
            random++;
    }



        }
    }
        if (random>=24){
            input1=rand()%3+1;
            input2=rand()%8+1;
        }
    }

        else if (err==0){
        printf("Enter square number (1,3)");
        scanf("%d",&input1);
        printf("Enter position (1,8)");
        scanf("%d",&input2);
        }
        possibleMvt();
        evaluate();
    if( pleft1 != 0  ||  pleft2 != 0 ){

        if(role-1 && pleft1>0 && stat[input1-1][input2-1]!=1 && stat[input1-1][input2-1]!=2){
            stat[input1-1][input2-1]=1;
            possibleMvt();
            evaluate();
            pleft1--;
            next=1;
            cl();
            drawgrid();
        }

        else if (pleft2>0 && stat[input1-1][input2-1]!=1 && stat[input1-1][input2-1]!=2){
            stat[input1-1][input2-1]=2;
            possibleMvt();
            evaluate();
            pleft2--;
            next=1;
            cl();
            drawgrid();

        }
        else {
        if (!(choice2==1 && role==1)){
        cl();
        drawgrid();
        printf("Wrong point. Choose another one!\n");
        }
        else
        printf("...");
        err=1;
        }

    }
    else if((stat[input1-1][input2-1]==1 && role-1) || (stat[input1-1][input2-1]==2 && role==1)){
        evaluate();//evaluation de notre table pour detecter les cases paralysées

        printf("\nMoves  ");
        if (role==1 && choice2==1)
            dest=rand()%4+1;
        else
            scanf ("%d",&dest);
        mov(dest , input1 , input2);
        possibleMvt();
        evaluate();
        if(err)
            printf("\nUnauthorised mouvement... Try again\n");

    }

    else{
        if (!(choice2==1 && role==1)){
        cl();
        drawgrid();
        printf("Wrong point. Choose another one!\n");}
    else
        printf("...");
        //err=1;
    }


eat:


        if((molin(input1-1,input2-1)==1 && err==0 && !moving) || (moving && molin(targetsqr,targetpos)==1 && err==0)){
            if (choice2==1 && role==1){
            input3=rand()%3+1;
            input4=rand()%8+1;
            }
            else if (choice2==1 && role==1){
                random=0;
                for (j=0;j<8;j++){for (i=0;i<3;i++){

                if (j%2==0 && stat[i][j]==1 && stat[i][(j+1)%8]==1 && stat[i][(j+2)%8]==0){
                    input3=i+1;
                    input4=(j+1)%8+1;
                    break;
                }

                else if (j%2==0 && stat[i][(j+1)%8]==1 && stat[i][(j+2)%8]==1 && stat[i][j]==0){
                    input3=i+1;
                    input4=(j+2)%8+1;
                    break;
                }

                else if (j%2==1 && stat[i][(j-1)%8]==1 && stat[i][(j+1)%8]==1 && stat[i][j]==0){
                    input3=i+1;
                    input4=(j+1)%8+1;
                    break;
                }

                else if (j%2==1 && stat[(i+2)%3][j]==1 && stat[(i+1)%3][j]==1 && stat[i][j]==0){
                    input3=(i+1)%3;
                    input4=j+1;
                    break;
                }
                 else{
                    random++;
                }
            }
        }
        if (random>=24){
            input3=rand()%3;
            input4=rand()%8;

        }
    }

            else
                scanf("%d%d",&input3,&input4);

            if (stat[input3-1][input4-1]!=stat[input1-1][input2-1] && stat[input3-1][input4-1]!=0 && molin(input3-1,input4-1)!=1){

                if(stat[input3-1][input4-1]==1)
                        greeneaten++;
                else if(stat[input3-1][input4-1]==2)
                        redeaten=redeaten+1;

                stat[input3-1][input4-1]=0;
                cl();
                drawgrid();
                next=1;
                }
            else{
                if (!(choice2==1 && role==1)){
                    cl();
                    drawgrid();
                    printf("\nYou can't remove that. Choose another one.\n");
                    }
                else
                    printf("...");

                next=0;
                goto eat;
                }
                }
    if (!(choice2==1 && role==2)){
        printf("\n                        \t\t\t\tAffected point: %d%d\t\t\t\n",input1,input2);
        if(moving)
            printf("\n                        \t\t\t\tTarget point: %d%d\n\n",targetsqr+1,targetpos+1);
        }

    if(next)
        role=(role+1)%2;

    // definission du vainqueur:
    if((onBoard1<=2 || onBoard1-paralized1==0) && moving==1)
        win=2;
    else if ((onBoard2<=2 || onBoard2-paralized2==0) && moving==1)
        win=1;

    if(win==1) //condition pour que le joueur 1 gagne
        {
        cl();
        color(0,2);printf("\n\n\n _____ _   _  _____   _    _ _____ _   _  _   _  ___________   _____ _____ \n");
        printf("|_   _| | | ||  ___| | |  | |_   _| \\ | || \\ | ||  ___| ___ \\ |_   _/  ___|\n");
        printf("  | | | |_| || |__   | |  | | | | |  \\| ||  \\| || |__ | |_/ /   | | \\ `--. \n");
        printf("  | | |  _  ||  __|  | |/\\| | | | | . ` || . ` ||  __||    /    | |  `--. \\\n");
        printf("  | | | | | || |___  \\  /\\  /_| |_| |\\  || |\\  || |___| |\\ \\   _| |_/\\__/ /\n");
        printf("  \\_/ \\_| |_/\\____/   \\/  \\/ \\___/\\_| \\_/\\_| \\_/\\____/\\_| \\_|  \\___/\\____/ \n\n\n");
        printf("                 ______ _       _____   _____________   __                 \n");
        printf("                 | ___ \\ |     / _ \\ \\ / /  ___| ___ \\ /  |                \n");
        printf("                 | |_/ / |    / /_\\ \\ V /| |__ | |_/ / `| |                \n");
        printf("                 |  __/| |    |  _  |\\ / |  __||    /   | |                \n");
        printf("                 | |   | |____| | | || | | |___| |\\ \\  _| |_               \n");
        printf("                 \\_|   \\_____/\\_| |_/\\_/ \\____/\\_| \\_| \\___/               \n");color(15,0);
        system("pause");
        //scanf("%s",choice3);
        pleft1=9;
        pleft2=9;
        goto go;
        }
    else if(win==2){
        cl();
        color(0,4);printf("\n\n\n _____ _   _  _____   _    _ _____ _   _  _   _  ___________   _____ _____ \n");
        printf("|_   _| | | ||  ___| | |  | |_   _| \\ | || \\ | ||  ___| ___ \\ |_   _/  ___|\n");
        printf("  | | | |_| || |__   | |  | | | | |  \\| ||  \\| || |__ | |_/ /   | | \\ `--. \n");
        printf("  | | |  _  ||  __|  | |/\\| | | | | . ` || . ` ||  __||    /    | |  `--. \\\n");
        printf("  | | | | | || |___  \\  /\\  /_| |_| |\\  || |\\  || |___| |\\ \\   _| |_/\\__/ /\n");
        printf("  \\_/ \\_| |_/\\____/   \\/  \\/ \\___/\\_| \\_/\\_| \\_/\\____/\\_| \\_|  \\___/\\____/ \n\n\n");
        printf("                 ______ _       _____   _____________   _____              \n");
        printf("                 | ___ \\ |     / _ \\ \\ / /  ___| ___ \\ / __  \\             \n");
        printf("                 | |_/ / |    / /_\\ \\ V /| |__ | |_/ / `' / /'             \n");
        printf("                 |  __/| |    |  _  |\\ / |  __||    /    / /               \n");
        printf("                 | |   | |____| | | || | | |___| |\\ \\  ./ /___             \n");
        printf("                 \\_|   \\_____/\\_| |_/\\_/ \\____/\\_| \\_| \\_____/             \n");color(15,0);
        scanf("%s",&choice3);
        goto go;
            }
if (!(choice2==1 && role==1))
        printf("\n\t\t\t\t\t\t\t     Player %d\n",role+1);
        counter++;

    } while (input1>0 && input1<=3 && input2>0 && input2<=8);
    if(!(input1>0 && input1<=3 && input2>0 && input2<=8)){
        cl();
        printf("Quit?:1/0");
        scanf("%d",&choice4);
        if (choice4==1)
            goto again;
        else{
            cl;
            drawgrid();
            printf("Incorrect values");
            goto run;

        }
        }
    }
    return 0;
}
