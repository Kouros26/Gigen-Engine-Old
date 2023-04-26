#pragma once
#include "Shader.h"
#include "Transform.h"
#include <vector>

class Line
{
public:
	Line() = default;
	Line(const lm::FVec3 start, const lm::FVec3 end, const lm::FVec3 color, float timer);
	~Line();

	[[nodiscard]] unsigned int GetVAO() const;
	float* GetColor();
	float timer = 0;

private:
	float vertices[6]{};
	float color[3]{};

	unsigned int VAO = 0;
	unsigned int  VBO = 0;
};

class Lines
{
public:
	static void Init();
	static void DrawLine(const lm::FVec3& start, const lm::FVec3& end, const lm::FVec3& color = lm::FVec3(1, 0, 0), float timer = 5.0f);
	static void DrawLines();
	static void Clear();
private:
	static void DrawDebugLines();
	static void DrawGuizmoLines();
	static void CreateGuizmo(Transform* t);
	static void CreateTranslatedEditorTransform();

	static inline Transform worldTransform;

	static inline ShaderProgram shaderProgram;
	static inline std::vector<Line*> debugLines;
	static inline std::vector<Line*> guizmoLines;

	static inline unsigned int MVPLocation;
	static inline unsigned int colorLocation;
};
