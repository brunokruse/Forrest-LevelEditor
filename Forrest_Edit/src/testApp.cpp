#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // fonts
    ofTrueTypeFont::setGlobalDpi(72);
    
	franklinBook12.loadFont("DINNeuzeitGroteskStd-Light.otf", 12, true, true);
	franklinBook12.setLineHeight(18.0f);
	franklinBook12.setLetterSpacing(1.037);

    worldPos = ofVec2f(0,0); // for minimap
    editorPos = ofVec2f(0,0);
    loadNewFile(worldPos.x, worldPos.y); // load files and assign to array
    
    showMenu = true;
    currentTile = '1';
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    // draw the current game map in passes
    
    // 1st pass - tiles
    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 40; x++) {
            
            int loc = x + y * 40; // proper 1D location
            ofNoFill();
            
            // DRAW TILE TYPES
            if      (TileArrayV[loc] == 0 || TileArrayV[loc] == '0') { ofSetColor(170, 170, 170); }
            else if (TileArrayV[loc] == 1 || TileArrayV[loc] == '1') { ofSetColor(30, 30, 30); }
            else if (TileArrayV[loc] == 2 || TileArrayV[loc] == '2') { ofSetColor(30, 30, 255); }
            else if (TileArrayV[loc] == 3 || TileArrayV[loc] == '3') { ofSetColor(255, 30, 30); }
            else if (TileArrayV[loc] == 4 || TileArrayV[loc] == '4') { ofSetColor(60, 60, 60); }
            else if (TileArrayV[loc] == 5 || TileArrayV[loc] == '5') { ofSetColor(60, 60, 60); }
            
            ofFill();
            ofRect(x * 32, y* 32, 32, 32);
        }
    }
    
    // 2nd pass - subtypes
    
    
    // 3rd pass - enemies
    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 40; x++) {
            
            int loc = x + y * 40; // proper 1D location
            ofNoFill();
            
            string enemyString = ofToString(EnemyArrayV[loc]);
            
            if (enemyString != "" && enemyString != "0") {
                franklinBook12.drawString(enemyString, x * 32 + 15, y * 32 + 20);
            }

        }
    }
    
    
    // grid
    if(showGrid) {
        for (int y = 0; y < 24; y++) {
            for (int x = 0; x < 40; x++) {
                    ofNoFill();
                    ofSetColor(30, 255, 255);
                    ofRect(x * 32, y* 32, 32, 32);
            }
        }
    }

    if (showMenu) {
        drawMenuBar();
    }

    drawMouseTiler();
    
    // draw current mode
    ofFill();
    ofSetColor(255,0,0);
    franklinBook12.drawString(tileMode, 20, 90);
    ofNoFill();
}

void testApp::drawMenuBar() {
    
    // draw menu bar
    ofFill();
    ofEnableAlphaBlending();
    ofSetColor(30, 30, 30, 90);
    ofRect(0, 0, 440, 100);
    ofDisableAlphaBlending();
    
    for (int i = 0; i <= 6; i++) {
        
        ofPushMatrix();
        ofTranslate(120, 0);
        
        if (i == 0 )ofSetColor(170, 170, 170);
        if (i == 1 )ofSetColor(30, 30, 30);
        if (i == 2 )ofSetColor(30, 30, 255);
        if (i == 3 )ofSetColor(255, 30, 30);
        if (i == 4 )ofSetColor(60, 60, 60);
        if (i == 5 )ofSetColor(60, 60, 60); // exit
        if (i == 6 )ofSetColor(60, 60, 60); // checkpoint
        
        ofFill();
        ofRect(i * 32 + i * 10, 25, 32, 32);
        ofNoFill();
        ofSetColor(255, 255, 255);
        string tileLbl = ofToString(i);
        franklinBook12.drawString(tileLbl, i * 32 + i * 10, 68);
        
        ofPopMatrix();
        
    }
    
    ofSetColor(255, 255, 255);
    string tilesTxt = "available tiles";
    franklinBook12.drawString(tilesTxt, 120, 20);
    
    // draw minimap
    for (int i = 0; i < kWorldSizeY; i++) {
        for(int j = 0; j < kWorldSizeX; j++) {
            ofPushMatrix();
            ofTranslate(20, 20);
            ofNoFill();
            ofSetColor(225, 225, 225);
            ofRect(8*i, 8*j, 8, 8);
            ofFill();
            ofRect(worldPos.x * 8, worldPos.y * 8, 8, 8);
            ofPopMatrix();            
        }
    }
    
    string posTxt = "(" + ofToString(worldPos.x) + "," + ofToString(worldPos.y) + ")";
    franklinBook12.drawString(posTxt, 20, 70);
}

