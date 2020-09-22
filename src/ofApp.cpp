#include "ofApp.h"
#include "Emitter.h"
//----------------------------------------------------------------------------------
//
// This example code demonstrates the use of an "Emitter" class to emit Sprites
// and set them in motion. The concept of an "Emitter" is taken from particle
// systems (which we will cover next week).
//
//  1) Creates a simple Emitter  that you can drag around (without images)
//  2) Creates an Sprite to Collide with
//
//  requires ofxGUI add-in for sliders for changing parameters
// 
//
//
//  Kevin M. Smith - CS 134 SJSU

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
    
    gui.setup();
    gui.add(rate.setup("rate", 5, 1, 10));
    gui.add(life.setup("life", 5, .1, 10));
    gui.add(velocity.setup("velocity", ofVec3f(0, -400, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
    
    bHide = false;
    
    isGameStarted = false;
    isGameOver = false;
    
    float musicVolume = 0.4;
    float effectVolume = 1.0;
    
    blastParticle1.setVelocity(ofVec3f(120, 120, 120));
    blastParticle1.setOneShot(true);
    blastParticle1.setEmitterType(RadialEmitter);
    blastParticle1.setGroupSize(150);
    blastParticle1.setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()*0.75, 0));
    blastParticle1.setParticleColor(ofColor::purple);
    blastParticle1.setLifespan(0.2);
    blastParticle1.setLifespanRange(ofVec2f(0.1 , 0.3));
    blastParticle1.setParticleRadius(0.75);
    blastParticle1.setParticleRadiusVariance(0.5);
    
    blastParticle2.setVelocity(ofVec3f(120, 120, 120));
    blastParticle2.setOneShot(true);
    blastParticle2.setEmitterType(RadialEmitter);
    blastParticle2.setGroupSize(150);
    blastParticle2.setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()*0.5, 0));
    blastParticle2.setParticleColor(ofColor::skyBlue);
    blastParticle2.setLifespan(0.2);
    blastParticle2.setLifespanRange(ofVec2f(0.1 , 0.3));
    blastParticle2.setParticleRadius(0.75);
    blastParticle1.setParticleRadiusVariance(0.5);
    
    blastParticle3.setVelocity(ofVec3f(120, 120, 120));
    blastParticle3.setOneShot(true);
    blastParticle3.setEmitterType(RadialEmitter);
    blastParticle3.setGroupSize(150);
    blastParticle3.setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()*0.25, 0));
    blastParticle3.setParticleColor(ofColor::greenYellow);
    blastParticle3.setLifespan(0.25);
    blastParticle3.setLifespanRange(ofVec2f(0.15 , 0.4));
    blastParticle3.setParticleRadius(0.75);
    
    textIntruction.load("verdana.ttf", 14, true, true);
    textIntruction.setLineHeight(18.0f);
    textIntruction.setLetterSpacing(1.037);
    
    textScore.load("verdana.ttf", 12, true, true);
    textScore.setLineHeight(18.0f);
    textScore.setLetterSpacing(1.037);
    
    invaderShip1 = new Emitter( new SpriteSystem());
    invaderShip1->setChildSize(30, 30);
    invaderShip1->setDrawable(false);
    invaderShip1->setLifespan(7 * 1000);    // convert to milliseconds
    invaderShip1->setChildVelocity(ofVec3f(50,100,0));
    invaderShip1->setPosition(ofVec3f(0,100,0));
    
    shipDestroySound1.load("sound/Explosion.mp3");
    shipDestroySound1.setSpeed(2);
    shipDestroySound1.setVolume(effectVolume);
    
    invaderShip2 = new Emitter( new SpriteSystem());
    invaderShip2->setChildSize(30, 30);
    invaderShip2->setDrawable(false);
    invaderShip2->setLifespan(7 * 1000);    // convert to milliseconds
    invaderShip2->setChildVelocity(ofVec3f(-50,100,0));
    invaderShip2->setPosition(ofVec3f(ofGetWindowWidth(),100,0));
    
    shipDestroySound2.load("sound/Explosion.mp3");
    shipDestroySound2.setSpeed(2);
    shipDestroySound2.setVolume(effectVolume);
    
    invaderShip3 = new Emitter( new SpriteSystem());
    invaderShip3->setChildSize(30, 30);
    invaderShip3->setDrawable(false);
    invaderShip3->setLifespan(6 * 1000);    // convert to milliseconds
    invaderShip3->setChildVelocity(ofVec3f(-25,150,0));
    invaderShip3->setPosition(ofVec3f(ofGetWindowWidth()*0.85,-50,0));
    
    shipDestroySound3.load("sound/Explosion.mp3");
    shipDestroySound3.setSpeed(2);
    shipDestroySound3.setVolume(effectVolume);
    
    invaderShip4 = new Emitter( new SpriteSystem());
    invaderShip4->setChildSize(30, 30);
    invaderShip4->setDrawable(false);
    invaderShip4->setLifespan(6 * 1000);    // convert to milliseconds
    invaderShip4->setChildVelocity(ofVec3f(25,150,0));
    invaderShip4->setPosition(ofVec3f(ofGetWindowWidth()*0.15,-50,0));
    
    shipDestroySound4.load("sound/Explosion.mp3");
    shipDestroySound4.setSpeed(2);
    shipDestroySound4.setVolume(effectVolume);
    
    invaderShip5 = new Emitter( new SpriteSystem());
    invaderShip5->setChildSize(30, 30);
    invaderShip5->setDrawable(false);
    invaderShip5->setLifespan(6 * 1000);    // convert to milliseconds
    invaderShip5->setChildVelocity(ofVec3f(0,250,0));
    invaderShip5->setPosition(ofVec3f(ofGetWindowWidth()*0.15,-50,0));
    
    shipDestroySound5.load("sound/Explosion.mp3");
    shipDestroySound5.setSpeed(2);
    shipDestroySound5.setVolume(effectVolume);
    
    invaderShip6 = new Emitter( new SpriteSystem());
    invaderShip6->setChildSize(30, 30);
    invaderShip6->setDrawable(true);
    invaderShip6->setLifespan(6 * 1000);    // convert to milliseconds
    invaderShip6->setChildVelocity(ofVec3f(0,250,0));
    invaderShip6->setPosition(ofVec3f(ofGetWindowWidth()*0.5,100,0));
    
    ofImage imgInShip4;
    if (imgInShip4.load("images/enemy_ship_4.png")) {
        invaderShip6->setImage(imgInShip4);
    }
    
    playerShip = new Emitter( new SpriteSystem() );
    playerShip->setChildSize(10, 10);
    playerShip->enableApplyAngle(true);
    
	if (missileImage.load("images/missile.png")) {
		playerShip->setChildImage(missileImage);
        invaderShip6->setChildImage(missileImage);
    }
    
    if (turretImage.load("images/turret.png")) {
        playerShip->setImage(turretImage);
    }
    
    if(missileFireSound.load("sound/missileFire.mp3")) {
        missileFireSound.setVolume(musicVolume);
        playerShip->setEmitSound(missileFireSound);
        invaderShip6->setEmitSound(missileFireSound);
    }

	playerShip->setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()-150, 0));

    if(bgMusic.load("sound/bgmusic.mp3")) {
        bgMusic.setVolume(musicVolume);
        bgMusic.setMultiPlay(true);
        bgMusic.play();
    }
    
    
    resetGame();
}
void ofApp::resetGame() {
    
    score = 0;
    playerHealth = 10;
    
    playerShip->setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()-150, 0));
    
    ofImage imgInShip1;
    if (imgInShip1.load("images/enemy_ship_1.png")) {
        invaderShip1->setChildImage(imgInShip1);
        invaderShip2->setChildImage(imgInShip1);
    }
    
    ofImage imgInShip2;
    if (imgInShip2.load("images/enemy_ship_2.png")) {
        invaderShip3->setChildImage(imgInShip2);
        invaderShip4->setChildImage(imgInShip2);
    }
    
    ofImage imgInShip3;
    if (imgInShip3.load("images/enemy_ship_3.png")) {
        invaderShip5->setChildImage(imgInShip3);
    }
    
    invaderShip1->setRate(0.5);
    invaderShip2->setRate(0.5);
    invaderShip3->setRate(0.5);
    invaderShip4->setRate(0.5);
    invaderShip5->setRate(0.5);
    
    invaderShip1->setChildScale(1.0);
    invaderShip2->setChildScale(1.0);
    invaderShip3->setChildScale(1.0);
    invaderShip4->setChildScale(1.0);
    invaderShip5->setChildScale(1.0);
    
    invaderShip6->setVelocity(ofVec3f(0,0,0));
    invaderShip6->setPosition(ofVec3f(-30 , 75 , 0));
}

