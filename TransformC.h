#pragma once
class TransformC : public Component
{
public :
	TransformC(Object* object);
	~TransformC();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	Vector2 m_position;
};