void testApp::drawMouseTiler() {
    ofEnableAlphaBlending();
    ofFill();
    
    // place appropriate tile on the mouse cursor
    if(tileMode == "tiles") {
        if      (currentTile == '0') { ofSetColor(170, 170, 170); }
        else if (currentTile == '1') { ofSetColor(30, 30, 30); }
        else if (currentTile == '2') { ofSetColor(30, 30, 255); }
        else if (currentTile == '3') { ofSetColor(255, 30, 30); }
        else if (currentTile == '4') { ofSetColor(60, 60, 60); }
        else if (currentTile == '5') { ofSetColor(255, 255, 255); } // exit
        else if (currentTile == '6') { ofSetColor(0, 0, 0); } // checkpoint
    
    }
    
    // calcuate + snap
    int xpos = ofMap(mouseX, 0, ofGetWidth(), 0, 40);
    int ypos = ofMap(mouseY, 0, ofGetHeight(), 0, 24);
    editorPos.x = xpos;
    editorPos.y = ypos;
    

    
    // also draw the corresponding letters
    if (tileMode == "enemies") {
        string enemyString = ofToString(currentTile);
        if (enemyString != "" && enemyString != "0") {
            franklinBook12.drawString(enemyString, xpos * 32 + 15, ypos * 32 + 15);
        }
    } else {
        // draw the tile
        ofRect(xpos * 32, ypos * 32, 32, 32);
    }
    
    ofDisableAlphaBlending();
}

void testApp::loadNewFile(int x, int y) {
    
    string filename = ofToString(x) + ofToString(y) + ".txt";
    ofBuffer buffer = ofBufferFromFile("lvldata/" + filename); // reading into the buffer
    cout << "loading: " + filename << endl;
    
    TileArrayV.clear();
    SubtypesArrayV.clear();
    EnemyArrayV.clear();
    
    int lineCounter = 0; // lets keep track!
    while(!buffer.isLastLine()) {
        
        string line = buffer.getNextLine();
        string curLineTxt = line;        
        lineCounter ++; // our current line for logic
        
        // 1st batch
        if (lineCounter < 25) {
            for (int x = 0; x < curLineTxt.size(); x++) {
                TileArrayV.push_back(curLineTxt[x]);
            }
        }
        
        // 2nd batch
        if (lineCounter >= 26  && lineCounter < 50) {
            for (int x=0; x<40; x++) {
                SubtypesArrayV.push_back(curLineTxt[x]);
            }
        }
        
        // 3rd batch
        if (lineCounter >= 51  && lineCounter < 75) {
            for (int x=0; x<40; x++) {
                EnemyArrayV.push_back(curLineTxt[x]);
            }
        }
        
        // misc
        if (lineCounter == 75) { powerUpCol = ofToInt(curLineTxt); } //powerUpCol
        if (lineCounter == 76) { powerUpRow = ofToInt(curLineTxt); } //powerUpRow
        if (lineCounter == 77) { powerUpType = ofToInt(curLineTxt); } //powerUpType
        if (lineCounter == 78) { checkPointCol = ofToInt(curLineTxt); } //checkPointCol
        if (lineCounter == 79) { checkPointRow = ofToInt(curLineTxt); } //checkPointRow
        
    }
}


