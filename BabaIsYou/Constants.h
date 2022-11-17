#pragma once

const int WINDOW_WIDTH = 854;
const int WINDOW_HEIGHT = 480;

constexpr size_t MAXCOMPONENTS = 256;
constexpr size_t MAXLAYERGROUP = 32;
//const unsigned long long COMPONENT_SIZE = 256;
//const unsigned long long LAYER_SIZE = 32;

const int WIDTH_INTERVAL = 31;
const int HEIGHT_INVERVAL = 24;

const int PIXEL_SIZE = 24;
const int LARGE_PIXEL_SIZE = 32;

enum LayerGroup : size_t
{
	LayerMap,
	LayerTile,
	LayerWall,
	LayerRock,
	LayerFlag,
	LayerWater,
	LayerSkul,
	LayerLava,
	LayerGrass,
	LayerHeadText,
	LayerVerbText,
	LayerTailText,
	LayerMenu,
	LayerBaba,
	LayerCollider,
	LayerEnd
};

inline const char* ToString(LayerGroup group)
{
	switch (group)
	{
	case LayerMap: return "Map";
	case LayerWall:return "Wall";
	case LayerRock:return "Rock";
	case LayerTile:return "Tile";
	case LayerFlag:return "Flag";
	case LayerWater:return "Water";
	case LayerSkul:return "Skul";
	case LayerLava:return "Lava";
	case LayerGrass:return "Grass";
	case LayerHeadText:return "HeadText";
	case LayerVerbText:return "VerbText";
	case LayerTailText:return "TailText";
	case LayerMenu:return "Menu";
	case LayerBaba:return "Baba";
	case LayerCollider:return "Collider";
	}

	return "End";
}

enum TextType : size_t
{
	You, Stop, Push,
	Win, Death, Shut, Open, Hot, Melt, Sink,
	Move,
	Default
};

enum class CollisionType
{
	Block, Overlap, Ignore
};

enum class CollisionState
{
	BeginOverlap, Overlapping, EndOverlap, NotOverlapping
};

enum Direction
{
	UP, DOWN, LEFT, RIGHT, DIREND
};