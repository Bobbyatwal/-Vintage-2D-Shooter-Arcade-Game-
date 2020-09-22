


#include "ofMain.h"
#include "Emitter.h"



//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 3000;    // milliseconds
	started = false;

	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	velocity = ofVec3f(0, 0, 0);
    childVelocity = ofVec3f(0, -100, 0);
	drawable = true;
	width = 50;
	height = 50;
	childWidth = 10;
	childHeight = 10;
    childScale = 1.0;
    applyAngle = false;
    haveEmitSound = false;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void Emitter::draw() {
    sys->draw();
    
	if (drawable) {
		if (haveImage) {
            ofSetColor(255, 255, 255 ,255);
            ofPushMatrix();
            ofTranslate(trans.x, trans.y);
            if(applyAngle){
                ofRotateDeg(angle);
            }
            image.setAnchorPoint(0.5, 0.5);
            image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
            ofPopMatrix();
		}
		else {
			ofSetColor(0, 0, 255);
			ofDrawRectangle(-width / 2 + trans.x, -height / 2 + trans.y, width, height);
		}
	}

	// draw sprite system
	//
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
    sys->update();

	if (!started) return;
    
    trans += velocity / ofGetFrameRate();

	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawned) > (1000.0 / rate)) {
		// spawn a new sprite
        if(haveEmitSound) emitSound.play();
		Sprite sprite;
		if (haveChildImage) sprite.setImage(childImage);
		sprite.velocity = childVelocity;
		sprite.lifespan = lifespan;
		sprite.setPosition(trans);
		sprite.birthtime = time;
		sprite.width = childWidth * childScale;
		sprite.height = childHeight * childScale;
        sprite.angle = angle;
		sys->add(sprite);
		lastSpawned = time;
	}
}

// Start/Stop the emitter.
//
void Emitter::start() {
	started = true;
    lastSpawned = 0;
}

void Emitter::stop() {
	started = false;
    lastSpawned = 0;
}


void Emitter::setLifespan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(ofVec3f v) {
	velocity = v;
}

void Emitter::setChildVelocity(ofVec3f v) {
    childVelocity = v;
    angle = -(atan2 (childVelocity.x, childVelocity.y) * (180 / PI));
}

void Emitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
	childWidth = img.getWidth();
	childHeight = img.getHeight();
    childImage.resize(childWidth * childScale, childHeight * childScale);
}

void Emitter::setChildScale(float scale) {
    childScale = scale;
    if(haveChildImage) {
        childImage.resize(childWidth * childScale, childHeight * childScale);
    }
}

void Emitter::setImage(ofImage img) {
	image = img;
    haveImage = true;
}

void Emitter::setEmitSound(ofSoundPlayer sound) {
    emitSound = sound;
    haveEmitSound = true;
}

void Emitter::setRate(float r) {
	rate = r;
}

float Emitter::maxDistPerFrame() {
	return  velocity.length() / ofGetFrameRate();
}

void Emitter::setDrawable(bool isDrawable) {
    drawable = isDrawable;
}
