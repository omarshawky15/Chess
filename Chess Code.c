#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>
// Changes the color of the text in CMD (Taken From An External Website)
void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
int g[2] = { 0 , 0};
int count = 1;
int countking=0;
char black[] = {"pkrnbq_"};
char white[] = {"PKRNBQ."};
char pieces[2][6] = {"pkrnbq" , "PKRNBQ"};
char players[2][20] = {"Player2(Black)" ,"Player1(White)" } , playersColor [] = {"bw"};
char temp [6];
char place[8][8] ={("rnbqkbnr") , ("pppppppp"),("._._._._"),("_._._._."),("._._._._"),("_._._._."),("PPPPPPPP") , ("RNBQKBNR")};
char placeColors[8][8] ={("._._._._"),("_._._._."),("._._._._"),("_._._._."),("._._._._"),("_._._._."),("._._._._"),("_._._._.")};
char graveyard [2][16] = {'\0'} ;
char moves[10000][6] = {'\0'};
int rowlast , columnlast;
int kingPlace[2][2] = {{0,4} , {7,4}};
int rk = 0 , ck = 4, rK = 7 , cK = 4;
int checkcolor (char x){
 int i;
    for (i=0;i<7;i++){
            if (black[i] == x){
                return 0;
            }
           else if (white[i] == x){
                return 1;
            }
     }
     return 2;
}
//Removes the extra entries after space so the game don’t skip a turn
void clear (){
    char c;
while((c = getchar()) != '\n' && c != EOF);
}
//Outputs the pored and its pieces on the screen
void printc(){
    int i , j,k,m=0,n=0 , check = 0;
    SetColor(3);
    printf ("\t    A\t    B\t    C\t    D\t    E\t    F\t    G\t    H\t         *****White GraveYard*****\n");
    SetColor(1);
    printf("        #################################################################        #########################\n");
    for (i=0 ; i<8 ; i++){
        if (i==4){
            n++; m=0;
        }
        for (j=0 ; j<3 ; j++){
            if(j%2 == 1){
                SetColor(3);
                printf ("    %d",i+1);
                SetColor(1);
                printf ("   #");
            }else{
                SetColor(1);
                 printf ("        #");}
          for (k=0 ; k<8 ; k++){
              if(j%2 == 1){
                printf ("   ");
                //SetColor(3);
                check = checkcolor(place[i][k]);
               switch (check){
                    case 0 :
                    SetColor(15);
                    break;
                    case 1 :
                    SetColor(4);
                    break;
                }
                printf ("%c",place[i][k]);
                SetColor(1);
                printf ("   #");
              }else printf ("       #");
          } printf ("  ");

          if(j%2 == 1){
            SetColor(3);
            printf ("%d",i+1);
            }else printf(" ");
            SetColor(1);
          printf ("     #");

        for(k=0 ; k<4 ; k++){
            if(j%2 == 1 && graveyard[n][m] != '\0' && m < g[n]){
                check = checkcolor(graveyard[n][m]);
               switch (check){
                    case 0 :
                    SetColor(15);
                    break;
                    case 1 :
                    SetColor(4);
                    break;
                }
                printf("  %c  ",graveyard[n][m++]);}
            else printf ("     ");
            SetColor(1);
            printf("#");}
          printf("\n");
        }
        if(i==3){
            printf("        #################################################################");
            SetColor(3);
            printf ("        *****Black Graveyard*****\n");
        } else printf("        #################################################################        #########################\n");
    }
    SetColor(3);
    printf ("\t    A\t    B\t    C\t    D\t    E\t    F\t    G\t    H\t     \n");
}
//Checks if the desired piece belongs to the color of the player which has the turn to play or not
int checkf (int r2 , int c2 , int turn ){
    int i;
    for (i=0;i<6;i++){
            if (playersColor[(count+turn)%2] == 'b'){
                    if (black[i] == place[r2][c2]){
                            return 0;
                    }
     }      else if (playersColor[(count+turn)%2] == 'w'){
         if (white[i] == place[r2][c2]){
                            return 0;
                    }
     }
     } return 1;
}
//moves a piece from r1,c1 to r2,c2 .
void placef (int r1 , int c1 , int r2 , int c2){
    place[r2][c2] = place [r1][c1];
    place[r1][c1] = placeColors[r1][c1];
}
//if the move was invalid it sacns for new move
void invalid ( int *r1 , int *c1 , int *r2 , int *c2){
    printf ("Invalid Move ,Enter Move Again %s\n",players[abs(count%2-1)]);
            scanf ("%s",temp);
            clear();
            *r1 = temp[1]-49;
            *r2 = temp[3] - 49;
            *c1 = temp[0]- 65;
            *c2 = temp[2] - 65;
}
//see if theres a fifth charcter entered and promotes the pawn to it
void promotion (int r2 , int c2 ){
        int flag = 0 , i;
        char c[100];
        while(flag == 0){
            for (i=2;i<6;i++){
                if (white[i] == temp[4]){
                    flag =1;
                    break ;
                }}
            if (flag ==0){
                printf ("Invalid Promotion , Please Enter A Suitable piece Capitalized \nB = BISHOP\nR = Rook \nN = Knight\nK = King\nQ = Queen\n");
                scanf("%s" , c);
                temp[4] = c[0];
            }
            else if (flag == 1){
                if (count%2 == 1){
                    place[r2][c2] = temp[4];
                }
                else place[r2][c2] = temp[4] +32 ;
            }
    }
}
//undone a move .
void undo(int r1 , int c1 , int r2 , int c2 ){
   if(count != 1){
    r1 = moves[count][1] - 49;
    r2 = moves[count][3] - 49;
    c1 = moves[count][0] - 65;
    c2 = moves[count][2] - 65;
    placef (r2 ,c2 ,r1 ,c1);
    if (moves[count][5]!= ' ' ){
        place[r2][c2] = moves[count][5];
        graveyard[count%2][--g[count%2]] = '\0';
    }
    if (moves[count][4]!= ' '){
        place[r1][c1] = pieces[count%2][0];
    }

    count--;
   }
    else printf("No Moves To Undo\n");
}
//redone a move .
void redo (int r1 , int c1 , int r2 , int c2 ){
    if(moves[count+1][0] != '\0'){
    r1 = moves[count+1][1] - 49;
    r2 = moves[count+1][3] - 49;
    c1 = moves[count+1][0] - 65;
    c2 = moves[count+1][2] - 65;
    placef (r1 ,c1 ,r2 ,c2);
    if (moves[count+1][5]!= ' '){
        graveyard[(count+1)%2][g[(count+1)%2]++] = moves[count+1][5] ;
    }
    if (moves[count+1][4]!= ' '){
        place[r2][c2] = pieces[count%2][0];
    }
    count++;
    }
    else printf ("No Moves Found To Redo\n");
}
int bpawn (int r1 , int c1 , int r2 , int c2,int checker,int turn ){
    int check =0;
    check = checkf (r2,c2,turn);
    if (r2== r1 +1 && c2 == c1 && (place[r1+1][c1]=='.' || place[r1+1][c1]=='_')){
        return rook(r1,c1,r2,c2 ,checker,turn);
    }
    else if (r2 == r1 +2 && r1 == 1 && c2==c1 && (place[r1+1][c1]=='.' || place[r1+1][c1]=='_') && (place[r1+2][c1]=='.' || place[r1+2][c1]=='_')){
        return rook(r1,c1,r2,c2 ,checker,turn);
    }
    else if (r2 ==r1 +1 && (c2 == c1+1 && (place[r1+1][c1+1]!='.' && place[r1+1][c1 +1]!='_')) || (c2 == c1-1 && place[r1+1][c1-1]!='.' && place[r1+1][c1 -1]!='_') ){
        return bishop(r1,c1,r2,c2 ,checker,turn);
    }else return 0;
}
int wpawn (int r1 , int c1 , int r2 , int c2 ,int checker,int turn  ){
    int check =0;
    check = checkf (r2,c2,turn);
    if (r2== r1 -1 && c2 == c1 && (place[r1-1][c1]=='.' || place[r1-1][c1]=='_')){
        return rook(r1,c1,r2,c2 ,checker,turn);
    }
    else if (r2 == r1 -2 && r1 == 6 && c2==c1 && (place[r1-1][c1]=='.' || place[r1-1][c1]=='_') && (place[r1-2][c1]=='.' || place[r1-2][c1]=='_')){
        return rook(r1,c1,r2,c2 ,checker,turn);
    }
    else if (r2 ==r1 -1 && (c2 == c1+1 && (place[r1-1][c1+1]!='.' && place[r1-1][c1 +1]!='_')) || (c2 == c1-1 && place[r1-1][c1-1]!='.' && place[r1-1][c1 -1]!='_') ){
        return bishop(r1,c1,r2,c2 ,checker,turn);
    }else return 0;
}
int rook(int r1,int c1 ,int r2 ,int c2,int checker,int turn ){
int i ,check =0 ;
if (r2 == r1 && c2 == c1) return 0 ;
check = checkf(r2,c2,turn);
if ((r2 == r1 && c2 != c1)|| (r2 != r1 && c2 == c1) ){
        if(r1<r2){
            for(i=r1+1;i<r2;i++){
                if(place[i][c1]!='.' && place[i][c1]!='_'){
                return 0;
                }
                }}
        else if(c1<c2){
                for(i=c1+1;i<c2;i++){
            if(place[r1][i]!='.' && place[r1][i]!='_'){
            return 0;
            }
            }}
        else if(r1>r2){
            for(i=r1-1;i>r2;i--){
                if(place[i][c1]!='.' && place[i][c1]!='_'){
                    return 0;
        }
        }}
        else if(c1>c2){
        for(i=c1-1;i>c2;i--){
            if(place[r1][i]!='.' && place[r1][i]!='_'){
            return 0;
            }}}

        if (place[r2][c2]!='.' && place[r2][c2]!='_' && check == 0){
                return 0;
        }
         if(checker==0){
              if(place[r2][c2]!='.' && place[r2][c2]!='_' && check==1){
                          temp[5] = place [r2][c2];graveyard[(count+1)%2][g[(count+1)%2]++] = place [r2][c2];
        }
        placef ( r1 ,c1 ,r2 ,c2);
        return 1;}else return 1;
    }else return 0;
}
int knight (int r1,int c1 ,int r2 ,int c2,int checker,int turn ){
    int flag = 0 , check =0;
    if (r2 == r1 && c2 == c1) return 0 ;
    check = checkf (r2,c2,turn);
    if (r2 ==r1 -1 || r2 == r1 +1){
        if (c2 == c1 -2 || c2 == c1 +2){
            flag =1 ;
        }
    }
    if (r2 ==r1 -2 || r2 == r1 +2){
        if (c2 == c1 -1 || c2 == c1 +1){
            flag =1 ;
        }
    }
    if (flag == 1){
        if (place[r2][c2]!='.' && place[r2][c2]!='_'){
           if(check == 1){
                    if(checker==0){
                        temp[5] = place [r2][c2];graveyard[(count+1)%2][g[(count+1)%2]++] = place [r2][c2];
                        placef ( r1 ,c1 ,r2 ,c2);
                        return 1;}else return 1;
            }
        }
        else if (place[r2][c2]=='.' || place[r2][c2]=='_'){
                if(checker==0){
            placef ( r1 ,c1 ,r2 ,c2);
            return 1;}else return 1;
        }
        else return 0;
    }
    return 0;
}
int bishop(int r1,int c1 ,int r2 ,int c2,int checker,int turn ){
    int i;
    int check ;
    if (r2 == r1 && c2 == c1) return 0 ;
    check = checkf(r2,c2,turn);
    if(abs(c2-c1) == abs(r2-r1)){

    if(r2>r1 && c2>c1 )
    {
        for(i=1;i<r2-r1;i++){
                if (place[r1+i][c1+i]!='.' && place[r1+i][c1+i]!='_' ){
                return 0;
        }}
    }
    else if(r2>r1 && c2<c1 ){
        for(i=1;i<r2-r1;i++){
            if (place[r1+i][c1-i]!='.' && place[r1+i][c1-i]!='_' ){
                return 0;
            }}
    }
    else if(r2<r1 && c2>c1){
        for(i=1; i<r1-r2;i++){
                if (place[r1-i][c1+i]!='.' && place[r1-i][c1+i]!='_'){
                return 0;
            }}
    }
    else if(r2<r1 && c2<c1 ){
        for(i=1; i<r1-r2;i++){
                if(place[r1-i][c1-i]!='.' && place[r1-i][c1-i]!='_'){
                return 0;
            }}
    }
    if (place[r2][c2]!='.' && place[r2][c2]!='_' && check == 0){
                return 0;
        }
      if(checker==0){
              if(place[r2][c2]!='.' && place[r2][c2]!='_' && check==1){
                temp[5] = place [r2][c2];graveyard[(count+1)%2][g[(count+1)%2]++] = place [r2][c2];}
        placef ( r1 ,c1 ,r2 ,c2);
        return 1;}else return 1;
    }
    else return 0;
}
int queen (int r1,int c1 ,int r2 ,int c2,int checker,int turn){
    if(r1==r2&&c2==c1)return 0;
    if(abs(c2-c1) == abs(r2-r1)){
    return bishop(r1,c1,r2,c2 ,checker,turn);}
    else if((r2 == r1 && c2 != c1)|| (r2 != r1 && c2 == c1)){return rook(r1,c1,r2,c2 ,checker,turn);}
    else return 0 ;
}
int king(int r1,int c1 ,int r2 ,int c2,int checker,int checkking,int turn ){
    int value=0, i,j;
    char x[2];
    char y[2];
    for (i=0 ; i<=7 ; i++){
            for (j=0 ; j<=7 ; j++){
        if ((count+turn)%2 == 1){
            switch (place[i][j]) {
            case 'r':
                value= rook(i ,j ,r2 ,c2 ,checker,turn);
                break;
            case 'n':
                value= knight(i ,j ,r2 ,c2 ,checker,turn);
                break;
            case 'b':
                value=bishop(i ,j ,r2 ,c2 ,checker,turn);
                break;
            case 'q':
                value=queen(i ,j ,r2 ,c2 ,checker,turn);
                break;
            case 'p':
               x[0]=place[r2][c2]; place[r2][c2] = 'P';
               value= bpawn(i ,j ,r2 ,c2 ,checker,0);
               place [r2][c2] = x[0];
                break;
            case 'k' :
                if(countking>=1){//place[r2][c2]=y[0];
                        break;}
                else{
                countking++;
                y[0]=place[r2][c2];
               value= king(i ,j ,r2 ,c2 ,checker,1,turn);
               break;}
                }}
            else {
                switch (place[i][j]) {
            case 'R':
               value= rook(i ,j ,r2 ,c2 ,checker,turn);
                break;
            case 'N':
               value= knight(i ,j ,r2 ,c2 ,checker,turn);
                break;
            case 'B':
                 value=bishop(i ,j ,r2 ,c2 ,checker,turn);
                    break;
            case 'Q':
                value=queen(i ,j ,r2 ,c2 ,checker,turn);
                break;
            case 'P':
                x[0]=place[r2][c2]; place[r2][c2] = 'p';
                value= wpawn(i ,j ,r2 ,c2 ,checker,0);
                place [r2][c2] = x[0];
                break;
            case 'K' :
                if(countking>=1){//place[r2][c2]=y[0];
                        break;}
                else{
                countking++;
                y[0]=place[r2][c2];
               value= king(i ,j ,r2 ,c2 ,checker,1,turn);
               break;}
            }}
        if (value == 1){
            break ;
        }}
        if (value == 1){
            break ;
        }
    }
    countking=0;
   if (value==1)return 0;
    else{
    if(abs(c2-c1) == abs(r2-r1) && abs(r2-r1)==1 && abs(c2-c1)==1){
    return bishop(r1,c1,r2,c2 ,checkking,turn);}
    else if(((r2 == r1 && c2 != c1)|| (r2 != r1 && c2 == c1)) && (abs(r2-r1)==1 || abs(c2-c1)==1 )){return rook(r1,c1,r2,c2 ,checkking,turn);}
    else return 0 ;}
    }