void testApp::saveMap(int x, int y) {
    
    string filename = ofToString(x) + ofToString(y) + ".txt";
    cout << "saving: " + filename << endl;
    
    string writeToText;
    
    // first pass
    for (int x = 0; x < 960; x++) {
        if (x % 40 == 0 && x != 0)
            writeToText += "\n";

        writeToText += char(TileArrayV[x]);
    }
   
    writeToText += "\n-\n";

    // second pass
    for (int x = 0; x < 960; x++) {
        if (x % 40 == 0 && x != 0)
            writeToText += "\n";
        
        writeToText += char(SubtypesArrayV[x]);
    }
    
    writeToText += "\n-\n";

    // third pass
    for (int x = 0; x < 960; x++) {
        if (x % 40 == 0 && x != 0)
            writeToText += "\n";
        
        writeToText += char(EnemyArrayV[x]);
    }
    
    // misc items
    writeToText += powerUpCol + "\n";
    writeToText += powerUpRow + "\n";
    writeToText += powerUpType + "\n";
    writeToText += checkPointCol + "\n";
    writeToText += checkPointRow + "\n";
    
    // now we write it all
    ofBuffer dataBuffer;
    dataBuffer.set(writeToText.c_str(), writeToText.size());

    bool fileWritten = ofBufferToFile("lvldata/" + filename, dataBuffer); 

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    cout << "keypressed: " << key << endl;
    
    // update current tile based on keypress
    if (tileMode == "tiles") {
        if (key == '0'){
            currentTile = '0';
        }
        if (key == '1'){
            currentTile = '1';
        }
        if (key == '2'){
            currentTile = '2';
        }
        if (key == '3'){
            currentTile = '3';
        }
        if (key == '4'){
            currentTile = '4';
        }
        if (key == '5'){
            currentTile = '5'; // exit
        }
    
    } else if (tileMode == "enemies") {
        
        // 9 total
        if (key == '0'){
            currentTile = 'A'; // enemy 1
        }
        if (key == '1'){
            currentTile = 'B';
        }
        if (key == '2'){
            currentTile = 'C';
        }
        if (key == '3'){
            currentTile = 'D';
        }
        if (key == '4'){
            currentTile = 'E';
        }
        if (key == '5'){
            currentTile = 'F';
        }
        if (key == '6'){
            currentTile = 'G';
        }
        if (key == '7'){
            currentTile = 'H';
        }
        if (key == '8'){
            currentTile = 'I';
        }
        if (key == '9'){
            currentTile = 'J'; // enemy 9
        }
    
    } else if (tileMode == "checkpoints") {
        currentTile = '6'; // checkpoint
    }
    
    
    // UPDATE TILE MODE
    if (key == 't'){
        tileMode = "tiles";
    }

    if (key == 'e'){
        tileMode = "enemies";
    }

    if (key == 'c'){
        tileMode = "checkpoints";
    }

    
    // EDITOR CONTROLS/INTERFACE
    if (key == 'f'){
        ofToggleFullscreen();
    }

    if (key == 'm'){
        showMenu = !showMenu;
    }
    
    if (key == 'o'){
        saveMap(worldPos.x, worldPos.y);
    }
    
    if (key == 'g'){
        showGrid = !showGrid;
    }
    
    
    // MINIMAP
    if (key == 'w' || key == 357) { // UP
        saveMap(worldPos.x, worldPos.y);
        cout << "up" << endl;
        worldPos.y -= 1;
        if (worldPos.y <= 0) worldPos.y = 0;
        if (worldPos.y >= 4) worldPos.y = 4;
        loadNewFile(worldPos.x, worldPos.y);
    }
    
    if (key == 's' || key == 359) { // DOWN
        saveMap(worldPos.x, worldPos.y);
        cout << "down" << endl;
        worldPos.y += 1;
        if (worldPos.y <= 0) worldPos.y =0;
        if (worldPos.y >= 4) worldPos.y = 4;
        loadNewFile(worldPos.x, worldPos.y);
    }
    
    if (key == 'a' || key == 356) { // LEFT
        saveMap(worldPos.x, worldPos.y);
        cout << "left" << endl;
        worldPos.x -= 1;
        if (worldPos.x <= 0) worldPos.x =0;
        if (worldPos.x >= 4) worldPos.x = 4;
        loadNewFile(worldPos.x, worldPos.y);
    }
    
    if (key == 'd' || key == 358) { // RIGHT
        saveMap(worldPos.x, worldPos.y);
        cout << "right" << endl;
        worldPos.x += 1;
        if (worldPos.x <= 0) worldPos.x =0;        
        if (worldPos.x >= 4) worldPos.x = 4;        
        loadNewFile(worldPos.x, worldPos.y);
        
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    int loc = editorPos.x + editorPos.y * 40;
    cout << button << endl;
    
    if(tileMode == "tiles") {
        if (button == 0) {
            TileArrayV[loc] = int(currentTile);
        } else if(button == 2) {
            
            TileArrayV[loc] = 0;
        }
    } else if (tileMode == "enemies") {
        
        EnemyArrayV[loc] = currentTile;
        
    }

    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    int loc = editorPos.x + editorPos.y * 40;
    cout << button << endl;
    
    if(tileMode == "tiles") {
        if (button == 0) {
            TileArrayV[loc] = int(currentTile);
        } else if(button == 2) {
            
            TileArrayV[loc] = 0;
        }
    } else if (tileMode == "enemies") {
        
        EnemyArrayV[loc] = currentTile;

    }

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}