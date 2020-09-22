#pragma once
//----------------------------------------------------------------------------------
//
// Basic Sprite Emitter Class
//
//
//  Kevin M. Smith - CS 134 SJSU

#include "Sprite.h"


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter : public BaseObject {
public:
	Emitter(SpriteSystem *);
	void draw();
	void start();
	void stop();
	void setLifespan(float);
	void setVelocity(ofVec3f);
    void setChildVelocity(ofVec3f);
	void setChildImage(ofImage);
	void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
    void setChildScale(float scale);
	void setImage(ofImage);
    void setEmitSound(ofSoundPlayer);
    void enableApplyAngle(bool isEnable) { applyAngle = isEnable; } ;
	void setRate(float);
    void setDrawable(bool isDrawable);
	float maxDistPerFrame();
	void update();
    
	SpriteSystem *sys;
	float rate;
	ofVec3f velocity;
    ofVec3f childVelocity;
    float angle;
	float lifespan;
	bool started;
    bool applyAngle;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	float width, height;
	float childWidth, childHeight , childScale;
    ofSoundPlayer emitSound;
    bool haveEmitSound;
};