//--------------------------------------------------------------
void ofApp::update() {
    blastParticle1.update();
    blastParticle2.update();
    blastParticle3.update();

    if(!isGameStarted) {
        return;
    }
    
	playerShip->setRate(rate);
	playerShip->setLifespan(life * 1000);    // convert to milliseconds
    playerShip->setChildVelocity(ofVec3f(velocity->x,velocity->y,velocity->z));
	playerShip->update();
    
    invaderShip1->update();
    
    invaderShip2->update();
    
    invaderShip3->update();
    
    invaderShip4->update();
    
    invaderShip5->setPosition(ofVec3f(ofRandom(ofGetWindowWidth()*0.1, ofGetWindowWidth()*0.9),-50,0));
    invaderShip5->update();
    
    invaderShip6->update();
    
    
    if (invaderShip1->rate < 1.8){
        float rate = 1.0 + ((0.5/300) * score);
        invaderShip1->setRate(rate);
        invaderShip2->setRate(rate);
    }
    if (invaderShip1->childScale > 0.7) {
        float scale = 1.0 - ((0.3/150) * score);
        invaderShip1->setChildScale(scale);
        invaderShip2->setChildScale(scale);
    }
    
    if ( score>40) {
        if (invaderShip3->rate < 1.0) {
            float rate = 0.5 + ((1.0/150) * (score-50));
            invaderShip3->setRate(rate);
            invaderShip4->setRate(rate);
        }
        
        if (invaderShip3->childScale > 0.7) {
            float scale = 1.0 - ((0.3/150) * (score-50));
            cout << "scale ( " << scale << " )" << endl;
            invaderShip3->setChildScale(scale);
            invaderShip4->setChildScale(scale);
        }
    }
    
    if ( score>100) {
        if (invaderShip5->childVelocity.y < 500 ) {
            float velY = 250 + (0.5 * (score-100));
            invaderShip5->childVelocity.y = velY;
        }
        
        if (invaderShip3->rate < 1.5) {
            float rate = 0.5 + ((1.0/150) * (score-100));
            invaderShip3->setRate(rate);
            invaderShip4->setRate(rate);
        }
    }
    if ( score>150){
        float velX = 100;
        if(invaderShip6->velocity.x == 0) {
            invaderShip6->velocity.x = velX;
            invaderShip6->start();
        }
        else if(invaderShip6->velocity.x == velX && invaderShip6->trans.x > (ofGetWindowWidth()-30)) {
            invaderShip6->velocity.x = -velX;
        }
        else if(invaderShip6->velocity.x == -velX && invaderShip6->trans.x < 30) {
            invaderShip6->velocity.x = velX;
        }
    }
    
    checkCollisions();
}


