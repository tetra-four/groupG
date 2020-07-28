#include <EzGraph.h>
#include <stdio.h>

#define MAX_OBJECTS 1

typedef struct {
    int x,y;
    int r;
    int valid;
} target_range;

enum colors{
    white, brown, blue, purple, num
};
char *colors_name[4] = {
    "White", "Brown", "Blue", "Purple"
};

target_range objects[4][MAX_OBJECTS];
int view;
int key;

void show_start(void ); /*スタート画面の表示する関数*/
void show_North(void ); /*北方向の視点を表示する関数*/
void show_East(void ); /*東方向の視点を表示する関数*/
void show_South(void ); /*南方向の視点を表示する関数*/
void show_West(void ); /*西方向の視点を表示する関数*/
void view_switch(void ); /*視点を切り替える関数*/
void key_handler(int ); /*キーボード入力を受け付ける関数*/
void check_range(int x, int y, unsigned int n); /*オブジェクトへの接触を確認する関数*/
void show_object(void ); /*オブジェクトを表示する関数*/


void show_start(void ){
    EzSetColorByName("Green");
    EzFillCircleB(100, 100, 30);
    EzShowBuffer();
}

void show_North(void ){
    EzSetColorByName("White");
    EzFillCircleB(100, 100, 30);
}

void show_East(void ){
    EzSetColorByName("Brown");
    EzFillCircleB(100, 100, 30);
}

void show_South(void ){
    EzSetColorByName("Blue");
    EzFillCircleB(100, 100, 30);
}

void show_West(void ){
    EzSetColorByName("Purple");
    EzFillCircleB(100, 100, 30);
}

void view_switch(void ){
    switch(view){
        case 0:
        show_North();
        break;
        case 1:
        show_East();
        break;
        case 2:
        show_South();
        break;
        case 3:
        show_West();
        break;
        default:
        printf("視点の切り替えに失敗。\n");
    }
    show_object();
    EzShowBuffer();
}

void key_event(int key){
    char keys[32];
    EzQueryKeymap(keys);
    if(EzIsKeyPress(keys, EZ_Right)){
        view = (view + 1 + 4)%4;
    }
    else if(EzIsKeyPress(keys, EZ_Left)){
        view = (view - 1 + 4)%4;
    }
    view_switch();
}

void show_object(void ){
    EzSetColorByName(colors_name[view]);
    EzFillCircleB(objects[view][0].x, objects[view][0].y, objects[view][0].r);
}

void check_range(int x, int y, unsigned int n){
    int i;
    for(i = 0; i < MAX_OBJECTS; i++){
        if(objects[view][i].valid != 0){
            if((x - objects[view][i].x) * (x - objects[view][i].x) + (y - objects[view][i].y) * (y - objects[view][i].y) <= objects[view][i].r * objects[view][i].r){
                //key = 1;
                EzExitEventLoop();
            }
        }
    }
}

int main(void){
    objects[0][0].x = 400;
    objects[0][0].y = 400;
    objects[0][0].r = 20;
    objects[0][0].valid = 1;
    objects[1][0].x = 400;
    objects[1][0].y = 400;
    objects[1][0].r = 20;
    objects[1][0].valid = 1;
    objects[2][0].x = 400;
    objects[2][0].y = 400;
    objects[2][0].r = 20;
    objects[2][0].valid = 1;
    objects[3][0].x = 400;
    objects[3][0].y = 400;
    objects[3][0].r = 20;
    objects[3][0].valid = 1;

    show_start();

    EzSetKeyHandler(key_event);

    EzSetMouseHandler(check_range);

    EzEventLoop();
}