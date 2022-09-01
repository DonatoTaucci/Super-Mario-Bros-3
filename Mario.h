#pragma once

#include "Entity.h"
#include <QPainter>


class Mario : public Entity
{
	protected:

		// textures
		QPixmap texture_stand[4];			//small/big/raccoon/tanooki stand texture
		QPixmap texture_walking[4][4];		//small/big/raccoon/tanooki walking animations
		QPixmap texture_jumping[4];			//small/big/raccoon/tanooki jumping texture
		QPixmap texture_falling[4];			//small/big/raccoon/tanooki falling texture
		QPixmap texture_brake[4];			//small/big/raccoon/tanooki brake texture
		QPixmap texture_kick[4];			//small/big kick texture
		QPixmap texture_crouch[3];			//big crouch texture
		QPixmap texture_run[4][4];			//small/big run texture
		QPixmap texture_jump_run[4];		//small/big jumping while running texture
		QPixmap texture_fall_run[4];		//small/big falling while running texture
		QPixmap texture_small2big[12];		//transformation texture from small to big
		QPixmap texture_big2small[12];		//transformation texture from big to small
		QPixmap texture_big2raccoon[5];		//transformation texture from big to raccoon
		QPixmap texture_raccoon2big[5];		//transformation texture from raccoon to big
		QPixmap texture_pipe[4];			//mario enters/exits the pipe
		QPixmap texture_pick_koopa[4][4];	//mario is holding the koopa
		QPixmap texture_big2tanooki[5];		//transformation texture from big to tanooki
		QPixmap texture_tanooki2big[5];		//transformation texture from tanooki to big
		QPixmap texture_cloud[4];
		QPixmap texture_inv_walk[2][7];		//invulnerable and walking texture (small/big only)
		QPixmap texture_inv_stand[2][2];	//invulnerable and standing texture (small/big only)
		QPixmap texture_inv_jumping[2][2];	//invulnerable and jumping texture (small/big only)
		QPixmap texture_inv_falling[2][2];	//invulnerable and falling texture (small/big only)
		QPixmap texture_spin[2][4];			//spinning texture (raccoon/tanooki only)
		QPixmap texture_gliding[2][2];		//gliding texture (raccoon/tanooki only)
		QPixmap texture_flying[2][3];		//flying texture (raccoon/tanooki only)
		QPixmap texture_statue[2];			//statue texture (tanooki only)
		QPixmap texture_death;				//death texture

		Direction prev_dir;

		// flags
		bool running;						// is Mario running?
		bool big;							// is Mario big?
		bool crouch;						// is Mario crouched?
		bool raccoon;
		bool tanooki;
		bool spinning;
		bool gliding;
		bool flying;
		bool statue;
		bool pick_koopa;
		bool change_scene;					//mario enters/exits the pipe
		bool become_big;					//true if mario was raccoon or tanooki and
											//takes damage; false if mario was small and
											//become big
		bool upDown;						//moves mario up or down while 
											//he is entering/exiting the pipe
		bool pipe_check;					//a	control variable use to avoid a
											//potential softlock during change scene

		// counters
		int moving_start_counter;			// counts the number of frames since moving started
		int moving_stop_counter;			// counts the number of frames since moving stopped
		int dir_change_counter;				// counts the number of frames since direction changed
		int transformation_counter;
		int inv_counter;
		int kick_counter;
		int spinning_counter;
		int flying_counter;
		int running_counter;
		int statue_counter;
		int pipe_counter;

		//other class variables
		int moving_div;
		int life;
		int texture_index;					//0 = small ; 1 = big
											//2 = raccoon; 3 = tanooki

	public:

		Mario(QPoint position, bool _big = false, bool _raccoon = false, bool _tanooki = false);

		virtual std::string name() { return "Mario"; }

		static Mario* instance();

		virtual void animate();
		virtual void hit(Object* what, Direction fromDir);
		virtual void advance();
		virtual void solveCollisions();
		virtual void setMoving(bool _moving);
		virtual void setDirection(Direction _dir);
		virtual void die();

		//defining hitboxes
		QPainterPath shape() const;

		//setters
		void setRunning(bool _running);
		void setJumpingDuration(int _jumping_duration) { jumping_duration = _jumping_duration; }
		void setGliding(bool _gliding) { gliding = _gliding; }
		void setChange_scene(bool _change_scene) { change_scene = _change_scene; }
		void setFlying(bool _flying) { flying = _flying; }
		void setStatue(bool _statue) { statue = _statue; }
		void setStatueCounter(int _statue_counter) { statue_counter = _statue_counter; }
		void setKickCounter(int _kick_counter) { kick_counter = _kick_counter; }
		void setUpDown(bool _upDown) { upDown = _upDown; }
		void setPipeCheck(bool _pipe_check) { pipe_check = _pipe_check; }
		void setPipeCounter(int _pipe_counter) { pipe_counter = _pipe_counter; }
		void setSpinning(bool _spinning) { spinning = _spinning; }

		//getters
		Direction getDir() { return dir; }
		bool isBig() { return big; }
		bool isJumping() { return jumping; }
		bool isFalling() { return falling; }
		bool isTanooki() { return tanooki; }
		bool isRaccoon() { return raccoon; }
		bool isSpinning() { return spinning; }
		bool getCrouch() { return crouch; }
		bool getChange_scene() { return change_scene; }
		bool isFlying() { return flying; }
		bool isRunning() { return running; }
		bool isStatue() { return statue; }
		bool getPickKoopa() { return pick_koopa; }
		bool isDying() { return dying; }
		int getRunningCounter() { return running_counter; }
		int getPipeCounter() { return pipe_counter; }
		int getInvCounter() { return inv_counter; }
	

		//other functions
		void jump();
		void bounce();
		void setCrouch(bool active);
		void powerUp();
		void powerUpLeaf();
		void powerUpTanooki();
		void MarioHurt();
		void back2small();
		void back2big();

};
