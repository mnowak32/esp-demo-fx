#ifndef Effect_h
#define Effect_h

class Effect {
  public:
    virtual void nextFrame();
    virtual uint16_t delayLength();
};

#endif
