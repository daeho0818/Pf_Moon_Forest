#pragma once
class BoxColliderC : Component
{
public:
	BoxColliderC(Object* object);
	~BoxColliderC();

	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	// Collider ũ�� ����
	void SetCollider(float width, float height);
	// (������ ����) ȭ�鿡 Collider�� ������
	void ShowCollider(bool active);

private:
	Image* rect_image;

	float m_width;
	float m_height;
	bool show_collider;
};