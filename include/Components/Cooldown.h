#ifndef COOLDOWN_H
#define COOLDOWN_H


class Cooldown
{
public:
    Cooldown(float _weaponCooldown);
    virtual ~Cooldown() {};
    float getCooldown();
    void  setCooldown(float _weaponCooldown);
    float getCurrentCooldown();
    void  reduceCooldown();
protected:
    float weaponCooldown;
    float currentCooldown;
private:
};

extern float frameTime;
#endif // COOLDOWN_H
