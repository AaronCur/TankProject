#pragma once

#include "entityx/Entity.h"

enum class PathType
{
	WT_Small,
};

struct Path : public entityx::Component<Path>
{
	Path(PathType type = PathType::WT_Small);

	PathType m_type;
};

