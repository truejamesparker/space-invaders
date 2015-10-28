#include "alienBlockSM.h"

// independent march and clean kill SM periods
volatile static uint32_t marchSMPeriods = 0;
volatile static uint32_t cleanSMPeriods = 0;


// how fast aliens are currently marching
volatile static uint32_t marchSpeed = ALIEN_BLOCK_MARCH_SLOW;

// Is this SM locked?
volatile bool locked = false;

void updateMarchingSpeed(uint32_t livingCount);

// ----------------------------------------------------------------------------

void alienBlockSM_tick() {
	// bail if this SM is locked
	if (locked) return;

	// It's been another SM Period
	marchSMPeriods++;
	cleanSMPeriods++;

	if (marchSMPeriods >= marchSpeed) {
		// march the aliens
		aliens_march();

		audio_play_alien_track();

		// get how many aliens are currently living
		uint32_t firingCount = aliens_getFiringCount();

		// if necessary update speed
		updateMarchingSpeed(firingCount);

		if (firingCount) { // if there are aliens living

			// Decide when to fire missiles
			uint16_t r = (rand()%(100))+1; // (rand()%(max-min+1))+min;

			// fancy probability CDF thing
			if (r <= ALIEN_BLOCK_MISSILE_PROBABILITY) {
				// Get the lowest living aliens
				uint16_t Xs[ALIEN_COL_COUNT];
				uint16_t Ys[ALIEN_COL_COUNT];
				aliens_getLowestAliens(Xs, Ys);

				// So, if the living number of aliens is less than MISSILE_ALIEN_COUNT, lets
				// use livingCount as our ceiling. If we don't, one alien would have an
				// unfair advantage against our mere 1 bullet on the screen at a time.
				uint16_t maxMissilesOnScreen = MISSILE_ALIEN_COUNT;
				if (firingCount < MISSILE_ALIEN_COUNT) maxMissilesOnScreen = firingCount;

				// figure out the max num of missiles even available to me to fire
				uint16_t maxMissilesFireable = maxMissilesOnScreen - missiles_getActiveAlienMissiles();

				// min between the two because we want the least amount of missiles
				// on the screen at once as possible. Whenever maxMissilesOnScreen
				// changes from the #define into the livingCount, it is possible a
				// negative number could occur
				maxMissilesFireable = MIN(firingCount, maxMissilesFireable);

				// get a random number of missiles in that range to fire
				uint16_t missilesLeftToFire = (rand()%(maxMissilesFireable+1));

				// this array will make sure that the same alien doesn't fire two
				// missiles on top of each other, which is imperceptible except
				// for the fact that a single missile could issue double bunker damage.
				bool alreadyFired[ALIEN_COL_COUNT] = { false };

				// The loop makes sure some alien will fire
				while(missilesLeftToFire) {
					// pick a random lowest living alien
					uint16_t x = (rand()%ALIEN_COL_COUNT);

					if (alreadyFired[x]) continue;

					// fire!
					bool fired = missiles_alienFire(Xs[x], Ys[x]);

					if (fired) {
						alreadyFired[x] = true;
						missilesLeftToFire--;
					}
				}
			}

		}

		// reset the period timer
		marchSMPeriods = 0;
	}

	if (cleanSMPeriods == ALIEN_BLOCK_KILL_REFRESH) {
		aliens_cleanupKills();

		// reset the period timer
		cleanSMPeriods = 0;
	}
}

// ----------------------------------------------------------------------------

void alienBlockSM_marchSlow() {
	marchSpeed = ALIEN_BLOCK_MARCH_SLOW;
}

// ----------------------------------------------------------------------------

void alienBlockSM_marchMedium() {
	marchSpeed = ALIEN_BLOCK_MARCH_MED;
}

// ----------------------------------------------------------------------------

void alienBlockSM_marchFast() {
	marchSpeed = ALIEN_BLOCK_MARCH_FAST;
}

// ----------------------------------------------------------------------------

void alienBlockSM_marchVeryFast() {
	marchSpeed = ALIEN_BLOCK_MARCH_VERY_FAST;
}

// ----------------------------------------------------------------------------

void alienBlockSM_lock() {
	locked = true;
}

// ----------------------------------------------------------------------------

void alienBlockSM_unlock() {
	locked = false;
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

void updateMarchingSpeed(uint32_t livingCount) {
	// Speeds based on how many are alive
	if (livingCount >= ALIEN_BLOCK_SLOW_MIN_COUNT) {
		marchSpeed = ALIEN_BLOCK_MARCH_SLOW;
	} else if (livingCount >= ALIEN_BLOCK_MED_MIN_COUNT) {
		marchSpeed = ALIEN_BLOCK_MARCH_MED;
	} else if (livingCount >= ALIEN_BLOCK_FAST_MIN_COUNT) {
		marchSpeed = ALIEN_BLOCK_MARCH_FAST;
	} else if (livingCount >= ALIEN_BLOCK_VERY_FAST_MIN_COUNT) {
		marchSpeed = ALIEN_BLOCK_MARCH_VERY_FAST;
	}
}
