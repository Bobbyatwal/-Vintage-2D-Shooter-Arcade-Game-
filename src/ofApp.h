mn#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "Particle.h"
#include "ParticleEmitter.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;



class Emitter;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw(); 
        void checkCollisions();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void movePlayerShip(MoveDir move);
        bool checkPlayerHit(ofVec3f point);
        void resetGame();
        void gameOver();
        void showBlastParticle(ofVec3f position,int particleNo);
    
        MoveDir movement;
    
        bool isGameStarted;
        bool isGameOver;
    
        bool isSpacePressed;
    
        ParticleEmitter blastParticle1;
        ParticleEmitter blastParticle2;
        ParticleEmitter blastParticle3;
		
		Emitter *playerShip;
    
        Emitter *invaderShip1;
        Emitter *invaderShip2;
        Emitter *invaderShip3;
        Emitter *invaderShip4;
        Emitter *invaderShip5;
    
        Emitter *invaderShip6;
    
        ofSoundPlayer shipDestroySound1;
        ofSoundPlayer shipDestroySound2;
        ofSoundPlayer shipDestroySound3;
        ofSoundPlayer shipDestroySound4;
        ofSoundPlayer shipDestroySound5;
    
        ofTrueTypeFont textIntruction;
        ofTrueTypeFont textScore;
    
        int playerHealth;
    
        int score;

        ofImage turretImage;
        ofImage missileImage;
    
        ofSoundPlayer  missileFireSound;
        ofSoundPlayer  bgMusic;

		ofVec3f mouse_last;

		bool bHide;

		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;

		ofxPanel gui;
};