//--------------------------------------------------------------
void ofApp::draw() {
    
    ofSetColor(ofColor::white);
    
    if(!isGameStarted && !isGameOver) {
        textIntruction.drawString("Click \"P\" to play game",ofGetWindowWidth()*0.5 - 110,ofGetWindowHeight()/2);
    }
    
    if (isGameOver) {
        textIntruction.drawString("Click \"P\" to replay",ofGetWindowWidth()*0.5 - 80,ofGetWindowHeight()/2 + 100);
        textIntruction.drawString("GAME OVER",ofGetWindowWidth()*0.5 - 60,ofGetWindowHeight()/2 - 100);
    }
    
    if (!bHide) {
        gui.draw();
    }
    
    
    if(isGameStarted) {
        movePlayerShip(movement);
        playerShip->draw();
        invaderShip1->draw();
        invaderShip2->draw();
        invaderShip3->draw();
        invaderShip4->draw();
        invaderShip5->draw();
        invaderShip6->draw();
        if(score>50 && !invaderShip3->started && !invaderShip4->started){
            invaderShip3->start();
            invaderShip4->start();
        }
        if(score>100 && !invaderShip5->started) {
            invaderShip5->start();
        }
    }
    std::ostringstream scoreString;
    scoreString << "Score : " << to_string(score);
    textScore.drawString(scoreString.str(),ofGetWindowWidth()-120,30);
    
    if(isGameStarted) {
        std::ostringstream healthString;
        healthString << "Health : " << to_string(playerHealth);
        textScore.drawString(healthString.str(),10,ofGetWindowHeight()-20);
    }
    
    blastParticle1.draw();
    blastParticle2.draw();
    blastParticle3.draw();
}

