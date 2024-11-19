#include <iostream>
#include "include/sl.h"
#include <err.h>
#include <vector>
#include <map>
#include <string>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux
#include <X11/Xlib.h>
#endif

const int UPPERLEFT = 0;
const int UPPERRIGHT = 1;
const int DOWNLEFT = 3;
const int DOWNRIGHT = 2;
const char* title = "JHONNY IS BACK";
const int margin = 50;

/*void rectDefine(std::map<int, std::map<std::strin(width - ((int)margin)g, std::map<std::string, float>>> &map) {
    for (int i = 0; i < map.size(); i++) {
        map[i]["dl"] = {{"x",map[i]["center"]["x"] - map[i]["size"]["x"]/2}, {"y", map[i]["center"]["y"] - map[i]["size"]["y"]/2}};
        map[i]["dr"] = {{"x",map[i]["center"]["x"] + map[i]["size"]["x"]/2}, {"y", map[i]["center"]["y"] - map[i]["size"]["y"]/2}};
        map[i]["ul"] = {{"x",map[i]["center"]["x"] - map[i]["size"]["x"]/2}, {"y", map[i]["center"]["y"] + map[i]["size"]["y"]/2}};
        map[i]["ur"] = {{"x",map[i]["center"]["x"] + map[i]["size"]["x"]/2}, {"y", map[i]["center"]["y"] + map[i]["size"]["y"]/2}};
    }
}*/

class Tile {
    public:
        int num;
        int challengeCode;
        std::vector<float> center;
        std::vector<float> size;
        std::vector<std::vector<float>> corner;
        Tile(int n, int challCode, std::vector<float>& c, std::vector<float>& s) {
            num = n; challengeCode = challCode; center = c; size = s;
            corner.push_back({this->center[0] - this->size[0]/2, this->center[1] + this->size[1]/2});
            corner.push_back({this->center[0] + this->size[0]/2, this->center[1] + this->size[1]/2});
            corner.push_back({this->center[0] + this->size[0]/2, this->center[1] - this->size[1]/2});
            corner.push_back({this->center[0] - this->size[0]/2, this->center[1] - this->size[1]/2});
        }
};

class ElementChallengeNumCode {
    public:
        int numInput;
        int numOutput;
        std::vector<float> center;
        std::vector<float> size;
        std::vector<std::vector<float>> corner;
        std::string input;
        std::string output;
		std::string img;
        ElementChallengeNumCode(int arg1, int arg2, std::vector<float> arg3, std::vector<float> arg4, std::string arg5 = "", std::string arg6 = "-1", std::string arg7 = "") {
            numInput = arg1;
            numOutput = arg2;
            center = arg3;
            size = arg4;
            input = arg5;
            output = arg6;
			img = arg7;
            corner.push_back({this->center[0] - this->size[0]/2, this->center[1] + this->size[1]/2});
            corner.push_back({this->center[0] + this->size[0]/2, this->center[1] + this->size[1]/2});
            corner.push_back({this->center[0] + this->size[0]/2, this->center[1] - this->size[1]/2});
            corner.push_back({this->center[0] - this->size[0]/2, this->center[1] - this->size[1]/2});
        }
};

class ChallengeNumCode {
	public:
		std::vector<ElementChallengeNumCode> vect;
};

ChallengeNumCode ChallengeCode(Tile tile, int paddingy, int paddingx, int spaceBlock) {
    ChallengeNumCode ElementList;
	std::vector<ElementChallengeNumCode> vect;
    std::vector<float> center;
    std::vector<float> size = {tile.size[0] - tile.size[0]/9, tile.size[1] - tile.size[1]/9};
    Tile tempTile(-1, 0, tile.center, size);
    ElementList.vect.push_back(ElementChallengeNumCode(10, -1, tempTile.center, size, "", ""));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "1"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "2"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "3"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "4"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "5"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "6"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "7"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "8"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "9"));
    ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, tempTile.center, size, "", "0"));
    /* CORE DUMPED Problem (fix after the delay) 
	 * for (int k = 1; k < 10; k++){
        std::string s = std::to_string(k);
		char const *pchar = s.c_str();  //use char const* as target type
		std::string lol;
		ElementList.vect.push_back(ElementChallengeNumCode(-1, 10, center, size, lol, pchar));
    }*/
    return ElementList;
}

