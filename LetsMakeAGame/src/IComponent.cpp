#include "IComponent.h"

std::string IComponent::GetName()
{
	return m_name;
}

size_t IComponent::GetType()
{
	return m_type;
}
