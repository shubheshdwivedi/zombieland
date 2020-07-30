#include "include/GameConstants.h"
#include <assert.h>

Constants* Constants::instance = nullptr;
Constants::Constants() {
	assert(instance == nullptr);
	instance = this;
}