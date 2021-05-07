#include "camera.h"

void Camera::Update(float deltaTime){
	const float MOVEMENT_SPEED = 5.0f * deltaTime;	//hard-coded constants. might move them somewhere else...
	const float ROTATION_SPEED = 1.0f * deltaTime;

	if(util::KEYS[SDL_SCANCODE_W]){					//check for input and update location accordingly
		position.X -= forwards.X * MOVEMENT_SPEED;
		position.Y -= forwards.Y * MOVEMENT_SPEED;
		position.Z += forwards.Z * MOVEMENT_SPEED;	//NOTE: Z-component has to be inversed
	}

	if(util::KEYS[SDL_SCANCODE_S]){
		position.X += forwards.X * MOVEMENT_SPEED;
		position.Y += forwards.Y * MOVEMENT_SPEED;
		position.Z -= forwards.Z * MOVEMENT_SPEED;
	}

	if(util::KEYS[SDL_SCANCODE_A]){
		position.X += right.X * MOVEMENT_SPEED;
		position.Y += right.Y * MOVEMENT_SPEED;
		position.Z -= right.Z * MOVEMENT_SPEED;
	}

	if(util::KEYS[SDL_SCANCODE_D]){
		position.X -= right.X * MOVEMENT_SPEED;
		position.Y -= right.Y * MOVEMENT_SPEED;
		position.Z += right.Z * MOVEMENT_SPEED;
	}

	if(util::KEYS[SDL_SCANCODE_SPACE]){
		position.X -= up.X * MOVEMENT_SPEED;
		position.Y -= up.Y * MOVEMENT_SPEED;
		position.Z += up.Z * MOVEMENT_SPEED;
	}

	if(util::KEYS[SDL_SCANCODE_LSHIFT]){
		position.X += up.X * MOVEMENT_SPEED;
		position.Y += up.Y * MOVEMENT_SPEED;
		position.Z -= up.Z * MOVEMENT_SPEED;
	}

	if(util::KEYS[SDL_SCANCODE_LEFT])
		rotation.Y -= ROTATION_SPEED;

	if(util::KEYS[SDL_SCANCODE_RIGHT])
		rotation.Y += ROTATION_SPEED;

	if(util::KEYS[SDL_SCANCODE_UP])
		rotation.X += ROTATION_SPEED;

	if(util::KEYS[SDL_SCANCODE_DOWN])
		rotation.X -= ROTATION_SPEED;

	viewProjection = viewProjection.Perspective(80.0f, display.getAspectRatio(), 0.1f, 1000.0f);	//update projection matrix in case window size has changed

	Matrix xRot = Matrix().Rotation(Vec3(rotation.X, 0.0f, 0.0f));		//Matrices to transform camera orientation vectors
	Matrix yRot = Matrix().Rotation(Vec3(0.0f, rotation.Y, 0.0f));

	forwards = yRot.Transform(xRot.Transform(Vec3(0.0f, 0.0f, 1.0f)));	//X right, Y up, Z forward
	up = yRot.Transform(xRot.Transform(Vec3(0.0f, 1.0f, 0.0f)));
	right = yRot.Transform(xRot.Transform(Vec3(1.0f, 0.0f, 0.0f)));
}

Matrix Camera::getViewProjection() const{
	return viewProjection * Matrix().Rotation(rotation) * Matrix().Translation(position);
}