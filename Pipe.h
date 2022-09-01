#pragma once

#include "Inert.h"
#include "Mario.h"

class Pipe : public Inert
{
protected:

	Mario* mario_p;

	bool entry;					//if true mario can enter the pipe
	bool upsidedown;
	bool hitted;				//used if upsideodwn and entry are both true
	bool in_the_pipe;
	bool gray;					//the pipe can have a different color

	int posX;

public:

	Pipe(QPoint position, int height = 1, bool upsidedown = false, bool _entry = false, bool _gray = false);

	virtual std::string name() { return "Pipe"; }

	virtual void hit(Object* what, Direction fromDir);
	virtual void advance();
};