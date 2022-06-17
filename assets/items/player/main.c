#include <raylib.h>
#include <math.h>

int main(void)
{
	int screenWidth = 800;
	int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "3D TEST");
	SetTargetFPS(60);

	/* CAMERA VARS */
	Camera3D camera = (Camera3D){(Vector3){-5, 8, -5}, (Vector3){0, 2, 0}, (Vector3){0, 2, 0}, 45, CAMERA_PERSPECTIVE};

	float cam_radius = 15;
	float cam_angle = 1.57;
	/**/

	// Load model mesh

	Model model_test = LoadModel("model.iqm");


	// Load model texture

	Texture2D texture = LoadTexture("txr_model.png");
	SetMaterialTexture(&model_test.materials[0], MATERIAL_MAP_DIFFUSE, texture);


	// Load model animation

	unsigned int animsCount = 1;
	ModelAnimation *anims = LoadModelAnimations("model.iqm", &animsCount);
	int animFrameCounter = 0;



	SetCameraMode(camera, CAMERA_CUSTOM);

	//--------------------------------------------------------------------------------------
	while (!WindowShouldClose())
	{
		/* ROTATE CAMERA */
		if (IsKeyDown('Q')) cam_angle+=0.02;
		if (IsKeyDown('E')) cam_angle-=0.02;
		camera.position.x = cam_radius * cos(cam_angle);
		camera.position.z = cam_radius * sin(cam_angle);

		/* UPDATE ANIMATION */


		if (IsKeyDown(KEY_SPACE))
		{
			UpdateModelAnimation(model_test, anims[0], animFrameCounter);
			animFrameCounter++;
			if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;
		}



		BeginDrawing();

			ClearBackground(BLACK);

			BeginMode3D(camera);

				DrawModel(model_test, (Vector3){0, 1, 0}, 1, WHITE);

				DrawGrid(15, 1.0);

			EndMode3D();

			DrawFPS(10, 10);

		EndDrawing();
	}

	// FREE MEMORY !! (important)


	for (unsigned int i = 0; i < animsCount; i++) UnloadModelAnimation(anims[i]);
	RL_FREE(anims);

	UnloadTexture(texture);

	UnloadModel(model_test);


	CloseWindow();
	return 0;
}