/*int
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

class Games {
	public:
		std::vector<std::pair<Tile, void*>> vec;
};

int main(int args, char *argv[]) {
    int mx, my;
    
    int width, height, snum;
    #ifdef linux
    char *wid; Display *dpy; Window w;
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
    #endif
    
    #ifdef _WIN32
    RECT desktop;
    // Get a handle to tgcc -g main.cpp -o main -L. -l:libsigil.so -lstdc++ -lX11he desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    width = desktop.right;
    height = desktop.bottom;#include <random>
    #endif

    slWindow(width, height, title, 1);
    slSetFont(slLoadFont("ttf/Branda.ttf"), 80);
    slSetTextAlign(SL_ALIGN_CENTER);
    //int tex = slLoadTexture("images/_.png");

    //std::map<int, std::map<std::string, std::map<std::string, float>>> tile = {};
    //tile[0] = {{"center", {{"x",width/2}, {"y",height/2}}}, {"size", {{"x", width - 200}, {"y", height - 200}}}};
    
	Games games;	

    std::vector<float> center;
    std::vector<float> size;

    std::vector<Tile> Tiles;
    center = {width/2, height/2}; size = {width-margin, height-margin};
    Tile PrimaryTile(0, -1, center, size);
    Tiles.push_back(PrimaryTile);
    int numberTiles = 3;
    
    std::vector<int> ChallengeAttr = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

    for (int i = 0;i < numberTiles*numberTiles; i++) {
        int x = i%numberTiles;
        int y = i/numberTiles;
        center = {(PrimaryTile.corner[DOWNLEFT][0] + (PrimaryTile.size[0] / (numberTiles * 2)) * (x+1+x)), PrimaryTile.corner[DOWNLEFT][1] + (PrimaryTile.size[1] / (numberTiles * 2)) * (y+1+y)};
        size = {PrimaryTile.size[0]/numberTiles, PrimaryTile.size[1]/numberTiles};
        
        // Define range
        int min = 0;
        int max = ChallengeAttr.size() - 1;

        // Initialize a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);
        int randomValue = distrib(gen);
        Tile temptile(i+1, ChallengeAttr[randomValue], center, size);
		Tiles.push_back(temptile);
		if (temptile.challengeCode == 0){ 
			ChallengeNumCode init = ChallengeCode(temptile, 30, 30, 30);
			games.vec.push_back({Tiles[i+1], reinterpret_cast<void*>(&init)});
		}
		/*if else (ChallengeAttr[randomValue] == 1){ games.add(temptile, ChallengeCode(temptile, 30, 30, 30)); }
		if else (ChallengeAttr[randomValue] == 2){ games.add(temptile, ChallengeCode(temptile, 30, 30, 30)); }
		if else (ChallengeAttr[randomValue] == 3){ games.add(temptile, ChallengeCode(temptile, 30, 30, 30)); }
		if else (ChallengeAttr[randomValue] == 4){ games.add(temptile, ChallengeCode(temptile, 30, 30, 30)); }
		if else (ChallengeAttr[randomValue] == 5){ games.add(temptile, ChallengeCode(temptile, 30, 30, 30)); }
		if else (ChallengeAttr[randomValue] == 6){ games.add(temptile, ChallengeCode(temptile, 30, 30, 30)); }
		if else (ChallengeAttr[randomValue] == 7){ games.add(temptile, ChallengeCode(temptile, 30, 30, 30)); }
		if else (ChallengeAttr[randomValue] == 8){ games.add(temptile, ChallengeCode(temptile, 30, 30, 30)); }*/
        ChallengeAttr.erase(ChallengeAttr.begin() + randomValue);
    }

    while(!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
    {
        // background
        slSetForeColor(0.0, 0.0, 0.0, 1.0);
        slRectangleFill(width/2, height/2, width, height);

        //slRectangleOutline(width/2, height/2, width - 200, height - 200);
        slSetForeColor(0.3, 0.3, 0.3, 1.0);
        for (int k = 0; k < 10; k++) {
            slRectangleOutline(Tiles[k].center[0], Tiles[k].center[1], Tiles[k].size[0], Tiles[k].size[1]);
            std::string s = std::to_string(Tiles[k].challengeCode);
            char const *pchar = s.c_str();  //use char const* as target type
            if (k!=0){
                slText(Tiles[k].center[0], Tiles[k].center[1], pchar);
            }
        }
		
		printf("%d ", games.vec.size());

		for (int m = 0; m < games.vec.size(); m++){
			games.vec[m][1];// test
		}

        if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {   
            for (int v = 1;v < numberTiles*numberTiles; v++) {
                mx = slGetMouseX();
                my = slGetMouseY();
                if ((mx < Tiles[v].corner[DOWNRIGHT][0] and mx > Tiles[v].corner[DOWNLEFT][0]) and (my < Tiles[v].corner[UPPERLEFT][1] and my > Tiles[v].corner[DOWNLEFT][1])) {
                    printf("%d %d\n", v, Tiles[v].challengeCode);
                }
            }
        }

        /*for (int i = 0; i < 1; i++) {
            slSetForeColor(0.0, 0.0, 1.0, 1.0);
            slCircleFill(Tiles[i].corner[UPPERLEFT][0],Tiles[i].corner[UPPERLEFT][1], 5, 10);
            slSetForeColor(0.0, 1.0, 0.0, 1.0);
            slCircleFill(Tiles[i].corner[UPPERRIGHT][0],Tiles[i].corner[UPPERRIGHT][1], 5, 10);
            slSetForeColor(0.0, 0.0, 0.0, 1.0);
            slCircleFill(Tiles[i].corner[DOWNLEFT][0],Tiles[i].corner[DOWNLEFT][1], 5, 10);
            slSetForeColor(1.0, 0.0, 0.0, 1.0);
            slCircleFill(Tiles[i].corner[DOWNRIGHT][0],Tiles[i].corner[DOWNRIGHT][1], 5, 10);
        }*/
        
        slSetForeColor(1.0, 1.0, 1.0, 1.0);
        // slSprite(tex, 200, 240, 300, 200);
        slRender();     // draw everything
    }
    slClose();          // close the window and shut down SIGIL
    return 0;
}
