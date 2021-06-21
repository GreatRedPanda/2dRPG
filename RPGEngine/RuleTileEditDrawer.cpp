#include "stdafx.h"
#include "RuleTileEditDrawer.h"




RuleTileEditDrawer::~RuleTileEditDrawer()
{
}

void RuleTileEditDrawer::render(RenderTarget * target)
{

	//if (selectedRuleTile != nullptr)
	{
	//	size_t n1 = 0;
	/*	for (auto n= this->selectedRuleTile->rules.begin(); n!=
			this->selectedRuleTile->rules.end(); n++)
*/
	

		for (auto rec : *rects)
		{
			for (auto r : rec)
			{
				r.render(target);
			//	target->draw(r);
			}
		}
	}
}