void ofApp::checkCollisions() {
    
    if(isGameOver) {
        return;
    }
    
    for(std::vector<Sprite>::iterator it = invaderShip1->sys->sprites.begin(); it != invaderShip1->sys->sprites.end(); ++it) {
        if(playerShip->sys->removeNear(it->trans, it->height*0.6)){
            showBlastParticle(it->trans, 1);
            invaderShip1->sys->remove(it);
            shipDestroySound1.play();
            score++;
            break;
        }
        if(checkPlayerHit(it->trans)) {
            showBlastParticle(it->trans, 1);
            invaderShip1->sys->remove(it);
            shipDestroySound1.play();
            break;
        }
    }
    
    for(std::vector<Sprite>::iterator it = invaderShip2->sys->sprites.begin(); it != invaderShip2->sys->sprites.end(); ++it) {
        if(playerShip->sys->removeNear(it->trans, it->height*0.6)){
            showBlastParticle(it->trans, 1);
            invaderShip2->sys->remove(it);
            shipDestroySound2.play();
            score++;
            break;
        }
        if(checkPlayerHit(it->trans)) {
            showBlastParticle(it->trans, 1);
            invaderShip2->sys->remove(it);
            shipDestroySound2.play();
            break;
        }
    }
    
    for(std::vector<Sprite>::iterator it = invaderShip3->sys->sprites.begin(); it != invaderShip3->sys->sprites.end(); ++it) {
        if(playerShip->sys->removeNear(it->trans, it->height*0.6)){
            showBlastParticle(it->trans, 2);
            invaderShip3->sys->remove(it);
            shipDestroySound3.play();
            score++;
            break;
        }
        if(checkPlayerHit(it->trans)) {
            showBlastParticle(it->trans, 2);
            invaderShip3->sys->remove(it);
            shipDestroySound3.play();
            break;
        }
    }
    
    for(std::vector<Sprite>::iterator it = invaderShip4->sys->sprites.begin(); it != invaderShip4->sys->sprites.end(); ++it) {
        if(playerShip->sys->removeNear(it->trans, it->height*0.6)){
            showBlastParticle(it->trans, 2);
            invaderShip4->sys->remove(it);
            shipDestroySound4.play();
            score++;
            break;
        }
        if(checkPlayerHit(it->trans)) {
            showBlastParticle(it->trans, 2);
            invaderShip4->sys->remove(it);
            shipDestroySound4.play();
            break;
        }
    }
    
    for(std::vector<Sprite>::iterator it = invaderShip5->sys->sprites.begin(); it != invaderShip5->sys->sprites.end(); ++it) {
        if(playerShip->sys->removeNear(it->trans, it->width)){
            showBlastParticle(it->trans, 3);
            invaderShip5->sys->remove(it);
            shipDestroySound5.play();
            score++;
            break;
        }
        if(checkPlayerHit(it->trans)) {
            showBlastParticle(it->trans, 3);
            invaderShip5->sys->remove(it);
            shipDestroySound5.play();
            break;
        }
    }
    
    for(std::vector<Sprite>::iterator it = invaderShip6->sys->sprites.begin(); it != invaderShip6->sys->sprites.end(); ++it) {
        if(checkPlayerHit(it->trans)) {
            invaderShip6->sys->remove(it);
            shipDestroySound5.play();
            break;
        }
    }
    
    if (playerHealth<=0) {
        gameOver();
    }
}

