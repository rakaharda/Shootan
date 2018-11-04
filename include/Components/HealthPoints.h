#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H


class HealthPoints
{
public:
    HealthPoints();
    HealthPoints(float _healthPoints);
    virtual ~HealthPoints();
    float getHealthPoints();
    float getCurrentHealthPoints();
    void setCurrentHealthPoints(float _hp);
    void  takeDamage(float _damage);
protected:
    float healthPoints;
    float currentHealthPoints;
private:
};

#endif // HEALTHPOINTS_H
