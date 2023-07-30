#pragma once
#include "Entity.h"
#include <vector>
#include <array>
#include <stack>
#include <iostream>
#include <memory>
#include "Vector2D.h"

struct RecordInfo
{
	RecordInfo(std::string _AnimName, Vector2D _Velocity) : AnimName(_AnimName), Velocity(_Velocity)
	{}

	std::string AnimName;
	Vector2D Velocity;
};

class EntityManager
{
private:
	//엔티티는 고유한 포인터 타입을 가진다
	std::vector<std::unique_ptr<Entity>> entities;
	//엔티티끼리 레이어로 묶여있습니다.
	std::array<std::vector<Entity*>, MAXLAYERGROUP> layerGroupEntities;
	//게임을 되돌리기 위한 데이터입니다.
	std::stack<std::vector<std::pair<Entity*, RecordInfo>>> EntityRecordStack;
	int RecordIndex = 0;
	bool IsRecording = false;
	int RecordCount = 0;

public:
	void update(float deltaTime);
	void render();
	bool HasNoEntities() const;
	void DestroyInactiveEntities();
	void ClearAllEntity();
	std::vector<Entity*> GetEntitiesByLayer(LayerGroup layer) const;
	Entity& addEntity();

	void AddToLayerGroup(Entity* _entity, std::size_t _layerID);
	std::vector<Entity*>& getLayerGroup(std::size_t _layerID);

	void CheckCollisions() const;

	void AddToRecordStack(std::vector<std::pair<Entity*, RecordInfo>>& EntityStacks);
	void UpdateRecordStack();
	void ClearRecordStack();
	void IncreaseRecordIndex();
	void DecreaseRecordIndex();

	int GetRecordCount() { return RecordCount; }
	void DecreaseRecordCount() { --RecordCount; }

	void SetIsRecording(bool InRecording) { IsRecording = InRecording; }
	bool GetIsRecording() { return IsRecording; }
};