void ofApp::showBlastParticle(ofVec3f position,int particleNo) {
    switch (particleNo) {
        case 1:
            blastParticle1.setPosition(position);
            blastParticle1.start();
            break;
            
        case 2:
            blastParticle2.setPosition(position);
            blastParticle2.start();
            break;
            
        case 3:
            blastParticle3.setPosition(position);
            blastParticle3.start();
            break;
            
        default:
            break;
    }
}

void ofApp::gameOver() {
    isGameOver = true;
    isGameStarted = false;
    
    playerShip->stop();
    
    invaderShip1->stop();
    invaderShip2->stop();
    invaderShip3->stop();
    invaderShip4->stop();
    invaderShip5->stop();
    invaderShip6->stop();
    
    playerShip->sys->removeAll();
    invaderShip1->sys->removeAll();
    invaderShip2->sys->removeAll();
    invaderShip3->sys->removeAll();
    invaderShip4->sys->removeAll();
    invaderShip5->sys->removeAll();
    invaderShip6->sys->removeAll();
}
bool ofApp::checkPlayerHit(ofVec3f point) {
    ofVec3f dist = playerShip->trans - point;
    if(dist.length() < playerShip->height*0.5) {
        playerHealth--;
        return true;
    }
    return false;
}

void ofApp::movePlayerShip(MoveDir move) {
    if(move) {
        float cX = playerShip->trans.x , cY = playerShip->trans.y , maxMove = 5 , boarderSpace = 30;
        switch (move) {
            case MoveLeft:
                cX -= maxMove;
                break;
            case MoveRight:
                cX += maxMove;
                break;
            case MoveUp:
                cY -= maxMove;
                break;
            case MoveDown:
                cY += maxMove;
                break;
            default:
                break;
        }
        if(cX < boarderSpace)
            cX = boarderSpace;
        else if(cX > ofGetWindowWidth()-boarderSpace)
            cX = ofGetWindowWidth()-boarderSpace;
        
        if(cY < boarderSpace)
            cY = boarderSpace;
        else if(cY > ofGetWindowHeight()-boarderSpace)
            cY = ofGetWindowHeight()-boarderSpace;
        
        playerShip->setPosition(ofVec3f(cX, cY, 0));
    }
}

//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//	cout << "mouse( " << x << "," << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofPoint mouse_cur = ofPoint(x, y);
	ofVec3f delta = playerShip->trans + (mouse_cur - mouse_last);
    
    float cX = delta.x , cY = delta.y , boarderSpace = 30;
    if(cX < boarderSpace)
        cX = boarderSpace;
    else if(cX > ofGetWindowWidth()-boarderSpace)
        cX = ofGetWindowWidth()-boarderSpace;
    
    if(cY < boarderSpace)
        cY = boarderSpace;
    else if(cY > ofGetWindowHeight()-boarderSpace)
        cY = ofGetWindowHeight()-boarderSpace;
    
    playerShip->setPosition(ofVec3f(cX, cY, 0));
	mouse_last = mouse_cur;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouse_last = ofPoint(x, y);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

void ofApp::keyPressed(int key) {
	switch (key) {
        case 'F':
        case 'f':
            ofToggleFullscreen();
            break;
        case 'H':
        case 'h':
            bHide = !bHide;
            break;
        case 'P':
        case 'p':
            if (!isGameStarted) {
                resetGame();
                isGameStarted = true;
                isGameOver = false;
                invaderShip1->start();
                invaderShip2->start();
            }
            break;
        case OF_KEY_LEFT:
            movement = MoveLeft;
            break;
        case OF_KEY_RIGHT:
            movement = MoveRight;
            break;
        case OF_KEY_UP:
            movement = MoveUp;
            break;
        case OF_KEY_DOWN:
            movement = MoveDown;
            break;
        case 32:
            if (!playerShip->started && isGameStarted) {
                playerShip->start();
            }
            break;
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
        case OF_KEY_UP:
        case OF_KEY_DOWN:
            movement = MoveStop;
            break;
        case 32:
            playerShip->stop();
            break;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

