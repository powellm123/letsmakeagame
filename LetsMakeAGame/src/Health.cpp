#include "Entity.h"
#include "Health.h"


HealthComponent::HealthComponent(Entity * actor, int health) : IComponent(actor, "health", type), Health(health), MaxHealth(health)
{
}

void HealthComponent::Damage(int amount)
{
	if (invincibleTimer > 0.00000001)
		return;

	Health -= amount;
	invincibleTimer = 1;
}

bool HealthComponent::IsInvincible()
{
	return invincibleTimer > 0;
}

int HealthComponent::GetLifePoints()
{
	return Health;
}

void HealthComponent::Update()
{
	if (Health <= 0 && m_status == HealthStatus::Alive)
	{
		m_actor->SetIsDying(true);
		m_status = HealthStatus::Dead;
	}
	if(invincibleTimer > 0)
		invincibleTimer -= TimeController::instance.DeltaTime;
}

void HealthComponent::Draw()
{
}
