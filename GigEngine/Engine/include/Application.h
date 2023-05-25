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
	static void ShowUI();
	static void UseEditorCam();
	static bool IsInEditor();
	static bool IsInPause();
	static bool IsUsingEditorCam();
	static bool IsShowUI();

	void Run();
	void SwapFrames();

private:

	GameObject* sk;
	static inline Window window;
	static inline EditorCamera editorCamera;

	static inline lm::FMat4 viewProj;
	static inline lm::FVec3 viewPos;

	static inline bool isEditor = true;
	static inline bool isPause = false;
	static inline bool useEditorCam = false;

	static inline bool showUI = true;

	//main shader
	static inline ShaderProgram mainShader;
	int viewProjLocation;
	int ModelLocation;
	int viewPosLocation;
	int nbLightLocation;

	void Init();
	void InitMainShader();
	void Draw();
	void ClearWindow();
	void UpdateGameObjectComponent();
	void UpdateGameObjectRender() const;
	void UpdateLights() const;
	void UpdateUniforms() const;

	static void StartGame();
};
