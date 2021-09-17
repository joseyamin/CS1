/*
 *  UCF COP3502 Spring 2021 Assignment Solution
 *  Copyright 2021 Jose Yamin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//defualt size of all my arrays
#define DEFAULT_CAP 30

// Some typedefs to make life easier
typedef struct Piece Piece;
typedef struct List List;
typedef struct Board Board;

// Our structs
struct Piece {
    int rank, file, id;
};

struct List {
    int identifier; 
    Piece ** arr;
    int size, cap;
};

struct Board {
    List ** arr;
    int size, cap;
};

// Prototypes
Board * createBoard();
List * createRank(int rank);
Piece * createPiece(int rank, int file, int id);


void destroyPieceList(List * pieceList);
void destroyBoard(Board *);
void destroyRank(List *);
void destroyPiece(Piece *);

void printBoard(List* pieces,Board* rankBoard, Board *fileBoard);

void addPieceToRank(List *rankList, Piece *piece);
void addRankToBoard(Board *board,List *rankList);
void expandRank(List *rankList);
void expandBoard(Board* board);
List * findRank(Board *board, int rank);

int rightRankAttacker(Piece *piece,List *rankList);
int leftRankAttacker(Piece *piece,List *rankList);
int topFileAttacker(Piece *piece, List* fileList);
int bottomFileAttacker(Piece *piece,List * fileList);


int main(void)
{
  //one board will hold array for each rank for each peice and the other board for each file;
  Board * rankBoard=createBoard();
  Board * fileBoard=createBoard();
  Piece * piece;
  List * rankList;
  List * fileList;

  //scan in first int/n number of rooks
  int n;
  scanf("%d", &n);

  //a list for every peice inputed
  List* pieceList=createRank(0);

  //loop n times to scan for each peice then save to both boards and peice list
  int rank,file;
  for (int i = 1; i <= n; i++)
  {
    scanf("%d %d",&rank,&file);
    piece=createPiece(rank,file,i);
    rankList=findRank(rankBoard,rank);
    fileList=findRank(fileBoard, file);
    addPieceToRank(fileList, piece);
    addPieceToRank(rankList,piece);
    addPieceToRank(pieceList,piece);
  }

  //print results
  printBoard(pieceList,rankBoard,fileBoard);

  //frees peices and peice list and frees boards and list within them but, not the peices since they have already been freed in 'destroyPieceList'
  destroyPieceList(pieceList);
  destroyBoard(rankBoard);
  destroyBoard(fileBoard);

    return 0;
}
//creates board and resturns its pointer
Board * createBoard(){
    Board* board=malloc(sizeof(board));
    board->arr=malloc(sizeof(List*)*DEFAULT_CAP); //new
    board->cap=DEFAULT_CAP;
    board->size=0;
    return board;
}

//creates a list with rank or file given to it within paramater and returns its pointer
List * createRank(int rank){
    List* list=malloc(sizeof(List)); //new
    list->arr=malloc(sizeof(Piece*)*DEFAULT_CAP); //new
    list->cap=DEFAULT_CAP;
    list->size=0;
    list->identifier=rank;
    return list;
}
//creates peice and returns its pointer
Piece * createPiece(int rank, int file, int id){
    Piece *piece=malloc(sizeof(Piece));
    piece->rank=rank;
    piece->file=file;
    piece->id=id;
    return piece;
}
//does a loop to find rank or file and returns the list when it finds it, if it doesnt find it it creates one and calls addranktoboard since the board needs one
List * findRank(Board *board, int rank){
    for(int i=0;i<board->size;i++){
        if(board->arr[i]->identifier==rank){
            return board->arr[i];
        }
    }
    List* x=createRank(rank);
    addRankToBoard(board,x);
    return x;
}
//gets a list and piece in paramater, adds piece to list, if size is full then it calls expand function
void addPieceToRank(List *rankList, Piece *piece){
    if(rankList->size==rankList->cap){
        expandRank(rankList);
    }
    rankList->arr[rankList->size]=piece;
    rankList->size++;
}
//gets a rank/file list and adds it to board given, if size if full then it calls expand function
void addRankToBoard(Board *board,List *rankList){
    if(board->size==board->cap){
        expandBoard(board);
    }
    board->arr[board->size]=rankList;
    board->size++;
}
//expands file or rank list by 2 times as much using realloc and gives it its new cap size 
void expandRank(List *rankList){
    rankList->cap=rankList->cap*2;
    rankList->arr=realloc(rankList->arr,rankList->cap*sizeof(Piece*)); //new

}
//expands board list by 2 times as much using realloc and gives it its new cap size 
void expandBoard(Board* board){
    board->cap=board->cap*2;
    board->arr=realloc(board->arr,board->cap*sizeof(List*)); //new
}
//gets passed the pieces list and frees ALL the pieces ever inputed this one time by calling destroypiece on each one then frees what is passed
void destroyPieceList(List * pieceList){
    for(int i=0;i<pieceList->size;i++){
    destroyPiece(pieceList->arr[i]);
  }
  free(pieceList->arr);
  free(pieceList);
}
//gets passed a board and does a loop to free rank/file before freeing what is passed
void destroyBoard(Board* board){
  for(int i=0;i<board->size;i++){
    destroyRank(board->arr[i]);
  }
  free(board->arr);
  free(board);
}
//frees its self but not the pieces since the pieces are already freed within the other list
void destroyRank(List * rankList){
  free(rankList->arr);
  free(rankList);
}
//frees the piece passed
void destroyPiece(Piece *piece){
  free(piece);
}

//will check the enemys coming from the left right top and bottom the enemy id will be saved it will stay as 0 if no enemy is found. The total of amount of enemys that exist is added and prints its total and each possible enemy
void printBoard(List* pieces,Board* rankBoard, Board *fileBoard){
  int enemy1=0,enemy2=0,enemy3=0,enemy4=0,total=0;
  for(int i=0;i<pieces->size;i++){
      enemy1=rightRankAttacker(pieces->arr[i],findRank(rankBoard,pieces->arr[i]->rank));
      enemy2=leftRankAttacker(pieces->arr[i],findRank(rankBoard,pieces->arr[i]->rank));
      enemy3=topFileAttacker(pieces->arr[i],findRank(fileBoard,pieces->arr[i]->file));
      enemy4=bottomFileAttacker(pieces->arr[i],findRank(fileBoard,pieces->arr[i]->file));
      if(enemy1>0){
        total++;
      }
      if(enemy2>0){
        total++;
      }
      if(enemy3>0){
        total++;
      }
      if(enemy4>0){
        total++;
      }

      printf("%d",total);

      if(enemy1>0){
        printf(" %d",enemy1);
      }
      if(enemy2>0){
        printf(" %d",enemy2);
      }
      if(enemy3>0){
        printf(" %d",enemy3);
      }
      if(enemy4>0){
        printf(" %d",enemy4);
      }

      printf("\n");
      total=0;
      enemy1=0;
      enemy2=0;
      enemy3=0;
      enemy4=0;
  }
}


//passes ranklist checks all its peices and finds the value closest to the right piece rank passed and returns enemy id, 0 if none found
int rightRankAttacker(Piece *piece,List *rankList){
  int enemyID=0;
  int enemyFile=0;
  for(int i=0;i<rankList->size;i++){
    if(rankList->arr[i]->file > piece->file && (enemyID==0 || rankList->arr[i]->file < enemyFile)){
      enemyID=rankList->arr[i]->id;
      enemyFile=rankList->arr[i]->file;
    }
  }
  return enemyID;
}
//passes ranklist checks all its peices and finds the value closest to the left of piece rank passed and returns enemy id, 0 if none found
int leftRankAttacker(Piece *piece,List *rankList){
  int enemyID=0;
  int enemyFile=0;
  for(int i=0;i<rankList->size;i++){
    if(rankList->arr[i]->file < piece->file && (enemyID==0 || rankList->arr[i]->file > enemyFile)){
      enemyID=rankList->arr[i]->id;
      enemyFile=rankList->arr[i]->file;
    }
  }
  return enemyID;
}
//passes filelist checks all its peices and finds the value closest to the top of piece rank passed and returns enemy id, 0 if none found
int topFileAttacker(Piece *piece, List* fileList){
  int enemyID=0;
  int enemyRank=0;
  for(int i=0;i<fileList->size;i++){
    if(fileList->arr[i]->rank > piece->rank && (enemyID==0 || fileList->arr[i]->rank < enemyRank)){
      enemyID=fileList->arr[i]->id;
      enemyRank=fileList->arr[i]->rank;
    }
  }
  return enemyID;
}
//passes filelist checks all its peices and finds the value closest to the bottom of piece rank passed and returns enemy id, 0 if none found
int bottomFileAttacker(Piece *piece,List * fileList){
  int enemyID=0;
  int enemyRank=0;
  for(int i=0;i<fileList->size;i++){
    if(fileList->arr[i]->rank < piece->rank && (enemyID==0 || fileList->arr[i]->rank > enemyRank)){
      enemyID=fileList->arr[i]->id;
      enemyRank=fileList->arr[i]->rank;
    }
  }
  return enemyID;
}