#ifndef OBJECTPROPERTIES_H
#define OBJECTPROPERTIES_H
struct ObjectProperties
{
    bool isActive;
    ObjectProperties(bool _isActive = true)
    {
        isActive = _isActive;
    }
};
#endif
