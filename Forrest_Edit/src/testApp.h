#pragma once

#include "ofMain.h"

#define kWorldSizeX 5
#define kWorldSizeY 5

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawMenuBar();
        void drawMouseTiler();

        // custom methods
        void loadNewFile(int x, int y);
        void saveMap(int x, int y);
        
        string curFileTxt;
    
        int TileArray1D[960]; // tiles
        vector<char>TileArrayV;
    
        int SubtypesArray1D[960]; // tiles
        vector<char>SubtypesArrayV;

        int EnemyArray1D[960]; // enemies
        vector<char>EnemyArrayV;

    
        int CheckpointArray1D[960]; // checkpoints
        //int MiscArray1D[5];
    
        int powerUpCol;
        int powerUpRow;
        int powerUpType;
        int checkPointCol;
        int checkPointRow;

        char currentTile;
        ofVec2f editorPos;
    
        // current mouse pos
        ofVec2f worldPos;
    
        // fonts
        ofTrueTypeFont  franklinBook12;
    
        // options
        bool showMenu;
        bool showGrid;
        string tileMode;

		
};
