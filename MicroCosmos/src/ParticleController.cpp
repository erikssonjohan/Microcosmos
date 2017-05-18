#include "ParticleController.h"

using namespace po::scene;

ParticleControllerRef ParticleController::create() {
	ParticleControllerRef node(new ParticleController());
	node->setup();
	return node;
}

ParticleController::ParticleController()
{
}


ParticleController::~ParticleController()
{
}

void ParticleController::setup()
{
	// Randomize the Perlin noise function.
	mPerlin.setSeed(clock());

	// Create particles.
	mParticles.reserve(NUM_PARTICLES);
	for (int s = 0; s < NUM_PARTICLES; ++s)
		mParticles.push_back(Particle(ci::vec2(ci::Rand::randFloat(ci::app::getWindowWidth()), ci::Rand::randFloat(ci::app::getWindowHeight()))));

	mConservationOfVelocity = 0.9f;
	mSpeed = 5.0f;
	mAnimationCounter = 0.0f;
}

void ParticleController::update()
{
	// Move ahead in time, which becomes the z-axis of our 3D noise.
	mAnimationCounter += 10.0f;

	for (auto &particle :  mParticles) {
		// Save off the last position for drawing lines.
		particle.mLastPosition = particle.mPosition;

		// Add some perlin noise to the velocity.
		ci::vec3 deriv = mPerlin.dfBm(ci::vec3(particle.mPosition.x, particle.mPosition.y, mAnimationCounter) * 0.001f);
		particle.mZ = deriv.z;
		ci::vec2 deriv2 = normalize(ci::vec2(deriv.x, deriv.y));
		particle.mVelocity += deriv2 * mSpeed;

		// Move the particles according to their velocities.
		particle.mPosition += particle.mVelocity;

		// Dampen the velocities for the next frame.
		particle.mVelocity *= mConservationOfVelocity;

		// Replace any particles that have gone offscreen with a random onscreen position.
		if (isOffscreen(particle.mPosition))
			particle.reset(ci::vec2(ci::Rand::randFloat(ci::app::getWindowWidth()), ci::Rand::randFloat(ci::app::getWindowHeight())));
	}
}

void ParticleController::draw()
{

	// Enable additive blending.
	ci::gl::ScopedBlendAdditive blend;

	// Draw all the particles as lines from mPosition to mLastPosition.
	// We use the convenience methods begin(), color(), vertex() and end() for simplicity,
	// see the ParticleSphere* samples for a faster method.
	ci::gl::begin(GL_LINES);
	for (auto &particle : mParticles) {
		// Color according to velocity.
		ci::gl::color(0.5f + particle.mVelocity.x / (mSpeed * 2), 0.5f + particle.mVelocity.y / (mSpeed * 2), 0.5f + particle.mZ * 0.5f);
		ci::gl::vertex(particle.mLastPosition);
		ci::gl::vertex(particle.mPosition);
	}
	ci::gl::end();
}

// Returns \c true if a given point is visible onscreen.
bool ParticleController::isOffscreen(const ci::vec2 &v)
{
	return ((v.x < 0) || (v.x > ci::app::getWindowWidth()) || (v.y < 0) || (v.y > ci::app::getWindowHeight()));
}