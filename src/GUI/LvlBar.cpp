#include "GUI/GUI/LvlBar.h

LvlBar::LvlBar()
{
    frame.setTexture(resources->getTexture("healthbar_frame"));
    healthCells.setTexture(resources->getTexture("healthbar_cells"));
}

LvlBar::~LvlBar()
{
    //
}
