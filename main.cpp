#include <iostream>
#include "include/sl.h"
#include <X11/Xlib.h>
#include <err.h>
#include <vector>
#include <map>
#include <string>

const char* title = "JHONNY IS BACK";
const int margin = 100;

void rectDefine(std::map<int, std::map<std::string, std::map<std::string, float>>> &map) {
    for (int i = 0; i < map.size(); i++) {
        map[i]["dl"] = {{"x",map[i]["center"]["x"] - map[i]["size"]["x"]/2}, {"y", map[i]["center"]["y"] - map[i]["size"]["y"]/2}};
        map[i]["dr"] = {{"x",map[i]["center"]["x"] + map[i]["size"]["x"]/2}, {"y", map[i]["center"]["y"] - map[i]["size"]["y"]/2}};
        map[i]["ul"] = {{"x",map[i]["center"]["x"] - map[i]["size"]["x"]/2}, {"y", map[i]["center"]["y"] + map[i]["size"]["y"]/2}};
        map[i]["ur"] = {{"x",map[i]["center"]["x"] + map[i]["size"]["x"]/2}, {"y", map[i]["center"]["y"] + map[i]["size"]["y"]/2}};
    }
}
/*
int mouseInTile(std::map<int, std::map<std::string, std::map<std::string, int>>> map){
    int mx = slGetMouseX();
    int my = slGetMouseY();
    for (int i = 0; i < map.size(); i++) {
        if (((mx < map[i]["dr"]["x"]) and (my > map[i]["dl"]["x"])) and ((my < map["dr"]["y"]) and (my > map["ul"]["y"]))) {
            return i;
        }
    }
    return -1;
}*/

int main(int args, char *argv[]) {
    int mx, my;
    char *wid; Display *dpy; Window w;
    int width, height, snum;
    if(!(dpy = XOpenDisplay(0)))
        errx(1, "cannot open display '%s'", XDisplayName(0));
    snum = DefaultScreen(dpy);
    width = DisplayWidth(dpy, snum);
    height = DisplayHeight(dpy, snum);
    printf("display size is %d x %d\n", width, height);
    if((wid = getenv("WINDOWID")) && (w = strtoul(wid, 0, 0))){
        XMoveWindow(dpy, w, width / 4, height / 4);
        XSync(dpy, False);
    }

    slWindow(width, height, title, 1);
    slSetFont(slLoadFont("ttf/Branda.ttf"), 24);
    slSetTextAlign(SL_ALIGN_CENTER);
    //int tex = slLoadTexture("images/_.png");

    std::map<int, std::map<std::string, std::map<std::string, float>>> tile = {};
    tile[0] = {{"center", {{"x",width/2}, {"y",height/2}}}, {"size", {{"x", width - 200}, {"y", height - 200}}}};
    
    int numTiles = 3;
    
    rectDefine(tile);

    for (int i = 0;i < numTiles*numTiles; i++) {
        int x = i%numTiles;
        int y = i/numTiles;

        tile[i+1] = {{"center", {{"x", (tile[0]["dl"]["x"] + (tile[0]["size"]["x"] / (numTiles * 2)) * (x+1+x)) }, {"y", tile[0]["dl"]["y"] + (tile[0]["size"]["y"] / (numTiles * 2)) * (y+1+y) }}}, {"size", {{"x", tile[0]["size"]["x"]/numTiles}, {"y",tile[0]["size"]["y"]/numTiles}}}};
    }

    rectDefine(tile);

    while(!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
    {
        // background
        slSetForeColor(0.0, 0.0, 0.0, 1.0);
        slRectangleFill(width/2, height/2, width, height);

        //slRectangleOutline(width/2, height/2, width - 200, height - 200);
        slSetForeColor(0.3, 0.3, 0.3, 1.0);
        for (int k = 0; k < tile.size(); k++) {
            slRectangleOutline(tile[k]["center"]["x"], tile[k]["center"]["y"], tile[k]["size"]["x"], tile[k]["size"]["y"]);
        }


        
        if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
            for (int v = 1;v < numTiles*numTiles; v++) {
                mx = slGetMouseX();
                my = slGetMouseY();
                if ((mx < tile[v]["dr"]["x"] and mx > tile[v]["dl"]["x"]) and (my < tile[v]["ul"]["y"] and my > tile[v]["dl"]["y"])) {
                    printf("%d\n", v);
                }

            }
        }

        /*for (int i = 0; i < tile.size(); i++) {
            slSetForeColor(0.0, 0.0, 1.0, 1.0);
            slCircleFill(tile[i]["ul"]["x"],tile[i]["ul"]["y"], 5, 10);
            slSetForeColor(0.0, 1.0, 0.0, 1.0);
            slCircleFill(tile[i]["ur"]["x"],tile[i]["ur"]["y"], 5, 10);
            slSetForeColor(0.0, 0.0, 0.0, 1.0);
            slCircleFill(tile[i]["dl"]["x"],tile[i]["dl"]["y"], 5, 10);
            slSetForeColor(1.0, 0.0, 0.0, 1.0);
            slCircleFill(tile[i]["dr"]["x"],tile[i]["dr"]["y"], 5, 10);
        }*/
        
        slSetForeColor(1.0, 1.0, 1.0, 1.0);
        // slSprite(tex, 200, 240, 300, 200);
        slRender();     // draw everything
    }
    slClose();          // close the window and shut down SIGIL
    return 0;
}
