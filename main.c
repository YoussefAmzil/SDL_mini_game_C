#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "math.h"

static int ob=30,score=100;

typedef struct RectangleElement{
SDL_Rect *rect;
struct RectangleElement *next;
}RectangleElement;

typedef struct monsterElement{
SDL_Rect *rect;
struct monsterElement *next;
}monsterElement;

monsterElement *createmonster(SDL_Rect *rect){
monsterElement *newe;
newe =(monsterElement*)malloc(sizeof(monsterElement));
newe->next=NULL;
newe->rect=rect;
return newe;
}

RectangleElement *createElment(SDL_Rect *rect){
RectangleElement *newe;
newe =(RectangleElement*)malloc(sizeof(RectangleElement));
newe->next=NULL;
newe->rect=rect;
return newe;
}

void insertB(RectangleElement **list,SDL_Rect *rect){
RectangleElement *p=createElment(rect);
p->next=*list;
*list=p;
}

void insertBmonster(monsterElement **list,SDL_Rect *rect){
monsterElement *p=createmonster(rect);
p->next=*list;
*list=p;
}

void moveobstacle(SDL_Rect *rect){
while(1){
    //if(rect->x>600){
      //  rect->x-=10;
    //}
        rect->x+=10;
}
}

void initobstacles(RectangleElement **rect){
time_t t;
/* Intializes random number generator */
srand((unsigned) time(&t));
int i=0,pos;
SDL_Rect *new;
for(i=0;i<ob;i++){
new =(SDL_Rect*)malloc(sizeof(SDL_Rect));
pos=rand()%600;
if(pos >30 ){
new->x=pos;
new->y=rand()%600;
new->w=30;
new->h=30;
insertB(rect,new);
}else{
    i-=1;
}
}
}

void drawRectangle(SDL_Renderer *rend,RectangleElement *rect){
    RectangleElement *pt=rect;
    while(pt){
    SDL_RenderFillRect(rend,pt->rect);
        pt=pt->next;
    }
}

void drawmonster(SDL_Renderer *rend,monsterElement *rect){
    monsterElement *pt=rect;
    while(pt){
    SDL_RenderFillRect(rend,pt->rect);
        pt=pt->next;
    }
}


int isclose(int x,int y,RectangleElement **list){

RectangleElement *l=*list;
while(l){
    if((abs(x-(l->rect->x))<30  && abs(y-(l->rect->y))<30)  || x>770 || y>570 || x<0 || y<0){
            printf("So close\n");
      return 1;
    }
    l=l->next;
}
return 0;
}

int inend(int x,int y){
    //end.x=790;
    //end.y=560;
if(abs(x-790)<30 && abs(y-560)<30){
    printf("u finished !!\n");
    printf("Your score is %d/100\n",score);
    return 1;
}
return 0;
}


int main(int c,char *T[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        printf("%s",SDL_GetError());exit(-1);
    }
    RectangleElement *list;
    monsterElement *m;
    m=NULL;
    list=NULL;
    SDL_Window *window;
    window=SDL_CreateWindow("Helloworld",100,100,800,600,SDL_WINDOW_OPENGL);
    initobstacles(&list);
   // SDL_Delay(5000);
   SDL_Rect rect,start,end;
   start.x=1;
   start.y=0;
   start.h=40;
   start.w=10;

   end.x=790;
   end.y=560;
   end.h=40;
   end.w=10;

   rect.x=20;
   rect.y=10;
   rect.h=30;
   rect.w=30;
   SDL_Event windowev;
   SDL_Renderer *rend=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
   while(1){

    if(SDL_PollEvent(&windowev)){
    if(windowev.type==SDL_QUIT) break;
    if(SDL_KEYDOWN==windowev.type){
        printf("X: %d Y:%d\n",rect.x,rect.y);

        switch(windowev.key.keysym.sym){
        case SDLK_LEFT:  {
            if(isclose(rect.x-5,rect.y,&list)==0){
            if(inend(rect.x-5,rect.y)==0){
                    rect.x-=5;
            }
            }else score-=5;
            break;
        }
        case SDLK_RIGHT: {
            if(isclose(rect.x+5,rect.y,&list)==0){
                    if(inend(rect.x+5,rect.y)==0){
                    rect.x+=5;
            }
            }else score-=5;;
            break;
        }
        case SDLK_UP: {
            if(isclose(rect.x,rect.y-5,&list)==0){
             if(inend(rect.x,rect.y-5)==0){
                    rect.y-=5;
            }

            }else score-=5;
            break;
        }
        case SDLK_DOWN: {
            if(isclose(rect.x,rect.y+5,&list)==0){
                    if(inend(rect.x,rect.y+5)==0){
                    rect.y+=5;
            }
            }else score-=5;
            break;
        }
        }
    }
    if(windowev.type==SDL_MOUSEBUTTONDOWN){
    if (windowev.button.button == SDL_BUTTON_RIGHT){
    SDL_Rect *monster;
    monster=(SDL_Rect*)malloc(sizeof(SDL_Rect));
    monster->x=windowev.button.x;
    monster->y=windowev.button.y;
    monster->w=50;
    monster->h=10;
    insertBmonster(&m,monster);
    }else{
    SDL_Rect *rectangle;
    rectangle=(SDL_Rect*)malloc(sizeof(SDL_Rect));
    rectangle->x=windowev.button.x;
    rectangle->y=windowev.button.y;
    rectangle->w=30;
    rectangle->h=30;
    insertB(&list,rectangle);
    }
    }
    }

    SDL_SetRenderDrawColor(rend,255,255,0,255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend,255,0,0,255);
    SDL_RenderFillRect(rend,&rect);
    SDL_SetRenderDrawColor(rend,0,0,50,255);
    SDL_RenderFillRect(rend,&start);
    SDL_RenderFillRect(rend,&end);
    SDL_SetRenderDrawColor(rend,50,205,50,255);
    drawRectangle(rend,list);
    SDL_SetRenderDrawColor(rend,0,0,0,255);
    drawmonster(rend,m);
    SDL_RenderPresent(rend);

   }
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(rend);
   SDL_Quit();
    return 0;
}