//this function check if the move makes the king check or not
int checkmatef (int turn,int stale2){
    int value=0, i,j,checker=1;
    for (i=0 ; i<=7 ; i++){
            for (j=0 ; j<=7 ; j++){
        if ((count+turn)%2 == 0){
            switch (place[i][j]) {
            case 'r':
                value= rook(i ,j ,rK ,cK ,checker,turn);
                break;
            case 'n':
                value= knight(i ,j ,rK ,cK ,checker,turn);
                break;
            case 'b':
                value=bishop(i ,j ,rK ,cK ,checker,turn);
                break;
            case 'q':
                value=queen(i ,j, rK ,cK ,checker,turn);
                break;
            case 'p':
               value= bpawn(i ,j ,rK ,cK ,checker,turn);
                break;
            case 'k' :
               value= king(i ,j ,rK ,cK ,checker,1,turn);
               break;
                }}
            else {
                switch (place[i][j]) {
            case 'R':
               value= rook(i ,j ,rk ,ck ,checker,turn);
                break;
            case 'N':
               value= knight(i ,j ,rk ,ck ,checker,turn);
                break;
            case 'B':
                 value=bishop(i ,j ,rk ,ck ,checker,turn);
                    break;
            case 'Q':
                value=queen(i ,j ,rk ,ck ,checker,turn);
                break;
            case 'P':
                value= wpawn(i ,j ,rk ,ck ,checker,turn);
                break;
            case 'K' :
               value= king(i ,j ,rk ,ck ,checker,1,turn);
               break;
            }}
        if (value == 1){

            break ;
        }}
        if (value == 1){
            break ;
        }
    }
    if (value == 1){
            if (stale2==0){
        printf ("CHECK !!!\n");
        rowlast=i;
        columnlast =j;
        return 1;}else return 1;
    }
    else return 0;
}
//this function check if any piece can stop the check on the king or not !
int lastcheck(int turn){
    int i , j , value =0, checker = 1;
    int k=0 , maxx=0;
    int rking ,cking ;
    if((count+turn)%2 == 0){
        rking=rk; cking=ck;
    }else{
        rking=rK; cking=cK;
    }

    if(abs(rking-rowlast)==abs(cking-columnlast)){
         maxx=abs(rking-rowlast);}

    else if(rking!=rowlast && cking==columnlast ){
         maxx = abs(rking-rowlast);}

    else if(rking==rowlast && cking!=columnlast){
         maxx = abs(cking-columnlast);}

    for(k=0;k<maxx;k++){
    for (i=0 ; i<=7 ; i++){
            for (j=0 ; j<=7 ; j++){
        if ((count+turn)%2 == 0){
            switch (place[i][j]) {
            case 'r':
                value= rook(i ,j ,rowlast ,columnlast,checker,turn);
                break;
            case 'n':
                value= knight(i ,j ,rowlast ,columnlast,checker,turn);
                break;
            case 'b':
                value=bishop(i ,j ,rowlast ,columnlast ,checker,turn);
                break;
            case 'q':
                value=queen(i ,j,rowlast ,columnlast ,checker,turn);
                break;
            case 'p':
               value= bpawn(i ,j ,rowlast ,columnlast ,checker,turn);
                break;
            case 'k' :
 if((abs(i-rowlast) == abs(j-columnlast) && abs(i-rowlast)==1 && abs(j-columnlast)==1) || (((i == rowlast && j != columnlast)|| (i != rowlast && j == columnlast)) && (abs(i-rowlast)==1 || abs(j-columnlast)==1 ))){
                    value=  king(i ,j ,rowlast ,columnlast ,checker,1,turn);}
                break;
                }}
            else {
                switch (place[i][j]) {
            case 'R':
               value= rook(i ,j ,rowlast ,columnlast ,checker,turn);
                break;
            case 'N':
               value= knight(i ,j ,rowlast ,columnlast ,checker,turn);
                break;
            case 'B':
                 value=bishop(i ,j ,rowlast ,columnlast ,checker,turn);
                    break;
            case 'Q':
                value=queen(i ,j ,rowlast ,columnlast ,checker,turn);
                break;
            case 'P':
                value= wpawn(i ,j ,rowlast ,columnlast ,checker,turn);
                break;
            case 'K' :
                if((abs(i-rowlast) == abs(j-columnlast) && abs(i-rowlast)==1 && abs(j-columnlast)==1) || (((i == rowlast && j != columnlast)|| (i != rowlast && j == columnlast)) && (abs(i-rowlast)==1 || abs(j-columnlast)==1 ))){
                   value=  king(i ,j ,rowlast ,columnlast ,checker,1,turn);}

                break;
            }}
        if (value == 1){
          return 1;
    }}}
     if(abs(rking-rowlast)==abs(cking-columnlast)){
                if(rking>rowlast){
                    rowlast++;
                }if(rking<rowlast){
                    rowlast--;
                }if(cking>columnlast){
                    columnlast++;
                }if(cking<columnlast){
                    columnlast--;
            }
    }else if((rking!=rowlast &&cking==columnlast) ){
            if(rking>rowlast){
                rowlast++;
            }else{rowlast--;}

    }else if (rking==rowlast && cking!=columnlast){
        if(cking>columnlast){
            columnlast++;
        }else{columnlast--;}
    }
    }
    return 0;
}
//this function check if the player won or not by check the possible moves for the king
int Winnerf (int turn){
    int i , j , m =-1, n=-1, value=0, w=0 , checker = 1; int noOfPlaces=0;
    char x[2];
    int rking ,cking ;
    if((count+turn)%2 == 0){
        rking=rk; cking=ck;
       place[rk][ck]='.';
    }else{
        rking=rK; cking=cK;
        place[rK][cK]='.';
    }

    if (rking ==0){
        m = 0;
    }
    for(m ; rking+m <8 && m <2 ; m++){
        if(cking == 0){
        n = 0;
    }else n =-1;
    for (n  ; cking+n < 8 && n < 2 ;n++){
         w+=king(rking,cking ,rking+m ,cking+n,checker,1,turn);
         noOfPlaces++;
    }}
    if (w == 0){
        place[rk][ck]='k';
        place[rK][cK]='K';
        system("cls");
        printc();
        printf ("Winner Winner Chicken Dinner %s\n", players[(count+turn)%2]);
        exit(0);
    }else{
        place[rk][ck]='k';
        place[rK][cK]='K';
        return 0;
    }
}
//checks if the king can move or not for the stalemate
int stalmate (int turn){
int i , j , m =-1, n=-1, value=0, w=0 , checker = 1; int noOfPlaces=0;
    char x[2];
    int rking ,cking ;
    if((count+turn)%2 == 0){
        rking=rk; cking=ck;
        place[rk][ck]='.';
    }else{
        rking=rK; cking=cK;
        place[rK][cK]='.';
    }

    if (rking ==0){
        m = 0;
    }
    for(m ; rking+m <8 && m <2 ; m++){
        if(cking == 0){
        n = 0;
    }else n =-1;
    for (n  ; cking+n < 8 && n < 2 ;n++){
         w+=king(rking,cking ,rking+m ,cking+n,checker,1,turn);
         noOfPlaces++;
    }}
    if (w == 0){
        place[rk][ck]='k';
        place[rK][cK]='K';
        system("cls");
        printc();
        printf ("Stalemate !!! \n");
        exit(0);
    }else{
        place[rk][ck]='k';
        place[rK][cK]='K';
        return 0;
    }

}
//this function check if the move of same color pieces make the king check or not !!
int stalmatecheck (int turn ,int r , int c){
     int value=0, i,j,checker=1 ;  char x[2];
                x[0]=place[r][c]; place[r][c]='.' ;
                value =checkmatef(0,1);
                place[r][c]=x[0];
                return value ;
}
//check for the stalemate if the any pieces can move or not !
int possible(int turn){
    int value=0, i,j,checker=1 , m =-1, n=-1 , stale=0;
    for (i=0 ; i<=7 ; i++){
            for (j=0 ; j<=7 ; j++){
        if ((count+turn)%2 == 0){
            switch (place[i][j]) {
            case 'r':
                m =-1, n=-1 ;
                if (i ==0){m = 0;}
                for(m ; i+m <8 && m <2 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 2 ;n++){
                    value = rook(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                    break;
            case 'n':
                m =-2, n=-2 ;
               if (i ==0){m = 0;}
                for(m ; i+m <8 && m <3 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n <3 ;n++){
                    value = knight(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                    break;
            case 'b':
                m =-1, n=-1 ;
                if (i ==0){m = 0;}
                for(m ; i+m <8 && m <2 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 2 ;n++){
                    value = bishop(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                    break;
            case 'q':
                m =-1, n=-1 ;
                if (i ==0){m = 0;}
                for(m ; i+m <8 && m <2 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 2 ;n++){
                    value = queen(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                    break;
            case 'p':
                m =-1, n=-1 ;
                if (i ==0){m = 0;}
                for(m ; i+m <8 && m <2 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 2 ;n++){
                    value = bpawn(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                    break;
            }}else {
                switch (place[i][j]) {
            case 'R':
                m =-1, n=-1 ;
               if (i ==0){m = 0;}
                for(m ; i+m <8 && m <2 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 2 ;n++){
                    value = rook(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                    break;
            case 'N':
                m =-2, n=-2 ;
             if (i ==0){m = 0;}
                for(m ; i+m <8 && m <3 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 3 ;n++){
                    value = knight(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                    break;
            case 'B':
                m =-1, n=-1 ;
                if (i ==0){m = 0;}
                for(m ; i+m <8 && m <2 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 2 ;n++){
                    value = bishop(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                    break;
            case 'Q':
                m =-1, n=-1 ;
                if (i ==0){m = 0;}
                for(m ; i+m <8 && m <2 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 2 ;n++){
                    value = queen(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                break;
            case 'P':
                m =-1, n=-1 ;
                 if (i ==0){m = 0;}
                for(m ; i+m <8 && m <2 ; m++){
                    if(j == 0){n = 0;}else n =-1;
                    for (n  ; j+n < 8 && n < 2 ;n++){
                    value = wpawn(i ,j ,i+m ,j+n ,checker,turn);
                    if (value==1){stale=stalmatecheck(1,i,j);
                        if(stale==1){value=0;}else return 1;}}}
                break;
                        }}
                    if (value==1){return 1;}
        }
    }
 return 0;
}
int main()
{
    int r1,r2,c1,c2 , fail =1,i,j,checkmate1 = 0,checkmate0 = 0, winner =0,turn=0,lastcheck1 =0 , stale1=0 , poss=1;
    FILE *fp;
    while (1){
    here2 : if (fail == 0 ){
        invalid (&r1 , &c1, &r2 , &c2);
        fail =1;
        count--;
        goto here;
    }
    else {
    system("cls");
    checkmate1 = checkmatef(turn,0);
    printc();
    SetColor(15);
    printf("Enter Your Move OR (U) Undo\\(R) Redo\\(S) Save \\(L) Load\n%s:\n" , players[count%2]);
    scanf ("%s",temp);clear();
    r1 = temp[1] - 49;
    r2 = temp[3] - 49;
    c1 = temp[0] - 65;
    c2 = temp[2] - 65;
   here:
      if (temp[0] == 'U'){
        undo(r1,c1,r2,c2);
        goto here2;
    }else if (temp[0] == 'R'){
        redo(r1,c1,r2,c2);
        goto here2;}
    else if (temp[0] == 'S'){
       fp = fopen("save.txt", "w");
        fprintf (fp , "%d",count);
        fputc (',', fp);
        fprintf(fp , "%d" , g[0]);
        fputc (',', fp);
        fprintf(fp , "%d" , g[1]);
        fputc (',', fp);
        fprintf(fp , "%d" , rk);
        fputc (',', fp);
        fprintf(fp , "%d" , ck);
        fputc (',', fp);
        fprintf(fp , "%d" , rK);
        fputc (',', fp);
        fprintf(fp , "%d" , cK);
        for (i=0 ; i<8 ; i++){
            for (j=0 ; j<8 ; j++){
                fputc(place[i][j] , fp);
            }
        }
        for (i=0 ; i<=count ; i++){
                for(j=0 ; j<6 ; j++){
            fputc(moves[i][j], fp);
            }}
        for (i=0 ; i<g[0] ; i++){
            fputc(graveyard[0][i], fp);
            }
        for (i=0 ; i<g[1] ; i++){
            fputc(graveyard[1][i], fp);
            }
        fclose(fp);
        goto here2;
    }else if (temp[0] == 'L'){
    fp = fopen("save.txt", "r");
    fscanf(fp , "%d,%d,%d,%d,%d,%d,%d" , &count , &g[0] , &g[1] , &rk , &ck ,&rK,&cK);
    for(j=0 ; j<8 ; j++){
        fgets(place[j] , 9 , fp);
        }
    for (j=0 ; j<=count;j++){
        fgets(moves[j] , 7 , fp);
    }
    for (j=0 ; j<g[0] ; j++){
        graveyard[0][j] = fgetc (fp);
    }
    for (j=0 ; j<g[1] ; j++){
        graveyard[1][j] = fgetc (fp);
    }
    fclose(fp);
    goto here2;
    }
    if (r1 >7 ||r1 <0 ||r2 >7 ||r2 <0 ||c1 >7 ||c1 <0 ||c2 >7 ||c2 <0 || place[r1][c1]== '_'||place[r1][c1]== '.' ||(r1==r2 && c1==c2 ) ){
            fail =0;count++;goto here2;
    }
    fail = checkf(r1,c1,0);
    count++;
    if (fail == 0){
        goto here2;
    }
    if (temp[4] == '\0') i=4;
    else i=5;
    for(i ; i<6 ; i++){
        temp[i] = ' ';
    }
    turn = 0;
     switch (place[r1][c1])  {
        case 'p' :
            fail = bpawn(r1 ,c1 ,r2 ,c2 ,0,turn);
            if (fail == 1 && r2 == 7){
                promotion(r2,c2);
                moves[count][4] = temp[4];
            }
            break;
        case 'r' :
            fail = rook(r1 ,c1 ,r2 ,c2 ,0,turn);
            break;
        case 'n' :
            fail=  knight(r1 ,c1 ,r2 ,c2 ,0,turn);
            break;
        case 'b' :
            fail=  bishop(r1 ,c1 ,r2 ,c2 ,0,turn);
            break;
        case 'q' :
            fail=  queen(r1 ,c1 ,r2 ,c2 ,0,turn);
            break;
        case 'P' :
            fail=  wpawn(r1 ,c1 ,r2 ,c2 ,0,turn);
            if (fail == 1 && r2 == 0){
                promotion(r2,c2);
                moves[count][4] = temp[4];
            }
            break;
        case 'R' :
            fail=  rook(r1 ,c1 ,r2 ,c2 ,0,turn);
            break;
        case 'N' :
            fail=  knight(r1 ,c1 ,r2 ,c2 ,0,turn);
            break;
        case 'B' :
            fail=  bishop(r1 ,c1 ,r2 ,c2 ,0,turn);
            break;
        case 'Q' :
            fail=  queen(r1 ,c1 ,r2 ,c2 ,0,turn);
            break;
        case 'k':
            fail=  king(r1 ,c1 ,r2 ,c2 ,1,0,turn);
            if (fail == 1){
                kingPlace[count%2][0] = r2; kingPlace[count%2][1] = c2;
                rk = r2; ck = c2;
            }
            break;
        case 'K' :
            fail=  king(r1 ,c1 ,r2 ,c2 ,1,0,turn);
            if (fail == 1){
                kingPlace[count%2][0] = r2; kingPlace[count%2][1] = c2;
                rK = r2 ; cK = c2;
            }
            break;
    }
    // for turn of white(count%2 == 1)
     // checks if my move prevented threat on my king or caused a threat to him
      checkmate0 = checkmatef(1,0);
      strcpy(moves[count],temp);
       if ( checkmate0 == 1 && fail == 1){
            if ( place[r1][c1] == 'k' || place[r1][c1] == 'K'  ){
        fail=0;goto here2;
      }else {
            undo(r1,c1,r2,c2);count++;
            fail=0;goto here2; }}
      // checks if i made a threat on enemy's king and i won or not
      // turn is used to check on the otherside of (count%2)
     if (fail == 1 ){
        checkmate1 = checkmatef(turn,0);
        lastcheck1=lastcheck(1);
        poss=possible(1);
            if(poss==0 && checkmate1==0){
                stalmate(1);
            }

        if(lastcheck1==0&&checkmate1==1){
        winner = Winnerf(1);

        }
        // saves moves
        //return all moves after my move to null so i can't redo them after undoing them
        for (i=count+1 ; moves[i][0] != '\0' ;i++){
                for (j=0 ; j<6 ; j++){
                   moves[i][j] = '\0';
                }
        }
     }
    }
    }
    return 0;
}
