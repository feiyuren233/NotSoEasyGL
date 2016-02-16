/*
 * Animatable.h
 *
 *  Created on: Feb 14, 2016
 *      Author: feiyu
 */

#ifndef ANIMATABLE_H_
#define ANIMATABLE_H_
#include "Animator.h"
class Animator;

class Animatable {
private:
	friend class mWindow;
	static Animator *animator;
	Animatable();
protected:
	
public:
	virtual ~Animatable();

	//virtual void onAnimationFinish();
	//virtual bool isRunning();

};

#endif /* ANIMATABLE_H_ */
