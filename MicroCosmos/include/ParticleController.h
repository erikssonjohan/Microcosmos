#pragma once

#include <stdio.h>
#include "poNodeContainer.h"
#include "cinder/Xml.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/Perlin.h"
#include "cinder/Color.h"

#include <vector>

class ParticleController;
typedef std::shared_ptr<ParticleController> ParticleControllerRef;

class Particle {
public:
	Particle(const ci::vec2 &position)
		: mPosition(position), mLastPosition(position), mVelocity(ci::vec2(0)), mZ(0) {}

	void reset(const ci::vec2 &position)
	{
		mPosition = mLastPosition = position;
		mVelocity = ci::vec2(0);
		mZ = 0;
	}

	ci::vec2 mPosition, mVelocity, mLastPosition;
	float mZ;
};

class ParticleController
	:public po::scene::NodeContainer
{
public:
	static ParticleControllerRef create();
	ParticleController();
	~ParticleController();
	void setup();
	void update();
	void draw();

	bool isOffscreen(const ci::vec2 &v);

public:
	static const int kNum_particles = 1e3;

	float conservation_of_velocity_;
	float speed_;
	float animation_counter_;

	ci::Perlin perlin_;
	std::vector<Particle> particles_;
};


