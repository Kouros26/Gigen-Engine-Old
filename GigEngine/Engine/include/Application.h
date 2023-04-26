#pragma once
#include "Shader.h"
#include "EditorCamera.h"
#include "Window.h"

class Application
{
public:
	Application();
	~Application();

	static Window& GetWindow();
	static EditorCamera& GetEditorCamera();
	static ShaderProgram& GetMainShader();

	static lm::FMat4& GetViewProj();
	static lm::FVec3& GetViewPos();

	static void Play();
	static void Pause();
	static void Stop();
	static void UseEditorCam();
	static bool IsInEditor();
	static bool IsInPause();
	static bool IsUsingEditorCam();

	void Run();
	void SwapFrames();

private:
	class Skybox* skybox;

	static inline Window window;
	static inline EditorCamera editorCamera;

	static inline lm::FMat4 viewProj;
	static inline lm::FVec3 viewPos;

	static inline bool isEditor = true;
	static inline bool isPause = false;
	static inline bool useEditorCam = false;

	//main shader
	static inline ShaderProgram mainShader;
	int viewProjLocation;
	int ModelLocation;
	int viewPosLocation;
	int nbDirLightLocation;
	int nbPointLightLocation;
	int nbSpotLightLocation;

	void Init();
	void CreateGameObjects();
	void InitMainShader();
	void Draw();
	void ClearWindow();
	void UpdateGameObjectComponent();
	void UpdateGameObjectRender();
	void UpdateLights();
	void UpdateUniforms();

	static void StartGame();
};
