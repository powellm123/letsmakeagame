#pragma once

class SpriteObjects
{
	bool m_active = true;
public:
	virtual ~SpriteObjects() {}
	virtual void Draw() = 0;
	void SetActive(bool active) { m_active = active; }
	bool GetActive() { return m_active; }
};